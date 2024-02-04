#include <iostream>
#include <sstream>

#include "auth_server.h"
#include "tools.h"

using namespace std;

static void Usage(const char* arg)
{
	stringstream ss;
	ss << arg << " <register_ip> <register_port> <auth_port>";
	cout << ss.str() << endl;
}

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL)); // 初始化随机数生成器
	Usage(argv[0]);
	AuthService service;
	service.main(argc, argv);
	service.Start();
	service.Wait();
	return 0;
}

