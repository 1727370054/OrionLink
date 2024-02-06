#ifndef UPLOAD_SERVICE_H
#define UPLOAD_SERVICE_H

#include "service.h"

class UploadService : public Service
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 根据命令行参数，初始化服务，需要先调用(连接注册中心注册服务)
    void main(int argc, char* argv[]);

    virtual ServiceHandle* CreateServiceHandle() override;
};

#endif // UPLOAD_SERVICE_H

