#ifndef SERVICE_HANDLE_H
#define SERVICE_HANDLE_H

#include "msg_event.h"

class XCOM_API ServiceHandle : public MsgEvent
{
public:

    void set_client_ip(const char* ip);
    const char* client_ip() { return client_ip_; }
    void set_client_port(int port) { client_port_ = port; }
    const int client_port() { return client_port_; }
private:
    char client_ip_[16] = { 0 };
    int client_port_ = 0;
};

#endif // SERVICE_HANDLE_H

