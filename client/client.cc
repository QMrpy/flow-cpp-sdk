#include "client.h"

FlowClient::FlowClient(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) 
    : stub_(flow::access::AccessAPI::NewStub(channel, options)) {}

::grpc::Status FlowClient::Ping(::grpc::ClientContext* context) {
    flow::access::PingRequest request;
    flow::access::PingResponse response;

    ::grpc::Status status = stub_->Ping(context, request, &response);

    return status;
}

std::unique_ptr<flow::access::BlockHeader> FlowClient::GetLatestBlockHeader(::grpc::ClientContext* context, bool is_sealed) {
    flow::access::GetLatestBlockHeaderRequest request;
    flow::access::BlockHeaderResponse response;
    std::unique_ptr<flow::access::BlockHeader> block_header;

    request.set_is_sealed(is_sealed);

    ::grpc::Status status = stub_->GetLatestBlockHeader(context, request, &response);
    if (status.ok()) {
        if (response.has_block())
            block_header = std::make_unique<flow::access::BlockHeader>(response.block());
    }

    return block_header;
}

std::unique_ptr<flow::access::BlockHeader> FlowClient::GetBlockHeaderByID(::grpc::ClientContext* context, const std::string& id) {
    flow::access::GetBlockHeaderByIDRequest request;
    flow::access::BlockHeaderResponse response;
    std::unique_ptr<flow::access::BlockHeader> block_header;

    request.set_id(id);

    ::grpc::Status status = stub_->GetBlockHeaderByID(context, request, &response);
    if (status.ok()) {
        if (response.has_block())
            block_header = std::make_unique<flow::access::BlockHeader>(response.block());
    }

    return block_header;
}

std::unique_ptr<flow::access::BlockHeader> FlowClient::GetBlockHeaderByHeight(::grpc::ClientContext* context, uint64_t height) {
    flow::access::GetBlockHeaderByHeightRequest request;
    flow::access::BlockHeaderResponse response;
    std::unique_ptr<flow::access::BlockHeader> block_header;

    request.set_height(height);

    ::grpc::Status status = stub_->GetBlockHeaderByHeight(context, request, &response);
    if (status.ok()) {
        if (response.has_block())
            block_header = std::make_unique<flow::access::BlockHeader>(response.block());
    }

    return block_header;
}

std::unique_ptr<flow::access::Block> FlowClient::GetLatestBlock(::grpc::ClientContext* context, bool is_sealed) {
    flow::access::GetLatestBlockRequest request;
    flow::access::BlockResponse response;
    std::unique_ptr<flow::access::Block> block;

    request.set_is_sealed(is_sealed);

    ::grpc::Status status = stub_->GetLatestBlock(context, request, &response);
    if (status.ok()) {
        if (response.has_block())
            block = std::make_unique<flow::access::Block>(response.block());
    }

    return block;
}

std::unique_ptr<flow::access::Block> FlowClient::GetBlockByID(::grpc::ClientContext* context, const std::string& id) {
    flow::access::GetBlockByIDRequest request;
    flow::access::BlockResponse response;
    std::unique_ptr<flow::access::Block> block;

    request.set_id(id);

    ::grpc::Status status = stub_->GetBlockByID(context, request, &response);
    if (status.ok()) {
        if (response.has_block()) 
            block = std::make_unique<flow::access::Block>(response.block());
    }

    return block;
}

std::unique_ptr<flow::access::Block> FlowClient::GetBlockByHeight(::grpc::ClientContext* context, uint64_t height) {
    flow::access::GetBlockByHeightRequest request;
    flow::access::BlockResponse response;
    std::unique_ptr<flow::access::Block> block;

    request.set_height(height);

    ::grpc::Status status = stub_->GetBlockByHeight(context, request, &response);
    if (status.ok()) {
        if (response.has_block()) 
            block = std::make_unique<flow::access::Block>(response.block());
    }

    return block;
}

