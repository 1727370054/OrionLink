#ifndef CONFIG_HANDLE_H
#define CONFIG_HANDLE_H

#include "service_handle.h"

class ConfigHandle : public ServiceHandle
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief ע����Ϣ����Ļص�����
    static void RegisterMsgCallback();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ���յ��������õ�����
    /// @param head �����л�ͷ��
    /// @param msg ���л�����Ϣ
    void SaveConfig(msg::MsgHead *head, Msg * msg);
};

#endif // CONFIG_HANDLE_H

