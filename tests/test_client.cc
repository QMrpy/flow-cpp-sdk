#include "../client/client.h"
#include "../convert/convert.h"
#include <assert.h>

int main() {
    const std::shared_ptr< ::grpc::ChannelInterface> channel = grpc::CreateChannel("127.0.0.1:3569", grpc::InsecureChannelCredentials());
    const grpc::StubOptions options;

    FlowClient client(channel, options);

    /** Test Ping **/
    grpc::ClientContext *context = new grpc::ClientContext();
    std::cout << "Ping Server" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    ::grpc::Status status = client.Ping(context);

    if (status.ok()) {
        std::cout << "Server is alive and responding." << std::endl;
    } else {
        std::cout << "Failed to ping server." << std::endl;
    }

    /** Test GetLatestBlock (sealed)**/
    new (context) grpc::ClientContext;
    std::cout << std::endl << "GetLatestBlock" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    flow::access::Block* latest_block = client.GetLatestBlock(context, true);

    if (latest_block) {
        std::cout << "Block ID: " << ConvertResponse().get_sha256_from_raw_bytes(latest_block->id()) << std::endl;
        std::cout << "Block Height: " << latest_block->height() << std::endl;
        std::cout << "Block Timestamp (seconds): " << latest_block->timestamp().seconds() << std::endl;
    } else {
        std::cout << "Failed to retrieve latest block. Exiting..." << std::endl;
        std::exit(0);
    }
    
    /** Test GetBlockByID using latest block **/
    new (context) grpc::ClientContext;
    std::cout << std::endl << "GetBlockByID" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    flow::access::Block* block_by_id = client.GetBlockByID(context, latest_block->id());
    
    if (block_by_id) {
        std::cout << "Block ID: " << ConvertResponse().get_sha256_from_raw_bytes(block_by_id->id()) << std::endl;
        std::cout << "Block Height: " << block_by_id->height() << std::endl;
        std::cout << "Block Timestamp (seconds): " << block_by_id->timestamp().seconds() << std::endl;

        assert(latest_block->height() == block_by_id->height() && "GetLatestBlock and GetBlockByID returned different blocks. Error!!\n");
    } else {
        std::cout << "Failed to retrieve block by ID." << std::endl;
    }

    /** Test GetBlockHeaderByID using latest block **/
    new (context) grpc::ClientContext;
    std::cout << std::endl << "GetBlockHeaderByID" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    flow::access::BlockHeader* blockheader_by_id = client.GetBlockHeaderByID(context, latest_block->id());

    if (block_by_id) {
        std::cout << "Block ID: " << ConvertResponse().get_sha256_from_raw_bytes(blockheader_by_id->id()) << std::endl;
        std::cout << "Block Height: " << blockheader_by_id->height() << std::endl;

        assert(latest_block->height() == blockheader_by_id->height() && "GetLatestBlock and GetBlockHeaderByID returned different blocks. Error!!\n");
    } else {
        std::cout << "Failed to retrieve block header by ID." << std::endl;
    }

    return 0;
}
