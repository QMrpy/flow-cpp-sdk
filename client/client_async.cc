#include "client_async.h"

AsyncFlowClient::AsyncFlowClient(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) 
    : stub_(flow::access::AccessAPI::NewStub(channel, options)) {}

int AsyncFlowClient::AsyncPing() {
    grpc::ClientContext *context = new grpc::ClientContext();

    flow::access::PingRequest request;
    flow::access::PingResponse response;
    ::grpc::Status status;

    std::mutex mutex;
    std::condition_variable cond_var;
    bool rpc_done = false;

    stub_->async()->Ping(context, &request, &response, [&mutex, &cond_var, &rpc_done, &status](::grpc::Status s) {
                    std::lock_guard<std::mutex> lock(mutex);
                    status = std::move(s);
                    std::cout << "AsyncPing RPC completed" << std::endl;
                    if (status.ok()) {
                        std::cout << "Server is alive and responding." << std::endl;
                    } else {
                        std::cout << "Failed to ping server." << std::endl;
                    }
                    rpc_done = true;
                    cond_var.notify_one();
                    });

    std::unique_lock<std::mutex> lock(mutex);
    cond_var.wait(lock, [&rpc_done]{ return rpc_done; });

    return 0;
}

int AsyncFlowClient::AsyncGetLatestBlock(bool is_sealed) {
    grpc::ClientContext *context = new grpc::ClientContext();

    flow::access::GetLatestBlockRequest request;
    flow::access::BlockResponse response;
    flow::access::Block* block;
    
    ::grpc::Status status;
    std::mutex mutex;
    std::condition_variable cond_var;
    bool rpc_done = false;

    request.set_is_sealed(is_sealed);

    stub_->async()->GetLatestBlock(context, &request, &response, [&mutex, &cond_var, &rpc_done, &status, &response](::grpc::Status s) {
                    std::lock_guard<std::mutex> lock(mutex);
                    status = std::move(s);
                    std::cout << "AsyncGetLatestBlock RPC completed" << std::endl;
                    if (status.ok()) {
                        if (response.has_block()) {
                            std::cout << "Block ID: " << ConvertResponse().get_sha256_from_raw_bytes(response.block().id()) << std::endl;
                            std::cout << "Block Height: " << response.block().height() << std::endl;
                            std::cout << "Block Timestamp (seconds): " << response.block().timestamp().seconds() << std::endl;
                        } else {
                            std::cout << "Failed to retrieve latest block." << std::endl;
                        }
                    } else {
                        std::cout << "Status is not OK at server" << std::endl;
                    }
                    rpc_done = true;
                    cond_var.notify_one();
                    });

    std::unique_lock<std::mutex> lock(mutex);
    cond_var.wait(lock, [&rpc_done]{ return rpc_done; });

    return 0;
}


// How to prove that the calls are truly asynchronous?
