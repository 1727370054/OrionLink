#include <iostream>

#include "dir_service.h"

using namespace std;

int main(int argc, char*argv[])
{
	DirService service;
	service.main(argc, argv);
	service.Start();
	service.Wait();
	return 0;
}

