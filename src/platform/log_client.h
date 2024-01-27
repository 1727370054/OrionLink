#ifndef LOG_CLIENT_H
#define LOG_CLIENT_H

#ifdef _WIN32
#ifdef XCOM_EXPORTS
#define XCOM_API __declspec(dllexport)
#else
#define XCOM_API __declspec(dllimport)
#endif
#else
#define XCOM_API
#endif // _WIN32

#include "service_client.h"

#include <fstream>
#include <list>
#include <mutex>

namespace ol
{
    XCOM_API void Log(msg::LogLevel level, std::string message, const char* filename, int line);
}

#define LOGDEBUG(message) ol::Log(msg::LOG_DEBUG, message, __FILE__, __LINE__)
#define LOGINFO(message) ol::Log(msg::LOG_INFO, message, __FILE__, __LINE__)
#define LOGERROR(message) ol::Log(msg::LOG_ERROR, message, __FILE__, __LINE__)
#define LOGFATAL(message) ol::Log(msg::LOG_FATAL, message, __FILE__, __LINE__)

class XCOM_API LogClient : public ServiceClient
{
public:
    ~LogClient();

    static LogClient* GetInstance()
    {
        static LogClient log_client;
        log_client.set_auto_delete(false);
        return &log_client;
    }

    void AddLog(const msg::AddLogReq* log);

    void StartLog();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 定时器回调函数
    virtual void TimerCallback() override;

    void set_log_level(msg::LogLevel level) { log_level_ = level; }

    void set_local_file(std::string filename)
    {
        log_ofs_.open(filename);
    }

    void set_service_name(std::string service_name) { service_name_ = service_name; }
    void set_service_port(int port) { service_port_ = port; }
private:
    LogClient();
    LogClient(const LogClient&) = delete;
    LogClient& operator=(const LogClient&) = delete;

private:
    msg::LogLevel log_level_ = msg::LOG_INFO;
    std::ofstream log_ofs_;
    std::list<msg::AddLogReq> logs_;
    std::mutex logs_mutex_;
    std::string service_name_ = "";
    int service_port_ = 0;
};

#endif // LOG_CLIENT_H
