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
    /// @brief 初始化，开始连接数据库
    /// @param host 主机IP地址
    /// @param user 用户名
    /// @param password 密码
    /// @param db 数据库
    /// @param port 端口号
    /// @return 连接是否成功
    ///////////////////////////////////////////////////////////////////////////
    bool Init(const char* host, const char* user, const char* password,
        const char* db, unsigned short port = 3306);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 安装数据库的表
    /// @return 安装是否成功
    ///////////////////////////////////////////////////////////////////////////
    bool Install();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 保存配置项，如果已有，就更新
    /// @param config 结构化配置信息
    /// @return 保存是否成功
    ///////////////////////////////////////////////////////////////////////////
    bool SaveConfig(const msg::Config * config);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 读取配置
    /// @param ip 微服务IP
    /// @param port 微服务端口
    /// @return 返回配置信息
    ///////////////////////////////////////////////////////////////////////////
    msg::Config LoadConfig(const char *ip, int port);
private:
    ConfigDao();
    ConfigDao(const ConfigDao &) = delete;
    ConfigDao& operator=(const ConfigDao&) = delete;
private:
    /// MYSQL 数据库上下文
    ol::OrionLinkDB* oldb_ = nullptr;
};

#endif // CONFIG_DAO_H

