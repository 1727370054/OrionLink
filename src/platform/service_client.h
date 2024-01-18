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
    /// @brief ��������뵽�̳߳��У��������ӣ����õ��� ComTask ��� Init ��������
    virtual void StartConnect();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief �����ȴ��߳��˳�
    void Wait();
private:
    ThreadPool* thread_pool_ = nullptr;
};

#endif // SERVICE_CLIENT_H

