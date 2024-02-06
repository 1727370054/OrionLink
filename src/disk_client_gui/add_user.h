#ifndef ADD_USER_H
#define ADD_USER_H

#include <QDialog>
#include "ui_add_user.h"
#include<string>

class AddUser : public QDialog
{
    Q_OBJECT

public:
    AddUser(QWidget *parent = Q_NULLPTR);
    ~AddUser();
    void AddUser::accept() override;
    std::string password = "";
    std::string username = "";
    std::string email ="";

private:
    Ui::AddUser ui;
};

#endif // ADD_USER_H
