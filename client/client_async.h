#ifndef ASYNC_FLOW_CLIENT_H
#define ASYNC_FLOW_CLIENT_H

#include <iostream>
#include <string>
#include <vector>
#include <condition_variable>
#include <mutex>

#include <grpc/grpc.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "../convert/convert.h"
#include "access.grpc.pb.h"

class AsyncFlowClient {
    public:
        AsyncFlowClient(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options);
        
        /** Asynchronous API **/
        int AsyncPing();
        int AsyncGetLatestBlock(bool is_sealed);

    private:
        std::unique_ptr<::flow::access::AccessAPI::Stub> stub_;
};

#endif