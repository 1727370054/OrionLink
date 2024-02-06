#include "log_client.h"
#include "auth_client.h"
#include "tools.h"
#include "msg_comm.pb.h"

#include <thread>

using namespace msg;
using namespace std;

void AuthClient::RegisterMsgCallback()
{
    RegisterCallback(MSG_ADD_USER_RES, (MsgCBFunc)&AuthClient::AddUserRes);
    RegisterCallback(MSG_LOGIN_RES, (MsgCBFunc)&AuthClient::LoginRes);
    RegisterCallback(MSG_CHECK_TOKEN_RES, (MsgCBFunc)&AuthClient::CheckTokenRes);
    RegisterCallback(MSG_REGISTER_USER_RES, (MsgCBFunc)&AuthClient::RegisterUserRes);
    RegisterCallback(MSG_EMAIL_LOGIN_RES, (MsgCBFunc)&AuthClient::EmailLoginRes);
    RegisterCallback(MSG_FORGET_PASSWORD_RES, (MsgCBFunc)&AuthClient::ForgetPasswordRes);
}

bool AuthClient::Login(std::string username, std::string password)
{
    LoginReq(username, password);
    auto res = GetCurLogin();
    if (res.desc() == LoginRes::ERROR)
        return false;
    return true;
}

msg::LoginRes AuthClient::GetCurLogin(int timeout_ms)
{
    msg::LoginRes res;

    if (!GetLoginInfo(cur_username_, &res, timeout_ms))
    {
        cur_login_mutex_.lock();
        res.set_desc(LoginRes::ERROR);
        cur_login_mutex_.unlock();
        return res;
    }
    return res;
}

void AuthClient::LoginReq(std::string username, std::string password)
{
    cur_login_mutex_.lock();
    cur_username_ = username;
    cur_login_mutex_.unlock();

    msg::LoginReq request;
    request.set_username(username);
    auto md5_passwd = OLMD5_base64((unsigned char*)password.c_str(), password.size());
    request.set_password(md5_passwd);
    // std::cout << request.DebugString() << std::endl;
    ClearLastLogin(username);

    SendMsg(MSG_LOGIN_REQ, &request);
}

void AuthClient::LoginRes(msg::MsgHead* head, Msg* msg)
{
    msg::LoginRes response;
    if (!response.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("AuthClient::LoginRes failed! ParseFromArray error");
        return;
    }
    /// cout << response.DebugString() << endl;
    {
        Mutex lock(&login_map_mutex_);
        if (response.username().empty()) return;
        login_map_[response.username()] = response;
    }
}

void AuthClient::EmailLoginReq(std::string email, std::string code)
{
    msg::EmailLoginReq req;
    req.set_email(email);
    req.set_code(code);
    cur_login_mutex_.lock();
    cur_username_ = "";
    cur_login_mutex_.unlock();
    SendMsg(MSG_EMAIL_LOGIN_REQ, &req);
}

int AuthClient::GetEmailLogin(int timeout_ms)
{
    int count = timeout_ms / 10;
    if (count <= 0)
        count = 2;
    for (int i = 0; i < count; i++)
    {
        cur_login_mutex_.lock();
        string tmp = cur_username_;
        cur_login_mutex_.unlock();

        if (!tmp.empty())
        {
            count -= i;
            break;
        }

        this_thread::sleep_for(10ms);
    }

    timeout_ms = timeout_ms - (count * 10);
    auto login = GetCurLogin(timeout_ms);
    int ret = 0;
    switch (login.desc())
    {
    case LoginRes::OK:
        if (login.username() == "unknown_user")
            ret = LoginRes::NOUSER;
        else
            ret = LoginRes::OK;
        break;
    case LoginRes::ERROR:
        ret = LoginRes::ERROR;
        break;
    case LoginRes::NOUSER:
        ret = LoginRes::NOUSER;
        break;
    default:
        break;
    }

    return ret;
}

void AuthClient::EmailLoginRes(msg::MsgHead* head, Msg* msg)
{
    msg::LoginRes res;
    if (!res.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("AuthClient::EmailLoginRes failed! ParseFromArray error");
        return;
    }

    cur_login_mutex_.lock();
    cur_username_ = res.username();
    cur_login_mutex_.unlock();

    {
        Mutex lock(&login_map_mutex_);
        if (res.username().empty()) return;
        login_map_[res.username()] = res;
    }
}

void AuthClient::AddUserReq(msg::AddUserReq* add_user)
{
    auto md5_passwd = OLMD5_base64((unsigned char*)add_user->password().c_str(), add_user->password().size());
    add_user->set_password(md5_passwd);
    SendMsg(MSG_ADD_USER_REQ, add_user);
}

