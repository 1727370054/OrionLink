#ifndef CONFIG_CLIENT_H
#define CONFIG_CLIENT_H

#include "service_client.h"

class ConfigClient : public ServiceClient
{
public:
    virtual ~ConfigClient() {};

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ��ȡ��������
    static ConfigClient* GetInstance()
    {
        static ConfigClient* register_client = nullptr;
        if (register_client == nullptr)
        {
            mutex_.lock();
            if (register_client == nullptr)
            {
                register_client = new ConfigClient();
                register_client->set_auto_delete(false);
            }
            mutex_.unlock();
        }
        return register_client;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ע����Ϣ����Ļص�����
    static void RegisterMsgCallback();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ���ͱ�����������
    /// @param config ������Ϣ(�ṹ������)
    void SendConfigReq(msg::Config *config);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ���յ��������õ���Ӧ
    /// @param head �����л�ͷ��
    /// @param msg ���л�����Ϣ
    void RecvConfigRes(msg::MsgHead* head, Msg* msg);
private:
    ConfigClient() {};
    ConfigClient(const ConfigClient&) = delete;
    ConfigClient& operator=(const ConfigClient&) = delete;
private:
    static std::mutex mutex_;
};

#endif // CONFIG_CLIENT_H

