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
    return new RegisterHandle();
}

