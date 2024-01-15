#ifndef CONFIG_HANDLE_H
#define CONFIG_HANDLE_H

#include "service_handle.h"

class ConfigHandle : public ServiceHandle
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 注册消息处理的回调函数
    static void RegisterMsgCallback();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收到保存配置的请求
    /// @param head 反序列化头部
    /// @param msg 序列化的消息
    void SaveConfig(msg::MsgHead *head, Msg * msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收到下载配置的请求
    /// @param head 反序列化头部
    /// @param msg 序列化的消息
    void LoadConfig(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收到下载所有配置的请求(分页)
    /// @param head 反序列化头部
    /// @param msg 序列化的消息
    void LoadAllConfig(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 删除配置的请求(通过ip和端口来删除配置项)
    /// @param head 反序列化头部
    /// @param msg 序列化的消息
    void DeleteConfig(msg::MsgHead* head, Msg* msg);
};

#endif // CONFIG_HANDLE_H

