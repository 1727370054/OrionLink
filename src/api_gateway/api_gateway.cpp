#include <iostream>

#include "tools.h"
#include "router_service.h"
#include "thread_pool.h"
#include "service_proxy.h"
#include "register_client.h"

using namespace std;

static void Usage(const char* arg)
{
    stringstream ss;
    ss << arg << " <router_port> <register_ip> <register_port>";
    cout << ss.str() << endl;
}

int main(int argc, char*argv[])
{
    int router_port = API_GATEWAY_PORT;
    if (argc > 1)
    {
        router_port = atoi(argv[1]);
        Usage(argv[0]);
    }
    string register_ip = "127.0.0.1";
    if (argc > 2)
    {
        register_ip = argv[2];
    }
    int register_port = REGISTER_PORT;
    if (argc > 3)
    {
        register_port = atoi(argv[3]);
    }
    /// 设置注册中心的IP和端口
    RegisterClient::GetInstance()->set_server_ip(register_ip.c_str());
    RegisterClient::GetInstance()->set_server_port(register_port);
    /// 注册到注册中心
    RegisterClient::GetInstance()->RegisterService(API_GATEWAY_NAME, NULL, router_port);
    /// 等待注册中心连接
    RegisterClient::GetInstance()->WaitConnected(3);

    ServiceProxy::GetInstance()->Start();
    RouterService service;
    service.set_server_port(router_port);
    service.Start();
    ThreadPool::Wait();
    return 0;
}

