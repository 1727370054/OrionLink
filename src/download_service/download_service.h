#ifndef DOWNLOAD_SERVICE_H
#define DOWNLOAD_SERVICE_H

#include "service.h"

class DownloadService :public Service
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 根据命令行参数，初始化服务，需要先调用(连接注册中心注册服务)
    void main(int argc, char* argv[]);

    virtual ServiceHandle* CreateServiceHandle() override;
};

#endif // DOWNLOAD_SERVICE_H

