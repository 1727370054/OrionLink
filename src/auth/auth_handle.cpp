#include "log_client.h"
#include "auth_handle.h"
#include "auth_dao.h"
#include "tools.h"
#include "msg_comm.pb.h"

#define AUTH AuthDAO::GetInstance()

using namespace msg;

void AuthHandle::RegisterMsgCallback()
{
    RegisterCallback(MSG_LOGIN_REQ, (MsgCBFunc)&AuthHandle::LonginReq);
    RegisterCallback(MSG_ADD_USER_REQ, (MsgCBFunc)&AuthHandle::AddUserReq);
}

void AuthHandle::LonginReq(msg::MsgHead* head, Msg* msg)
{
    int timeout_sec = 1800;
    LoginReq request;
    if (!request.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("LonginReq failed! ParseFromArray error");
        return;
    }
    LoginRes response;
    /// 验证用户名和密码
    int ret = AuthDAO::GetInstance()->Login(&request, &response, timeout_sec);
    if (!ret)
    {
        LOGDEBUG("Login failed!");
    }
    head->set_msg_type(MSG_LOGIN_RES);
    SendMsg(head, &response);
}

void AuthHandle::AddUserReq(msg::MsgHead* head, Msg* msg)
{
    /// 响应
    msg::MessageRes response;
    msg::AddUserReq add_user;
    if (!add_user.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("AddUserReq failed! ParseFromArray error");
        response.set_return_(MessageRes::ERROR);
        response.set_desc("AddUserReq failed! ParseFromArray error");
        SendMsg(MSG_ADD_USER_RES, &response);
        return;
    }

    if (!AUTH->AddUser(&add_user))
    {
        LOGDEBUG("user name have existed!");
        response.set_return_(MessageRes::ERROR);
        response.set_desc("user name have existed!");
        SendMsg(MSG_ADD_USER_RES, &response);
        return;
    }
    response.set_return_(MessageRes::OK);
    response.set_desc("OK");
    SendMsg(MSG_ADD_USER_RES, &response);
}
