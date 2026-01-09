#include <grpcpp/grpcpp.h>
#include <moodycamel/concurrentqueue.h>

#include <atomic>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "talos_service.h"

int main(int argc, char **argv)
{
    const std::string listen_address = (argc > 1) ? argv[1] : "0.0.0.0:50051";

    // Create a concurrent queue for task management
    auto task_queue = std::make_shared<moodycamel::ConcurrentQueue<talos::icd::server::Task>>();

    // Start background thread to process tasks from the queue
    std::atomic<bool> running{true};
    std::thread task_processor([task_queue, &running]()
                               {
        talos::icd::server::Task task;
        while (running.load()) {
            // Try to dequeue a task with a timeout
            if (task_queue->try_dequeue(task)) {
                if (task.work) {
                    ABSL_LOG(INFO) << "Processing task: " << task.name;
                    task.work();
                    ABSL_LOG(INFO) << "Task completed: " << task.name;
                    
                    // Signal completion to any waiter
                    if (task.completion) {
                        task.completion->set_value();
                    }
                }
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        } });

    talos::icd::server::TalosOperatorService service(task_queue);

    grpc::ServerBuilder builder;
    builder.AddListeningPort(listen_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server = builder.BuildAndStart();
    if (!server)
    {
        std::cerr << "Failed to start TalosOperator server on " << listen_address << std::endl;
        running.store(false);
        task_processor.join();
        return 1;
    }

    std::cout << "TalosOperator server listening on " << listen_address << std::endl;
    std::cout << "Task processor thread running for sequential task execution" << std::endl;

    server->Wait();

    // Cleanup
    running.store(false);
    task_processor.join();

    return 0;
}