#ifndef FLOW_CLIENT_H
#define FLOW_CLIENT_H

#include <iostream>
#include <string>
#include <vector>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "access.grpc.pb.h"

class FlowClient {
    public:
        FlowClient(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options);
        
        /** Synchronous API **/
        ::grpc::Status Ping(::grpc::ClientContext* context);
        std::unique_ptr<flow::access::BlockHeader> GetLatestBlockHeader(::grpc::ClientContext* context, bool is_sealed);
        std::unique_ptr<flow::access::BlockHeader> GetBlockHeaderByID(::grpc::ClientContext* context, const std::string& id);
        std::unique_ptr<flow::access::BlockHeader> GetBlockHeaderByHeight(::grpc::ClientContext* context, uint64_t height);
        std::unique_ptr<flow::access::Block> GetLatestBlock(::grpc::ClientContext* context, bool is_sealed);
        std::unique_ptr<flow::access::Block> GetBlockByID(::grpc::ClientContext* context, const std::string& id);
        std::unique_ptr<flow::access::Block> GetBlockByHeight(::grpc::ClientContext* context, uint64_t height);
        std::unique_ptr<flow::access::Collection> GetCollectionByID(::grpc::ClientContext* context, const std::string& id);
        flow::access::SendTransactionResponse* SendTransaction(::grpc::ClientContext* context, flow::access::Transaction* transaction);
        std::unique_ptr<flow::access::Transaction> GetTransaction(::grpc::ClientContext* context, const std::string& id);
        std::vector<::flow::access::Event> GetTransactionResult(::grpc::ClientContext* context, const std::string& id);
        std::unique_ptr<flow::access::Account> GetAccountAtLatestBlock(::grpc::ClientContext* context, const std::string& address);
        std::unique_ptr<flow::access::Account> GetAccountAtBlockHeight(::grpc::ClientContext* context, const std::string& address, uint64_t height);
        flow::access::ExecuteScriptResponse* ExecuteScriptAtLatestBlock(::grpc::ClientContext* context, const char* script);
        flow::access::ExecuteScriptResponse* ExecuteScriptAtBlockID(::grpc::ClientContext* context, const char* script, const std::string& id);
        flow::access::ExecuteScriptResponse* ExecuteScriptAtBlockHeight(::grpc::ClientContext* context, const char* script, uint64_t height);
        std::vector<::flow::access::EventsResponse_Result> GetEventsForHeightRange(::grpc::ClientContext* context, uint64_t start_height, uint64_t end_height);
        std::vector<::flow::access::EventsResponse_Result> GetEventsForBlockIDs(::grpc::ClientContext* context, int index, const std::string& id);
        std::string GetNetworkParameters(::grpc::ClientContext* context);
        std::string GetLatestProtocolStateSnapshot(::grpc::ClientContext* context);
        std::unique_ptr<flow::access::ExecutionResult> ExecutionResultForBlockID(::grpc::ClientContext* context, const std::string& id);

    private:
        std::unique_ptr<::flow::access::AccessAPI::Stub> stub_;
};

#endif
