#ifndef AUTH_CLIENT_H
#define AUTH_CLIENT_H

#include "service_client.h"

#include <string>
#include <map>
#include <mutex>

namespace msg
{
    class AddUserReq;
}

class AuthClient : public ServiceClient
{
public:
    static AuthClient* GetInstance()
    {
        static AuthClient auth_client;
        auth_client.set_auto_delete(false);
        return &auth_client;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 注册消息处理的回调函数
    static void RegisterMsgCallback();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送登陆的请求
    /// @param username 用户名
    /// @param password 密码(明文)，在函数中会经过md5，base64编码
    void LoginReq(std::string username, std::string password);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送添加用户的请求
    /// @param add_user 用户信息
    void AddUserReq(msg::AddUserReq* add_user);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief获取登陆响应信息，如果token快要过期，会自动发送更新请求
    /// @param username 用户名
    /// @param out_info 返回的登陆信息
    /// @param timeout_ms 检测的超时时间，但如果连接异常则立刻返回
    bool GetLoginInfo(std::string username, msg::LoginRes* out_info, int timeout_ms);
private:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收登陆的响应
    /// @param head 反序列化后消息头部
    /// @param msg 序列化的消息内容码
    void LoginRes(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 添加用户的响应
    /// @param head 反序列化后消息头部
    /// @param msg 序列化的消息内容
    void AddUserRes(msg::MsgHead* head, Msg* msg);
private:
    std::map<std::string, msg::LoginRes> login_map_;
    std::mutex login_map_mutex_;
};

#endif // AUTH_CLIENT_H

