#ifndef TEST_ASYNC_CLIENT_H
#define TEST_ASYNC_CLIENT_H

#include <assert.h>
#include <thread>
#include <functional>

#include "../client/client_async.h"
#include "../convert/convert.h"

void test_async_client(const std::shared_ptr< ::grpc::ChannelInterface> channel, const grpc::StubOptions& options);

#endif