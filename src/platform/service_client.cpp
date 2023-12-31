#include "service_client.h"

ServiceClient::ServiceClient()
{
    this->thread_pool_ = ThreadPoolFactory::Create();
}

ServiceClient::~ServiceClient()
{
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
