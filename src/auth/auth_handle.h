#ifndef AUTH_HANDLE_H
#define AUTH_HANDLE_H

#include "service_handle.h"

class AuthHandle : public ServiceHandle
{
public:

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 注册消息处理的回调函数
    static void RegisterMsgCallback();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收用户登陆的请求
    /// @param head 反序列化后消息头部
    /// @param msg 序列化的消息内容
    void LonginReq(msg::MsgHead * head, Msg* msg);

};

#endif // AUTH_HANDLE_H

