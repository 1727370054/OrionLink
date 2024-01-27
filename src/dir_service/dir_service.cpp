#include "dir_service.h"
#include "dir_handle.h"
#include "register_client.h"
#include "tools.h"

#include <string>

using namespace std;

void DirService::main(int argc, char* argv[])
{
    DirHandle::RegisterMsgCallback();
    string register_ip = GetHostByName(OL_REGISTER_SERVER_NAME);
    if (argc > 1)
    {
        register_ip = argv[1];
    }
    int register_port = REGISTER_PORT;
    if (argc > 2)
    {
        register_port = atoi(argv[2]);
    }
    int dir_port = DIR_PORT;
    if (argc > 3)
    {
        dir_port = atoi(argv[3]);
    }
    /// 设置服务监听的端口
    set_server_port(dir_port);

    /// 设置注册中心的IP和端口
    RegisterClient::GetInstance()->set_server_ip(register_ip.c_str());
    RegisterClient::GetInstance()->set_server_port(register_port);
    /// 注册到注册中心
    RegisterClient::GetInstance()->RegisterService(DIR_NAME, NULL, dir_port);
    /// 等待注册中心连接
    RegisterClient::GetInstance()->WaitConnected(3);
}

ServiceHandle* DirService::CreateServiceHandle()
{
    return new DirHandle();
}
