#include <iostream>

#include "config_client.h"
#include "msg_comm.pb.h"

using namespace std;
using namespace msg;

int main(int argc, char *argv)
{
	ConfigClient::RegisterMsgCallback();
	ConfigClient::GetInstance()->set_server_ip("127.0.0.1");
	ConfigClient::GetInstance()->set_server_port(CONFIG_PORT);
	ConfigClient::GetInstance()->StartConnect();
	ConfigClient::GetInstance()->WaitConnected(10);
	Config config;
	config.set_service_name("test_name1");
	config.set_service_ip("127.0.0.1");
	config.set_service_port(20030);
	config.set_protocol("message");
	config.set_private_pb("test pb");
	ConfigClient::GetInstance()->SendConfigReq(&config);
	ConfigClient::GetInstance()->Wait();
	return 0;
}

