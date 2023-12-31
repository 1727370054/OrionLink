#ifndef SERVICE_H
#define SERVICE_H

#include "task.h"
#include "service_handle.h"
#include "thread_pool.h"

class XCOM_API Service : public Task
{
public:
    Service();
    ~Service();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 每个连接进入，调用该函数创建处理对象，加入到线程池
    /// @return 返回具体任务对象
    ///////////////////////////////////////////////////////////////////////////
    virtual ServiceHandle* CreateServiceHandle() = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 微服务初始化，由线程池线程调用
    /// @return 初始化是否成功
    ///////////////////////////////////////////////////////////////////////////
    virtual bool Init() override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 初始化线程池，将监听任务派发到监听事件线程池中，线程回调该类的 Init 
    /// @return 初始化是否成功
    ///////////////////////////////////////////////////////////////////////////
    bool Start();

    void ListenCallback(int client_socket,struct sockaddr* client_addr, int socklen);

    void set_server_port(int port) { server_port_ = port; }

private:
    /// 接收用户连接的线程池
    ThreadPool* thread_listen_pool_ = nullptr;
    /// 处理用户数据线程池
    ThreadPool* thread_handle_pool_ = nullptr;
    /// 处理用户数据线程池，线程数量
    int thread_count_ = 10;

    int server_port_ = 0;
};

#endif // SERVICE_H

