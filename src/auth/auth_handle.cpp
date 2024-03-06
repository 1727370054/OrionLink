#include "log_client.h"
#include "auth_handle.h"
#include "auth_dao.h"
#include "tools.h"
#include "msg_comm.pb.h"

#include <thread>

using namespace std;
using namespace msg;

#define AUTH AuthDAO::GetInstance()

static const int token_timeout_sec = 600;
static const int code_timeout_sec = 300;

AuthHandle::AuthHandle()
{
    set_timer_ms(1000);
}

AuthHandle::~AuthHandle()
{
}

void AuthHandle::RegisterMsgCallback()
{ 
    RegisterCallback(MSG_LOGIN_REQ, (MsgCBFunc)&AuthHandle::LonginReq);
    RegisterCallback(MSG_ADD_USER_REQ, (MsgCBFunc)&AuthHandle::AddUserReq);
    RegisterCallback(MSG_CHECK_TOKEN_REQ, (MsgCBFunc)&AuthHandle::CheckTokenReq);
    RegisterCallback(MSG_GET_AUTH_CODE, (MsgCBFunc)&AuthHandle::GetAuthCodeReq);
    RegisterCallback(MSG_REGISTER_USER_REQ, (MsgCBFunc)&AuthHandle::RegisterUserReq);
    RegisterCallback(MSG_EMAIL_LOGIN_REQ, (MsgCBFunc)&AuthHandle::EmailLonginReq);
    RegisterCallback(MSG_FORGET_PASSWORD_REQ, (MsgCBFunc)&AuthHandle::ForgetPasswordReq);
}

void AuthHandle::LonginReq(msg::MsgHead* head, Msg* msg)
{
    int timeout_sec = token_timeout_sec;
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
    response.set_username(request.username());
    head->set_msg_type(MSG_LOGIN_RES);
    SendMsg(head, &response);
}

void AuthHandle::AddUserReq(msg::MsgHead* head, Msg* msg)
{
    /// 响应
    msg::MessageRes response;
    msg::AddUserReq add_user;
    head->set_msg_type(MSG_ADD_USER_RES);
    if (!add_user.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("AddUserReq failed! ParseFromArray error");
        response.set_return_(MessageRes::ERROR);
        response.set_desc("AddUserReq failed! ParseFromArray error");
        SendMsg(head, &response);
        return;
    }

    if (!AUTH->AddUser(&add_user))
    {
        LOGDEBUG("user name have existed!");
        response.set_return_(MessageRes::ERROR);
        response.set_desc("user name have existed!");
        SendMsg(head, &response);
        return;
    }
    response.set_return_(MessageRes::OK);
    response.set_desc("OK");
    SendMsg(head, &response);
}

void AuthHandle::CheckTokenReq(msg::MsgHead* head, Msg* msg)
{
    LoginRes res;
    int timeout_sec = token_timeout_sec;
    AUTH->CheckToken(head, &res, timeout_sec);

    head->set_msg_type(MSG_CHECK_TOKEN_RES);
    SendMsg(head, &res);
}

void AuthHandle::GetAuthCodeReq(msg::MsgHead* head, Msg* msg)
{
    GetAuthCode auth_code;
    if (!auth_code.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("AuthHandle::GetAuthCodeReq failed! ParseFromArray error");
        return;
    }

    string to = auth_code.email();
    string code = GenerateNumericCode(6);

    string text = "尊敬的用户: \n感谢您使用[OL云盘]。您的验证码是：";
    text += code;
    text += " 请在该页面输入此验证码以完成登陆或注册流程。\n";
    text += "请注意，验证码有效期为5分钟。如有任何问题，请不要犹豫，直接回复此邮件或联系我们的客户支持。\n";
    text += "祝您使用愉快！\n";
    text += "[OL云盘]团队";

    string smtp_server = "smtp.163.com";
    int smtp_port = 994; /// 163邮箱的smtp的SSL的端口为994端口
    string username = "你的邮箱地址";
    string password = "密码";
    string subject = "验证码";
    SendEmail(smtp_server, smtp_port, username, to, subject, text, username, password);

    msg::RegisterUserReq reg;
    reg.set_email(to);
    auto cur_time = time(0);
    cur_time += code_timeout_sec;
    reg.set_expired_time(cur_time);
    reg.set_code(code);
    Mutex lock(&code_map_mutex_);
    code_map_[to] = reg;
}

