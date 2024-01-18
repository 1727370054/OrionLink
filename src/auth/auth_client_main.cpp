#include <iostream>

#include "auth_client.h"
#include "msg_comm.pb.h"

using namespace std;
using namespace msg;

int main(int argc, char *argv[])
{
	AuthClient* client = new AuthClient();
	AuthClient::RegisterMsgCallback();
	client->set_auto_delete(false);
	client->set_server_port(AUTH_PORT);
	client->set_server_ip("127.0.0.1");
	client->StartConnect();
	client->WaitConnected(3);

	AddUserReq add_user; 
	add_user.set_username("hwk");
	add_user.set_password("123456");
	add_user.set_rolename("hwk");
	client->AddUserReq(&add_user);

	client->LoginReq("hwk", "123456");

	client->Wait();
	return 0;
}

