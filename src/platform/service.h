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
    /// @brief 开始服务运行，初始化线程池，将监听任务派发到监听事件线程池中
    /// @return 初始化是否成功
    ///////////////////////////////////////////////////////////////////////////
    bool Start();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 阻塞等待线程退出
    void Wait();

    void ListenCallback(int client_socket,struct sockaddr* client_addr, int socklen);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 设置服务器监听的端口号
    void set_server_port(int port) { server_port_ = port; }
    int server_port() { return server_port_; }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 设置SSL通信的上下文，如果设置了，就是使用SLL加密通信
    void set_ssl_ctx(SSLCtx* ssl_ctx) { ssl_ctx_ = ssl_ctx; }
    SSLCtx* ssl_ctx() { return ssl_ctx_; }
private:
    // SSL通信的上下文
    SSLCtx* ssl_ctx_ = nullptr;

    /// 接收用户连接的线程池
    ThreadPool* thread_listen_pool_ = nullptr;
    /// 处理用户数据线程池
    ThreadPool* thread_handle_pool_ = nullptr;
    /// 处理用户数据线程池，线程数量
    int thread_count_ = 10;

    int server_port_ = 0;
};

#endif // SERVICE_H

