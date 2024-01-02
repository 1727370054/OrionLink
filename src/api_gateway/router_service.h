#ifndef ROUTER_SERVICE_H
#define ROUTER_SERVICE_H

#include "service.h"

class RouterService : public Service
{
public:
    virtual ServiceHandle* CreateServiceHandle() override;
};

#endif // ROUTER_SERVICE_H

