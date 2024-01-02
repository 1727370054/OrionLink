#include "service_handle.h"

#include <cstring>

void ServiceHandle::set_client_ip(const char* ip)
{
    if (!ip) return;
    strncpy(client_ip_, ip, sizeof(client_ip_));
}
