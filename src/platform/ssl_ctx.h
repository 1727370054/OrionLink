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
    /// @brief ��ʼ��SSL������
    /// @param crt_file �����֤���ļ�
    /// @param key_file ������˽Կ�ļ�
    /// @param ca_file ��֤�ͻ���֤��(��ѡ)
    virtual bool InitServer(const char* crt_file, const char* key_file, const char* ca_file = 0);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ��ʼ��SSL�ͻ���
    /// @param ca_file ��֤�����֤��(��ѡ)
    virtual bool InitClient(const char* ca_file = 0);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ����SSLͨѶ����socket��ssl_st��Դ�ɵ������ͷ�
    ///        ����ʧ�ܷ���ͨ��SSL::IsEmpty()�ж�
    /// @param crt_file �����֤���ļ�
    /// @param socket socket������
    OLSSL NewSSL(int socket);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief �ͷ�ssl��������Դ
    void Close();
private:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief ��֤�Է�֤��
    void SetVerify(const char* ca_crt);
private:
    struct ssl_ctx_st* ssl_ctx_ = nullptr;
};

#endif // SSL_CTX_H

