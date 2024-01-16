#ifndef AUTH_CLIENT
#define AUTH_CLIENT

#include "service_client.h"

#include <string>

class AuthClient : public ServiceClient
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送登陆的请求
    /// @param username 用户名
    /// @param password 密码(明文)，在函数中会经过md5，base64编码
    void LoginReq(std::string username, std::string password);
};

#endif // AUTH_CLIENT

