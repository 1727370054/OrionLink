#ifndef GET_DIR_CLIENT_H
#define GET_DIR_CLIENT_H

#include "service_client.h"
#include "disk_client_gui.pb.h"

class GetDirClient : public ServiceClient
{
public:
    static GetDirClient* GetInstance()
    {
        static GetDirClient get_dir_client;
        get_dir_client.set_auto_delete(false);
        return &get_dir_client;
    }

    void GetDirReq(disk::GetDirReq req);

};

#endif // GET_DIR_CLIENT_H

