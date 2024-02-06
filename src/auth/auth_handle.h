#ifndef AUTH_HANDLE_H
#define AUTH_HANDLE_H

#include "service_handle.h"

#include <map>
#include <string>
#include <mutex>

class AuthHandle : public ServiceHandle
{
public:
    AuthHandle();
    ~AuthHandle();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 注册消息处理的回调函数
    static void RegisterMsgCallback();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收用户登陆的请求
    /// @param head 反序列化后消息头部
    /// @param msg 序列化的消息内容
    void LonginReq(msg::MsgHead * head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 处理添加用户的请求
    /// @param head 反序列化后消息头部
    /// @param msg 序列化的消息内容
    void AddUserReq(msg::MsgHead* head, Msg* msg);

    //////////////////////////////////////////////////////////////////
    /// @brief 接收更新token请求
    void CheckTokenReq(msg::MsgHead* head, Msg* msg);

    //////////////////////////////////////////////////////////////////
    /// @brief 接收获取验证码请求
    void GetAuthCodeReq(msg::MsgHead* head, Msg* msg);

    //////////////////////////////////////////////////////////////////
    /// @brief 接收用户注册请求
    void RegisterUserReq(msg::MsgHead* head, Msg* msg);

    //////////////////////////////////////////////////////////////////
    /// @brief 邮箱登陆请求
    void EmailLonginReq(msg::MsgHead* head, Msg* msg);

    //////////////////////////////////////////////////////////////////
    /// @brief 忘记密码请求
    void ForgetPasswordReq(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 清理过期token
    void TimerCallback() override;
private:
    /// 邮箱为key，注册信息为value
    std::map<std::string, msg::RegisterUserReq> code_map_;
    std::mutex code_map_mutex_;
};

#endif // AUTH_HANDLE_H

