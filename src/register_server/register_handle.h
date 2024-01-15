#ifndef REGISTER_HANDLE_H
#define REGISTER_HANDLE_H

#include "service_handle.h"

class RegisterHandle : public ServiceHandle
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 注册消息处理的回调函数
    static void RegisterMsgCallback();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 处理服务注册的请求
    /// @param head 反序列化后消息头部
    /// @param msg 消息内容
    void RegisterReq(msg::MsgHead *head, Msg *msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收发现服务的请求
    /// @param head 反序列化后消息头部
    /// @param msg 消息内容
    void GetServiceReq(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收心跳
    void HeartRes(msg::MsgHead* head, Msg* msg) {};
};

#endif // REGISTER_HANDLE_H

