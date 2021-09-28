#ifndef ASYNC_FLOW_CLIENT_H
#define ASYNC_FLOW_CLIENT_H

#include <iostream>
#include <string>
#include <vector>

#include <grpc/grpc.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "access.grpc.pb.h"

class AsyncFlowClient {
    public:
        AsyncFlowClient(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options);
        
        /** Asynchronous API **/
        ::grpc::Status AsyncPing(::grpc::ClientContext* context);
        flow::access::Block* AsyncGetLatestBlock(::grpc::ClientContext* context, bool is_sealed);

        ~AsyncFlowClient();

    private:
        std::unique_ptr<::flow::access::AccessAPI::Stub> stub_;
};

#endif