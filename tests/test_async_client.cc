#include "test_async_client.h"

void test_async_client(const std::shared_ptr< ::grpc::ChannelInterface> channel, const grpc::StubOptions& options) {
    AsyncFlowClient client(channel, options);

    /** Test AsynGetLatestBlock (sealed)**/
    std::cout << "AsyncGetLatestBlock" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    std::thread t1(&AsyncFlowClient::AsyncGetLatestBlock, std::ref(client), true);

    /** Test AsyncPing **/
    std::cout << std::endl << "AsyncPing Server" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    std::thread t2(&AsyncFlowClient::AsyncPing, std::ref(client));

    t1.join();
    t2.join();
}
