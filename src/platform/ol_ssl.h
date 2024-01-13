#ifndef OL_SSL_H
#define OL_SSL_H

#ifdef _WIN32
#ifdef XCOM_EXPORTS
#define XCOM_API __declspec(dllexport)
#else
#define XCOM_API __declspec(dllimport)
#endif
#else
#define XCOM_API
#endif // _WIN32

struct ssl_st;

class XCOM_API OLSSL
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 判断对象是否为空
    bool IsEmpty() { return ssl_ == nullptr; }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 服务端接收ssl协议
    bool Accept();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 客户端处理ssl握手
    bool Connect();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 通过openssl加密写入
    /// @param data 需要写入的数据
    /// @param data_size 需要写入的数据的大小
    int Write(const void* data, int data_size);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 通过openssl解密读取
    /// @param buffer 读数据缓冲区
    /// @param buffer_size 读数据缓冲区大小
    int Read(void* buffer, int buffer_size);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 释放ssl资源
    void Close();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 打印通信使用的算法
    void PrintCipher();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 打印对方证书信息
    void PrintCert();

    void set_ssl_st(struct ssl_st* ssl) { ssl_ = ssl; }
    struct ssl_st* ssl() { return ssl_; }
private:
    struct ssl_st* ssl_ = nullptr;
};

#endif // OL_SSL_H

