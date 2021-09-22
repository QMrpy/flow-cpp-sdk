#include "../client/client.h"

int main() {
    const std::shared_ptr< ::grpc::ChannelInterface> channel = grpc::CreateChannel("127.0.0.1:3569", grpc::InsecureChannelCredentials());
    const grpc::StubOptions options;
    grpc::ClientContext context;

    FlowClient client(channel, options);

    std::cout << "=============Ping Server===========";
    ::grpc::Status status = client.Ping(&context, options);

    if (status.ok()) {
        std::cout << "Server is alive and responding" << "\n";
    } else {
        std::cout << "Failed to ping server" << "\n";
    }

    return 0;
}