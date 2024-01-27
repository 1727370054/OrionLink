#include "login_gui.h"
#include "auth_client.h"
#include "ui_login_gui.h"

#include <QMessageBox>
#include <string>

using namespace std;


LoginUI::LoginUI(QDialog*parent) :
    QDialog(parent),
    ui(new Ui::LoginUI)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");
    this->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(251,102,102, 200), stop:1 rgba(20,196,188, 210));");
    ui->login_frame->setStyleSheet("border-radius:25px;background-color: rgb(255, 255, 255);");
    ui->label_logo->setStyleSheet("image: url(:/pic/profile.png);");
    this->InitGUI();
}

LoginUI::~LoginUI()
{
    delete ui;
}

void LoginUI::Login()
{
    if (ui->lineEdit_name->text().isEmpty() || ui->lineEdit_pwd->text().isEmpty())
    {
        QMessageBox::information(this, "input error", "username or password not empty");
        return;
    }

    string username = ui->lineEdit_name->text().toStdString();
    string password = ui->lineEdit_pwd->text().toStdString();

    AuthClient::GetInstance()->LoginReq(username, password);
    msg::LoginRes login_info;
    bool ret = AuthClient::GetInstance()->GetLoginInfo(username, &login_info, 1000);
    if (!ret)
    {
        QMessageBox::information(this,"error","username or password error");
        return;
    }
    cout << "login success" << endl;
    accept();
}

void LoginUI::InitGUI()
{
    auto lineEdit_name = ui->lineEdit_name;
    auto lineEdit_pwd = ui->lineEdit_pwd;
    auto login_button = ui->login_Button;
    auto register_button = ui->regilaster_Button;
    lineEdit_name->setFixedSize(500, 50);
    //    lineEdit_name->setMinimumSize(500,50);
    //    lineEdit_name->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    lineEdit_name->setPlaceholderText("input username"); //ÉèÖÃÊäÈë¿òÖÐµÄÌáÊ¾ÎÄ×Ö
    lineEdit_name->setStyleSheet("font: 25 14pt 'Î¢ÈíÑÅºÚ Light';"
        "padding-left:20px;"
        "color: rgb(31,31,31);"
        "background-color: rgb(255, 255, 255);"
        "border:2px solid rgb(20,196,188);border-radius:15px;  ");

    lineEdit_pwd->setFixedSize(500, 50);
    lineEdit_pwd->setEchoMode(QLineEdit::Password);//ÃÜÎÄÊäÈë
    lineEdit_pwd->setPlaceholderText("input password");
    lineEdit_pwd->setStyleSheet("font: 25 14pt 'Î¢ÈíÑÅºÚ Light';"
        "padding-left:20px;"
        "color: rgb(31,31,31);"
        "background-color: rgb(255, 255, 255);"
        "border:2px solid rgb(20,196,188);border-radius:15px;");//

    //rgb(20,196,188)À¶ÂÌ rgb(22,218,208)Ã÷¶È½Ï¸ßÀ¶ÂÌ rgb(17,171,164)Ã÷¶È½ÏµÍÀ¶ÂÌ
    login_button->setFixedSize(500, 50);
    login_button->setStyleSheet("QPushButton{font: 25 14pt 'Î¢ÈíÑÅºÚ Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
        "border: none;border-radius:15px;}"
        "QPushButton:hover{background-color: rgb(22,218,208);}"
        "QPushButton:pressed{background-color: rgb(17,171,164);}");

    register_button->setFixedSize(500, 50);
    register_button->setStyleSheet("QPushButton{font: 25 14pt 'Î¢ÈíÑÅºÚ Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
        "border: none;border-radius:15px;}"
        "QPushButton:hover{background-color: rgb(22,218,208);}"
        "QPushButton:pressed{background-color: rgb(17,171,164);}");
}


