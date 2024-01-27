#ifndef AUTH_PROXY_H
#define AUTH_PROXY_H

#include "service_proxy_client.h"

class AuthProxy : public ServiceProxyClient
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 开启线程，定时清理过期token
    static void InitAuth();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 验证token
    static bool CheckToken(const msg::MsgHead* head);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收了鉴权微服务的反馈，缓存 token 信息
    /// @param head 反序列化后消息头部
    /// @param msg 序列化的消息内容
    virtual void ReadCallback(msg::MsgHead* head, Msg* msg) override;
};

#endif // AUTH_PROXY_H

