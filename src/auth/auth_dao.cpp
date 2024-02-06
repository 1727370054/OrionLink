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
        `ol_email`    VARCHAR(128) ,                           \
        PRIMARY KEY(`id`),                                     \
        UNIQUE KEY `ol_username_UNIQUE` (`ol_username`),       \
        UNIQUE KEY `ol_email_UNIQUE` (`ol_email`)              \
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
    data["ol_email"] = user->email().c_str();

    Mutex lock(&auth_mutex);
    if (!oldb_)
    {
        LOGERROR("mysql not init");
        return false;
    }

    return oldb_->Insert(data, AUTH_TABLE);
}

bool AuthDAO::BuildToken(const std::string& username, const std::string& rolename, msg::LoginRes* user_res, int timeout_sec)
{
    stringstream ss;
    /// 生成token
    string table = TOKEN_TABLE;
    string token = "";
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
    auto rows = oldb_->GetResult(ss.str().c_str());
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

    return true;
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
    
    return BuildToken(username, rolename, user_res, timeout_sec);
}

bool AuthDAO::EmailLogin(const msg::EmailLoginReq* user_req, msg::LoginRes* user_res, int timeout_sec)
{
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

    if (user_req->email().empty())
    {
        token = "email is empty";
        LOGERROR(token.c_str());
        user_res->set_token(token);
        return false;
    }

    string table = AUTH_TABLE;
    stringstream ss;
    ss << "select ol_username,ol_rolename, ol_email from " << table;
    ss << " where ol_email='" << user_req->email() << "'";

    auto rows = oldb_->GetResult(ss.str().c_str());
    if (rows.size() == 0)
    {
        token = "email not exists!";
        LOGERROR(token);
        user_res->set_token(token);
        return false;
    }

    string username = rows[0][0].data;
    string rolename = rows[0][1].data;
    user_res->set_rolename(rolename);
    user_res->set_username(username);

    return BuildToken(username, rolename, user_res, timeout_sec);
}

bool AuthDAO::ForgetPassword(const msg::RegisterUserReq* user_req, msg::MessageRes* user_res)
{
    string desc = "";
    user_res->set_return_(MessageRes::USER_NOT_EXISTS);

    Mutex lock(&auth_mutex);
    if (!oldb_)
    {
        desc = "mysql not init";
        LOGERROR(desc.c_str());  
        user_res->set_desc(desc);
        return false;
    }

    if (user_req->email().empty() || user_req->username().empty())
    {
        desc = "username or email is empty";
        LOGERROR(desc.c_str());
        user_res->set_desc(desc);
        return false;
    }

    string table = AUTH_TABLE;
    stringstream ss;
    ss << "select ol_email from " << table;
    ss << " where ol_username='" << user_req->username() << "'";

    auto rows = oldb_->GetResult(ss.str().c_str());
    if (rows.size() == 0)
    {
        desc = "user not exists!";
        LOGERROR(desc);
        user_res->set_desc(desc);
        return false;
    }

    string email = rows[0][0].data;
    if (email != user_req->email())
    {
        desc = "bind email error!";
        LOGERROR(desc);
        user_res->set_return_(MessageRes::BIND_EMAIL_ERR);
        user_res->set_desc(desc);
        return false;
    }

    table = AUTH_TABLE;
    stringstream where;
    where << " where ol_username='" << user_req->username() << "'";
    KVData data;
    data["ol_password"] = user_req->password().c_str();

    return oldb_->Update(data, table, where.str()) != -1;
}

bool AuthDAO::CheckToken(msg::MsgHead* head, msg::LoginRes* user_res, int timeout_sec)
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
        << " where ol_username='" << head->username() << "'";
    auto rows = oldb_->GetResult(ss.str().c_str());
    if (rows.size() != 0)
    {
        /// token未过期，直接返回错误
        user_res->set_desc(LoginRes::ERROR);
        return false;
    }

    /// token过期，更新token
    string rolename = head->rolename();
    string username = head->username();
    user_res->set_username(username);
    user_res->set_rolename(rolename);

    return BuildToken(username, rolename, user_res, timeout_sec);
}

void AuthDAO::ClearToken()
{
    string table = TOKEN_TABLE;
    int now = time(0);
    stringstream ss;
    /// 清理过期登录信息
    ss << "delete from " << table << " where expired_time<" << now;
    Mutex lock(&auth_mutex);
    if (!oldb_->Query(ss.str().c_str()))
    {
        LOGDEBUG(ss.str().c_str());
    }
}

AuthDAO::AuthDAO()
{
}

AuthDAO::~AuthDAO()
{
}
