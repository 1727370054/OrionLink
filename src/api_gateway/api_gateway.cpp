#include <iostream>

#include "tools.h"
#include "router_service.h"
#include "thread_pool.h"
#include "service_proxy.h"

using namespace std;

int main(int argc, char*argv[])
{
    int router_port = API_GATEWAY_PORT;
    if (argc > 1)
    {
        router_port = atoi(argv[1]);
    }
    ServiceProxy::GetInstance()->Init();
    ServiceProxy::GetInstance()->Start();
    RouterService service;
    service.set_server_port(router_port);
    service.Start();
    ThreadPool::Wait();
    return 0;
}

