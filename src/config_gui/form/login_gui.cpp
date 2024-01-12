#include "login_gui.h"
#include "ui_login_gui.h"

LoginGUI::LoginGUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginGUI)
{
    ui->setupUi(this);
}

LoginGUI::~LoginGUI()
{
    delete ui;
}
