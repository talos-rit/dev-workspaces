#include "talos_service.h"

#include <moodycamel/concurrentqueue.h>
#include <absl/log/log.h>
#include <grpcpp/grpcpp.h>

namespace talos
{
	namespace icd
	{
		namespace server
		{

			TalosOperatorService::TalosOperatorService(std::shared_ptr<TaskQueue> queue)
					: queue_(queue) {}

			TalosOperatorService::~TalosOperatorService() = default;

			void TalosOperatorService::enqueue_task(const std::string &task_name,
																							std::function<void()> work)
			{
				if (!queue_)
					return;
				auto prom = std::make_shared<std::promise<void>>();
				auto fut = prom->get_future();
				queue_->enqueue(Task{task_name, std::move(work), prom});
				// Wait until the background processor dequeues and executes this task
				fut.get();
			}

			::grpc::Status TalosOperatorService::Handshake(::grpc::ServerContext * /*context*/, const ::icd::v1::HandshakeRequest * /*request*/, ::icd::v1::HandshakeResponse *response)
			{
				enqueue_task("Handshake", []()
										 { ABSL_LOG(INFO) << "Executing Handshake task"; });
				response->mutable_status()->set_return_code(0);
				response->set_major_version(1);
				response->set_minor_version(0);
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::PolarPanDiscrete(::grpc::ServerContext * /*context*/, const ::icd::v1::PolarPanDiscreteRequest * /*request*/, ::google::protobuf::UInt32Value *response)
			{
				enqueue_task("PolarPanDiscrete", []()
										 { ABSL_LOG(INFO) << "Executing PolarPanDiscrete task"; });
				response->set_value(0);
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::Home(::grpc::ServerContext * /*context*/, const ::icd::v1::HomeRequest * /*request*/, ::google::protobuf::UInt32Value *response)
			{
				enqueue_task("Home", []()
										 { ABSL_LOG(INFO) << "Executing Home task"; });
				response->set_value(0);
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::PolarPanContinuousStart(::grpc::ServerContext * /*context*/, const ::icd::v1::PolarPanContinuousStartRequest * /*request*/, ::google::protobuf::UInt32Value *response)
			{
				enqueue_task("PolarPanContinuousStart", []()
										 { ABSL_LOG(INFO) << "Executing PolarPanContinuousStart task"; });
				response->set_value(0);
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::PolarPanContinuousStop(::grpc::ServerContext * /*context*/, const ::google::protobuf::Empty * /*request*/, ::google::protobuf::UInt32Value *response)
			{
				enqueue_task("PolarPanContinuousStop", []()
										 { ABSL_LOG(INFO) << "Executing PolarPanContinuousStop task"; });
				response->set_value(0);
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::CartesianMoveDiscrete(::grpc::ServerContext * /*context*/, const ::icd::v1::CartesianMoveDiscreteRequest * /*request*/, ::google::protobuf::UInt32Value *response)
			{
				enqueue_task("CartesianMoveDiscrete", []()
										 { ABSL_LOG(INFO) << "Executing CartesianMoveDiscrete task"; });
				response->set_value(0);
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::CartesianMoveContinuousStart(::grpc::ServerContext * /*context*/, const ::icd::v1::CartesianMoveContinuousStartRequest * /*request*/, ::google::protobuf::UInt32Value *response)
			{
				enqueue_task("CartesianMoveContinuousStart", []()
										 { ABSL_LOG(INFO) << "Executing CartesianMoveContinuousStart task"; });
				response->set_value(0);
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::CartesianMoveContinuousStop(::grpc::ServerContext * /*context*/, const ::google::protobuf::Empty * /*request*/, ::google::protobuf::UInt32Value *response)
			{
				enqueue_task("CartesianMoveContinuousStop", []()
										 { ABSL_LOG(INFO) << "Executing CartesianMoveContinuousStop task"; });
				response->set_value(0);
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::ExecuteHardwareOperation(::grpc::ServerContext * /*context*/, const ::icd::v1::ExecuteHardwareOperationRequest *request, ::icd::v1::ExecuteHardwareOperationResponse *response)
			{
				enqueue_task("ExecuteHardwareOperation", []()
										 { ABSL_LOG(INFO) << "Executing ExecuteHardwareOperation task"; });
				response->mutable_status()->set_return_code(0);
				response->set_subcommand_id(request->subcommand_id());
				response->clear_payload();
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::GetSpeed(::grpc::ServerContext * /*context*/, const ::google::protobuf::Empty * /*request*/, ::icd::v1::GetSpeedResponse *response)
			{
				enqueue_task("GetSpeed", []()
										 { ABSL_LOG(INFO) << "Executing GetSpeed task"; });
				response->mutable_status()->set_return_code(0);
				response->set_speed(0);
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::SetSpeed(::grpc::ServerContext * /*context*/, const ::icd::v1::SetSpeedRequest * /*request*/, ::google::protobuf::UInt32Value *response)
			{
				enqueue_task("SetSpeed", []()
										 { ABSL_LOG(INFO) << "Executing SetSpeed task"; });
				response->set_value(0);
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::SavePosition(::grpc::ServerContext * /*context*/, const ::icd::v1::SavePositionRequest * /*request*/, ::google::protobuf::UInt32Value *response)
			{
				enqueue_task("SavePosition", []()
										 { ABSL_LOG(INFO) << "Executing SavePosition task"; });
				response->set_value(0);
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::DeletePosition(::grpc::ServerContext * /*context*/, const ::icd::v1::DeletePositionRequest * /*request*/, ::google::protobuf::UInt32Value *response)
			{
				enqueue_task("DeletePosition", []()
										 { ABSL_LOG(INFO) << "Executing DeletePosition task"; });
				response->set_value(0);
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::GoToPosition(::grpc::ServerContext * /*context*/, const ::icd::v1::GoToPositionRequest * /*request*/, ::google::protobuf::UInt32Value *response)
			{
				enqueue_task("GoToPosition", []()
										 { ABSL_LOG(INFO) << "Executing GoToPosition task"; });
				response->set_value(0);
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::SetPolarPosition(::grpc::ServerContext * /*context*/, const ::icd::v1::SetPolarPositionRequest * /*request*/, ::google::protobuf::UInt32Value *response)
			{
				enqueue_task("SetPolarPosition", []()
										 { ABSL_LOG(INFO) << "Executing SetPolarPosition task"; });
				response->set_value(0);
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::GetPolarPosition(::grpc::ServerContext * /*context*/, const ::icd::v1::GetPolarPositionRequest * /*request*/, ::icd::v1::GetPolarPositionResponse *response)
			{
				enqueue_task("GetPolarPosition", []()
										 { ABSL_LOG(INFO) << "Executing GetPolarPosition task"; });
				response->mutable_status()->set_return_code(0);
				response->set_delta_tenths_deg(0);
				response->set_azimuth_tenths_deg(0);
				response->set_radius_tenths(0);
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::SetCartesianPosition(::grpc::ServerContext * /*context*/, const ::icd::v1::SetCartesianPositionRequest * /*request*/, ::google::protobuf::UInt32Value *response)
			{
				enqueue_task("SetCartesianPosition", []()
										 { ABSL_LOG(INFO) << "Executing SetCartesianPosition task"; });
				response->set_value(0);
				return ::grpc::Status::OK;
			}

			::grpc::Status TalosOperatorService::GetCartesianPosition(::grpc::ServerContext * /*context*/, const ::icd::v1::GetCartesianPositionRequest * /*request*/, ::icd::v1::GetCartesianPositionResponse *response)
			{
				enqueue_task("GetCartesianPosition", []()
										 { ABSL_LOG(INFO) << "Executing GetCartesianPosition task"; });
				response->mutable_status()->set_return_code(0);
				response->set_x_tenths_mm(0);
				response->set_y_tenths_mm(0);
				response->set_z_tenths_mm(0);
				return ::grpc::Status::OK;
			}

		} // namespace server
	} // namespace icd
} // namespace talos
