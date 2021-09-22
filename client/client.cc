#include <iostream>
#include <string>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "flow.grpc.pb.h"


class FlowClient {
    public:
        FlowClient(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) : stub_(flow::access::AccessAPI::NewStub(channel, options)) {}

        ::grpc::Status Ping(::grpc::ClientContext* context, const ::grpc::StubOptions& options) {
            ::flow::access::PingRequest request;
            ::flow::access::PingResponse response;

            ::grpc::Status status = stub_->Ping(context, request, &response);

            return status;
        }

        ::flow::access::BlockHeader GetLatestBlockHeader(::grpc::ClientContext* context, bool is_sealed, const ::grpc::StubOptions& options) {
            ::flow::access::GetLatestBlockHeaderRequest request;
            ::flow::access::BlockHeaderResponse response;
            
            request.set_is_sealed(is_sealed);

            ::grpc::Status status = stub_->GetLatestBlockHeader(context, request, &response);
            if (status.ok()) {
                if (response.has_block()) {
                    return response.block();
                }
            } 
            /** handle error here **/ 
        }

        ::flow::access::BlockHeader GetBlockHeaderByID(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options) {
            ::flow::access::GetBlockHeaderByIdRequest request;
            ::flow::access::BlockHeaderResponse response;

            request.set_id(id);

            ::grpc::Status status = stub_->GetBlockHeaderByID(context, request, &response);
            if (status.ok()) {
                if (response.has_block()) {
                    return response.block();
                }
            } 
            /** handle error here **/ 
        }
        
    private:
        std::unique_ptr<flow::access::AccessAPI::Stub> stub_;
};
