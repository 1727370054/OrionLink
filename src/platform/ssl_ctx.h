#ifndef SSL_CTX_H
#define SSL_CTX_H

#include "ol_ssl.h"

struct ssl_ctx_st;

class XCOM_API SSLCtx
{
public:
    SSLCtx();
    ~SSLCtx();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 初始化SSL服务器
    /// @param crt_file 服务端证书文件
    /// @param key_file 服务器私钥文件
    /// @param ca_file 验证客户端证书(可选)
    virtual bool InitServer(const char* crt_file, const char* key_file, const char* ca_file = 0);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 初始化SSL客户端
    /// @param ca_file 验证服务端证书(可选)
    virtual bool InitClient(const char* ca_file = 0);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 创建SSL通讯对象，socket和ssl_st资源由调用者释放
    ///        创建失败返回通过SSL::IsEmpty()判断
    /// @param crt_file 服务端证书文件
    /// @param socket socket描述符
    OLSSL NewSSL(int socket);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 释放ssl上下文资源
    void Close();
private:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 验证对方证书
    void SetVerify(const char* ca_crt);
private:
    struct ssl_ctx_st* ssl_ctx_ = nullptr;
};

#endif // SSL_CTX_H

