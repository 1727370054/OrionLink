#include "router_service.h"
#include "router_handle.h"
#include "register_client.h"
#include "config_client.h"
#include "ssl_ctx.h"

#include <string>

using namespace std;

void RouterService::main(int argc, char* argv[])
{
    string register_ip = "127.0.0.1";
    if (argc > 1)
    {
        register_ip = argv[1];
    }
    int register_port = REGISTER_PORT;
    if (argc > 2)
    {
        register_port = atoi(argv[2]);
    }
    int router_port = API_GATEWAY_PORT;
    if (argc > 3)
    {
        router_port = atoi(argv[3]);
    }
    /// 设置API网关监听的端口
    set_server_port(router_port);

    /// 设置注册中心的IP和端口
    RegisterClient::GetInstance()->set_server_ip(register_ip.c_str());
    RegisterClient::GetInstance()->set_server_port(register_port);
    /// 注册到注册中心
    RegisterClient::GetInstance()->RegisterService(API_GATEWAY_NAME, NULL, router_port);
    /// 等待注册中心连接
    RegisterClient::GetInstance()->WaitConnected(3);
}

ServiceHandle* RouterService::CreateServiceHandle()
{
    auto router = new RouterHandle();
    bool is_ssl = ConfigClient::GetInstance()->GetBool("is_ssl");
    if (!is_ssl)
        return router;

    /// 已经设置过，暂时不考虑修改
    if (ssl_ctx())
        return router;

    auto ctx = new SSLCtx();
    if (ctx == nullptr)  return router;
    string crt_path = ConfigClient::GetInstance()->GetString("crt_path");
    string key_path = ConfigClient::GetInstance()->GetString("key_path");
    string ca_path = ConfigClient::GetInstance()->GetString("ca_path");
    ctx->InitServer(crt_path.c_str(), key_path.c_str(), ca_path.c_str());
    this->set_ssl_ctx(ctx);
    return router;
}
