#include "log_client.h"
#include "tools.h"

#include <string>

using namespace std;
using namespace msg;

#define LOG_LIST_MAX 100

void ol::Log(msg::LogLevel level, std::string msg, const char* filename, int line)
{
    AddLogReq req;
    req.set_log_level(level);
    req.set_log_txt(msg);
    req.set_filename(filename);
    req.set_line(line);

    LogClient::GetInstance()->AddLog(&req);
}

void LogClient::AddLog(const msg::AddLogReq* req)
{
    if (!req) return;

    if (req->log_level() < log_level_) return;

    string log_str = "DEBUG";
    switch (req->log_level())
    {
    case LOG_DEBUG:
        log_str = "DEBUG";
        break;
    case LOG_INFO:
        log_str = "INFO";
        break;
    case LOG_ERROR:
        log_str = "ERROR";
        break;
    case LOG_FATAL:
        log_str = "FATAL";
        break;
    default:
        break;
    }

    string log_time = GetCurTime(0, "%F %T");
    stringstream log_txt;
    log_txt << log_time << " - [" << log_str << "] " << req->filename()
        << "<line:" << req->line() << "> \n";
    log_txt << req->log_txt() << "\n";
    cout << log_txt.str() << endl;

    if (log_ofs_.is_open())
    {
        log_ofs_.write(log_txt.str().c_str(), log_txt.str().size());
    }

    AddLogReq tmp = *req;
    if (tmp.log_time() <= 0)
    {
        tmp.set_log_time(time(0));
    }
    tmp.set_service_name(service_name_);
    tmp.set_service_port(service_port_);

    logs_mutex_.lock();
    if (logs_.size() > LOG_LIST_MAX)
    {
        logs_.pop_front();
    }
    logs_.push_back(tmp);
    logs_mutex_.unlock();
}

void LogClient::StartLog()
{
    if (strlen(server_ip()) == 0)
        set_server_ip("127.0.0.1");
    if (server_port() <= 0)
        set_server_port(LOG_PORT);

    set_auto_connect(true);
    set_timer_ms(100);

    StartConnect();
}

void LogClient::TimerCallback()
{
    for (;;)
    {
        AddLogReq log;
        {
            Mutex lock(&logs_mutex_);
            if (logs_.empty())
                return;
            log = logs_.front();
            logs_.pop_front();
        }
        SendMsg(MSG_ADD_LOG_REQ, &log);
    }
}

LogClient::LogClient()
{
}

LogClient::~LogClient()
{
}

