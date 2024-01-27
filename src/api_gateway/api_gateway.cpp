#include <iostream>

#include "log_client.h"
#include "tools.h"
#include "router_service.h"
#include "service_proxy.h"
#include "config_client.h"
#include "register_client.h"
#include "msg_comm.pb.h"

using namespace std;
using namespace msg;

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

    /// 连接配置中心，获取配置(只取第一个配置中心的IP)
    auto confs = RegisterClient::GetInstance()->GetServices(CONFIG_NAME, 5);
    LOGDEBUG(confs.DebugString());
    if (confs.service_size() <= 0)
    {
        LOGERROR("can`t find the config service");
    }
    else
    {
        auto conf = confs.service()[0];
        static GatewayConfig config;
        int ret = ConfigClient::GetInstance()->StartGetConf(conf.ip().c_str(), conf.port(), 
            0, service.server_port(), &config);
        if (ret)
        {
            LOGINFO("连接配置中心成功!");
        }
    }

    /// 开启服务运行，接收客户端的连接
    service.Start();
    service.Wait();
    return 0;
}

