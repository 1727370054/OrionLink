#ifndef ROUTER_SERVICE_H
#define ROUTER_SERVICE_H

#include "service.h"

class RouterService : public Service
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 根据命令行参数，初始化服务，需要先调用
    void main(int argc, char* argv[]);

    virtual ServiceHandle* CreateServiceHandle() override;
};

#endif // ROUTER_SERVICE_H

