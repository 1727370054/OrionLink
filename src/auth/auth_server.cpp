#include <iostream>

#include "service.h"
#include "auth_handle.h"

class AuthService : public Service
{
public:
	virtual ServiceHandle* CreateServiceHandle() override
	{
		return new AuthHandle();
	}

private:

};

int main(int argc, char *argv[])
{
	int server_port = AUTH_PORT;
	if (argc > 1)
	{
		server_port = atoi(argv[1]);
	}
	AuthHandle::RegisterMsgCallback();
	AuthService service;
	service.set_server_port(server_port);
	service.Start();
	service.Wait();
	return 0;
}

