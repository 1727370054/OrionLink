#include "log_client.h"
#include "config_server.h"
#include "config_handle.h"
#include "register_client.h"
#include "config_dao.h"
#include "tools.h"

#include <string>

using namespace std;

void ConfigServer::main(int argc, char* argv[])
{
    ConfigHandle::RegisterMsgCallback();

    /// 注册中心的配置
    string register_ip = GetHostByName(OL_REGISTER_SERVER_NAME);
    if (argc > 1)
        register_ip = argv[1];

    int register_port = REGISTER_PORT;
    if (argc > 2)
        register_port = atoi(argv[2]);

    /// 配置中心端口
    int port = CONFIG_PORT;
    if (argc > 3)
        port = std::atoi(argv[3]);
    /// 设置服务监听端口
    set_server_port(port);

    /// 向注册中心注册服务
    /// 设置注册中心的IP和端口
    RegisterClient::GetInstance()->set_server_ip(register_ip.c_str());
    RegisterClient::GetInstance()->set_server_port(register_port);
    RegisterClient::GetInstance()->RegisterService(CONFIG_NAME, NULL, port);

    if (!ConfigDao::GetInstance()->Init())
    {
        LOGDEBUG("init SQL failed!");
        exit(-1);
    }

    if (!ConfigDao::GetInstance()->Install())
    {
        LOGDEBUG("Install SQL table failed!");
        exit(-2);
    }

    LOGINFO("init SQL success!");
}

ServiceHandle* ConfigServer::CreateServiceHandle()
{
    return new ConfigHandle();
}
