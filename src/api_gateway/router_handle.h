#ifndef ROUTER_HANDLE_H
#define ROUTER_HANDLE_H

#include "service_handle.h"

class RouterHandle : public ServiceHandle
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收了客户端的消息，进行消息路由（该函数重写 MsgEvent 的虚函数）
    /// @param head 反序列化后消息头部
    /// @param msg 序列化的消息内容
    virtual void ReadCallback(msg::MsgHead* head, Msg* msg) override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 重写 ComTask 的 Close，超时、连接关闭、错误时，会调用
    virtual void Close() override;
};

#endif // ROUTER_HANDLE_H