void AuthHandle::RegisterUserReq(msg::MsgHead* head, Msg* msg)
{
    msg::RegisterUserReq reg;
    if (!reg.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("AuthHandle::RegisterUserReq! ParseFromArray error");
        return;
    }

    msg::MessageRes res;
    msg::AddUserReq add_user;
    add_user.set_username(reg.username());
    add_user.set_rolename(reg.username());
    add_user.set_password(reg.password());
    add_user.set_email(reg.email());
    
    head->set_msg_type(MSG_REGISTER_USER_RES);
    /// 验证验证码的正确性
    code_map_mutex_.lock();
    auto ptr = code_map_.find(reg.email());
    if (ptr == code_map_.end())
    {
        res.set_return_(MessageRes::ERROR);
        res.set_desc("auth code error!");
        code_map_mutex_.unlock();
        SendMsg(head, &res);
        return;
    }
    code_map_mutex_.unlock();

    if (ptr->second.code() != reg.code())
    {
        res.set_return_(MessageRes::ERROR);
        res.set_desc("auth code error!");
        SendMsg(head, &res);
        return;
    }

    /// 开始添加用户
    if (!AUTH->AddUser(&add_user))
    {
        LOGDEBUG("user name have existed!");
        res.set_return_(MessageRes::USER_EXISTS);
        res.set_desc("user name have existed!");
        SendMsg(head, &res);
        return;
    }
    res.set_return_(MessageRes::OK);
    res.set_desc("OK");
    SendMsg(head, &res);
}

void AuthHandle::EmailLonginReq(msg::MsgHead* head, Msg* msg)
{
    msg::EmailLoginReq req;
    if (!req.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("AuthHandle::EmailLonginReq! ParseFromArray error");
        return;
    }

    msg::LoginRes res;
    res.set_username("unknown_user");

    /// 先验证验证码
    head->set_msg_type(MSG_EMAIL_LOGIN_RES);
    /// 验证验证码的正确性
    code_map_mutex_.lock();
    auto ptr = code_map_.find(req.email());
    if (ptr == code_map_.end())
    {
        res.set_desc(LoginRes::ERROR);
        code_map_mutex_.unlock();
        SendMsg(head, &res);
        return;
    }
    code_map_mutex_.unlock();

    if (ptr->second.code() != req.code())
    {
        res.set_desc(LoginRes::ERROR);
        SendMsg(head, &res);
        return;
    }

    int timeout_sec = token_timeout_sec;
    if (!AUTH->EmailLogin(&req, &res, timeout_sec))
    {
        res.set_desc(LoginRes::NOUSER);
        SendMsg(head, &res);
        return;
    }

    res.set_desc(LoginRes::OK);
    SendMsg(head, &res);
}

void AuthHandle::ForgetPasswordReq(msg::MsgHead* head, Msg* msg)
{
    msg::RegisterUserReq req;
    if (!req.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("AuthHandle::ForgetPasswordReq! ParseFromArray error");
        return;
    }

    head->set_msg_type(MSG_FORGET_PASSWORD_RES);
    msg::MessageRes res;

    code_map_mutex_.lock();
    auto ptr = code_map_.find(req.email());
    if (ptr == code_map_.end())
    {
        res.set_return_(MessageRes::ERROR);
        res.set_desc("auth code error!");
        code_map_mutex_.unlock();
        SendMsg(head, &res);
        return;
    }
    code_map_mutex_.unlock();

    if (ptr->second.code() != req.code())
    {
        res.set_return_(MessageRes::ERROR);
        res.set_desc("auth code error!");
        SendMsg(head, &res);
        return;
    }

    if (!AUTH->ForgetPassword(&req, &res))
    {
        SendMsg(head, &res);
        return;
    }

    res.set_return_(MessageRes::OK);
    res.set_desc("ok");
    SendMsg(head, &res);
}

void AuthHandle::TimerCallback()
{
    AUTH->ClearToken();

    Mutex lock(&code_map_mutex_);
    auto ptr = code_map_.begin();
    for (; ptr != code_map_.end(); )
    {
        auto tmp = ptr;
        auto tt = time(0);
        ptr++;
        if (tmp->second.expired_time() < tt)
        {
            cout << "expired_time " << tmp->second.expired_time() << endl;
            code_map_.erase(tmp);
        }
    }
}

