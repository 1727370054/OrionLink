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
    /// @brief �ж϶����Ƿ�Ϊ��
    bool IsEmpty() { return ssl_ == nullptr; }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ����˽���sslЭ��
    bool Accept();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief �ͻ��˴���ssl����
    bool Connect();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ͨ��openssl����д��
    /// @param data ��Ҫд�������
    /// @param data_size ��Ҫд������ݵĴ�С
    int Write(const void* data, int data_size);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ͨ��openssl���ܶ�ȡ
    /// @param buffer �����ݻ�����
    /// @param buffer_size �����ݻ�������С
    int Read(void* buffer, int buffer_size);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief �ͷ�ssl��Դ
    void Close();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ��ӡͨ��ʹ�õ��㷨
    void PrintCipher();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ��ӡ�Է�֤����Ϣ
    void PrintCert();

    void set_ssl_st(struct ssl_st* ssl) { ssl_ = ssl; }
    struct ssl_st* ssl() { return ssl_; }
private:
    struct ssl_st* ssl_ = nullptr;
};

#endif // OL_SSL_H

