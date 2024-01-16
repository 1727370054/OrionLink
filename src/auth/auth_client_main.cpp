#include <iostream>

#include "auth_client.h"

using namespace std;

int main(int argc, char *argv[])
{
	AuthClient* client = new AuthClient();
	client->set_server_port(AUTH_PORT);
	client->set_server_ip("127.0.0.1");
	client->StartConnect();
	client->WaitConnected(3);
	client->LoginReq("root", "123456");
	client->Wait();
	return 0;
}

