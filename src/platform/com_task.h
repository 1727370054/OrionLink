#ifndef COM_TASH_H
#define COM_TASH_H

#include "task.h"
#include "msg.h"

#include <string>

class XCOM_API ComTask : public Task
{
public:
    ComTask();
    virtual ~ComTask();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ���� bufferevent �����ûص�����
    /// @return ��ʼ���Ƿ�ɹ�
    ///////////////////////////////////////////////////////////////////////////
    virtual bool Init() override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief �ر� bufferevent, ������Ϣ�������ݺ��������
    virtual void Close();
     
    ///////////////////////////////////////////////////////////////////////////
    /// @brief ���ӷ������������Զ�����
    /// @return �����Ƿ�ɹ�
    ///////////////////////////////////////////////////////////////////////////
    virtual bool Connect();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief �ͻ������ӳɹ��Ļص�����ҵ������д
    virtual void ConnectCallback() {};

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ���¼������ص�������MsgEvent ����д
    virtual void ReadCallback() = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ����д��ص�
    virtual void TriggerWrite();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief д�¼������ص�������ҵ������д
    virtual void WriteCallback() {};

    ///////////////////////////////////////////////////////////////////////////
    /// @brief �¼��ص����� 
    /// @param what �¼�����
    virtual void EventCallback(short what);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ��pb����ú�������ȡ���������л��������
    /// @param data ��������
    /// @param size ���ݴ�С
    int Read(void * data, int size);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ��pb����ú�����д�����л��������
    /// @param data ��������
    /// @param size ���ݴ�С
    virtual bool Write(const void* data, int size);

    void set_server_ip(const char* ip);
    void set_port(int port) { server_port_ = port; }
    bool is_connecting() { return is_connecting_; }
    bool is_connected() { return is_connected_; }
protected:
    /// �ļ��������ݻ�����
    char read_buf_[4096];

private:
    bool InitBufferevent(int sock);

    struct bufferevent* bev_ = nullptr;

    /// ������IP
    char server_ip_[16] = {0};
    /// �������˿�
    int server_port_ = 0;

    /// �ͻ�������״̬
    /// 1 δ����       =>  ��ʼ����(�̳߳ش���)  
    /// 2 ������       =>  �ȴ����ӳɹ�
    /// 3 ���ӳɹ�     =>  ��ʼҵ����
    /// 4 ���Ӻ�ʧ��   =>  �������Ӽ�����ٴ�����
    bool is_connecting_ = false;
    bool is_connected_ = false;
    std::mutex* mtx_ = nullptr;
};

#endif // COM_TASH_H

