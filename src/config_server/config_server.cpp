#include "config_server.h"
#include "config_handle.h"
#include "thread_pool.h"
#include "register_client.h"
#include "tools.h"

#include <string>

using namespace std;

void ConfigServer::main(int argc, char* argv[])
{
    ConfigHandle::RegisterMsgCallback();

    /// 注册中心的配置
    string register_ip = "127.0.0.1";
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
    RegisterClient::GetInstance()->RegisterService(CONFIG_NAME, NULL, port);
}

ServiceHandle* ConfigServer::CreateServiceHandle()
{
    return new ConfigHandle();
}
