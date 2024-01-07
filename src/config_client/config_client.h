﻿#ifndef CONFIG_CLIENT_H
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
        static ConfigClient* config_client = nullptr;
        if (config_client == nullptr)
        {
            mutex_.lock();
            if (config_client == nullptr)
            {
                config_client = new ConfigClient();
                config_client->set_auto_delete(false);
            }
            mutex_.unlock();
        }
        return config_client;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 开始连接配置中心，开启定时器获取配置
    /// @param server_ip 配置中心IP
    /// @param server_port 配置中心端口
    /// @param conf_message 配置对象
    /// @param timeout_sec 等待连接配置中心的超时时间
    /// @return 成功返回true
    bool StartGetConf(const char* server_ip, int server_port,
        const char *local_ip, int local_port,
        google::protobuf::Message* conf_message, int timeout_sec = 10);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 定时器回调函数
    virtual void TimerCallback() override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 获取下载的本地参数配置信息
    /// @param key 字段名称
    /// @return 成功返回对应配置信息，失败返回 0
    int GetInt(const char* key);
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 获取下载的本地参数配置信息
    /// @param key 字段名称
    /// @return 成功返回对应配置信息，失败返回 空串
    std::string GetString(const char* key);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 获取配置项
    /// @param ip 微服务IP
    /// @param port 微服务端口
    /// @param out_config 存在该配置项，拷贝返回，输出型参数
    /// @return 存在返回true，不存在返回false
    bool GetConfig(const char* ip, int port, msg::Config* out_config);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 注册消息处理的回调函数
    static void RegisterMsgCallback();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送上传配置请求
    /// @param config 配置信息(结构化数据)
    void SendConfigReq(msg::Config *config);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收到上传配置的响应
    /// @param head 反序列化头部
    /// @param msg 序列化的消息
    void RecvConfigRes(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送下载配置请求，如果IP为null，则取连接配置中心的地址
    /// @param ip 微服务IP
    /// @param port 微服务端口
    void LoadConfigReq(const char *ip, int port);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 下载配置响应
    /// @param head 反序列化头部
    /// @param msg 序列化的消息
    void LoadConfigRes(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 设置当前配置对象
    /// @param message 配置对象
    void SetCurServiceMessage(google::protobuf::Message* message);
private:
    ConfigClient() {};
    ConfigClient(const ConfigClient&) = delete;
    ConfigClient& operator=(const ConfigClient&) = delete;
private:
    static std::mutex mutex_;

    /// 本地微服务的IP和端口
    char local_ip_[16] = { 0 };
    int local_port_ = 0;
};

#endif // CONFIG_CLIENT_H

