#ifndef IFILE_MANAGER_H
#define IFILE_MANAGER_H

#include <QObject>

#include "disk_client_gui.pb.h"

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
signals:
    void RefreshData(disk::FileInfoList file_list, std::string cur_dir);

protected:
    static iFileManager* instance_;
};

#endif // IFILE_MANAGER_H
