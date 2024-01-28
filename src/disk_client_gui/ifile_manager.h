#ifndef IFILE_MANAGER_H
#define IFILE_MANAGER_H

#include <QObject>

#include "disk_client_gui.pb.h"
#include "msg_comm.pb.h"

class iFileManager  : public QObject
{
    Q_OBJECT

public:
    static iFileManager* GetInstance()
    {
        return instance_;
    }

    iFileManager(QObject *parent = 0);
    ~iFileManager();

    virtual void GetDir(std::string root) = 0;

    virtual void InitFileManager(std::string server_ip, int server_port) = 0;

    virtual void NewDir(std::string path) = 0;

    virtual void set_login_info(msg::LoginRes login) { login_info_ = login; }
    msg::LoginRes login_info() { return login_info_; }
signals:
    void RefreshData(disk::FileInfoList file_list, std::string cur_dir);

protected:
    static iFileManager* instance_;
    msg::LoginRes login_info_;
};

#endif // IFILE_MANAGER_H
