#ifndef SERVICE_PROXY_CLIENT_H
#define SERVICE_PROXY_CLIENT_H

#include "service_client.h"

#include <map>
#include <mutex>

class ServiceProxyClient : public ServiceClient
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收了微服务的反馈，消息转发给对应的 RouterHandle（该函数重写 MsgEvent 的虚函数）
    /// @param head 反序列化后消息头部
    /// @param msg 序列化的消息内容
    virtual void ReadCallback(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 该客户端消息先和 RouterHandle 进行关联，再路由转发到微服务集群
    /// @param head 消息头部
    /// @param msg 序列化的消息内容
    /// @param event RouterHandle 对象
    /// @return 发送成功返回true，否则相反
    ///////////////////////////////////////////////////////////////////////////
    bool SendMsg(msg::MsgHead* head, Msg* msg, MsgEvent* event);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 注册一个事件 (RouterHandle) (每个客户端对应一个 RouterHandle)
    /// @param event 事件对象指针
    void RegisterEvent(MsgEvent* event);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 删除一个事件 (RouterHandle)
    /// @param event 事件对象指针
    void DeleteEvent(MsgEvent* event);

private:
    /// 消息转发的对象，一个 proxy 对应多个 MsgEvent
    /// 用指针的置作为索引，要兼容64位
    static std::map<long long, MsgEvent*> callback_task_;
    static std::mutex callback_task_mutex_;
};

#endif // SERVICE_PROXY_CLIENT_H

