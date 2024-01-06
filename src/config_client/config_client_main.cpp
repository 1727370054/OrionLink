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
	msg::Config config;
	config.set_service_name("test_name1");
	config.set_service_ip("127.0.0.1");
	config.set_service_port(20030);
	config.set_protocol("message");
	//string pb = config.SerializeAsString();
	config.set_private_pb("test pb");
	ConfigClient::GetInstance()->SendConfigReq(&config);
	ConfigClient::GetInstance()->LoadConfigReq(NULL, 20030);

	this_thread::sleep_for(500ms);
	Config tmp_conf;
	ConfigClient::GetInstance()->GetConfig("127.0.0.1", 20030, &tmp_conf);
	cout << "tmp_conf: \n" << tmp_conf.DebugString() << endl;

	ConfigClient::GetInstance()->Wait();
	return 0;
}

