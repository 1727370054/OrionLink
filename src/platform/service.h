#ifndef SERVICE_H
#define SERVICE_H

#include "task.h"
#include "service_handle.h"
#include "thread_pool.h"

class XCOM_API Service : public Task
{
public:
    Service();
    ~Service();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ÿ�����ӽ��룬���øú�������������󣬼��뵽�̳߳�
    /// @return ���ؾ����������
    ///////////////////////////////////////////////////////////////////////////
    virtual ServiceHandle* CreateServiceHandle() = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ΢�����ʼ�������̳߳��̵߳���
    /// @return ��ʼ���Ƿ�ɹ�
    ///////////////////////////////////////////////////////////////////////////
    virtual bool Init() override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ��ʼ���̳߳أ������������ɷ��������¼��̳߳��У��̻߳ص������ Init 
    /// @return ��ʼ���Ƿ�ɹ�
    ///////////////////////////////////////////////////////////////////////////
    bool Start();

    void ListenCallback(int client_socket,struct sockaddr* client_addr, int socklen);

    void set_server_port(int port) { server_port_ = port; }

private:
    /// �����û����ӵ��̳߳�
    ThreadPool* thread_listen_pool_ = nullptr;
    /// �����û������̳߳�
    ThreadPool* thread_handle_pool_ = nullptr;
    /// �����û������̳߳أ��߳�����
    int thread_count_ = 10;

    int server_port_ = 0;
};

#endif // SERVICE_H

