#ifndef CONFIG_CLIENT_H
#define CONFIG_CLIENT_H

#include "service_client.h"

class ConfigClient : public ServiceClient
{
public:
    virtual ~ConfigClient() {};

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 获取单例对象
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
    /// @brief 注册消息处理的回调函数
    static void RegisterMsgCallback();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送保存配置请求
    /// @param config 配置信息(结构化数据)
    void SendConfigReq(msg::Config *config);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收到保存配置的响应
    /// @param head 反序列化头部
    /// @param msg 序列化的消息
    void RecvConfigRes(msg::MsgHead* head, Msg* msg);
private:
    ConfigClient() {};
    ConfigClient(const ConfigClient&) = delete;
    ConfigClient& operator=(const ConfigClient&) = delete;
private:
    static std::mutex mutex_;
};

#endif // CONFIG_CLIENT_H

