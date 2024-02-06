#include <iostream>

#include "download_service.h"

using namespace std;

int main(int argc, char *argv[])
{
	DownloadService service;
	service.main(argc, argv);
	service.Start();
	service.Wait();
	return 0;
}

