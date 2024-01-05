#include "msg_event.h"
#include "tools.h"

#include <string>
#include <map>

using namespace std;
using namespace msg;
using namespace google;
using namespace protobuf;

static map<MsgType, MsgEvent::MsgCBFunc> msg_callback_t;

void MsgEvent::RegisterCallback(msg::MsgType type, MsgEvent::MsgCBFunc func)
{
    if (msg_callback_t.find(type) != msg_callback_t.end())
    {
        stringstream ss;
        ss << "A callback already exists for this type" << type;
        LOGERROR(ss.str());
        return;
    }
    msg_callback_t[type] = func;
}

void MsgEvent::ReadCallback(msg::MsgHead* head, Msg* msg)
{
    auto pos = msg_callback_t.find(msg->type);
    if (pos == msg_callback_t.end())
    {
        LOGDEBUG("this message type not function callback");
        Clear();
        return;
    }
    auto func = pos->second;
    (this->*func)(head, msg);
}

void MsgEvent::ReadCallback()
{
    while (true)
    {
        if (!RecvMsg())
        {
            Clear();
            return;
        }
        if (!pb_head_) break;
        auto msg = GetMsg();
        if (!msg) break;

        /// 回调消息函数
        LOGDEBUG("service name: " << pb_head_->service_name());
        ReadCallback(pb_head_, msg);
        Clear();
    }
}

bool MsgEvent::SendMsg(MsgType type, const Message* message)
{
    if (!message) return false;

    MsgHead head;
    head.set_msg_type(type);

    return SendMsg(&head, message);
}

bool MsgEvent::SendMsg(msg::MsgHead *head, const google::protobuf::Message* message)
{
    if (!message || !head) return false;

    /// 消息内容序列化
    std::string msg_str = message->SerializeAsString();
    int msg_size = msg_str.size();

    Msg msg;
    msg.data = (char*)msg_str.c_str();
    msg.size = msg_size;
    return SendMsg(head, &msg);
}

bool MsgEvent::SendMsg(msg::MsgHead* head, Msg* msg)
{
    if (!head || !msg) return false;

    head->set_msg_size(msg->size);
    /// 消息头序列化
    std::string head_str;
    head->SerializeToString(&head_str);
    /// 也可以用该接口获取序列化后的数据 head.ByteSizeLong();
    int head_size = head_str.size();

    /// 1. 发送消息头大小 4字节 (暂时不考虑字节序问题)
    bool ret = Write(&head_size, sizeof(head_size));
    if (!ret) return false;

    /// 2. 发送消息头 (pb序列化)
    ret = Write(head_str.c_str(), head_str.size());
    if (!ret) return false;

    /// 3. 发送消息内容 (pb序列化)
    ret = Write(msg->data, msg->size);
    if (!ret) return false;

    return true;
}

bool MsgEvent::RecvMsg()
{
    /// 解包

    /// 1.消息头大小
    if (!head_.size)
    {
        int len = Read(&head_.size, sizeof(head_.size));
        if (len <= 0 || head_.size <= 0)
        {
            return false;
        }
        /// 分配消息头空间 读取消息头（鉴权，消息大小）
        if (!head_.Alloc(head_.size))
        {
            LOGERROR("XMsgEvent::RecvMsg - head_.Alloc failed!");
            return false;
        }
    }

    /// 2.消息头内容(鉴权，消息大小)
    if (!head_.recved())
    {
        int len = Read(head_.data + head_.recv_size, head_.size - head_.recv_size);
        if (len <= 0)
            return true; /// 接收了消息头大小，里面可能没有消息头内容
        head_.recv_size += len;

        if (!head_.recved())
            return true;

        /// 完整头部接收完成，反序列化
        if (!pb_head_)
        {
            pb_head_ = new MsgHead();
        }
        if (!pb_head_->ParseFromArray(head_.data, head_.size))
        {
            LOGERROR("XMsgEvent::RecvMsg - pb_head.ParseFromArray failed!");
            return false;
        }

        /// 鉴权
        /// 分配消息内容大小空间
        if (!msg_.Alloc(pb_head_->msg_size()))
        {
            LOGERROR("XMsgEvent::RecvMsg - msg_.Alloc failed!");
            return false;
        }
        /// 保存消息类型
        msg_.type = pb_head_->msg_type();
    }

    /// 3.消息内容
    if (!msg_.recved())
    {
        int len = Read(msg_.data + msg_.recv_size, msg_.size - msg_.recv_size);
        if (len <= 0)
            return true; /// 接收了消息头大小，里面可能没有消息内容
        msg_.recv_size += len;
    }

    if (msg_.recved())
    {
        LOGDEBUG("message recv success!");
    }

    return true;
}

Msg* MsgEvent::GetMsg()
{
    if (msg_.recved())
        return &msg_;
    return nullptr;
}

void MsgEvent::Close()
{
    Clear();
    if (pb_head_)
    {
        delete pb_head_;
        pb_head_ = nullptr;
    }
    ComTask::Close();
}

void MsgEvent::Clear()
{
    head_.Clear();
    msg_.Clear();
}

