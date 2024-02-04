#include "log_client.h"
#include "router_handle.h"
#include "service_proxy.h"
#include "auth_proxy.h"
#include "tools.h"

using namespace std;
using namespace msg;

void RouterHandle::ReadCallback(msg::MsgHead* head, Msg* msg)
{
    /// 转发消息
    LOGDEBUG("RouterHandle::ReadCallback");
    string token = head->token();
    string username = head->username();
    if (!AuthProxy::CheckToken(head))
    {  
        LOGDEBUG("CheckToken failed!");
        return;
    }

    head->set_router_id((long long)this);
    ServiceProxy::GetInstance()->SendMsg(head, msg, this);
}

void RouterHandle::Close()
{
    ServiceProxy::GetInstance()->DeleteEvent(this);
    MsgEvent::Close();
}