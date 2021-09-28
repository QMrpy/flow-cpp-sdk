#include "tests/test_client.h"
#include "tests/test_async_client.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Run as: ./main <host>[flow-emulator-url|flow-mainnet-url|flow-testnet-url]" << std::endl;
        std::exit(0);
    }
    std::cout << "Creating grpc channel on: " << argv[1] << std::endl;

    const std::shared_ptr< ::grpc::ChannelInterface> channel = grpc::CreateChannel(argv[1], grpc::InsecureChannelCredentials());
    const grpc::StubOptions options;

    std::cout << "Testing Synchronous Flow Client" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    test_client(channel, options);

    std::cout << std::endl << "Testing Asynchronous Flow Client" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    test_async_client(channel, options);

    return 0;
}
