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
    LOGDEBUG("MsgEvent::ReadCallback");
    if (!RecvMsg())
    {
        Clear();
        return;
    }
    auto msg = GetMsg();
    if (!msg) return;

    /// �ص���Ϣ����
    LOGDEBUG("service name: " << pb_head_->service_name());
    ReadCallback(pb_head_, msg);
    Clear();
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

    /// ��Ϣ�������л�
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
    /// ��Ϣͷ���л�
    std::string head_str;
    head->SerializeToString(&head_str);
    /// Ҳ�����øýӿڻ�ȡ���л�������� head.ByteSizeLong();
    int head_size = head_str.size();

    /// 1. ������Ϣͷ��С 4�ֽ� (��ʱ�������ֽ�������)
    bool ret = Write(&head_size, sizeof(head_size));
    if (!ret) return false;

    /// 2. ������Ϣͷ (pb���л�)
    ret = Write(head_str.c_str(), head_str.size());
    if (!ret) return false;

    /// 3. ������Ϣ���� (pb���л�)
    ret = Write(msg->data, msg->size);
    if (!ret) return false;

    return true;
}

bool MsgEvent::RecvMsg()
{
    /// ���

    /// 1.��Ϣͷ��С
    if (!head_.size)
    {
        int len = Read(&head_.size, sizeof(head_.size));
        if (len <= 0 || head_.size <= 0)
        {
            return false;
        }
        /// ������Ϣͷ�ռ� ��ȡ��Ϣͷ����Ȩ����Ϣ��С��
        if (!head_.Alloc(head_.size))
        {
            LOGERROR("XMsgEvent::RecvMsg - head_.Alloc failed!");
            return false;
        }
    }

    /// 2.��Ϣͷ����(��Ȩ����Ϣ��С)
    if (!head_.recved())
    {
        int len = Read(head_.data + head_.recv_size, head_.size - head_.recv_size);
        if (len <= 0)
            return true; /// ��������Ϣͷ��С���������û����Ϣͷ����
        head_.recv_size += len;

        if (!head_.recved())
            return true;

        /// ����ͷ��������ɣ������л�
        if (!pb_head_)
        {
            pb_head_ = new MsgHead();
        }
        if (!pb_head_->ParseFromArray(head_.data, head_.size))
        {
            LOGERROR("XMsgEvent::RecvMsg - pb_head.ParseFromArray failed!");
            return false;
        }

        /// ��Ȩ
        /// ������Ϣ���ݴ�С�ռ�
        if (!msg_.Alloc(pb_head_->msg_size()))
        {
            LOGERROR("XMsgEvent::RecvMsg - msg_.Alloc failed!");
            return false;
        }
        /// ������Ϣ����
        msg_.type = pb_head_->msg_type();
    }

    /// 3.��Ϣ����
    if (!msg_.recved())
    {
        int len = Read(msg_.data + msg_.recv_size, msg_.size - msg_.recv_size);
        if (len <= 0)
            return true; /// ��������Ϣͷ��С���������û����Ϣ����
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
    ComTask::Close();
    delete pb_head_;
}

void MsgEvent::Clear()
{
    head_.Clear();
    msg_.Clear();
}

