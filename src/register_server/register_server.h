#ifndef REGISTER_SERVER_H
#define REGISTER_SERVER_H

#include "service.h"

class RegisterServer : public Service
{
public:

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 根据命令行参数，初始化服务，需要先调用
    void main(int argc, char* argv[]);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 每个连接进入，调用该函数创建处理对象，加入到线程池
    /// @return 返回具体任务对象
    ///////////////////////////////////////////////////////////////////////////
    virtual ServiceHandle* CreateServiceHandle() override;
};

#endif // REGISTER_SERVER_H

