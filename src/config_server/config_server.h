#ifndef CONFIG_SERVER_H
#define CONFIG_SERVER_H

#include "service.h"

class ConfigServer : public Service
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

#endif // CONFIG_SERVER_H

