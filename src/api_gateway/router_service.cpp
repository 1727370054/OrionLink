#include "router_service.h"
#include "router_handle.h"


ServiceHandle* RouterService::CreateServiceHandle()
{
    return new RouterHandle();
}
