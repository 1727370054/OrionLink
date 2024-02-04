#include "file_password.h"

FilePassword::FilePassword(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
}

FilePassword::~FilePassword()
{
}
void FilePassword::accept()
{
    password = ui.passwordEdit->text().toLocal8Bit();
    QDialog::accept();
}