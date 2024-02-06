#include <iostream>

#include "upload_service.h"

using namespace std;

int main(int argc, char*argv[])
{
	UploadService service;
	service.main(argc, argv);
	service.Start();
	service.Wait();
	return 0;
}

