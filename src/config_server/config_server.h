#ifndef CONFIG_SERVER_H
#define CONFIG_SERVER_H

#include "service.h"

class ConfigServer : public Service
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief ���������в�������ʼ��������Ҫ�ȵ���
    void main(int argc, char* argv[]);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ÿ�����ӽ��룬���øú�������������󣬼��뵽�̳߳�
    /// @return ���ؾ����������
    ///////////////////////////////////////////////////////////////////////////
    virtual ServiceHandle* CreateServiceHandle() override;
};

#endif // CONFIG_SERVER_H