std::unique_ptr<flow::access::Collection> FlowClient::GetCollectionByID(::grpc::ClientContext* context, const std::string& id) {
    flow::access::GetCollectionByIDRequest request;
    flow::access::CollectionResponse response;
    std::unique_ptr<flow::access::Collection> collection;

    request.set_id(id);

    ::grpc::Status status = stub_->GetCollectionByID(context, request, &response);
    if (status.ok()) {
        if (response.has_collection())
            collection = std::make_unique<flow::access::Collection>(response.collection());
    }

    return collection;
}

flow::access::SendTransactionResponse* FlowClient::SendTransaction(::grpc::ClientContext* context, flow::access::Transaction* transaction) {
    flow::access::SendTransactionRequest request;
    flow::access::SendTransactionResponse* response;

    request.set_allocated_transaction(transaction);

    ::grpc::Status status = stub_->SendTransaction(context, request, response);
    if (status.ok()) {
        return response;
    } else {
        return nullptr;
    }
}

std::unique_ptr<flow::access::Transaction> FlowClient::GetTransaction(::grpc::ClientContext* context, const std::string& id) {
    flow::access::GetTransactionRequest request;
    flow::access::TransactionResponse response;
    std::unique_ptr<flow::access::Transaction> transaction;

    request.set_id(id);

    ::grpc::Status status = stub_->GetTransaction(context, request, &response);
    if (status.ok()) {
        if (response.has_transaction())
            transaction = std::make_unique<flow::access::Transaction>(response.transaction());
    }

    return transaction;
}

std::vector<::flow::access::Event> FlowClient::GetTransactionResult(::grpc::ClientContext* context, const std::string& id) {
    flow::access::GetTransactionRequest request;
    flow::access::TransactionResultResponse response;
    std::vector<::flow::access::Event> results;

    request.set_id(id);
    
    ::grpc::Status status = stub_->GetTransactionResult(context, request, &response);
    if (status.ok()) {
        if (response.events_size() > 0) {

            for (int idx = 0; idx < response.events_size(); idx++)
                results.emplace_back(response.events(idx));
        }
    }

    return results;
}

std::unique_ptr<flow::access::Account> FlowClient::GetAccountAtLatestBlock(::grpc::ClientContext* context, const std::string& address) {
    flow::access::GetAccountAtLatestBlockRequest request;
    flow::access::AccountResponse response;
    std::unique_ptr<flow::access::Account> account;

    request.set_address(address);

    ::grpc::Status status = stub_->GetAccountAtLatestBlock(context, request, &response);
    if (status.ok()) {
        if (response.has_account())
            account = std::make_unique<flow::access::Account>(response.account());
    }
    
    return account;
}

std::unique_ptr<flow::access::Account> FlowClient::GetAccountAtBlockHeight(::grpc::ClientContext* context, const std::string& address, uint64_t height) {
    flow::access::GetAccountAtBlockHeightRequest request;
    flow::access::AccountResponse response;
    std::unique_ptr<flow::access::Account> account;

    request.set_address(address);
    request.set_block_height(height);

    ::grpc::Status status = stub_->GetAccountAtBlockHeight(context, request, &response);
    if (status.ok()) {
        if (response.has_account())
            account = std::make_unique<flow::access::Account>(response.account());
    }

    return account;
    
}

flow::access::ExecuteScriptResponse* FlowClient::ExecuteScriptAtLatestBlock(::grpc::ClientContext* context, const char* script) {
    flow::access::ExecuteScriptAtLatestBlockRequest request;
    flow::access::ExecuteScriptResponse* response;

    request.set_script(script);

    ::grpc::Status status = stub_->ExecuteScriptAtLatestBlock(context, request, response);
    if (status.ok()) {
        return response;
    } else {
        return nullptr;
    }
}

flow::access::ExecuteScriptResponse* FlowClient::ExecuteScriptAtBlockID(::grpc::ClientContext* context, const char* script, const std::string& id) {
    flow::access::ExecuteScriptAtBlockIDRequest request;
    flow::access::ExecuteScriptResponse* response;

    request.set_block_id(id);
    request.set_script(script);

    ::grpc::Status status = stub_->ExecuteScriptAtBlockID(context, request, response);
    if (status.ok()) {
        return response;
    } else {
        return nullptr;
    }
}

