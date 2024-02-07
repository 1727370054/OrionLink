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
    password = ui.passwordEdit->text().toUtf8().constData();
    username = ui.userEdit->text().toUtf8().constData();
    email = ui.emailEdit->text().toUtf8().constData();
    QDialog::accept();
}