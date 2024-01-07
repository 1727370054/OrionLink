#include <iostream>

#include "tools.h"
#include "router_service.h"
#include "service_proxy.h"

using namespace std;

static void Usage(const char* arg)
{
    stringstream ss;
    ss << arg << " <register_ip> <register_port> <router_port>";
    cout << ss.str() << endl;
}

int main(int argc, char*argv[])
{
    Usage(argv[0]);
   
    RouterService service;
    service.main(argc, argv);
    /// 开启自动重连的线程，定时向注册中心请求微服务列表，与微服务建立连接
    ServiceProxy::GetInstance()->Start();
    service.Start();
    service.Wait();
    return 0;
}

