#ifndef AUTH_CLIENT_H
#define AUTH_CLIENT_H

#include "service_client.h"
#include "ssl_ctx.h"

#include <string>
#include <map>
#include <mutex>
#include <atomic>

namespace msg
{
    class AddUserReq;
}

class AuthClient : public ServiceClient
{
public:
    ~AuthClient();

    static AuthClient *GetInstance()
    {
        static AuthClient auth_client;
        auth_client.set_auto_delete(false);
        auth_client.set_timer_ms(1000);
        SSLCtx *ssl_ctx_ = new SSLCtx();
        ssl_ctx_->InitClient();
        auth_client.set_ssl_ctx(ssl_ctx_);
        return &auth_client;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 注册消息处理的回调函数
    static void RegisterMsgCallback();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送登陆的请求，并等待获取登陆响应(3秒)
    /// @param username 用户名
    /// @param password 密码(明文)，在函数中会经过md5，base64编码
    bool Login(std::string username, std::string password);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 获取当前用户登陆信息
    /// @return 返回登陆信息
    msg::LoginRes GetCurLogin(int timeout_ms = 3000);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送登陆的请求
    /// @param username 用户名
    /// @param password 密码(明文)，在函数中会经过md5，base64编码
    void LoginReq(std::string username, std::string password);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送登陆的请求
    /// @param email 邮箱
    /// @param code 验证码
    void EmailLoginReq(std::string email, std::string code);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送邮箱登陆的结果
    /// @param timeout_ms 超时时间
    /// @return 0: 超时 1: 成功 3: 验证码错误 4: 用户不存在
    int GetEmailLogin(int timeout_ms = 3000);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送添加用户的请求
    /// @param add_user 用户信息
    void AddUserReq(msg::AddUserReq *add_user);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 获取登陆响应信息，如果token快要过期，会自动发送更新请求
    /// @param username 用户名
    /// @param out_info 返回的登陆信息
    /// @param timeout_ms 检测的超时时间，但如果连接异常则立刻返回
    bool GetLoginInfo(std::string username, msg::LoginRes *out_info, int timeout_ms);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 检查token 是否有效 更新本地的 login 登录数据
    void CheckTokenReq();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送获取验证码请求
    void GetAuthCodeReq(const std::string &email);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送注册请求
    void RegisterUserReq(msg::RegisterUserReq &req);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 获取注册结果和获取忘记密码结果
    /// @param timeout_ms 超时时间
    /// @return 注册结果 0: 超时返回 1: 验证码错误 2: 用户名已经存在 3: 成功
    /// @return 忘记密码 0: 超时返回 1: 成功 2: 验证码错误 3: 用户不存在 4: 该用户绑定的邮箱不正确
    int GetResult(int timeout_ms);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送忘记密码请求
    void ForgetPasswordReq(msg::RegisterUserReq &req);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 清理上一次登陆用户缓存
    void ClearLastLogin(std::string username = "");

    virtual void TimerCallback() override;

    std::string cur_username() { return cur_username_; }

private:
    AuthClient();
    AuthClient(const AuthClient &) = delete;
    AuthClient &operator=(const AuthClient &) = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收登陆的响应
    /// @param head 反序列化后消息头部
    /// @param msg 序列化的消息内容码
    void LoginRes(msg::MsgHead *head, Msg *msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 添加用户的响应
    /// @param head 反序列化后消息头部
    /// @param msg 序列化的消息内容
    void AddUserRes(msg::MsgHead *head, Msg *msg);

    void CheckTokenRes(msg::MsgHead *head, Msg *msg);

    void RegisterUserRes(msg::MsgHead *head, Msg *msg);

    void EmailLoginRes(msg::MsgHead *head, Msg *msg);

    void ForgetPasswordRes(msg::MsgHead *head, Msg *msg);

private:
    /// 当前登陆的用户名
    std::string cur_username_ = "";

    std::map<std::string, msg::LoginRes> login_map_;
    std::mutex login_map_mutex_;

    std::mutex cur_login_mutex_;

    SSLCtx *ssl_ctx_ = nullptr;

    /// 用于获取注册结果
    std::atomic<int> result_{0};
};

#endif // AUTH_CLIENT_H
