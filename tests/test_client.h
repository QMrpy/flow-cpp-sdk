#ifndef TEST_CLIENT_H
#define TEST_CLIENT_H

#include <assert.h>

#include "../client/client.h"
#include "../convert/convert.h"

void test_client(const std::shared_ptr< ::grpc::ChannelInterface> channel, const grpc::StubOptions& options);

#endif