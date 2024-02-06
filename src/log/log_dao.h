#ifndef LOG_DAO_H
#define LOG_DAO_H

namespace msg
{
    class AddLogReq;
}

namespace ol
{
    class OrionLinkDB;
}

class LogDAO
{
public:
    ~LogDAO();
    static LogDAO* GetInstance()
    {
        static LogDAO log_dao;
        return &log_dao;
    }

    bool Init();

    bool Install();

    bool AddLog(msg::AddLogReq *log);
private:
    LogDAO();
    LogDAO(const LogDAO&) = delete;
    LogDAO& operator=(const LogDAO&) = delete;

private:
    ol::OrionLinkDB* oldb_ = nullptr;
};

#endif // LOG_DAO_H

