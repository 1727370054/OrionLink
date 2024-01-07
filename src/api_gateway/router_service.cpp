#include "router_service.h"
#include "router_handle.h"
#include "register_client.h"

#include <string>

using namespace std;

void RouterService::main(int argc, char* argv[])
{
    string register_ip = "127.0.0.1";
    if (argc > 1)
    {
        register_ip = argv[1];
    }
    int register_port = REGISTER_PORT;
    if (argc > 2)
    {
        register_port = atoi(argv[2]);
    }
    int router_port = API_GATEWAY_PORT;
    if (argc > 3)
    {
        router_port = atoi(argv[3]);
    }
    /// 设置API网关监听的端口
    set_server_port(router_port);

    /// 设置注册中心的IP和端口
    RegisterClient::GetInstance()->set_server_ip(register_ip.c_str());
    RegisterClient::GetInstance()->set_server_port(register_port);
    /// 注册到注册中心
    RegisterClient::GetInstance()->RegisterService(API_GATEWAY_NAME, NULL, router_port);
    /// 等待注册中心连接
    RegisterClient::GetInstance()->WaitConnected(3);
}

ServiceHandle* RouterService::CreateServiceHandle()
{
    return new RouterHandle();
}
