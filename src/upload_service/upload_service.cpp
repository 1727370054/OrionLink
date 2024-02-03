#include "upload_service.h"
#include "upload_handle.h"
#include "register_client.h"
#include "tools.h"

using namespace std;

void UploadService::main(int argc, char* argv[])
{
    UploadHandle::RegisterMsgCallback();

    /// 注册中心的配置
    string register_ip = GetHostByName(OL_REGISTER_SERVER_NAME);
    if (argc > 1)
        register_ip = argv[1];

    int register_port = REGISTER_PORT;
    if (argc > 2)
        register_port = atoi(argv[2]);

    /// 上传微服务端口
    int port = UPLOAD_PORT;
    if (argc > 3)
        port = std::atoi(argv[3]);
    /// 设置服务监听端口
    set_server_port(port);

    /// 向注册中心注册服务
    /// 设置注册中心的IP和端口
    RegisterClient::GetInstance()->set_server_ip(register_ip.c_str());
    RegisterClient::GetInstance()->set_server_port(register_port);
    RegisterClient::GetInstance()->RegisterService(UPLOAD_NAME, NULL, port, true);
}

ServiceHandle* UploadService::CreateServiceHandle()
{
    return new UploadHandle();
}
