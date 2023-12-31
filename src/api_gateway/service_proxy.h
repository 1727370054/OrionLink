#ifndef SERVICE_PROXY_H
#define SERVICE_PROXY_H

#include "service_proxy_client.h"

#include <map>
#include <string>
#include <atomic>
#include <vector>

class ServiceProxy
{
public:
    ~ServiceProxy();

    static ServiceProxy* GetInstance()
    {
        static ServiceProxy service_proxy;
        return &service_proxy;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ��ʼ��΢�����б�(ע�����Ļ�ȡ)����΢����������
    bool Init();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ���ؾ����ҵ�΢��������ӣ��������ݷ���
    /// @param head ��Ϣͷ��
    /// @param msg ��Ϣ����
    /// @param event RouterHandle ����
    /// @return ���ͳɹ�����true�������෴
    ///////////////////////////////////////////////////////////////////////////
    bool SendMsg(msg::MsgHead* head, Msg *msg, MsgEvent * event);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ������Ϣ�ص�
    /// @param event �¼�����ָ��
    void DeleteEvent(MsgEvent* event);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief �����Զ��������߳�
    void Start();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief �ر��Զ��������߳�
    void Stop();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief �Զ������̻߳ص�����
    void Main();

private:
    ServiceProxy();
    ServiceProxy(const ServiceProxy&) = delete;
    ServiceProxy& operator=(const ServiceProxy&) = delete;

private:
    /// ��Ÿ���΢�������Ӷ���
    std::map<std::string, std::vector<ServiceProxyClient*>> client_map_;

    /// ��¼��һ����ѯ����
    std::map<std::string, int> client_map_last_index_;

    /// �������� callback_task_ ���� (��Ҫ֪�� RouterHandle ��Ӧ�� ServiceProxyClient
    /// ������ö�Ӧ�� DeleteEvent ����)
    std::map<MsgEvent*, ServiceProxyClient*> callbacks_;
    std::mutex callbacks_mutex_;

    std::atomic_bool is_exit_ = false;
};

#endif // SERVICE_PROXY_H

