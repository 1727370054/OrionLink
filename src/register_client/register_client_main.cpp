#include <iostream>
#include <string>
#include <thread>

#include "register_client.h"
#include "tools.h"

using namespace std;

int main(int argc, char *argv[])
{
	string ip = "127.0.0.1";
	int port = REGISTER_PORT;
	if (argc > 1)
		ip = argv[1];
	if (argc > 2)
		port = atoi(argv[2]);
	RegisterClient::GetInstance()->set_server_ip(ip.c_str());
	RegisterClient::GetInstance()->set_server_port(port);
	RegisterClient::GetInstance()->RegisterService("test", 0, 20020);
	RegisterClient::GetInstance()->WaitConnected(3);
	//RegisterClient::GetInstance()->GetServiceListReq(NULL);
	//RegisterClient::GetInstance()->GetServiceListReq("test");
	//RegisterClient::GetInstance()->Wait();

	for (;;)
	{
		// RegisterClient::GetInstance()->GetServiceListReq("test");
		RegisterClient::GetInstance()->GetServiceListReq(NULL);
		std::this_thread::sleep_for(1000ms);
		auto services = RegisterClient::GetInstance()->GetAllServiceList();
		if (services)
			LOGDEBUG(services->DebugString().c_str());
		//auto services = RegisterClient::GetInstance()->GetServices("test", 1);
		//if (services.service_size() > 0)
		//	LOGDEBUG(services.DebugString());
		std::this_thread::sleep_for(5000ms);
	}

	RegisterClient::GetInstance()->Wait();
	return 0;
}
