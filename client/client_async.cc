#include "client_async.h"

AsyncFlowClient::AsyncFlowClient(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) 
    : stub_(flow::access::AccessAPI::NewStub(channel, options)) {}

::grpc::Status AsyncFlowClient::AsyncPing(::grpc::ClientContext* context) {
    flow::access::PingRequest request;
    flow::access::PingResponse response;
    ::grpc::CompletionQueue cq;
    ::grpc::Status status;

    std::unique_ptr<::grpc::ClientAsyncResponseReader<::flow::access::PingResponse>> rpc_call = stub_->AsyncPing(context, request, &cq);

    rpc_call->Finish(&response, &status, (void*)1);
    
    void* got_tag;
    bool gpr_ok = false;
    
    GPR_ASSERT(cq.Next(&got_tag, &gpr_ok));
    GPR_ASSERT(got_tag == (void*)1);
    GPR_ASSERT(gpr_ok);
    
    return status;
}

flow::access::Block* AsyncFlowClient::AsyncGetLatestBlock(::grpc::ClientContext* context, bool is_sealed) {
    flow::access::GetLatestBlockRequest request;
    flow::access::BlockResponse response;
    flow::access::Block* block;
    ::grpc::CompletionQueue cq;
    ::grpc::Status status;

    request.set_is_sealed(is_sealed);

    std::unique_ptr<::grpc::ClientAsyncResponseReader<flow::access::BlockResponse>> rpc_call = stub_->AsyncGetLatestBlock(context, request, &cq);

    rpc_call->Finish(&response, &status, (void*)2);

    void* got_tag;
    bool gpr_ok = false;

    GPR_ASSERT(cq.Next(&got_tag, &gpr_ok));
    GPR_ASSERT(got_tag == (void*)2);
    GPR_ASSERT(gpr_ok);

    if (status.ok()) {
        if (response.has_block()) {
            block = new flow::access::Block(response.block());
            return block;
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

AsyncFlowClient::~AsyncFlowClient() {}


// Should there be one completion queue per rpc call or a single completion queue for the entire class AsyncFlowClient?
// What is got_tag and should it be unique per rpc call method?
// Does GPR_ASSERT(cq.Next(&got_tag, &gpr_ok)); effectively cause the calls to be sequential, because it does some sort of blocking?
// Why is rpc_call->StartCall() giving assertion != started error?
// How to prove that the calls are truly asynchronous?
