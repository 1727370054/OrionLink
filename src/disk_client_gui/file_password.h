#ifndef FILE_PASSWORD_H
#define FILE_PASSWORD_H

#include <QDialog>
#include "ui_file_password.h"
#include<string>

class FilePassword : public QDialog
{
    Q_OBJECT

public:
    FilePassword(QWidget *parent = Q_NULLPTR);
    ~FilePassword();
    void FilePassword::accept() override;
    std::string password="";

private:
    Ui::FilePassword ui;
};

#endif // FILE_PASSWORD_H
