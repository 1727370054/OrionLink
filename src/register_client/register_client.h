#ifndef REGISTER_CLIENT_H
#define REGISTER_CLIENT_H

#include "service_client.h"

class RegisterClient : public ServiceClient
{
public:
    ~RegisterClient();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 获取单例对象
    static RegisterClient *GetInstance()
    {
        static RegisterClient register_client;
        register_client.set_auto_delete(false);
        return &register_client;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 客户端连接成功的回调(向注册中心发起注册请求)
    virtual void ConnectCallback() override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 向注册中心注册服务，此函数需要第一个调用，建立连接(会开启自动重连)
    /// @param service_name 微服务名称
    /// @param ip 微服务IP地址，如果传递NULL，则采用客户端连接地址
    /// @param port 微服务端口
    /// @param is_find 是否可以被外网发现
    void RegisterService(const char *service_name, const char *ip, int port, bool is_find = false);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 处理服务端注册的响应
    /// @param head 反序列化后消息头部
    /// @param msg 消息内容
    void RegisterRes(msg::MsgHead *head, Msg *msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 处理服务端返回微服务列表的响应
    /// @param head 反序列化后消息头部
    /// @param msg 消息内容
    void GetServiceRes(msg::MsgHead *head, Msg *msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送获取微服务列表的请求
    /// @param service_name 如果为NULL，则请求全部的微服务列表
    void GetServiceListReq(const char *service_name);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 获取所有的微服务列表，复制原数据到本地，每次清理上一次的复制数据
    /// 此函数和操作 ServiceMap 数据的函数在一个线程
    /// @return 返回复制的数据
    ///////////////////////////////////////////////////////////////////////////
    msg::ServiceMap *GetAllServiceList();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 获取指定名称的微服务列表 (阻塞函数)
    /// 1.等待连接成功 2.发送获取微服务列表请求 3.等待获取微服务消息反馈(有可能拿到上一次的内容)
    /// @param service_name 微服务名称
    /// @param timeout_sec 超时时间
    /// @return 微服务列表
    ///////////////////////////////////////////////////////////////////////////
    msg::ServiceList GetServices(const char *service_name, int timeout_sec);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 注册消息处理的回调函数
    static void RegisterMsgCallback();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 定时器回调函数，用于发送心跳
    virtual void TimerCallback() override;
private:
    RegisterClient();
    RegisterClient(const RegisterClient &) = delete;
    RegisterClient &operator=(const RegisterClient &) = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 读取本地缓存(线程不安全，需要在外部加锁保证内部service_map线程安全)
    bool LoadLocalCache();
private:
    char service_name_[32] = {0};
    char service_ip_[16] = {0};
    int service_port_ = 0;

    //是否可以被外网发现
    bool is_find_ = false;
};

#endif // REGISTER_CLIENT_H
