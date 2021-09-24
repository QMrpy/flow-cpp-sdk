#include "client.h"

FlowClient::FlowClient(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) 
    : stub_(flow::access::AccessAPI::NewStub(channel, options)) {}

::grpc::Status FlowClient::Ping(::grpc::ClientContext* context, const ::grpc::StubOptions& options) {
    flow::access::PingRequest request;
    flow::access::PingResponse response;

    ::grpc::Status status = stub_->Ping(context, request, &response);

    return status;
}

flow::access::BlockHeader* FlowClient::GetLatestBlockHeader(::grpc::ClientContext* context, bool is_sealed, const ::grpc::StubOptions& options) {
    flow::access::GetLatestBlockHeaderRequest request;
    flow::access::BlockHeaderResponse response;
    flow::access::BlockHeader *block_header;

    request.set_is_sealed(is_sealed);

    ::grpc::Status status = stub_->GetLatestBlockHeader(context, request, &response);
    if (status.ok()) {
        if (response.has_block()) {
            block_header = new flow::access::BlockHeader(response.block());
            return block_header;
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

flow::access::BlockHeader* FlowClient::GetBlockHeaderByID(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options) {
    flow::access::GetBlockHeaderByIdRequest request;
    flow::access::BlockHeaderResponse response;
    flow::access::BlockHeader *block_header;

    request.set_id(id);

    ::grpc::Status status = stub_->GetBlockHeaderByID(context, request, &response);
    if (status.ok()) {
        if (response.has_block()) {
            block_header = new flow::access::BlockHeader(response.block());
            return block_header;
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

flow::access::BlockHeader* FlowClient::GetBlockHeaderByHeight(::grpc::ClientContext* context, uint64_t height, const ::grpc::StubOptions& options) {
    flow::access::GetBlockHeaderByHeightRequest request;
    flow::access::BlockHeaderResponse response;
    flow::access::BlockHeader *block_header;

    request.set_height(height);

    ::grpc::Status status = stub_->GetBlockHeaderByHeight(context, request, &response);
    if (status.ok()) {
        if (response.has_block()) {
            block_header = new flow::access::BlockHeader(response.block());
            return block_header;
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

flow::access::Block* FlowClient::GetLatestBlock(::grpc::ClientContext* context, bool is_sealed, const ::grpc::StubOptions& options) {
    flow::access::GetLatestBlockRequest request;
    flow::access::BlockResponse response;
    flow::access::Block *block;

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

flow::access::Block* FlowClient::GetBlockByID(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options) {
    flow::access::GetBlockByIdRequest request;
    flow::access::BlockResponse response;
    flow::access::Block *block;

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

flow::access::Block* FlowClient::GetBlockByHeight(::grpc::ClientContext* context, uint64_t height, const ::grpc::StubOptions& options) {
    flow::access::GetBlockByHeightRequest request;
    flow::access::BlockResponse response;
    flow::access::Block *block;

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

flow::access::Collection* FlowClient::GetCollectionByID(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options) {
    flow::access::GetCollectionByIdRequest request;
    flow::access::CollectionResponse response;
    flow::access::Collection *collection;

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

flow::access::SendTransactionResponse* FlowClient::SendTransaction(::grpc::ClientContext* context, flow::access::Transaction* transaction, const ::grpc::StubOptions& options) {
    flow::access::SendTransactionRequest request;
    flow::access::SendTransactionResponse *response;

    request.set_allocated_transaction(transaction);

    ::grpc::Status status = stub_->SendTransaction(context, request, response);
    if (status.ok()) {
        return response;
    } else {
        return nullptr;
    }
}

flow::access::Transaction* FlowClient::GetTransaction(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options) {
    flow::access::GetTransactionRequest request;
    flow::access::TransactionResponse response;
    flow::access::Transaction *transaction;

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

std::vector<::flow::access::Event> FlowClient::GetTransactionResult(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options) {
    flow::access::GetTransactionRequest request;
    flow::access::TransactionResultResponse response;
    std::vector<::flow::access::Event> results;

    request.set_id(id);
    
    ::grpc::Status status = stub_->GetTransactionResult(context, request, &response);
    if (status.ok()) {
        if (response.events_size() > 0) {
            
            for (int idx = 0; idx < response.events_size(); idx++) {
                results.emplace_back(response.events(idx));
            }

            return results;
        } else {
            return {};
        }
    } else {
        return {};
    }
}

flow::access::Account* FlowClient::GetAccountAtLatestBlock(::grpc::ClientContext* context, const char *address, const ::grpc::StubOptions& options) {
    flow::access::GetAccountAtLatestBlockRequest request;
    flow::access::AccountResponse response;
    flow::access::Account *account;

    request.set_address(address);

    ::grpc::Status status = stub_->GetAccountAtLatestBlock(context, request, &response);
    if (status.ok()) {
        if (response.has_account()) {
            account = new flow::access::Account(response.account());
            return account;
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

flow::access::Account* FlowClient::GetAccountAtBlockHeight(::grpc::ClientContext* context, const char *address, uint64_t height, const ::grpc::StubOptions& options) {
    flow::access::GetAccountAtBlockHeightRequest request;
    flow::access::AccountResponse response;
    flow::access::Account *account;

    request.set_address(address);
    request.set_block_height(height);

    ::grpc::Status status = stub_->GetAccountAtBlockHeight(context, request, &response);
    if (status.ok()) {
        if (response.has_account()) {
            account = new flow::access::Account(response.account());
            return account;
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

flow::access::ExecuteScriptResponse* FlowClient::ExecuteScriptAtLatestBlock(::grpc::ClientContext* context, const char *script, const ::grpc::StubOptions& options) {
    flow::access::ExecuteScriptAtLatestBlockRequest request;
    flow::access::ExecuteScriptResponse *response;

    request.set_script(script);
    
    ::grpc::Status status = stub_->ExecuteScriptAtLatestBlock(context, request, response);
    if (status.ok()) {
        return response;
    } else {
        return nullptr;
    }
}

flow::access::ExecuteScriptResponse* FlowClient::ExecuteScriptAtBlockID(::grpc::ClientContext* context, const char *script, const char *id, const ::grpc::StubOptions& options) {
    flow::access::ExecuteScriptAtBlockIdRequest request;
    flow::access::ExecuteScriptResponse *response;

    request.set_block_id(id);
    request.set_script(script);

    ::grpc::Status status = stub_->ExecuteScriptAtBlockID(context, request, response);
    if (status.ok()) {
        return response;
    } else {
        return nullptr;
    }
}

flow::access::ExecuteScriptResponse* FlowClient::ExecuteScriptAtBlockHeight(::grpc::ClientContext* context, const char *script, uint64_t height, const ::grpc::StubOptions& options) {
    flow::access::ExecuteScriptAtBlockHeightRequest request;
    flow::access::ExecuteScriptResponse *response;

    request.set_block_height(height);
    request.set_script(script);

    ::grpc::Status status = stub_->ExecuteScriptAtBlockHeight(context, request, response);
    if (status.ok()) {
        return response;
    } else {
        return nullptr;
    }
}

std::vector<::flow::access::EventsResponse_Result> FlowClient::GetEventsForHeightRange(::grpc::ClientContext* context, uint64_t start_height, uint64_t end_height, const ::grpc::StubOptions& options) {
    flow::access::GetEventsForHeightRangeRequest request;
    flow::access::EventsResponse response;
    std::vector<::flow::access::EventsResponse_Result> events;

    request.set_start_height(start_height);
    request.set_end_height(end_height);

    ::grpc::Status status = stub_->GetEventsForHeightRange(context, request, &response);
    if (status.ok()) {
        if (response.results_size() > 0) {

            for (int idx = 0; idx < response.results_size(); idx++) {
                events.emplace_back(response.results(idx));
            }

            return events;
        } else {
            return {};
        }
    } else {
        return {};
    }
}

std::vector<::flow::access::EventsResponse_Result> FlowClient::GetEventsForBlockIDs(::grpc::ClientContext* context, int index, const char *id, const ::grpc::StubOptions& options) {
    flow::access::GetEventsForBlockIdsRequest request;
    flow::access::EventsResponse response;
    std::vector<::flow::access::EventsResponse_Result> events;

    request.set_block_ids(index, id);

    ::grpc::Status status = stub_->GetEventsForBlockIDs(context, request, &response);
    if (status.ok()) {
        if (response.results_size() > 0) {

            for (int idx = 0; idx < response.results_size(); idx++) {
                events.emplace_back(response.results(idx));
            }

            return events;
        } else {
            return {};
        }
    } else {
        return {};
    }

}

std::string FlowClient::GetNetworkParameters(::grpc::ClientContext* context, const ::grpc::StubOptions& options) {
    flow::access::GetNetworkParametersRequest request;
    flow::access::GetNetworkParametersResponse response;

    ::grpc::Status status = stub_->GetNetworkParameters(context, request, &response);
    if (status.ok()) {
        return response.chain_id();
    } else {
        return nullptr;
    }
}

std::string FlowClient::GetLatestProtocolStateSnapshot(::grpc::ClientContext* context, const ::grpc::StubOptions& options) {
    flow::access::GetLatestProtocolStateSnapshotRequest request;
    flow::access::ProtocolStateSnapshotResponse response;

    ::grpc::Status status = stub_->GetLatestProtocolStateSnapshot(context, request, &response);
    if (status.ok()) {
        return response.serializedsnapshot();
    } else {
        return nullptr;
    }
}

flow::access::ExecutionResult* FlowClient::ExecutionResultForBlockID(::grpc::ClientContext* context, const char *id, const ::grpc::StubOptions& options) {
    flow::access::GetExecutionResultForBlockIdRequest request;
    flow::access::ExecutionResultForBlockIdResponse response;
    flow::access::ExecutionResult *result;

    request.set_block_id(id);

    ::grpc::Status status = stub_->GetExecutionResultForBlockID(context, request, &response);
    if (status.ok()) {
        if (response.has_execution_result()) {
            result = new flow::access::ExecutionResult(response.execution_result());
            return result;
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

FlowClient::~FlowClient() {}


int main() {
    const std::shared_ptr< ::grpc::ChannelInterface> channel = grpc::CreateChannel("127.0.0.1:3569", grpc::InsecureChannelCredentials());
    const grpc::StubOptions options;
    grpc::ClientContext context;

    FlowClient client(channel, options);

    std::cout << "=============Ping Server===========" << std::endl;
    ::grpc::Status status = client.Ping(&context, options);

    if (status.ok()) {
        std::cout << "Server is alive and responding" << std::endl;
    } else {
        std::cout << "Failed to ping server" << std::endl;
    }

    return 0;
}

// Handle errors in a better way. Use nullptr to initialize or make separate error types for response and status
// Do any server method or any of data type methods such as set_id() need implementation?
// Is a convert class needed to convert between message types? Is an entity class also needed?
// May also implmenent async API
// Should std::unique_ptr be used to deal with memory leaks and std:shared_ptr be used for thread safety?
// We can choose return types and function arguments in client, so we should parse the response properly before sending the result to the caller code
// Write tests in separate file, main in separate file