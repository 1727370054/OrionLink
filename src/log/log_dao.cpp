#include "log_client.h"
#include "log_dao.h"
#include "orion_link_db.h"
#include "orion_link_data.h"
#include "msg_comm.pb.h"
#include "tools.h"

#include <mutex>

using namespace std;
using namespace msg;
using namespace ol;

static mutex log_mutex;

#define LOG_TABLE "ol_log"

bool LogDAO::Init()
{
    Mutex lock(&log_mutex);
    if (oldb_ == nullptr)
        oldb_ = new OrionLinkDB();
    if (!oldb_->Init())
    {
        LOGDEBUG("LogDAO oldb_->Init() failed!");
        return false;
    }

    oldb_->SetReconnect(true);
    oldb_->SetConnectTimeout(3);

    if (!oldb_->InputDBConfig())
    {
        LOGDEBUG("oldb_->InputDBConfig failed!");
        return false;
    }

    return true;
}

bool LogDAO::Install()
{
    Mutex lock(&log_mutex);
    if (!oldb_)
    {
        LOGERROR("mysql not init");
        return false;
    }

    string sql = "";
    string table_name = LOG_TABLE;

    //如果表不存在则创建
    sql = "CREATE TABLE IF NOT EXISTS `" + table_name + "` ( \
        `id` INT AUTO_INCREMENT,                             \
        `service_name` VARCHAR(16) ,                         \
        `service_ip` VARCHAR(16) ,                           \
        `service_port` INT ,                                 \
        `log_txt` VARCHAR(4096) ,                            \
        `log_time` INT ,                                     \
        `log_level` INT ,                                    \
        PRIMARY KEY(`id`));";

    if (!oldb_->Query(sql.c_str(), sql.size()))
    {
        LOGERROR("CREATE TABLE ol_log failed!");
        return false;
    }
    LOGINFO("CREATE TABLE ol_log success!");

    return true;
}

bool LogDAO::AddLog(msg::AddLogReq* log)
{
    if (!log) 
        return false;

    KVData data;
    data["service_name"] = log->service_name().c_str();
    data["service_ip"] = log->service_ip().c_str();
    int service_port = log->service_port();
    data["service_port"] = &service_port;
    data["log_txt"] = log->log_txt().c_str();
    int log_time = log->log_time();
    data["log_time"] = &log_time;
    int log_level = log->log_level();
    data["log_level"] = &log_level;

    Mutex lock(&log_mutex);
    if (!oldb_)
    {
        LOGERROR("mysql not init");
        return false;
    }
    string table_name = LOG_TABLE;
    return oldb_->InsertBin(data, table_name);
}

LogDAO::LogDAO()
{
}

LogDAO::~LogDAO()
{
}



