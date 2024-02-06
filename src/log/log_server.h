#ifndef LOG_SERVER_H
#define LOG_SERVER_H

#include "service.h"

class LogServer : public Service
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 根据命令行参数，初始化服务，需要先调用
    void main(int argc, char* argv[]);

    virtual ServiceHandle* CreateServiceHandle() override;
};

#endif // LOG_SERVER_H

