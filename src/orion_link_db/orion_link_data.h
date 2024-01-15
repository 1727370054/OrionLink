#ifndef ORION_LINK_DATA_H
#define ORION_LINK_DATA_H

#include <map>
#include <vector>
#include <string>

#ifdef ORIONLINKDB_STATIC   /// 静态库
#define ORIONLINKDB_API
#else                       /// 动态库
#ifdef _WIN32
#ifdef ORIONLINKDB_EXPORTS
#define ORIONLINKDB_API __declspec(dllexport)
#else
#define ORIONLINKDB_API __declspec(dllimport)
#endif
#else  // linux mac
#define ORIONLINKDB_API
#endif // _WIN32
#endif // ORIONLINKDB_STATIC

namespace ol
{
    enum ol_field_types {
        OL_TYPE_DECIMAL,
        OL_TYPE_TINY,
        OL_TYPE_SHORT,
        OL_TYPE_LONG,
        OL_TYPE_FLOAT,
        OL_TYPE_DOUBLE,
        OL_TYPE_NULL,
        OL_TYPE_TIMESTAMP,
        OL_TYPE_LONGLONG,
        OL_TYPE_INT24,
        OL_TYPE_DATE,
        OL_TYPE_TIME,
        OL_TYPE_DATETIME,
        OL_TYPE_YEAR,
        OL_TYPE_NEWDATE, /**< Internal to MySQL. Not used in protocol */
        OL_TYPE_VARCHAR,
        OL_TYPE_BIT,
        OL_TYPE_TIMESTAMP2,
        OL_TYPE_DATETIME2, /**< Internal to MySQL. Not used in protocol */
        OL_TYPE_TIME2,     /**< Internal to MySQL. Not used in protocol */
        OL_TYPE_JSON = 245,
        OL_TYPE_NEWDECIMAL = 246,
        OL_TYPE_ENUM = 247,
        OL_TYPE_SET = 248,
        OL_TYPE_TINY_BLOB = 249,
        OL_TYPE_MEDIUM_BLOB = 250,
        OL_TYPE_LONG_BLOB = 251,
        OL_TYPE_BLOB = 252,
        OL_TYPE_VAR_STRING = 253,
        OL_TYPE_STRING = 254,
        OL_TYPE_GEOMETRY = 255
    };

    enum orion_option {
        OL_OPT_CONNECT_TIMEOUT,
        OL_OPT_COMPRESS,
        OL_OPT_NAMED_PIPE,
        OL_INIT_COMMAND,
        OL_READ_DEFAULT_FILE,
        OL_READ_DEFAULT_GROUP,
        OL_SET_CHARSET_DIR,
        OL_SET_CHARSET_NAME,
        OL_OPT_LOCAL_INFILE,
        OL_OPT_PROTOCOL,
        OL_SHARED_MEMORY_BASE_NAME,
        OL_OPT_READ_TIMEOUT,
        OL_OPT_WRITE_TIMEOUT,
        OL_OPT_USE_RESULT,
        OL_REPORT_DATA_TRUNCATION,
        OL_OPT_RECONNECT,
        OL_PLUGIN_DIR,
        OL_DEFAULT_AUTH,
        OL_OPT_BIND,
        OL_OPT_SSL_KEY,
        OL_OPT_SSL_CERT,
        OL_OPT_SSL_CA,
        OL_OPT_SSL_CAPATH,
        OL_OPT_SSL_CIPHER,
        OL_OPT_SSL_CRL,
        OL_OPT_SSL_CRLPATH,
        OL_OPT_CONNECT_ATTR_RESET,
        OL_OPT_CONNECT_ATTR_ADD,
        OL_OPT_CONNECT_ATTR_DELETE,
        OL_SERVER_PUBLIC_KEY,
        OL_ENABLE_CLEARTEXT_PLUGIN,
        OL_OPT_CAN_HANDLE_EXPIRED_PASSWORDS,
        OL_OPT_MAX_ALLOWED_PACKET,
        OL_OPT_NET_BUFFER_LENGTH,
        OL_OPT_TLS_VERSION,
        OL_OPT_SSL_MODE,
        OL_OPT_GET_SERVER_PUBLIC_KEY,
        OL_OPT_RETRY_COUNT,
        OL_OPT_OPTIONAL_RESULTSET_METADATA,
        OL_OPT_SSL_FIPS_MODE
    };

    struct ORIONLINKDB_API OLData
    {
        OLData(const int* d);
        OLData(const char* data = nullptr);

        ///////////////////////////////////////////////////////////////////////////
        /// @brief 读取文件到 data 中，size 大小，申请的 data 空间是堆上的，需要用Drop释放
        /// @param filename 文件名
        /// @return 读取是否成功
        ///////////////////////////////////////////////////////////////////////////
        bool LoadFile(const char *filename);

        ///////////////////////////////////////////////////////////////////////////
        /// @brief 将数据中的二进制数据写入到本地文件中
        /// @param filename 写入的文件名
        /// @return 写入是否成功
        ///////////////////////////////////////////////////////////////////////////
        bool SaveFile(const char* filename);

        ///////////////////////////////////////////////////////////////////////////
        /// @brief 释放 LoadFile 申请的 data 空间
        void Drop();

        ///////////////////////////////////////////////////////////////////////////
        /// @brief UTF8转GBK
        /// @return 转换后的字符串
        ///////////////////////////////////////////////////////////////////////////
        std::string UTF8ToGBK();

        ///////////////////////////////////////////////////////////////////////////
        /// @brief GBK转UTF8
        /// @return 转换后的字符串
        ///////////////////////////////////////////////////////////////////////////
        std::string GBKToUTF8();

        const char* data = nullptr;
        int size = 0;
        ol_field_types type;
    };

    /// 插入和更新的数据结构
    typedef std::map<std::string, OLData> KVData;

    /// 数据列表
    typedef std::vector<std::vector<OLData>> OLROWS;
}

#endif // ORION_LINK_DATA_H

