#include <iostream>

#include "tools.h"
#include "msg_comm.pb.h"
#include "config_server.h"

using namespace std;
using namespace msg;

static void Usage(const char *arg)
{
	stringstream ss;
	ss << arg << " <register_ip> <register_port> <config_port>";
	cout << ss.str() << endl;
}

int main(int argc, char *argv[])
{
	Usage(argv[0]);
	ConfigServer config;
	config.main(argc, argv);
	config.Start();
	config.Wait();
#if 0
	if (!ConfigDao::GetInstance()->Init("127.0.0.1", "root", "HWK5326282003@mysql", "orion_link", 3306))
	{
		return -1;
	}
	LOGINFO("connect mysql success!");

	/// 测试安装
	ConfigDao::GetInstance()->Install();

	/// 测试配置保存
	Config config;
	config.set_service_name("test1");
	config.set_service_ip("127.0.0.1");
	config.set_service_port(20050);
	config.set_protocol("messge Test{string name = 1;}");
	string pb = config.SerializeAsString();
	config.set_private_pb(pb.c_str());
	ConfigDao::GetInstance()->SaveConfig(&config);

	/// 测试读取配置
	Config read_config = ConfigDao::GetInstance()->LoadConfig("127.0.0.1", 20050);
	LOGDEBUG(read_config.DebugString().c_str());
#endif
	return 0;
}
