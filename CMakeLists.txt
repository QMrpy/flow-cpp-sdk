cmake_minimum_required(VERSION 3.5.1)

project(FlowClient C CXX)

include(./cmake-commons/common.cmake)

# Proto file
get_filename_component(access_proto "./proto/access.proto" ABSOLUTE)
get_filename_component(access_proto_path "${access_proto}" PATH)

# access_grpc_proto sources
set(access_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/access.pb.cc")
set(access_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/access.pb.h")
set(access_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/access.grpc.pb.cc")
set(access_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/access.grpc.pb.h")
add_custom_command(
      OUTPUT "${access_proto_srcs}" "${access_proto_hdrs}" "${access_grpc_srcs}" "${access_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${access_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${access_proto}"
      DEPENDS "${access_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# access_grpc_proto object
add_library(access_grpc_proto
  ${access_grpc_srcs}
  ${access_grpc_hdrs}
  ${access_proto_srcs}
  ${access_proto_hdrs})
target_link_libraries(access_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Convert sources
set(convert_srcs "${CMAKE_CURRENT_BINARY_DIR}/../../convert/convert.cc")
set(convert_hdrs "${CMAKE_CURRENT_BINARY_DIR}/../../convert/convert.h")

# convert object
add_library(convert
  ${convert_srcs}
  ${convert_hdrs})

# Client sources
set(client_srcs "${CMAKE_CURRENT_BINARY_DIR}/../../client/client.cc")
set(client_hdrs "${CMAKE_CURRENT_BINARY_DIR}/../../client/client.h")

# client object
add_library(client
  ${client_srcs}
  ${client_hdrs})
target_link_libraries(client
  access_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Async Client sources
set(async_client_srcs "${CMAKE_CURRENT_BINARY_DIR}/../../client/client_async.cc")
set(async_client_hdrs "${CMAKE_CURRENT_BINARY_DIR}/../../client/client_async.h")

# async_client object
add_library(async_client
  ${async_client_srcs}
  ${async_client_hdrs})
target_link_libraries(async_client
  access_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Test Client sources
set(test_client_srcs "${CMAKE_CURRENT_BINARY_DIR}/../../tests/test_client.cc")
set(test_client_hdrs "${CMAKE_CURRENT_BINARY_DIR}/../../tests/test_client.h")

# test_client object
add_library(test_client
  ${test_client_srcs}
  ${test_client_hdrs})
target_link_libraries(test_client
  client
  convert
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Test Async Client sources
set(test_async_client_srcs "${CMAKE_CURRENT_BINARY_DIR}/../../tests/test_async_client.cc")
set(test_async_client_hdrs "${CMAKE_CURRENT_BINARY_DIR}/../../tests/test_async_client.h")

# test_async_client object
add_library(test_async_client
  ${test_async_client_srcs}
  ${test_async_client_hdrs})
target_link_libraries(test_async_client
  async_client
  convert
  ${_THREADS}
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Target main executable
add_executable(main "./main.cc")
target_link_libraries(main
  test_client
  client
  test_async_client
  async_client
  convert
  access_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})
