#include "log_client.h"
#include "service_proxy_client.h"
#include "tools.h"

void ServiceProxyClient::ReadCallback(msg::MsgHead* head, Msg* msg)
{
    if (!head || !msg) return;
    LOGDEBUG("ServiceProxyClient::ReadCallback");
    /// 通过 RouterHandle 将消息转发给客户端
    /// ServiceProxyClient 每个对象可能关联多个 RouterHandle，
    /// 一个客户端，对应一个 RouterHandle 对象
 
    Mutex lock(&callback_task_mutex_);
    auto router = callback_task_.find(head->router_id());
    if (router == callback_task_.end())
    {
        LOGDEBUG("callback_task_ can't find");
        return;
    }

    router->second->SendMsg(head, msg);
}

bool ServiceProxyClient::SendMsg(msg::MsgHead* head, Msg* msg, MsgEvent* event)
{
    RegisterEvent(event);
    {
        Mutex lock(&callback_task_mutex_);
        if (event) head->set_router_id((long long)event);
    }
    return MsgEvent::SendMsg(head, msg);
}

void ServiceProxyClient::RegisterEvent(MsgEvent* event)
{
    Mutex lock(&callback_task_mutex_);
    callback_task_[(long long)event] = event;
}

void ServiceProxyClient::DeleteEvent(MsgEvent* event)
{
    Mutex lock(&callback_task_mutex_);
    callback_task_.erase((long long)event);
}
