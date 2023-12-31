#ifndef COM_TASH_H
#define COM_TASH_H

#include "task.h"
#include "msg.h"

#include <string>

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
    virtual void ConnectCallback() {};

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 读事件就绪回调函数，MsgEvent 类重写
    virtual void ReadCallback() = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 激活写入回调
    virtual void TriggerWrite();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 写事件就绪回调函数，业务类重写
    virtual void WriteCallback() {};

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 事件回调函数 
    /// @param what 事件类型
    virtual void EventCallback(short what);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 由pb层调用函数，读取网络中序列化后的数据
    /// @param data 内容数据
    /// @param size 数据大小
    int Read(void * data, int size);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 由pb层调用函数，写入序列化后的数据
    /// @param data 内容数据
    /// @param size 数据大小
    virtual bool Write(const void* data, int size);

    void set_server_ip(const char* ip);
    void set_port(int port) { server_port_ = port; }
    bool is_connecting() { return is_connecting_; }
    bool is_connected() { return is_connected_; }
protected:
    /// 文件内容数据缓存区
    char read_buf_[4096];

private:
    bool InitBufferevent(int sock);

    struct bufferevent* bev_ = nullptr;

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
    std::mutex* mtx_ = nullptr;
};

#endif // COM_TASH_H

