#ifndef CONFIG_DAO_H
#define CONFIG_DAO_H

#include "msg_comm.pb.h"

namespace ol {
    class OrionLinkDB;
}

class ConfigDao
{
public:
    virtual ~ConfigDao();

    static ConfigDao* GetInstance()
    {
        static ConfigDao config_dao;
        return &config_dao;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ��ʼ������ʼ�������ݿ�
    /// @param host ����IP��ַ
    /// @param user �û���
    /// @param password ����
    /// @param db ���ݿ�
    /// @param port �˿ں�
    /// @return �����Ƿ�ɹ�
    ///////////////////////////////////////////////////////////////////////////
    bool Init(const char* host, const char* user, const char* password,
        const char* db, unsigned short port = 3306);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ��װ���ݿ�ı�
    /// @return ��װ�Ƿ�ɹ�
    ///////////////////////////////////////////////////////////////////////////
    bool Install();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ���������������У��͸���
    /// @param config �ṹ��������Ϣ
    /// @return �����Ƿ�ɹ�
    ///////////////////////////////////////////////////////////////////////////
    bool SaveConfig(const msg::Config * config);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ��ȡ����
    /// @param ip ΢����IP
    /// @param port ΢����˿�
    /// @return ����������Ϣ
    ///////////////////////////////////////////////////////////////////////////
    msg::Config LoadConfig(const char *ip, int port);
private:
    ConfigDao();
    ConfigDao(const ConfigDao &) = delete;
    ConfigDao& operator=(const ConfigDao&) = delete;
private:
    /// MYSQL ���ݿ�������
    ol::OrionLinkDB* oldb_ = nullptr;
};

#endif // CONFIG_DAO_H

