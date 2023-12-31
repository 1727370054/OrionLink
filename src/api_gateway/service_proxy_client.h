#ifndef SERVICE_PROXY_CLIENT_H
#define SERVICE_PROXY_CLIENT_H

#include "service_client.h"

#include <map>
#include <mutex>

class ServiceProxyClient : public ServiceClient
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief ������΢����ķ�������Ϣת������Ӧ�� RouterHandle���ú�����д MsgEvent ���麯����
    /// @param head �����л�����Ϣͷ��
    /// @param msg ���л�����Ϣ����
    virtual void ReadCallback(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief �ÿͻ�����Ϣ�Ⱥ� RouterHandle ���й�������·��ת����΢����Ⱥ
    /// @param head ��Ϣͷ��
    /// @param msg ���л�����Ϣ����
    /// @param event RouterHandle ����
    /// @return ���ͳɹ�����true�������෴
    ///////////////////////////////////////////////////////////////////////////
    bool SendMsg(msg::MsgHead* head, Msg* msg, MsgEvent* event);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ע��һ���¼� (RouterHandle) (ÿ���ͻ��˶�Ӧһ�� RouterHandle)
    /// @param event �¼�����ָ��
    void RegisterEvent(MsgEvent* event);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ɾ��һ���¼� (RouterHandle)
    /// @param event �¼�����ָ��
    void DeleteEvent(MsgEvent* event);

private:
    /// ��Ϣת���Ķ���һ�� proxy ��Ӧ��� MsgEvent
    /// ��ָ�������Ϊ������Ҫ����64λ
    static std::map<long long, MsgEvent*> callback_task_;
    static std::mutex callback_task_mutex_;
};

#endif // SERVICE_PROXY_CLIENT_H

