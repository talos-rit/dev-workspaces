cmake_minimum_required(VERSION 3.16)
project(talos_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(gRPC CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)

set(PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../proto/icd/v1)
set(PROTO_FILES ${PROTO_DIR}/icd.proto)

set(GENERATED_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/icd/v1)

set(PROTO_SRCS ${GENERATED_SRC_DIR}/icd.pb.cc)
set(PROTO_HDRS ${GENERATED_SRC_DIR}/icd.pb.h)
set(GRPC_SRCS ${GENERATED_SRC_DIR}/icd.grpc.pb.cc)
set(GRPC_HDRS ${GENERATED_SRC_DIR}/icd.grpc.pb.h)

set(PROTOC $<TARGET_FILE:protobuf::protoc>)
set(GRPC_CPP_PLUGIN $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

add_custom_command(
    OUTPUT ${PROTO_SRCS} ${PROTO_HDRS} ${GRPC_SRCS} ${GRPC_HDRS}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${GENERATED_SRC_DIR}
    COMMAND ${PROTOC} 
        --grpc_out=${GENERATED_SRC_DIR}
        --cpp_out=${GENERATED_SRC_DIR}
        --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
        -I ${PROTO_DIR}
        ${PROTO_FILES}
    DEPENDS ${PROTO_FILES}
    COMMENT "Generating protobuf and gRPC sources..."
)

add_library(talos_icd_proto STATIC
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)

target_include_directories(talos_icd_proto PUBLIC ${GENERATED_SRC_DIR})

target_link_libraries(talos_icd_proto
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc++
)

add_executable(talos
    src/main.cpp
    src/talos_service.cpp
)

target_link_libraries(talos
    PRIVATE
        talos_icd_proto
        gRPC::grpc++
)

target_include_directories(talos
    PRIVATE
        ${GENERATED_SRC_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
