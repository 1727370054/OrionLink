#include "log_client.h"
#include "router_handle.h"
#include "service_proxy.h"
#include "tools.h"

void RouterHandle::ReadCallback(msg::MsgHead* head, Msg* msg)
{
    /// 转发消息
    LOGDEBUG("RouterHandle::ReadCallback");
    ServiceProxy::GetInstance()->SendMsg(head, msg, this);
}

void RouterHandle::Close()
{
    ServiceProxy::GetInstance()->DeleteEvent(this);
    MsgEvent::Close();
}