#ifndef SERVICE_PROXY_H
#define SERVICE_PROXY_H

#include "service_proxy_client.h"

#include <map>
#include <string>
#include <atomic>
#include <vector>

class ServiceProxy
{
public:
    ~ServiceProxy();

    static ServiceProxy* GetInstance()
    {
        static ServiceProxy service_proxy;
        return &service_proxy;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 负载均衡找到微服务的连接，进行数据发送
    /// @param head 消息头部
    /// @param msg 消息内容
    /// @param event RouterHandle 对象
    /// @return 发送成功返回true，否则相反
    ///////////////////////////////////////////////////////////////////////////
    bool SendMsg(msg::MsgHead* head, Msg *msg, MsgEvent * event);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 清理消息回调
    /// @param event 事件对象指针
    void DeleteEvent(MsgEvent* event);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 开启自动重连的线程，定时向注册中心请求微服务列表，与微服务建立连接
    void Start();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 关闭自动重连的线程
    void Stop();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 自动重连线程回调函数
    void Main();

private:
    ServiceProxy();
    ServiceProxy(const ServiceProxy&) = delete;
    ServiceProxy& operator=(const ServiceProxy&) = delete;

private:
    /// 存放各个微服务连接对象
    std::map<std::string, std::vector<ServiceProxyClient*>> client_map_;
    std::mutex client_map_mutex_;

    /// 记录上一次轮询索引
    std::map<std::string, int> client_map_last_index_;

    /// 用于清理 callback_task_ 缓存 (需要知道 RouterHandle 对应的 ServiceProxyClient
    /// 方便调用对应的 DeleteEvent 函数)
    std::map<MsgEvent*, ServiceProxyClient*> callbacks_;
    std::mutex callbacks_mutex_;

    std::atomic_bool is_exit_ = false;
};

#endif // SERVICE_PROXY_H

