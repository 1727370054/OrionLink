#include "auth_server.h"
#include "auth_dao.h"
#include "auth_handle.h"
#include "register_client.h"
#include "tools.h"

#include <string>

using namespace std;

void AuthService::main(int argc, char* argv[])
{
	AuthHandle::RegisterMsgCallback();

    /// 注册中心的配置
    string register_ip = "127.0.0.1";
    if (argc > 1)
        register_ip = argv[1];

    int register_port = REGISTER_PORT;
    if (argc > 2)
        register_port = atoi(argv[2]);

    /// 鉴权中心端口
    int port = AUTH_PORT;
    if (argc > 3)
        port = std::atoi(argv[3]);
    /// 设置服务监听端口
    set_server_port(port);

    /// 向注册中心注册服务
    /// 设置注册中心的IP和端口
    RegisterClient::GetInstance()->set_server_ip(register_ip.c_str());
    RegisterClient::GetInstance()->set_server_port(register_port);
    RegisterClient::GetInstance()->RegisterService(AUTH_NAME, NULL, port);

    if (!AuthDAO::GetInstance()->Init())
    {
        LOGDEBUG("init SQL failed!");
        exit(-1);
    }

    if (!AuthDAO::GetInstance()->Install())
    {
        LOGDEBUG("Install SQL table failed!");
        exit(-2);
    }
	LOGINFO("init SQL success!");
}

ServiceHandle* AuthService::CreateServiceHandle()
{
    return new AuthHandle();
}

