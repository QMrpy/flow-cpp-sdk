#include "test_async_client.h"

void test_async_client(const std::shared_ptr< ::grpc::ChannelInterface> channel, const grpc::StubOptions& options) {
    AsyncFlowClient client(channel, options);

    /** Test AsyncPing **/
    grpc::ClientContext *context = new grpc::ClientContext();
    std::cout << "AsyncPing Server" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    ::grpc::Status status = client.AsyncPing(context);

    if (status.ok()) {
        std::cout << "Server is alive and responding." << std::endl;
    } else {
        std::cout << "Failed to ping server." << std::endl;
    }

    /** Test GetLatestBlock (sealed)**/
    new (context) grpc::ClientContext;
    std::cout << std::endl << "AsyncGetLatestBlock" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    flow::access::Block* latest_block = client.AsyncGetLatestBlock(context, true);

    if (latest_block) {
        std::cout << "Block ID: " << ConvertResponse().get_sha256_from_raw_bytes(latest_block->id()) << std::endl;
        std::cout << "Block Height: " << latest_block->height() << std::endl;
        std::cout << "Block Timestamp (seconds): " << latest_block->timestamp().seconds() << std::endl;
    } else {
        std::cout << "Failed to retrieve latest block. Exiting..." << std::endl;
        std::exit(0);
    }
}
