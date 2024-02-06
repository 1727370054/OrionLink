#ifndef DIR_SERVICE_H
#define DIR_SERVICE_H

#include "service.h"

class DirService : public Service
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 根据命令行参数，初始化服务，需要先调用(连接注册中心注册服务)
    void main(int argc, char* argv[]);

    virtual ServiceHandle* CreateServiceHandle() override;
};

#endif // DIR_SERVICE_H

