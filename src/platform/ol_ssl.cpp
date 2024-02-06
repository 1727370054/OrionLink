#include "log_client.h"
#include "ol_ssl.h"
#include "tools.h"

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <iostream>

using namespace std;

bool OLSSL::Accept()
{
    if (!ssl_) return false;
    /// 建立ssl连接验证，密钥协商
    int ret = SSL_accept(ssl_);
    if (ret <= 0)
    {
        LOGERROR("SSL_accept failed!");
        ERR_print_errors_fp(stderr);
        return false;
    }

    return true;
}

bool OLSSL::Connect()
{
    /// 要保证socket的connect已经完成
    if (!ssl_)
        return false;
    int ret = SSL_connect(ssl_);
    if (ret <= 0)
    {
        LOGERROR("SSL_connect failed!");
        ERR_print_errors_fp(stderr);
        return false;
    }
    PrintCipher();
    PrintCert();
    return true;
}

int OLSSL::Write(const void* data, int data_size)
{
    if (!ssl_) return 0;
    return SSL_write(ssl_, data, data_size);
}

int OLSSL::Read(void* buffer, int buffer_size)
{
    if (!ssl_) return 0;
    return SSL_read(ssl_, buffer, buffer_size);
}

void OLSSL::Close()
{
    if (ssl_)
    {
        SSL_shutdown(ssl_);
        SSL_free(ssl_);
        ssl_ = nullptr;
    }
}

void OLSSL::PrintCipher()
{
    if (!ssl_) return;
    LOGINFO(SSL_get_cipher(ssl_));
}

void OLSSL::PrintCert()
{
    if (!ssl_) return;
    /// 获取到证书
    auto cert = SSL_get_peer_certificate(ssl_);
    if (cert == NULL)
    {
        LOGERROR("no certificate");
        return;
    }
    char buf[1024] = { 0 };
    auto sname = X509_get_subject_name(cert);
    char* str = X509_NAME_oneline(sname, buf,sizeof(buf));
    if (str)
    {
        stringstream ss;
        ss << "subject: " << str;
        LOGINFO(ss.str().c_str());
    }
    /// 证书发行方
    auto issuer = X509_get_issuer_name(cert);
    str = X509_NAME_oneline(issuer, buf, sizeof(buf));
    if (str)
    {
        stringstream ss;
        ss << "issuer: " << str;
        LOGINFO(ss.str().c_str());
    }
    X509_free(cert);
}
