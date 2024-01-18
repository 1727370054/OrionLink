#include "log_client.h"
#include "auth_dao.h"
#include "orion_link_db.h"
#include "msg_comm.pb.h"
#include "tools.h"

#include <mutex>
#include <iostream>
#include <string>

using namespace ol;
using namespace std;
using namespace msg;
 
static mutex auth_mutex;

#define AUTH_TABLE "ol_auth"
#define TOKEN_TABLE "ol_token"

bool AuthDAO::Init()
{
    Mutex lock(&auth_mutex);
    if (oldb_ == nullptr)
        oldb_ = new OrionLinkDB();
    if (!oldb_->Init())
    {
        LOGDEBUG("AuthDao oldb_->Init() failed!");
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

bool AuthDAO::Install()
{
    Mutex lock(&auth_mutex);
    if (!oldb_)
    {
        LOGERROR("mysql not init");
        return false;
    }

    string sql = "CREATE TABLE IF NOT EXISTS `ol_auth` (       \
        `id` INT AUTO_INCREMENT,                               \
        `ol_username` VARCHAR(128) ,                           \
        `ol_password` VARCHAR(1024) ,                          \
        `ol_rolename` VARCHAR(128) ,                           \
        PRIMARY KEY(`id`),                                     \
        UNIQUE KEY `ol_username_UNIQUE` (`ol_username`)        \
        );";

    if (!oldb_->Query(sql.c_str(), sql.size()))
    {
        LOGERROR("CREATE TABLE ol_auth failed!");
        return false;
    }
    LOGINFO("CREATE TABLE ol_auth success!");

    sql = "CREATE TABLE IF NOT EXISTS `ol_token` (           \
        `id` INT AUTO_INCREMENT,                             \
        `ol_username` VARCHAR(1024) ,                        \
        `ol_rolename` VARCHAR(128) ,                         \
        `token` VARCHAR(64) ,                                \
        `expired_time` int ,                                 \
        PRIMARY KEY(`id`));";

    if (!oldb_->Query(sql.c_str(), sql.size()))
    {
        LOGERROR("CREATE TABLE ol_token failed!");
        return false;
    }
    LOGINFO("CREATE TABLE ol_token success!");
    return true;
}

bool AuthDAO::AddUser(msg::AddUserReq* user)
{
    KVData data;
    data["ol_username"] = user->username().c_str();
    data["ol_password"] = user->password().c_str();
    data["ol_rolename"] = user->rolename().c_str();

    Mutex lock(&auth_mutex);
    if (!oldb_)
    {
        LOGERROR("mysql not init");
        return false;
    }

    return oldb_->Insert(data, AUTH_TABLE);
}

bool AuthDAO::Login(const msg::LoginReq* user_req, msg::LoginRes* user_res, int timeout_sec)
{
    LOGDEBUG("ConfigDao::LoadConfig");
    string token = "";
    user_res->set_desc(LoginRes::ERROR);

    Mutex lock(&auth_mutex);
    if (!oldb_)
    {
        token = "mysql not init";
        LOGERROR(token.c_str());
        user_res->set_token(token);
        return false;
    }

    if (user_req->username().empty())
    {
        token = "user name is empty";
        LOGERROR(token.c_str());
        user_res->set_token(token);
        return false;
    }
    /// 验证用户名密码
    string table = AUTH_TABLE;
    stringstream ss;
    ss << "select ol_username,ol_rolename from " << table;
    ss << " where ol_username='" << user_req->username() << "'"
       << " and ol_password='" << user_req->password().c_str() << "'";

    auto rows = oldb_->GetResult(ss.str().c_str());
    if (rows.size() == 0)
    {
        token = "username or password error!";
        LOGERROR(token);
        user_res->set_token(token);
        return false;
    }

    string rolename = rows[0][1].data;
    string username = rows[0][0].data;
    user_res->set_rolename(rolename);
    user_res->set_username(username);
    /// 生成token
    table = TOKEN_TABLE;
    int now = time(0);
    int expired_time = now + timeout_sec;
    KVData data;
    data["@token"] = "UUID()";
    data["ol_username"] = username.c_str();
    data["ol_rolename"] = rolename.c_str();
    ss.str("");
    ss << expired_time;
    string expired = ss.str();
    data["expired_time"] = expired.c_str();
    if (!oldb_->Insert(data, table))
    {
        token = "Insert token failed！";
        LOGERROR(token);
        user_res->set_token(token);
        return false;
    }

    /// 通过id获取token
    int id = oldb_->GetInsertID();
    ss.str("");
    ss << "select token, expired_time from " << table << " where id=" << id;
    rows = oldb_->GetResult(ss.str().c_str());
    if (rows.size() <= 0 || rows[0][0].data == NULL || rows[0][0].size <= 0)
    {
        token = "Insert token id error！";
        LOGERROR(token);
        user_res->set_token(token);
        return false;
    }

    token = rows[0][0].data;
    user_res->set_token(token);
    user_res->set_expired_time(atoi(rows[0][1].data));
    user_res->set_desc(LoginRes::OK);
    /// 清理过期登录信息,后面改成用线程定期清理
    ss.str("");
    ss << "delete from " << table << " where expired_time<" << now;
    if (!oldb_->Query(ss.str().c_str()))
    {
        LOGDEBUG(ss.str().c_str());
    }

    return true;
}

bool AuthDAO::CheckToken(msg::MsgHead* head, msg::LoginRes* user_res)
{
    LOGDEBUG("ConfigDao::CheckToken");
    string token = "";
    user_res->set_desc(LoginRes::ERROR);
    if (!head || !user_res || head->token().empty())
    {
        token = "token is null";
        LOGERROR(token.c_str());
        user_res->set_token(token);
        return false;
    }

    token = head->token();
    Mutex lock(&auth_mutex);
    if (!oldb_)
    {
        token = "mysql not init";
        LOGERROR(token.c_str());
        user_res->set_token(token);
        return false;
    }

    /// 验证token的有效性
    string table = TOKEN_TABLE;
    stringstream ss;
    ss << "select ol_username, ol_rolename, expired_time from " << table
        << " where token='" << token << "'";
    auto rows = oldb_->GetResult(ss.str().c_str());
    if (rows.size() == 0)
    {
        token = "token invalid!";
        LOGERROR(token);
        user_res->set_token(token);
        return false;
    }
    user_res->set_desc(LoginRes::OK);
    user_res->set_username(rows[0][0].data);
    user_res->set_rolename(rows[0][1].data);
    user_res->set_expired_time(atoi(rows[0][2].data));
    return true;
}

AuthDAO::AuthDAO()
{
}

AuthDAO::~AuthDAO()
{
}
