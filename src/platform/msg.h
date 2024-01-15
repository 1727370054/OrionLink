#ifndef MSG_H
#define MSG_H

#include "msg_type.pb.h"

#define MAX_MSG_SIZE 8192
#define API_GATEWAY_PORT 20010
#define API_GATEWAY_SSL_PORT 20011
#define API_GATEWAY_NAME "gateway"
#define REGISTER_PORT 20018
#define CONFIG_NAME "config"
#define CONFIG_PORT 20019

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
        if (size <= 0) return false;
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

