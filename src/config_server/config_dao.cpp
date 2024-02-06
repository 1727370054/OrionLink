#include "log_client.h"
#include "config_dao.h"
#include "orion_link_db.h"
#include "tools.h"

#include <string>
#include <mutex>
#include <cstring>

using namespace std;
using namespace ol;
using namespace msg;

#define CONFIG_TABLE "ol_service_config"

static mutex oldb_mutex;

bool ConfigDao::Init()
{
    Mutex lock(&oldb_mutex);
    if (!oldb_)
        oldb_ = new OrionLinkDB();

    if (!oldb_->Init())
    {
        LOGDEBUG("mysql init failed!");
        delete oldb_;
        return false;
    }

    oldb_->SetReconnect();
    oldb_->SetConnectTimeout(3);

    if (!oldb_->InputDBConfig())
    {
        LOGDEBUG("oldb_->InputDBConfig failed!");
        return false;
    }

    return true;
}

bool ConfigDao::Install()
{
    Mutex lock(&oldb_mutex);
    if (!oldb_)
    {
        LOGERROR("create table failed! mysql not init");
        return false;
    }
    string sql = "";
    sql = "CREATE TABLE IF NOT EXISTS `ol_service_config` ( \
        `id` INT AUTO_INCREMENT,                            \
        `service_name` VARCHAR(16) ,                        \
        `service_ip` VARCHAR(16) ,                          \
        `service_port` INT ,                                \
        `private_pb` BLOB ,                                 \
        `protocol` VARCHAR(4096) ,                          \
        PRIMARY KEY(`id`));";

    if (!oldb_->Query(sql.c_str(), sql.size()))
    {
        LOGINFO("create table `ol_service_config` failed!");
        return false;
    }
    LOGINFO("create table `ol_service_config` success!");
    return true;
}

bool ConfigDao::SaveConfig(const msg::Config *config)
{
    Mutex lock(&oldb_mutex);
    if (!oldb_)
    {
        LOGERROR("save config failed! mysql not init");
        return false;
    }
    if (!config || config->service_ip().empty())
    {
        LOGERROR("save config failed! config is null or service ip empty");
        return false;
    }

    string table_name = CONFIG_TABLE;
    KVData data;
    string service_ip = config->service_ip();
    int service_port = config->service_port();
    data["service_name"] = OLData(config->service_name().c_str());
    data["service_port"] = OLData(&service_port);
    data["service_ip"] = OLData(service_ip.c_str());

    /// 再序列化一次，把整个config序列化存到
    string private_pb = config->SerializeAsString();
    data["private_pb"].data = private_pb.c_str();
    data["private_pb"].size = private_pb.size();
    data["protocol"].data = config->protocol().c_str();
    data["protocol"].size = config->protocol().size();

    /// 如果记录存在，则修改配置信息
    stringstream ss;
    ss << " where service_ip='" << service_ip << "' and service_port=" << service_port;
    string where = ss.str();
    string sql = "select id from ";
    sql += table_name;
    sql += where;
    auto rows = oldb_->GetResult(sql.c_str());
    if (rows.size() > 0)
    {
        int count = oldb_->UpdateBin(data, table_name, where);
        if (count >= 0)
        {
            LOGDEBUG("配置更新成功!");
            return true;
        }
        LOGDEBUG("配置更新失败!");
        return false;
    }

    bool ret = oldb_->InsertBin(data, table_name);
    if (ret)
        LOGDEBUG("配置插入成功!");
    else
        LOGDEBUG("配置插入失败!");
    return ret;
}

msg::Config ConfigDao::LoadConfig(const char *ip, int port)
{
    Config config;
    Mutex lock(&oldb_mutex);
    if (!oldb_)
    {
        LOGERROR("download config failed! mysql not init");
        return config;
    }
    if (!ip || strlen(ip) == 0 || port <= 0 || port > 65535)
    {
        LOGDEBUG("download config failed! ip or port error");
        return config;
    }

    string table_name = CONFIG_TABLE;
    stringstream ss;
    ss << "select private_pb from " << table_name;
    ss << " where service_ip='" << ip << "' and service_port=" << port;
    auto rows = oldb_->GetResult(ss.str().c_str());
    config.set_service_ip(ip);
    config.set_service_port(port);
    if (rows.size() == 0)
    {
        LOGERROR("download config failed! not result");
        return config;
    }

    /// 只取一条数据
    auto row = rows[0];
    if (!config.ParseFromArray(row[0].data, row[0].size))
    {
        LOGERROR("download config failed! ParseFromArray error");
        return config;
    }
    LOGDEBUG("download config success!");

    return config;
}

msg::ConfigList ConfigDao::LoadAllConfig(int page, int page_count)
{
    msg::ConfigList config_list;
    LOGDEBUG("LoadAllConfig");
    Mutex lock(&oldb_mutex);
    if (!oldb_)
    {
        LOGERROR("download all config failed! mysql not init");
        return config_list;
    }
    if (page <= 0 || page_count <= 0)
    {
        LOGERROR("download all config failed! page or page_count error");
        return config_list;
    }
    string table_name = CONFIG_TABLE;
    stringstream ss;
    /// select * from table limit 0, 10 ... 10,10, ... 20, 10
    ss << "select `service_name`, `service_ip`, `service_port` from " << table_name;
    ss << " order by id desc";
    ss << " limit " << (page - 1) * page_count << ", " << page_count;
    auto rows = oldb_->GetResult(ss.str().c_str());
    /// 遍历结果集插入到proto中
    for (const auto &row : rows)
    {
        auto conf = config_list.add_configs();
        conf->set_service_name(row[0].data);
        conf->set_service_ip(row[1].data);
        conf->set_service_port(atoi(row[2].data));
    }

    return config_list;
}

bool ConfigDao::DeleteConfig(const char *ip, int port)
{
    Mutex lock(&oldb_mutex);
    if (!oldb_)
    {
        LOGERROR("delete config failed! mysql not init");
        return false;
    }
    if (!ip || strlen(ip) == 0 || port < 0 || port > 65535)
    {
        LOGDEBUG("delete config failed! ip or port error");
        return false;
    }
    string table_name = CONFIG_TABLE;
    stringstream ss;
    ss << "delete from " << table_name;
    ss << " where service_ip='" << ip << "' and service_port=" << port;
    return oldb_->Query(ss.str().c_str(), ss.str().size());
}

ConfigDao::ConfigDao()
{
}

ConfigDao::~ConfigDao()
{
}
