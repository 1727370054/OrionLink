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

///////////////////////////////////////////////////////////////////////////
/// @brief 生成md5 128bit(16字节) 
/// @param in_data 输入数据
/// @param in_data_size 输入数据的字节数
/// @param out_md 输出的MD5数据(16字节)
XCOM_API unsigned char* OLMD5(const unsigned char* in_data, unsigned long in_data_size, unsigned char* out_md);

///////////////////////////////////////////////////////////////////////////
/// @brief 生成md5 128bit(16字节) 再经过base64转化为字符串
/// @param in_data 输入数据
/// @param in_data_size 输入数据的字节数
/// @return 输出的MD5 base64 数据(24字节)
XCOM_API std::string OLMD5_base64(const unsigned char* in_data, unsigned long in_data_size);

///////////////////////////////////////////////////////////////////////////
/// @brief 生成base64 返回编码后字节大小
XCOM_API int Base64Encode(const unsigned char* in, int len, char* out_base64);

///////////////////////////////////////////////////////////////////////////
/// @brief 解码base64 返回解码字节大小
XCOM_API int Base64Decode(const char* in, int len, unsigned char* out_data);

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

