#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "ifile_manager.h"

class FileManager : public iFileManager
{
public:
    FileManager();
    ~FileManager();
    virtual void GetDir(std::string root) override;
};

#endif // FILE_MANAGER_H

