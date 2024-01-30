#ifndef MSG_EVENT_H
#define MSG_EVENT_H

#include "msg_comm.pb.h"
#include "com_task.h"
#include "msg.h" 

class XCOM_API MsgEvent : public ComTask
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收消息读事件回调，分发消息 
    virtual void ReadCallback() override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 消息回调函数，默认发送到用户注册的回调函数，路由重写则回调到路由层
    /// @param head 反序列化后消息头部
    /// @param msg 序列化的消息内容
    virtual void ReadCallback(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送消息，包含消息头部(内部创建)
    /// @param type 消息类型
    /// @param message 结构化的消息内容
    /// @return 发送成功返回true，否则相反 (bev可能未设置)
    ///////////////////////////////////////////////////////////////////////////
    virtual bool SendMsg(msg::MsgType type, const google::protobuf::Message *message);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送消息，包含消息头部(外部创建)，只序列化消息内容，再向下传递
    /// @param head 消息头部
    /// @param message 结构化的消息内容
    /// @return 发送成功返回true，否则相反 (bev可能未设置)
    ///////////////////////////////////////////////////////////////////////////
    virtual bool SendMsg(msg::MsgHead *head, const google::protobuf::Message* message);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送消息，包含消息头部(外部传递)，只序列化消息头部，接收调用者的序列化消息内容
    /// @param head 消息头部
    /// @param msg 序列化的消息内容
    /// @return 发送成功返回true，否则相反
    ///////////////////////////////////////////////////////////////////////////
    virtual bool SendMsg(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收数据包 （只反序列化头部，消息内容还是序列化数据，由业务层反序列化）
    /// 1.正确接收消息，调用接收消息处理函数
    /// 2.消息接收不完整，等待下一次接收
    /// 3.消息接收错误，退出清理空间
    /// @return 1 和 2 返回true，3 返回false
    ///////////////////////////////////////////////////////////////////////////
    bool RecvMsg();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 获取接收到的数据包，（不包含头部消息）由调用者清理Msg
    /// @return 如果没有完整的数据包，返回NULL
    ///////////////////////////////////////////////////////////////////////////
    Msg* GetMsg();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 调用 该类的 Clear 和 ComTask 的 close 进行资源清理
    virtual void Close() override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 清理消息头和消息内容，用于接收下一次
    void Clear();

    typedef void (MsgEvent::* MsgCBFunc)(msg::MsgHead *head, Msg *msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 注册消息处理的回调函数，根据消息类型分发，同一个类型只能有一个回调
    /// @param type 消息类型
    /// @param func 回调函数
    static void RegisterCallback(msg::MsgType type, MsgCBFunc func);

    virtual void DropInMsg() { is_drop_ = true; }
private:
    Msg head_;  /// 消息头部
    Msg msg_;   /// 消息内容
    msg::MsgHead *pb_head_ = nullptr; /// 反序列化后的消息头
    bool is_drop_ = false;
};

#endif // MSG_EVENT_H

