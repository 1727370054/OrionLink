#ifndef AUTH_SERVER_H
#define AUTH_SERVER_H

#include "service.h"

class AuthService : public Service
{
public:
	void main(int argc, char* argv[]);

	virtual ServiceHandle* CreateServiceHandle() override;
};

#endif // AUTH_SERVER_H

