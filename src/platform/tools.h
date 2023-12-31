#ifndef TOOLS_H
#define TOOLS_H

#ifdef _WIN32
#ifdef XCOM_EXPORTS
#define XCOM_API __declspec(dllexport)
#else
#define XCOM_API __declspec(dllimport)
#endif
#else
#define XCOM_API
#endif // _WIN32

#include <string>
#include <mutex>
#include <iostream>
#include <sstream>

#define LOG(level, msg) std::cout << "[" << level << "]" <<":"<< __FILE__ << ":"<<__LINE__ << \
    "\n" << msg << "\n" <<std::endl 
#define LOGDEBUG(msg) LOG("DEBUG", msg)
#define LOGINFO(msg)  LOG("INFO", msg)  
#define LOGERROR(msg) LOG("ERROR", msg)  

XCOM_API std::string GetDirData(std::string path);

class XCOM_API Mutex
{
public:
    Mutex(std::mutex* mtx)
        :mtx_(mtx)
    {
        mtx_->lock();
    }
    ~Mutex()
    {
        mtx_->unlock();
    }
private:
    std::mutex* mtx_;
};

#endif

