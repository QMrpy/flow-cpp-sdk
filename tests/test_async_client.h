#ifndef TEST_ASYNC_CLIENT_H
#define TEST_ASYNC_CLIENT_H

#include "../client/client_async.h"
#include "../convert/convert.h"
#include <assert.h>

void test_async_client(const std::shared_ptr< ::grpc::ChannelInterface> channel, const grpc::StubOptions& options);

#endif