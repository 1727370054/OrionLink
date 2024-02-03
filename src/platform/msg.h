#ifndef MSG_H
#define MSG_H

#include "msg_type.pb.h"

#define MAX_MSG_SIZE 200000000

/// windows ->> C:\Windows\System32\drivers\etc
/// Linux   ->> /etc/hosts
/// 127.0.0.1 ol_gateway_server
/// 127.0.0.1 ol_register_server
#define OL_GATEWAY_SERVER_NAME "ol_gateway_server"
#define API_GATEWAY_PORT 20010
#define API_GATEWAY_SSL_PORT 20011
#define API_GATEWAY_NAME "gateway"

#define OL_REGISTER_SERVER_NAME "ol_register_server"
#define REGISTER_NAME "register"
#define REGISTER_PORT 20018

#define CONFIG_NAME "config"
#define CONFIG_PORT 20019

#define AUTH_PORT 20020
#define AUTH_NAME "auth"

#define LOG_PORT 20021
#define LOG_NAME "log"

#define DIR_PORT 20200
#define DIR_NAME "dir"

#define UPLOAD_PORT 20201
#define UPLOAD_NAME "upload"

#define DOWNLOAD_PORT 20202
#define DOWNLOAD_NAME "download"

class Msg
{
public:
    /// 数据的大小
    int size = 0;

    /// 数据存放(protobuf序列化的数据)
    char* data = nullptr;

    /// 已经接收数据的大小
    int recv_size;

    /// 消息的类型
    msg::MsgType type = msg::NONE_DO_NOT_USE;

    bool Alloc(int size)
    {
        if (size <= 0 || size > MAX_MSG_SIZE)
            return false;
        if (data)
            delete data;
        data = new char[size];
        if (!data)
            return false;
        this->size = size;
        this->recv_size = 0;
        return true;
    }

    /// 判断数据是否接收完成
    bool recved()
    {
        if (size < 0) return false;
        return (size == recv_size);
    }

    void Clear()
    {
        if (data)
            delete data;
        memset(this, 0, sizeof(Msg));
    }
};

#endif // MSG_H

