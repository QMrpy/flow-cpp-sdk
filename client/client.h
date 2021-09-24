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
        ::grpc::Status Ping(::grpc::ClientContext* context, const ::grpc::StubOptions& options);
        flow::access::BlockHeader* GetLatestBlockHeader(::grpc::ClientContext* context, bool is_sealed, const ::grpc::StubOptions& options);
        flow::access::BlockHeader* GetBlockHeaderByID(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options);
        flow::access::BlockHeader* GetBlockHeaderByHeight(::grpc::ClientContext* context, uint64_t height, const ::grpc::StubOptions& options);
        flow::access::Block* GetLatestBlock(::grpc::ClientContext* context, bool is_sealed, const ::grpc::StubOptions& options);
        flow::access::Block* GetBlockByID(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options);
        flow::access::Block* GetBlockByHeight(::grpc::ClientContext* context, uint64_t height, const ::grpc::StubOptions& options);
        flow::access::Collection* GetCollectionByID(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options);
        flow::access::SendTransactionResponse* SendTransaction(::grpc::ClientContext* context, flow::access::Transaction* transaction, const ::grpc::StubOptions& options);
        flow::access::Transaction* GetTransaction(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options);
        std::vector<::flow::access::Event> GetTransactionResult(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options);
        flow::access::Account* GetAccountAtLatestBlock(::grpc::ClientContext* context, const char *address, const ::grpc::StubOptions& options);
        flow::access::Account* GetAccountAtBlockHeight(::grpc::ClientContext* context, const char *address, uint64_t height, const ::grpc::StubOptions& options);
        flow::access::ExecuteScriptResponse* ExecuteScriptAtLatestBlock(::grpc::ClientContext* context, const char *script, const ::grpc::StubOptions& options);
        flow::access::ExecuteScriptResponse* ExecuteScriptAtBlockID(::grpc::ClientContext* context, const char *script, const char *id, const ::grpc::StubOptions& options);
        flow::access::ExecuteScriptResponse* ExecuteScriptAtBlockHeight(::grpc::ClientContext* context, const char *script, uint64_t height, const ::grpc::StubOptions& options);
        std::vector<::flow::access::EventsResponse_Result> GetEventsForHeightRange(::grpc::ClientContext* context, uint64_t start_height, uint64_t end_height, const ::grpc::StubOptions& options);
        std::vector<::flow::access::EventsResponse_Result> GetEventsForBlockIDs(::grpc::ClientContext* context, int index, const char *id, const ::grpc::StubOptions& options);
        std::string GetNetworkParameters(::grpc::ClientContext* context, const ::grpc::StubOptions& options);
        std::string GetLatestProtocolStateSnapshot(::grpc::ClientContext* context, const ::grpc::StubOptions& options);
        flow::access::ExecutionResult* ExecutionResultForBlockID(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options);
        ~FlowClient();

    private:
        std::unique_ptr<::flow::access::AccessAPI::Stub> stub_;
};

#endif
