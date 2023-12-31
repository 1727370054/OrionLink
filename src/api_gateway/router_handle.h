#ifndef ROUTER_HANDLE_H
#define ROUTER_HANDLE_H

#include "service_handle.h"

class RouterHandle : public ServiceHandle
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief �����˿ͻ��˵���Ϣ��������Ϣ·�ɣ��ú�����д MsgEvent ���麯����
    /// @param head �����л�����Ϣͷ��
    /// @param msg ���л�����Ϣ����
    virtual void ReadCallback(msg::MsgHead* head, Msg* msg) override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ��д ComTask �� Close����ʱ�����ӹرա�����ʱ�������
    virtual void Close() override;
};

#endif // ROUTER_HANDLE_H

