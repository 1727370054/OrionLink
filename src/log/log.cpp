#include <iostream>
#include <string>

#include "log_server.h"

using namespace std;

int main(int argc, char*argv[])
{
	LogServer server;
	server.main(argc, argv);
	server.Start();
	server.Wait();
	return 0;
}

