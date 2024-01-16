#include "auth_handle.h"
#include "tools.h"
#include "msg_comm.pb.h"

using namespace msg;

void AuthHandle::RegisterMsgCallback()
{
    RegisterCallback(MSG_LOGIN_REQ, (MsgCBFunc)&AuthHandle::LonginReq);
}

void AuthHandle::LonginReq(msg::MsgHead* head, Msg* msg)
{
    LoginReq request;
    if (!request.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("LonginReq failed! ParseFromArray error");
        return;
    }

    /// 验证用户名和密码
    std::cout << request.DebugString() << std::endl;
}
