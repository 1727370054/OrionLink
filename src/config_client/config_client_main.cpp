#include <iostream>

#include "config_client.h"
#include "register_client.h"
#include "msg_comm.pb.h"

using namespace std;
using namespace msg;

#define REG RegisterClient::GetInstance()
#define CONF ConfigClient::GetInstance()

void ConfigTimer()
{
	static string conf_ip = "";
	static int conf_port = 0;
	/** 获取配置项***********************************************************************/
	cout << "root: " << CONF->GetString("root") << endl;
	if (conf_port <= 0)
	{
		/// 从注册中心获取配置中心的IP的端口
		auto confs = REG->GetServices(CONFIG_NAME, 2);
		cout << confs.DebugString() << endl;
		if (confs.service_size() <= 0) return;
		auto conf = confs.service()[0];
		if (conf.ip().empty() || conf.port() <= 0) return;

		conf_ip = conf.ip();
		conf_port = conf.port();
		CONF->set_server_ip(conf_ip.c_str());
		CONF->set_server_port(conf_port);
		CONF->Connect();
	}
}

int main(int argc, char *argv)
{
	int client_port = 4000;
	/// 向注册中心注册ip和端口
	REG->set_server_ip("127.0.0.1");
	REG->set_server_port(REGISTER_PORT);
	REG->RegisterService("test_client", NULL, client_port);

	/// 初始化配置中心
	DirConfig tmp_conf;
	CONF->StartGetConf(0, client_port, &tmp_conf, ConfigTimer);
	CONF->WaitConnected(2);

	/** 存储配置项***********************************************************************/
	string proto;
	auto message = CONF->LoadProto("msg_comm.proto", "DirConfig", proto);
	if (!message)
	{
		cerr << "CONF->LoadProto xmsg_com.proto failed!" << endl;
		return -3;
	}
	/// 通过反射设置值
	auto ref = message->GetReflection();
	auto field = message->GetDescriptor()->FindFieldByName("root");
	ref->SetString(message, field, "/root/test/");
	cout << message->GetDescriptor()->DebugString() << endl;

	msg::Config save_conf;
	save_conf.set_service_name("test_config");
	save_conf.set_service_port(client_port);
	save_conf.set_protocol(proto.c_str());
	string pb = message->SerializeAsString();
	save_conf.set_private_pb(pb.c_str());
	CONF->SendConfigReq(&save_conf);

	/** 获取配置列表**********************************************************************/
	for (;;)
	{
		auto config_list = CONF->GetAllConfig(1, 1000, 10);
		cout << config_list.DebugString() << endl;
		if (config_list.configs_size() <= 0)
		{
			this_thread::sleep_for(2s);
			continue;
		}
		/// 获取单个配置信息
		string ip = config_list.configs()[0].service_ip();
		int port = config_list.configs()[0].service_port();
		CONF->LoadConfigReq(ip.c_str(), port);
		Config one_config;
		CONF->GetConfig(ip.c_str(), port, &one_config);
		cout << "=================================" << endl;
		cout << one_config.DebugString() << endl;
		this_thread::sleep_for(2s);
	}
#if 0
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
	auto confs = ConfigClient::GetInstance()->GetAllConfig(2, 1, 10);
	cout << confs.DebugString() << endl;
#endif
	ConfigClient::GetInstance()->Wait();
	return 0;
}

