#ifndef SERVICE_HANDLE_H
#define SERVICE_HANDLE_H

#include "msg_event.h"

class XCOM_API ServiceHandle : public MsgEvent
{
public:
    ServiceHandle();
    ~ServiceHandle();
private:
};

#endif // SERVICE_HANDLE_H

