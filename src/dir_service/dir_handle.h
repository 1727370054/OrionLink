#ifndef DIR_HANDLE_H
#define DIR_HANDLE_H

#include "service_handle.h"

class DirHandle : public ServiceHandle
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 注册消息处理的回调函数
    static void RegisterMsgCallback();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收获取目录请求
    void GetDirReq(msg::MsgHead* head, Msg* msg);

    void NewDirReq(msg::MsgHead* head, Msg* msg);

    void DeleteFileReq(msg::MsgHead* head, Msg* msg);

    void GetDiskInfoReq(msg::MsgHead* head, Msg* msg);
};

#endif // DIR_HANDLE_H