flow::access::ExecuteScriptResponse* FlowClient::ExecuteScriptAtBlockHeight(::grpc::ClientContext* context, const char* script, uint64_t height) {
    flow::access::ExecuteScriptAtBlockHeightRequest request;
    flow::access::ExecuteScriptResponse* response;

    request.set_block_height(height);
    request.set_script(script);

    ::grpc::Status status = stub_->ExecuteScriptAtBlockHeight(context, request, response);
    if (status.ok()) {
        return response;
    } else {
        return nullptr;
    }
}

std::vector<::flow::access::EventsResponse_Result> FlowClient::GetEventsForHeightRange(::grpc::ClientContext* context, uint64_t start_height, uint64_t end_height) {
    flow::access::GetEventsForHeightRangeRequest request;
    flow::access::EventsResponse response;
    std::vector<::flow::access::EventsResponse_Result> events;

    request.set_start_height(start_height);
    request.set_end_height(end_height);

    ::grpc::Status status = stub_->GetEventsForHeightRange(context, request, &response);
    if (status.ok()) {
        if (response.results_size() > 0) {

            for (int idx = 0; idx < response.results_size(); idx++)
                events.emplace_back(response.results(idx));
        }
    }

    return events;
}

std::vector<::flow::access::EventsResponse_Result> FlowClient::GetEventsForBlockIDs(::grpc::ClientContext* context, int index, const std::string& id) {
    flow::access::GetEventsForBlockIDsRequest request;
    flow::access::EventsResponse response;
    std::vector<::flow::access::EventsResponse_Result> events;

    request.set_block_ids(index, id);

    ::grpc::Status status = stub_->GetEventsForBlockIDs(context, request, &response);
    if (status.ok()) {
        if (response.results_size() > 0) {

            for (int idx = 0; idx < response.results_size(); idx++)
                events.emplace_back(response.results(idx));
        }
    }

    return events;
}

std::string FlowClient::GetNetworkParameters(::grpc::ClientContext* context) {
    flow::access::GetNetworkParametersRequest request;
    flow::access::GetNetworkParametersResponse response;

    ::grpc::Status status = stub_->GetNetworkParameters(context, request, &response);
    if (status.ok()) {
        return response.chain_id();
    } else {
        return nullptr;
    }
}

std::string FlowClient::GetLatestProtocolStateSnapshot(::grpc::ClientContext* context) {
    flow::access::GetLatestProtocolStateSnapshotRequest request;
    flow::access::ProtocolStateSnapshotResponse response;

    ::grpc::Status status = stub_->GetLatestProtocolStateSnapshot(context, request, &response);
    if (status.ok()) {
        return response.serializedsnapshot();
    } else {
        return nullptr;
    }
}

std::unique_ptr<flow::access::ExecutionResult> FlowClient::ExecutionResultForBlockID(::grpc::ClientContext* context, const std::string& id) {
    flow::access::GetExecutionResultForBlockIDRequest request;
    flow::access::ExecutionResultForBlockIDResponse response;
    std::unique_ptr<flow::access::ExecutionResult> result;

    request.set_block_id(id);

    ::grpc::Status status = stub_->GetExecutionResultForBlockID(context, request, &response);
    if (status.ok()) {
        if (response.has_execution_result())
            result = std::make_unique<flow::access::ExecutionResult>(response.execution_result());
    }
            
    return result;
}


// Handle errors in a better way. Use nullptr to initialize or make separate error types for response and status
// Should std::unique_ptr be used to deal with memory leaks and std:shared_ptr be used for thread safety?
// We can choose return types and function arguments in client, so we should parse the response properly before sending the result to the caller code
// Take care of overloads in request format and request methods. Can use templates for this purpose
// Handle destruction, cleaning of objects and memory leaks
// Implement another layer of client operations, which will contain sync and async calls, and services such as create account, etc. Will use the crypto module
