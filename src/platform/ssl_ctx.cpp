#include "ssl_ctx.h"
#include "tools.h"

#include <iostream>
#include <cstring>
#include <openssl/ssl.h>
#include <openssl/err.h>

using namespace std;


///@brief 验证证书的回调
static int SVerifyCallback(int preverify_ok, X509_STORE_CTX* x509_ctx)
{
    if (preverify_ok == 0)
    {
        LOGERROR("SSL cert validata failed!");
    }
    else
    {
        LOGINFO("SSL cert validata success!");
    }
    /// 可以进一步验证，比如验证证书的域名是否正确
    return preverify_ok;
}

bool SSLCtx::InitServer(const char* crt_file, const char* key_file, const char* ca_file)
{
    /// 创建服务器 ssl ctx上下文
    ssl_ctx_ = SSL_CTX_new(TLS_server_method());
    if (!ssl_ctx_)
    {
        LOGERROR("SSL_CTX_new TLS_server_method failed!");
        return false;
    }
    /// 加载证书，私钥，并验证
    int ret = SSL_CTX_use_certificate_file(ssl_ctx_, crt_file, SSL_FILETYPE_PEM);
    if (ret <= 0)
    {
        ERR_print_errors_fp(stderr);
        return false;
    }
    cout << "Load certificate success!" << endl;
    ret = SSL_CTX_use_PrivateKey_file(ssl_ctx_, key_file, SSL_FILETYPE_PEM);
    if (ret <= 0)
    {
        ERR_print_errors_fp(stderr);
        return false;
    }
    cout << "Load PrivateKey success!" << endl;
    ret = SSL_CTX_check_private_key(ssl_ctx_);
    if (ret <= 0)
    {
        LOGDEBUG("private key does not match the certificate!");
        return false;
    }
    LOGDEBUG("check_private_key success!");
    /// 验证客户端的证书
    SetVerify(ca_file);
    return true;
}

bool SSLCtx::InitClient(const char* ca_file)
{
    /// 创建客户端 ssl ctx上下文
    ssl_ctx_ = SSL_CTX_new(TLS_client_method());
    if (!ssl_ctx_)
    {
        LOGERROR("SSL_CTX_new TLS_client_method failed!");
        return false;
    }
    /// 验证服务器的证书
    SetVerify(ca_file);
    return true;
}

OLSSL SSLCtx::NewSSL(int socket)
{
    OLSSL olssl;
    if (!ssl_ctx_)
    {
        LOGDEBUG("ssl_ctx_ is null");
        return olssl;
    }
    auto ssl = SSL_new(ssl_ctx_);
    if (!ssl)
    {
        LOGDEBUG("SSL_new failed");
        return olssl;
    }
    /// 如果socket = -1 bufferevent会自己创建(这里可以不设置)
    if (socket > 0)
        SSL_set_fd(ssl, socket);
    olssl.set_ssl_st(ssl);
    return olssl;
}

void SSLCtx::Close()
{
    if (ssl_ctx_)
    {
        SSL_CTX_free(ssl_ctx_);
        ssl_ctx_ = nullptr;
    }
}

void SSLCtx::SetVerify(const char* ca_crt)
{
    if (!ca_crt || !ssl_ctx_ || strlen(ca_crt) == 0) return;
    /// 设定验证对方证书
    SSL_CTX_set_verify(ssl_ctx_, SSL_VERIFY_PEER, SVerifyCallback);
    SSL_CTX_load_verify_locations(ssl_ctx_, ca_crt, 0);
}

SSLCtx::SSLCtx()
{
    OpenSSL_add_all_algorithms();
    /// 为打印调试信息做准备
    SSL_load_error_strings();
}

SSLCtx::~SSLCtx()
{

}
