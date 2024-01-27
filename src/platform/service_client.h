#ifndef SERVICE_CLIENT_H
#define SERVICE_CLIENT_H

#include "msg_event.h"
#include "thread_pool.h"

class XCOM_API ServiceClient : public MsgEvent
{
public:
    ServiceClient();
    ~ServiceClient();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 将任务加入到线程池中，进行连接，调用的是 ComTask 类的 Init 进行连接
    virtual void StartConnect();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 阻塞等待线程退出
    void Wait();
private:
    ThreadPool* thread_pool_ = nullptr;
};

#endif // SERVICE_CLIENT_H

