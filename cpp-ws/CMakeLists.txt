cmake_minimum_required(VERSION 3.16)
project(talos_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(TALOS_BUILD_PROTO "Generate and build gRPC/proto sources" ON)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../proto/icd/v1)
set(PROTO_FILE ${PROTO_DIR}/icd.proto)

# Branch 1: Build from .proto if enabled and available
set(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/icd/v1)
if(TALOS_BUILD_PROTO AND EXISTS ${PROTO_FILE})
    find_package(gRPC CONFIG REQUIRED)
    find_package(protobuf CONFIG REQUIRED)

    set(PROTO_SRCS ${GENERATED_DIR}/icd.pb.cc)
    set(GRPC_SRCS  ${GENERATED_DIR}/icd.grpc.pb.cc)

    set(PROTOC $<TARGET_FILE:protobuf::protoc>)
    set(GRPC_CPP_PLUGIN $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

    add_custom_command(
        OUTPUT ${PROTO_SRCS} ${GRPC_SRCS}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${GENERATED_DIR}
        COMMAND ${PROTOC}
            --grpc_out=${GENERATED_DIR}
            --cpp_out=${GENERATED_DIR}
            --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
            -I ${PROTO_DIR}
            ${PROTO_FILE}
        DEPENDS ${PROTO_FILE}
        COMMENT "Generating protobuf and gRPC sources"
    )

    add_library(talos_icd_proto STATIC ${PROTO_SRCS} ${GRPC_SRCS})
    target_include_directories(talos_icd_proto PUBLIC ${GENERATED_DIR})
    target_link_libraries(talos_icd_proto PUBLIC protobuf::libprotobuf gRPC::grpc++)

    add_executable(talos ${SRC_DIR}/main.cpp ${SRC_DIR}/talos_service.cpp)
    target_include_directories(talos PRIVATE ${GENERATED_DIR} ${SRC_DIR})
    target_link_libraries(talos PRIVATE talos_icd_proto gRPC::grpc++)

# Branch 2: Use pre-generated stubs from src/ if present
elseif(EXISTS ${SRC_DIR}/icd.pb.cc AND EXISTS ${SRC_DIR}/icd.grpc.pb.cc)
    message(STATUS "Using pre-generated proto stubs from ${SRC_DIR}")
    find_package(gRPC CONFIG REQUIRED)
    find_package(protobuf CONFIG REQUIRED)

    add_library(talos_icd_proto STATIC ${SRC_DIR}/icd.pb.cc ${SRC_DIR}/icd.grpc.pb.cc)
    target_include_directories(talos_icd_proto PUBLIC ${SRC_DIR})
    target_link_libraries(talos_icd_proto PUBLIC protobuf::libprotobuf gRPC::grpc++)

    add_executable(talos ${SRC_DIR}/main.cpp ${SRC_DIR}/talos_service.cpp)
    target_include_directories(talos PRIVATE ${SRC_DIR})
    target_link_libraries(talos PRIVATE talos_icd_proto gRPC::grpc++)

# Branch 3: Error if neither branch 1 nor 2 conditions are met
else()
    message(FATAL_ERROR "Cannot build talos: proto generation disabled or .proto missing, and no pre-generated stubs found in ${SRC_DIR}")
endif()
