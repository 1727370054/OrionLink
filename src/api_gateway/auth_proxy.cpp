#include "auth_proxy.h"
#include "log_client.h"
#include "tools.h"

#include <string>
#include <thread>
#include <map>
#include <mutex>
#include <atomic>

using namespace std;
using namespace msg;

static map<string, LoginRes> token_cache;
static mutex token_cache_mutex;

/*
* @brief 清理过期token 
*/
class TokenThread
{
public:
    void Start()
    {
        thread th(&TokenThread::Main, this);
        th.detach();
    }
    ~TokenThread()
    {
        is_exit_ = true;
        this_thread::sleep_for(10ms);
    }
private:
    bool is_exit_ = false;
    void Main()
    {
        while (!is_exit_)
        {
            token_cache_mutex.lock();
            //检测过期token 需要优化
            auto ptr = token_cache.begin();
            for (; ptr != token_cache.end(); )
            {
                auto tmp = ptr;
                auto tt = time(0);
                ptr++;
                if (tmp->second.expired_time() < tt)
                {
                    cout << "expired_time " << tmp->second.expired_time() << endl;
                    token_cache.erase(tmp);
                }
            }
            token_cache_mutex.unlock();
            this_thread::sleep_for(1s);
        }
    }
};

static TokenThread token_thread;

void AuthProxy::InitAuth()
{
    token_thread.Start();
}

bool AuthProxy::CheckToken(const msg::MsgHead* head)
{
    if (!head) return false;
    if (head->msg_type() == MSG_LOGIN_REQ || head->msg_type() == MSG_CHECK_TOKEN_REQ 
        || head->msg_type() == MSG_GET_AUTH_CODE || head->msg_type() == MSG_REGISTER_USER_REQ
        || head->msg_type() == MSG_EMAIL_LOGIN_REQ || head->msg_type() == MSG_FORGET_PASSWORD_REQ)
        return true;
    string token = head->token();
    if (token.empty())
    {
        LOGDEBUG("token is empty!");
        return false;
    }
    Mutex lock(&token_cache_mutex);
    auto iter = token_cache.find(token);
    if (iter == token_cache.end())
    {
        LOGDEBUG("can't find token!");
        return false;
    }

    if (iter->second.username() != head->username())
        return false;
    if (iter->second.rolename() != head->rolename())
        return false;

    return true;
}

void AuthProxy::ReadCallback(msg::MsgHead* head, Msg* msg)
{
    if (!head) return;
    LoginRes res;
    switch (head->msg_type())
    {
    case MSG_LOGIN_RES:
        if (res.ParseFromArray(msg->data, msg->size))
        {
            Mutex lock(&token_cache_mutex);
            token_cache[res.token()] = res;
        }
    case MSG_CHECK_TOKEN_RES:
        if (res.ParseFromArray(msg->data, msg->size))
        {
            if (res.desc() == LoginRes::OK)
            {
                Mutex lock(&token_cache_mutex);
                token_cache[res.token()] = res;
            }
        }
    case MSG_EMAIL_LOGIN_RES:
        if (res.ParseFromArray(msg->data, msg->size))
        {
            if (res.desc() == LoginRes::OK)
            {
                Mutex lock(&token_cache_mutex);
                token_cache[res.token()] = res;
            }
        }
    default:
        break;
    }

    ServiceProxyClient::ReadCallback(head, msg);
}
