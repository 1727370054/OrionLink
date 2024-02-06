#ifndef CONFIG_DAO_H
#define CONFIG_DAO_H

#include "msg_comm.pb.h"

namespace ol
{
    class OrionLinkDB;
}

class ConfigDao
{
public:
    virtual ~ConfigDao();

    static ConfigDao *GetInstance()
    {
        static ConfigDao config_dao;
        return &config_dao;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 初始化数据库，开始连接数据库(数据库信息会读取配置文件)
    bool Init();

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
    bool SaveConfig(const msg::Config *config);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 读取配置(微服务获取自己的配置项) proto序列化存储在private_pb字段
    /// @param ip 微服务IP
    /// @param port 微服务端口
    /// @return 返回配置信息
    ///////////////////////////////////////////////////////////////////////////
    msg::Config LoadConfig(const char *ip, int port);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 读取分页配置列表(配置管理工具获取配置)
    /// @param page 页数，从1开始
    /// @param page_count 页显示的记录数量
    /// @return 返回所有分页的配置信息
    ///////////////////////////////////////////////////////////////////////////
    msg::ConfigList LoadAllConfig(int page, int page_count);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 删除配置(通过ip和端口来删除配置项)
    /// @param ip 微服务IP
    /// @param port 微服务端口
    bool DeleteConfig(const char *ip, int port);

private:
    ConfigDao();
    ConfigDao(const ConfigDao &) = delete;
    ConfigDao &operator=(const ConfigDao &) = delete;

private:
    /// MYSQL 数据库上下文
    ol::OrionLinkDB *oldb_ = nullptr;
};

#endif // CONFIG_DAO_H
