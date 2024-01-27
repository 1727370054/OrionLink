#include "log_client.h"
#include "log_server.h"
#include "log_handle.h"
#include "log_dao.h"
#include "tools.h"
#include "register_client.h"

#include <string>

using namespace std;

void LogServer::main(int argc, char* argv[])
{
    LogHandle::RegisterMsgCallback();

    /// 注册中心的配置
    string register_ip = GetHostByName(OL_REGISTER_SERVER_NAME);
    if (argc > 1)
        register_ip = argv[1];

    int register_port = REGISTER_PORT;
    if (argc > 2)
        register_port = atoi(argv[2]);

    /// 日志中心端口
    int port = LOG_PORT;
    if (argc > 3)
        port = std::atoi(argv[3]);
    /// 设置服务监听端口
    set_server_port(port);

    /// 向注册中心注册服务
    /// 设置注册中心的IP和端口
    RegisterClient::GetInstance()->set_server_ip(register_ip.c_str());
    RegisterClient::GetInstance()->set_server_port(register_port);
    RegisterClient::GetInstance()->RegisterService(LOG_NAME, NULL, port);

    if (!LogDAO::GetInstance()->Init())
    {
        LOGDEBUG("init SQL failed!");
        exit(-1);
    }

    if (!LogDAO::GetInstance()->Install())
    {
        LOGDEBUG("Install SQL table failed!");
        exit(-2);
    }
    LOGINFO("init SQL success!");
}

ServiceHandle* LogServer::CreateServiceHandle()
{
    return new LogHandle();
}
