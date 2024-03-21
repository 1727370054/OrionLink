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
#include <list>
#include <vector>
#include <iostream>
#include <sstream>

XCOM_API std::string GetDirData(std::string path);

struct ToolFileInfo
{
    std::string filename = "";
    long long filesize = 0;
    bool is_dir = false;
    long long time_write = 0;
    std::string time_str = "";
};

XCOM_API std::list<ToolFileInfo> GetDirList(std::string path);

XCOM_API std::string GetIconFilename(std::string filename, bool is_dir);

XCOM_API std::string GetFileSuffix(std::string filename);

XCOM_API std::string GetSizeString(long long size);

XCOM_API std::string FormatDir(const std::string &dir);

XCOM_API void StringSplit(std::vector<std::string> &vec, std::string str, std::string find);

XCOM_API void NewDir(std::string path);

XCOM_API void DelFile(std::string path, bool is_dir);

XCOM_API void DeleteDirectoryAndFiles(const std::string &path);

XCOM_API long long GetDirSize(const char *path);

XCOM_API bool GetDiskSize(const char *path, unsigned long long *avail, unsigned long long *total, unsigned long long *free);

XCOM_API bool Rename(const char *old_filename, const char *new_filename);

///////////////////////////////////////////////////////////////////////////
/// @brief 生成md5 128bit(16字节)
/// @param in_data 输入数据
/// @param in_data_size 输入数据的字节数
/// @param out_md 输出的MD5数据(16字节)
XCOM_API unsigned char *OLMD5(const unsigned char *in_data, unsigned long in_data_size, unsigned char *out_md);

///////////////////////////////////////////////////////////////////////////
/// @brief 生成md5 128bit(16字节) 再经过base64转化为字符串
/// @param in_data 输入数据
/// @param in_data_size 输入数据的字节数
/// @return 输出的MD5 base64 数据(24字节)
XCOM_API std::string OLMD5_base64(const unsigned char *in_data, unsigned long in_data_size);

///////////////////////////////////////////////////////////////////////////
/// @brief 生成base64 返回编码后字节大小
XCOM_API int Base64Encode(const unsigned char *in, int len, char *out_base64);

///////////////////////////////////////////////////////////////////////////
/// @brief 解码base64 返回解码字节大小
XCOM_API int Base64Decode(const char *in, int len, unsigned char *out_data);

///////////////////////////////////////////////////////////////////////////
/// @brief 通过域名获取IP地址(只取第一个)
/// windows ->> C:\Windows\System32\drivers\etc
/// Linux   ->> /etc/hosts
/// 127.0.0.1 ol_gateway_server
/// 127.0.0.1 ol_register_server
XCOM_API std::string GetHostByName(std::string host_name);

///////////////////////////////////////////////////////////////////////////
/// @brief 同过smtp协议发送发送邮件
/// @param smtpServer 可以使用域名
XCOM_API bool SendEmail(const std::string &smtpServer, int port, const std::string &from,
                        const std::string &to, const std::string &subject, const std::string &message, const std::string &username,
                        const std::string &password);

// 生成指定长度的纯数字验证码
XCOM_API std::string GenerateNumericCode(int length);

/*********************************时间格式***********************************
%a 星期几的简写
%A 星期几的全称
%b 月份的简写
%B 月份的全称
%c 标准的日期的时间串
%C 年份的后两位数字
%d 十进制表示的每月的第几天
%D 月/天/年
%e 在两字符域中，十进制表示的每月的第几天
%F 年-月-日
%g 年份的后两位数字，使用基于周的年
%G 年分，使用基于周的年
%h 简写的月份名
%H 24小时制的小时
%I 12小时制的小时
%j 十进制表示的每年的第几天
%m 十进制表示的月份
%M 十时制表示的分钟数
%n 新行符
%p 本地的AM或PM的等价显示
%r 12小时的时间
%R 显示小时和分钟：hh:mm
%S 十进制的秒数
%t 水平制表符
%T 显示时分秒：hh:mm:ss
%u 每周的第几天，星期一为第一天 （值从0到6，星期一为0）
%U 第年的第几周，把星期日做为第一天（值从0到53）
%V 每年的第几周，使用基于周的年
%w 十进制表示的星期几（值从0到6，星期天为0）
%W 每年的第几周，把星期一做为第一天（值从0到53）
%x 标准的日期串
%X 标准的时间串
%y 不带世纪的十进制年份（值从0到99）
%Y 带世纪部分的十制年份
%z，%Z 时区名称，如果不能得到时区名称则返回空字符。
%% 百分号下面的程序则显示当前的完整日期：
***************************************************************************/
XCOM_API std::string GetCurTime(int timestamp, std::string format = "%F %T");

class XCOM_API Mutex
{
public:
    Mutex(std::mutex *mtx)
        : mtx_(mtx)
    {
        mtx_->lock();
    }
    ~Mutex()
    {
        mtx_->unlock();
    }

private:
    std::mutex *mtx_;
};

#endif

class XCOM_API OLAES
{
public:
    static OLAES *Create();
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 秘钥长度 128位（16字节） 192位 （24字节） 256位 (32字节)
    /// 长度不能超过32字节，返回失败
    /// 秘钥不足自动补充
    /// @param key 秘钥
    /// @param key_size 秘钥长度 字节 <=32 会自动补秘钥
    /// @param is_enc true 加密 false 解密
    /// @return 设置成功失败
    virtual bool SetKey(const char *key, int key_byte_size, bool is_enc) = 0;

    /// @brief 清理空间，删除对象
    virtual void Drop() = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 加解密
    /// @param in 输入数据
    /// @param in_size 输入数据大小
    /// @param out 输出 数据空间要保证16字节的倍数
    /// @return  输出大小，失败返回<=0
    virtual long long Decrypt(const unsigned char *in, long long in_size, unsigned char *out) = 0;
    virtual long long Encrypt(const unsigned char *in, long long in_size, unsigned char *out) = 0;
};
