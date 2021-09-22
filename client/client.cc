#include <iostream>
#include <string>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "flow.grpc.pb.h"
#include "flow.pb.h"


class FlowClient {
    public:
        FlowClient(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) : stub_(flow::access::AccessAPI::NewStub(channel, options)) {}

        ::grpc::Status Ping(::grpc::ClientContext* context, const ::grpc::StubOptions& options) {
            ::flow::access::PingRequest request;
            ::flow::access::PingResponse response;

            ::grpc::Status status = stub_->Ping(context, request, &response);

            return status;
        }

        ::flow::access::BlockHeader* GetLatestBlockHeader(::grpc::ClientContext* context, bool is_sealed, const ::grpc::StubOptions& options) {
            ::flow::access::GetLatestBlockHeaderRequest request;
            ::flow::access::BlockHeaderResponse response;
            ::flow::access::BlockHeader *blockHeader;

            request.set_is_sealed(is_sealed);

            ::grpc::Status status = stub_->GetLatestBlockHeader(context, request, &response);
            if (status.ok()) {
                if (response.has_block()) {
                    blockHeader = new flow::access::BlockHeader(response.block());
                    return blockHeader;
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        }

        ::flow::access::BlockHeader* GetBlockHeaderByID(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options) {
            ::flow::access::GetBlockHeaderByIdRequest request;
            ::flow::access::BlockHeaderResponse response;
            ::flow::access::BlockHeader *blockHeader;

            request.set_id(id);

            ::grpc::Status status = stub_->GetBlockHeaderByID(context, request, &response);
            if (status.ok()) {
                if (response.has_block()) {
                    blockHeader = new flow::access::BlockHeader(response.block());
                    return blockHeader;
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        }

        ::flow::access::BlockHeader* GetBlockHeaderByHeight(::grpc::ClientContext* context, uint64_t height, const ::grpc::StubOptions& options) {
            ::flow::access::GetBlockHeaderByHeightRequest request;
            ::flow::access::BlockHeaderResponse response;
            ::flow::access::BlockHeader *blockHeader;

            request.set_height(height);

            ::grpc::Status status = stub_->GetBlockHeaderByHeight(context, request, &response);
            if (status.ok()) {
                if (response.has_block()) {
                    blockHeader = new flow::access::BlockHeader(response.block());
                    return blockHeader;
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        }

        ::flow::access::Block* GetLatestBlock(::grpc::ClientContext* context, bool is_sealed, const ::grpc::StubOptions& options) {
            ::flow::access::GetLatestBlockRequest request;
            ::flow::access::BlockResponse response;
            ::flow::access::Block *block;

            request.set_is_sealed(is_sealed);

            ::grpc::Status status = stub_->GetLatestBlock(context, request, &response);
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

        ::flow::access::Block* GetBlockByID(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options) {
            ::flow::access::GetBlockByIdRequest request;
            ::flow::access::BlockResponse response;
            ::flow::access::Block *block;

            request.set_id(id);

            ::grpc::Status status = stub_->GetBlockByID(context, request, &response);
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

        ::flow::access::Block* GetBlockByHeight(::grpc::ClientContext* context, uint64_t height, const ::grpc::StubOptions& options) {
            ::flow::access::GetBlockByHeightRequest request;
            ::flow::access::BlockResponse response;
            ::flow::access::Block *block;

            request.set_height(height);

            ::grpc::Status status = stub_->GetBlockByHeight(context, request, &response);
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

        ::flow::access::Collection* GetCollectionByID(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options) {
            ::flow::access::GetCollectionByIdRequest request;
            ::flow::access::CollectionResponse response;
            ::flow::access::Collection *collection;

            request.set_id(id);

            ::grpc::Status status = stub_->GetCollectionByID(context, request, &response);
            if (status.ok()) {
                if (response.has_collection()) {
                    collection = new flow::access::Collection(response.collection());
                    return collection;
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        }

        ::grpc::Status SendTransaction(::grpc::ClientContext* context, ::flow::access::Transaction* transaction, const ::grpc::StubOptions& options) {
            ::flow::access::SendTransactionRequest request;
            ::flow::access::SendTransactionResponse response;

            request.set_allocated_transaction(transaction);

            ::grpc::Status status = stub_->SendTransaction(context, request, &response);

            return status;
        }

        ::flow::access::Transaction* GetTransaction(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options) {
            ::flow::access::GetTransactionRequest request;
            ::flow::access::TransactionResponse response;
            ::flow::access::Transaction* transaction;

            request.set_id(id);

            ::grpc::Status status = stub_->GetTransaction(context, request, &response);
            if (status.ok()) {
                if (response.has_transaction()) {
                    transaction = new flow::access::Transaction(response.transaction());
                    return transaction;
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        }

        ::flow::access::TransactionResultResponse* GetTransactionResult(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options) {
            ::flow::access::GetTransactionRequest request;
            ::flow::access::TransactionResultResponse* response;

            request.set_id(id);

            ::grpc::Status status = stub_->GetTransactionResult(context, request, response);
            if (status.ok()) {
                return response;
            } else {
                return nullptr;
            }
        }
        
    private:
        std::unique_ptr<flow::access::AccessAPI::Stub> stub_;
};
