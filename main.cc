#include "tests/test_client.h"
#include "tests/test_async_client.h"

int main(int argc, char *argv[]) {
    std::cout << "Creating grpc channel on: " << argv[1] << std::endl;

    const std::shared_ptr< ::grpc::ChannelInterface> channel = grpc::CreateChannel(argv[1], grpc::InsecureChannelCredentials());
    const grpc::StubOptions options;

    std::cout << "Testing Synchronous Flow Client" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    test_client(channel, options);

    std::cout << "Testing Asynchronous Flow Client" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    test_async_client(channel, options);

    return 0;
}

//Do error checking of argv