#include "log_client.h"
#include "auth_client.h"
#include "tools.h"
#include "msg_comm.pb.h"

using namespace msg;
using namespace std;

void AuthClient::RegisterMsgCallback()
{
    RegisterCallback(MSG_ADD_USER_RES, (MsgCBFunc)&AuthClient::AddUserRes);
    RegisterCallback(MSG_LOGIN_RES, (MsgCBFunc)&AuthClient::LoginRes);
}

void AuthClient::LoginReq(std::string username, std::string password)
{
    msg::LoginReq request;
    request.set_username(username);
    auto md5_passwd = OLMD5_base64((unsigned char*)password.c_str(), password.size());
    request.set_password(md5_passwd);
    // std::cout << request.DebugString() << std::endl;
    {
        Mutex lock(&login_map_mutex_);
        login_map_.erase(username);
    }
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
        if (login.desc() == LoginRes::OK)
        {
            out_info->CopyFrom(login);
            return true;
        }
        return false;
    }
    return false;
}

