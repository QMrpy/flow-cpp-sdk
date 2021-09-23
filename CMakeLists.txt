# Copyright 2018 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# cmake build file for FlowClient
# Assumes protobuf and gRPC have been installed using cmake.

cmake_minimum_required(VERSION 3.5.1)

project(FlowClient C CXX)

include(./cmake-commons/common.cmake)

# Proto file
get_filename_component(flow_proto "./proto/flow.proto" ABSOLUTE)
get_filename_component(flow_proto_path "${flow_proto}" PATH)

# Generated sources
set(flow_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/flow.pb.cc")
set(flow_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/flow.pb.h")
set(flow_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/flow.grpc.pb.cc")
set(flow_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/flow.grpc.pb.h")
add_custom_command(
      OUTPUT "${flow_proto_srcs}" "${flow_proto_hdrs}" "${flow_grpc_srcs}" "${flow_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${flow_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${flow_proto}"
      DEPENDS "${flow_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# flow_grpc_proto
add_library(flow_grpc_proto
  ${flow_grpc_srcs}
  ${flow_grpc_hdrs}
  ${flow_proto_srcs}
  ${flow_proto_hdrs})
target_link_libraries(flow_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Target client
add_executable(client "./client/client.cc" "./client/client.h")
target_link_libraries(client
  flow_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

