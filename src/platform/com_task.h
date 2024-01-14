#ifndef COM_TASH_H
#define COM_TASH_H

#include "task.h"
#include "msg.h"

#include <string>

class SSLCtx;

class XCOM_API ComTask : public Task
{
public:
    ComTask();
    virtual ~ComTask();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 创建 bufferevent 并设置回调函数
    /// @return 初始化是否成功
    ///////////////////////////////////////////////////////////////////////////
    virtual bool Init() override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 关闭 bufferevent, 清理消息缓冲数据和任务对象
    virtual void Close();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 连接服务器，考虑自动重连
    /// @return 连接是否成功
    ///////////////////////////////////////////////////////////////////////////
    virtual bool Connect();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 客户端连接成功的回调，由业务类重写
    virtual void ConnectCallback(){};

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 读事件就绪回调函数，MsgEvent 类重写
    virtual void ReadCallback() = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 激活写入回调
    virtual void TriggerWrite();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 写事件就绪回调函数，业务类重写
    virtual void WriteCallback(){};

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 事件回调函数
    /// @param what 事件类型
    virtual void EventCallback(short what);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 由pb层调用函数，读取网络中序列化后的数据
    /// @param data 内容数据
    /// @param size 数据大小
    int Read(void *data, int size);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 由pb层调用函数，写入序列化后的数据
    /// @param data 内容数据
    /// @param size 数据大小
    virtual bool Write(const void *data, int size);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 等待连接成功
    /// @param timeout_sec 最大等待时间
    bool WaitConnected(int timeout_sec);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 建立连接，如果断开自动重连，直到连接成功或者超时返回
    /// @param timeout_sec 最大等待时间
    bool AutoConnect(int timeout_sec);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 设置定时器，只能设置一个定时器，定时调用TimerCallback回调(在Init函数调用)
    /// @param ms 定时调用的毫秒
    virtual void SetTimer(int ms);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 定时器回调函数
    virtual void TimerCallback() {}

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 设置自动重连的定时器
    /// @param ms 定时调用的毫秒
    virtual void SetAutoConnectTimer(int ms);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 自动重连的定时器回调函数
    virtual void AutoConnectTimerCallback();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 清理所有定时器资源
    virtual void ClearTimer();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 设置SSL通信的上下文，如果设置了，就是使用SLL加密通信
    void set_ssl_ctx(SSLCtx *ssl_ctx) { ssl_ctx_ = ssl_ctx; }
    SSLCtx *ssl_ctx() { return ssl_ctx_; }

    void set_server_ip(const char *ip);
    const char *server_ip() { return server_ip_; }

    void set_server_port(int port) { server_port_ = port; }
    int server_port() { return server_port_; }

    bool is_connecting() { return is_connecting_; }
    bool is_connected() { return is_connected_; }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 是否开启自动清理对象(包含清理定时器资源), 会清理定时器资源(默认开启)
    void set_auto_delete(bool is_auto_delete) { auto_delete_ = is_auto_delete; }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 是否开启自动重连(默认关闭), 需要在对象添加到线程池之前设置
    /// 如果开启自动重连，对象就不能清理
    void set_auto_connect(bool is_auto_connect)
    {
        auto_connect_ = is_auto_connect;
        if (is_auto_connect)
            auto_delete_ = false;
    }

protected:
    /// 文件内容数据缓存区
    char read_buf_[4096];

private:
    bool InitBufferevent(int sock);

    /// SSL通信的上下文
    SSLCtx *ssl_ctx_ = nullptr;

    struct bufferevent *bev_ = nullptr;

    /// 连接断开是否自动清理对象
    bool auto_delete_ = true;

    /// 开启自动重连的开关
    bool auto_connect_ = false;
    /// 定时器事件关闭自动清理对象close时不清理
    struct event *auto_connect_timer_event_ = nullptr;

    /// 服务器IP
    char server_ip_[16] = {0};
    /// 服务器端口
    int server_port_ = 0;

    /// 客户端连接状态
    /// 1 未处理       =>  开始连接(线程池处理)
    /// 2 连接中       =>  等待连接成功
    /// 3 连接成功     =>  开始业务处理
    /// 4 连接后失败   =>  根据连接间隔，再次连接
    bool is_connecting_ = false;
    bool is_connected_ = false;
    std::mutex *mtx_ = nullptr;

    /// 定时器事件关闭自动清理对象close时不清理
    struct event *timer_event_ = nullptr;
};

#endif // COM_TASH_H
