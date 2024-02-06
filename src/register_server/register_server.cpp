#include "register_server.h"
#include "register_handle.h"
#include "thread_pool.h"
#include "tools.h"

void RegisterServer::main(int argc, char* argv[])
{
    RegisterHandle::RegisterMsgCallback();
    int port = REGISTER_PORT;
    if (argc > 1)
        port = std::atoi(argv[1]);
    set_server_port(port);
}

ServiceHandle* RegisterServer::CreateServiceHandle()
{
    auto handle = new RegisterHandle();
    /// 设置超时时间用于接收心跳包
    handle->set_read_timeout_ms(5000);
    return handle;
}