void AuthClient::AddUserRes(msg::MsgHead* head, Msg* msg)
{
    msg::MessageRes response;
    if (!response.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("AuthClient::AddUserRes failed! ParseFromArray error");
        return;
    }
    if (response.return_() == MessageRes::ERROR)
    {
        LOGDEBUG(response.desc().c_str());
        return;
    }

    LOGDEBUG("add user success!");
}

bool AuthClient::GetLoginInfo(string username, msg::LoginRes* out_info, int timeout_ms)
{
    if (!out_info || username.empty()) return false;
    int count = timeout_ms / 10;
    if (count <= 0) count = 1;
    for (int i = 0; i < count; i++)
    {
        login_map_mutex_.lock();
        auto iter = login_map_.find(username);
        if (iter == login_map_.end())
        {
            login_map_mutex_.unlock();
            this_thread::sleep_for(10ms);
            continue;
        }
        auto login = iter->second;
        login_map_mutex_.unlock();
        if (login.desc() != LoginRes::NONE)
        {
            out_info->CopyFrom(login);
            return true;
        }
        return false;
    }
    return false;
}

void AuthClient::CheckTokenReq()
{
    msg::LoginRes login;
    login = GetCurLogin(100);
    if (login.desc() == msg::LoginRes::ERROR) return;

    auto tt = time(0);
    if (tt < login.expired_time()) 
        return;

    set_login_info(&login);
    MessageRes res;
    res.set_desc("check");
    SendMsg(MSG_CHECK_TOKEN_REQ, &res);
}

void AuthClient::GetAuthCodeReq(const std::string& email)
{
    GetAuthCode code;
    code.set_email(email);
    SendMsg(MSG_GET_AUTH_CODE, &code);
}

void AuthClient::RegisterUserReq(msg::RegisterUserReq& req)
{
    auto md5_passwd = OLMD5_base64((unsigned char*)req.password().c_str(), req.password().size());
    req.set_password(md5_passwd);
    SendMsg(MSG_REGISTER_USER_REQ, &req);
}

void AuthClient::ForgetPasswordReq(msg::RegisterUserReq& req)
{
    auto md5_passwd = OLMD5_base64((unsigned char*)req.password().c_str(), req.password().size());
    req.set_password(md5_passwd);
    SendMsg(MSG_FORGET_PASSWORD_REQ, &req);
}

void AuthClient::ForgetPasswordRes(msg::MsgHead* head, Msg* msg)
{
    msg::MessageRes res;
    if (!res.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("AuthClient::ForgetPasswordRes! ParseFromArray error");
        return;
    }

    switch (res.return_())
    {
    case MessageRes::OK:
        result_ = 1;
        break;
    case MessageRes::ERROR:
        result_ = 2;
        break;
    case MessageRes::USER_NOT_EXISTS:
        result_ = 3;
        break;
    case MessageRes::BIND_EMAIL_ERR:
        result_ = 4;
        break;
    default:
        break;
    }
}

void AuthClient::RegisterUserRes(msg::MsgHead* head, Msg* msg)
{
    msg::MessageRes res;
    if (!res.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("AuthClient::RegisterUserRes! ParseFromArray error");
        return;
    }

    switch (res.return_())
    {
    case MessageRes::ERROR:
        result_ = 1;
        break;
    case MessageRes::USER_EXISTS:
        result_ = 2;
        break;
    case MessageRes::OK:
        result_ = 3;
        break;
    default:
        break;
    }
}

int AuthClient::GetResult(int timeout_ms)
{
    int count = timeout_ms / 10;
    if (count <= 0) count = 1;
    for (int i = 0; i < count; i++)
    {
       this_thread::sleep_for(10ms);
    }
    return result_;
}

void AuthClient::ClearLastLogin(std::string username)
{
    string obj = "";
    if (!username.empty())
    {
        obj = username;
    }
    else
    {
        Mutex lock(&cur_login_mutex_);
        obj = cur_username_;
    }
    Mutex lock(&login_map_mutex_);
    login_map_.erase(obj);
}

void AuthClient::TimerCallback()
{
    CheckTokenReq();
}

void AuthClient::CheckTokenRes(msg::MsgHead* head, Msg* msg)
{
    msg::LoginRes res;
    if (!res.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("AuthClient::CheckTokenRes failed! ParseFromArray error");
        return;
    }

    if (res.desc() == LoginRes::ERROR)
        return;

    Mutex lock(&login_map_mutex_);
    if (res.username().empty()) return;
    login_map_[res.username()] = res;
}

AuthClient::AuthClient()
{
    set_service_name(AUTH_NAME);
    AuthClient::RegisterMsgCallback();
}

AuthClient::~AuthClient()
{
    delete ssl_ctx_;
    ssl_ctx_ = nullptr;
}



