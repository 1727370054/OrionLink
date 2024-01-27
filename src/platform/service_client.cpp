#include "service_client.h"
#include "log_client.h"
#include "tools.h"

using namespace msg;

ServiceClient::ServiceClient()
{
    this->thread_pool_ = ThreadPoolFactory::Create();
}

ServiceClient::~ServiceClient()
{
    login_info_mutex_.lock();
    delete login_info_;
    login_info_ = NULL;
    login_info_mutex_.unlock();

    delete thread_pool_;
    thread_pool_ = nullptr;
}

void ServiceClient::StartConnect()
{
    if (thread_pool_)
    {
        thread_pool_->Init(1);
        thread_pool_->Dispatch(this);
    }
}

void ServiceClient::Wait()
{
    ThreadPool::Wait();
}

bool ServiceClient::SendMsg(msg::MsgType type, const google::protobuf::Message* message)
{
    msg::MsgHead head;
    head.set_msg_type(type);
    SetHead(&head);
    return MsgEvent::SendMsg(&head, message);
}

void ServiceClient::SetHead(msg::MsgHead* head)
{
    if (!head) return;
    if (service_name_.empty())
    {
        LOGDEBUG("service_name is empty");
    }
    else if (head->service_name().empty())
    {
        head->set_service_name(service_name_);
    }
    Mutex lock(&login_info_mutex_);
    if (!login_info_) return;

    /// 登陆信息时 login_info_ 的 token 是空的
    if (!login_info_->token().empty())
    {
        head->set_token(login_info_->token().c_str());
        head->set_username(login_info_->username().c_str());
        head->set_rolename(login_info_->rolename().c_str());
    }
}

void ServiceClient::set_login_info(msg::LoginRes* login)
{
    if (!login) return;
    Mutex lock(&login_info_mutex_);
    if (!login_info_)
    {
        login_info_ = new LoginRes();
    }
    login_info_->CopyFrom(*login);
}
