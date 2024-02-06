#include "add_user.h"

AddUser::AddUser(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
}

AddUser::~AddUser()
{
}
void AddUser::accept()
{
    password = ui.passwordEdit->text().toLocal8Bit();
    username = ui.userEdit->text().toLocal8Bit();
    email = ui.emailEdit->text().toLocal8Bit();
    QDialog::accept();
}