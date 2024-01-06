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

    /// ע�����ĵ�����
    string register_ip = "127.0.0.1";
    if (argc > 1)
        register_ip = argv[1];

    int register_port = REGISTER_PORT;
    if (argc > 2)
        register_port = atoi(argv[2]);

    /// �������Ķ˿�
    int port = CONFIG_PORT;
    if (argc > 3)
        port = std::atoi(argv[3]);
    /// ���÷�������˿�
    set_server_port(port);

    /// ��ע������ע�����
    RegisterClient::GetInstance()->RegisterService(CONFIG_NAME, NULL, port);
}

ServiceHandle* ConfigServer::CreateServiceHandle()
{
    return new ConfigHandle();
}
