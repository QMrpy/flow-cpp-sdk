#ifndef FLOW_CLIENT_H
#define FLOW_CLIENT_H

#include <iostream>
#include <string>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "../proto/flow.grpc.pb.h"
#include "../proto/flow.pb.h"

class FlowClient : ::flow::access::AccessAPI::Stub {
    public:
        FlowClient(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options);
        ::grpc::Status Ping(::grpc::ClientContext* context, const ::grpc::StubOptions& options);
        flow::access::BlockHeader* FlowClient::GetLatestBlockHeader(::grpc::ClientContext* context, bool is_sealed, const ::grpc::StubOptions& options);
        flow::access::BlockHeader* GetBlockHeaderByID(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options);
        flow::access::BlockHeader* GetBlockHeaderByHeight(::grpc::ClientContext* context, uint64_t height, const ::grpc::StubOptions& options);
        flow::access::Block* GetLatestBlock(::grpc::ClientContext* context, bool is_sealed, const ::grpc::StubOptions& options);
        flow::access::Block* GetBlockByID(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options);
        flow::access::Block* GetBlockByHeight(::grpc::ClientContext* context, uint64_t height, const ::grpc::StubOptions& options);
        flow::access::Collection* GetCollectionByID(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options);
        ::grpc::Status SendTransaction(::grpc::ClientContext* context, flow::access::Transaction* transaction, const ::grpc::StubOptions& options);
        flow::access::Transaction* GetTransaction(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options);
        flow::access::TransactionResultResponse* GetTransactionResult(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options);
        flow::access::Account* GetAccountAtLatestBlock(::grpc::ClientContext* context, const char *address, const ::grpc::StubOptions& options);
        flow::access::Account* GetAccountAtBlockHeight(::grpc::ClientContext* context, const char *address, uint64_t height, const ::grpc::StubOptions& options);
        
    private:
        std::unique_ptr<::flow::access::AccessAPI::Stub> stub_;
};

#endif
