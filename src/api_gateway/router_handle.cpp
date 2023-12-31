#include "router_handle.h"
#include "service_proxy.h"
#include "tools.h"

void RouterHandle::ReadCallback(msg::MsgHead* head, Msg* msg)
{
    /// ת����Ϣ
    LOGDEBUG("RouterHandle::ReadCallback");
    ServiceProxy::GetInstance()->SendMsg(head, msg, this);
}

void RouterHandle::Close()
{
    MsgEvent::Close();
    ServiceProxy::GetInstance()->DeleteEvent(this);
}