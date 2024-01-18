#ifndef AUTH_DAO_H
#define AUTH_DAO_H

namespace msg
{
    class AddUserReq;
    class LoginReq;
    class LoginRes;
}

namespace ol
{
    class OrionLinkDB;
}

class AuthDAO
{
public:
    ~AuthDAO();

    static AuthDAO* GetInstance()
    {
        static AuthDAO auth_dao;
        return &auth_dao;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 初始化数据库
    bool Init();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 安装表
    bool Install();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 添加用户
    bool AddUser(msg::AddUserReq * user);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收登陆信息，生成token，设置token超时时间
    /// @param user_req 用户登陆信息(输入型参数)
    /// @param user_res 返回登陆响应(输出型参数)
    /// @param timeout_sec token超时时间
    bool Login(const msg::LoginReq* user_req, msg::LoginRes* user_res, int timeout_sec);
private:
    AuthDAO();
    AuthDAO(const AuthDAO&) = delete;
    AuthDAO& operator=(const AuthDAO&) = delete;

private:
    ol::OrionLinkDB* oldb_ = nullptr;
};

#endif // AUTH_DAO_H

