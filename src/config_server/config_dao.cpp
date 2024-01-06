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

bool ConfigDao::Init(const char* host, const char* user, const char* password, 
    const char* db, unsigned short port)
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

    if (!oldb_->Connect(host, user, password, db, port))
    {
        LOGDEBUG("mysql conncet failed!");
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
    sql = "CREATE TABLE IF NOT EXISTS `ol_service_config` (                         \
        `id` INT(11) NOT NULL AUTO_INCREMENT,                                       \
        `service_name` VARCHAR(64) COLLATE utf8_bin NOT NULL,                       \
        `service_port` INT(11) NOT NULL,                                            \
        `service_ip` VARCHAR(16) COLLATE utf8_bin NOT NULL,                         \
        `private_pb` VARCHAR(4096) CHARACTER                                        \
        SET utf8 COLLATE utf8_bin DEFAULT '',                                       \
        `protocol` VARCHAR(4096) CHARACTER                                          \
        SET utf8 COLLATE utf8_bin DEFAULT '',                                       \
        PRIMARY KEY(`id`)                                                           \
        ) ENGINE = INNODB DEFAULT CHARSET = utf8 COLLATE = utf8_bin; ";

    if (!oldb_->Query(sql.c_str(), sql.size()))
    {
        LOGINFO("create table `ol_service_config` failed!");
        return false;
    }
    LOGINFO("create table `ol_service_config` success!");
    return true;
}

bool ConfigDao::SaveConfig(const msg::Config* config)
{
    Mutex lock(&oldb_mutex);
    if (!oldb_)
    {
        LOGERROR("save config failed! mysql not init");
        return false;
    }
    string table_name = CONFIG_TABLE;
    KVData data; 
    string service_ip = config->service_ip();
    int service_port = config->service_port();
    data["service_name"] = OLData(config->service_name().c_str());
    data["service_port"] = OLData(&service_port);
    data["service_ip"] = OLData(service_ip.c_str());
    data["private_pb"].data = config->private_pb().c_str();
    data["private_pb"].size = config->private_pb().size();
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

    bool ret = oldb_->InsertBin(data,table_name);
    if (ret)
        LOGDEBUG("配置插入成功!");
    else
        LOGDEBUG("配置插入失败!");
    return ret;
}

msg::Config ConfigDao::LoadConfig(const char* ip, int port)
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

ConfigDao::ConfigDao()
{
}

ConfigDao::~ConfigDao()
{
}
