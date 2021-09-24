cmake_minimum_required(VERSION 3.5.1)

project(FlowClient C CXX)

include(./cmake-commons/common.cmake)

# Proto file
get_filename_component(access_proto "./proto/access.proto" ABSOLUTE)
get_filename_component(access_proto_path "${access_proto}" PATH)

# Generated sources
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

# access_grpc_proto
add_library(access_grpc_proto
  ${access_grpc_srcs}
  ${access_grpc_hdrs}
  ${access_proto_srcs}
  ${access_proto_hdrs})
target_link_libraries(access_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Target client
add_executable(client "./client/client.cc" "./client/client.h")
target_link_libraries(client
  access_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})
