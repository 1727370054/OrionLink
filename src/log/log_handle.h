#ifndef LOG_HANDLE_H
#define LOG_HANDLE_H

#include "service_handle.h"

class LogHandle : public ServiceHandle
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 注册消息处理的回调函数
    static void RegisterMsgCallback();

    void AddLogReq(msg::MsgHead* head, Msg* msg);
};

#endif // LOG_HANDLE_H

