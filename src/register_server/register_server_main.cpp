#include <iostream>

#include "register_server.h"

using namespace std;

int main(int argc, char*argv[])
{
	RegisterServer server;
	server.main(argc, argv);
	server.Start();
	server.Wait();
	return 0;
}