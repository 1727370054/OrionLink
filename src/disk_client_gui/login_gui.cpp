#include "login_gui.h"
#include "ui_login_gui.h"
#include "auth_client.h"

#include <QFile>
#include <QTextStream>
#include <QMouseEvent>
#include <QIntValidator>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QGraphicsEffect>
#include <QMessageBox>
#include <QTimer>

using namespace std;
using namespace msg;

LoginGUI::LoginGUI(QDialog*parent) :
    QDialog(parent),
    ui(new Ui::LoginGUI)
{
    ui->setupUi(this);
    ui->label_user_name->setScaledContents(true);   //图片自适应label大小
    ui->label_pwd->setScaledContents(true);         //图片自适应label大小
    /// 去除原窗口边框
    setWindowFlags(Qt::FramelessWindowHint);
    /// 隐藏背景，用于圆角边框
    setAttribute(Qt::WA_TranslucentBackground);

    ui->lineE_pwd->setEchoMode(QLineEdit::Password);//设置为小黑点

    connect(ui->btn_1,SIGNAL(clicked(bool)),this,SLOT(set_style()));
    connect(ui->btn_2,SIGNAL(clicked(bool)),this,SLOT(set_style()));
    connect(ui->btn_3,SIGNAL(clicked(bool)),this,SLOT(set_style()));
    connect(ui->btn_4,SIGNAL(clicked(bool)),this,SLOT(set_style()));

    QPushButton* btn_login = ui->btn_login;

    // 创建阴影效果并设置给按钮
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(10);
    shadowEffect->setColor(QColor(0, 0, 0, 80));
    shadowEffect->setOffset(2, 2);
    btn_login->setGraphicsEffect(shadowEffect);

    // 连接按钮的信号到槽来改变阴影效果
    connect(btn_login, &QPushButton::pressed, [=]() {
        shadowEffect->setOffset(1, 1);
        shadowEffect->setBlurRadius(5);
    });

    connect(btn_login, &QPushButton::released, [=]() {
        shadowEffect->setOffset(2, 2);
        shadowEffect->setBlurRadius(10);
    });

    // 设置为默认按钮，这样按下回车键时，如果当前焦点所在的控件不处理回车事件，则点击此按钮
    ui->btn_login->setDefault(true);

    // 设置自动默认，表示按钮能自动接收回车键作为触发
    ui->btn_login->setAutoDefault(true);

    ui->frame_err->hide();
    ui->frame_err_2->hide();
    ui->frame_err_3->hide();
    ui->frame_err_4->hide();

    countdown_timer_ = new QTimer(this);
    connect(countdown_timer_, &QTimer::timeout, this, &LoginGUI::UpdateButton);
    remaining_time_ = 60; // 假设倒计时时间为60秒

    /// 邮箱格式
    QRegExp exp("[a-zA-Z0-9-_]+@[a-zA-Z0-9-_]+\\.[a-zA-Z]+");
    QRegExpValidator* rval = new QRegExpValidator(exp);
    ui->email_edit->setValidator(rval);
    ui->email_edit_2->setValidator(rval);
    ui->email_edit_3->setValidator(rval);
}

void LoginGUI::Login()
{
    ui->frame_err->show();
    ui->err_msg->setText(QString::fromLocal8Bit("正在登陆 ..."));
    string username = ui->lineE_user_name->text().toUtf8().constData();
    string password = ui->lineE_pwd->text().toUtf8().constData();
    if (username.empty() || password.empty()) 
    {
        ui->err_msg->setText(QString::fromLocal8Bit("用户名或密码不能为空!"));
        return;
    }

    ui->frame_err->hide();
    ui->btn_login->setEnabled(false);
    ui->btn_login->setText(QString::fromLocal8Bit("登陆中..."));

    auto tt = time(0);

    QCoreApplication::processEvents(); // 允许事件处理，以便定时器能够更新

    bool loginSuccess = AuthClient::GetInstance()->Login(username, password);

    QCoreApplication::processEvents(); // 再次处理事件，以确保超时处理逻辑可以执行

    ui->frame_err->show();
    ui->btn_login->setEnabled(true);
    ui->btn_login->setText(QString::fromLocal8Bit("登陆"));
    if (tt + 3 <= time(0))
    {
        ui->err_msg->setText(QString::fromLocal8Bit("登陆超时!"));
        return;
    }

    if (!loginSuccess)
    {
        ui->err_msg->setText(QString::fromLocal8Bit("用户名或密码错误!"));
        return;
    }

    ui->btn_login->setText(QString::fromLocal8Bit("登陆"));
    ui->frame_err->hide();
    QDialog::accept();
}

void LoginGUI::Register()
{
    ui->frame_err_2->show();
    if (ui->user_name_edit->text().isEmpty()
        || ui->pwd_edit->text().isEmpty())
    {
        ui->err_msg_2->setText(QString::fromLocal8Bit("用户名或密码不能为空!"));
        return;
    }

    if (ui->code_edit->text().isEmpty())
    {
        ui->err_msg_2->setText(QString::fromLocal8Bit("验证码不能为空!"));
        return;
    }

    ui->frame_err_2->hide();
    ui->btn_register_2->setText(QString::fromLocal8Bit("正在注册..."));
    ui->btn_register_2->setEnabled(false);

    string username = ui->user_name_edit->text().toUtf8().constData();
    string password = ui->pwd_edit->text().toUtf8().constData();
    string email = ui->email_edit->text().toUtf8().constData();
    string code = ui->code_edit->text().toUtf8().constData();

    msg::RegisterUserReq req;
    req.set_username(username);
    req.set_password(password);
    req.set_email(email);
    req.set_code(code);

    AuthClient::GetInstance()->RegisterUserReq(req);

    QCoreApplication::processEvents(); // 允许事件处理，以便定时器能够更新

    int ret = AuthClient::GetInstance()->GetResult(3000);

    QCoreApplication::processEvents(); // 再次处理事件，以确保超时处理逻辑可以执行

    ui->btn_register_2->setText(QString::fromLocal8Bit("注册"));
    ui->frame_err_2->show();
    ui->btn_register_2->setEnabled(true);
    switch (ret)
    {
    case 0:
        ui->err_msg_2->setText(QString::fromLocal8Bit("注册超时!"));
        break;
    case 1:
        ui->err_msg_2->setText(QString::fromLocal8Bit("验证码错误!"));
        break;
    case 2:
        ui->err_msg_2->setText(QString::fromLocal8Bit("用户名已存在或邮箱已被绑定!"));
        break;
    case 3:
        ui->err_msg_2->setText(QString::fromLocal8Bit("注册成功请登录"));
        ui->lineE_user_name->setText(username.c_str());
        ui->lineE_pwd->setText(password.c_str());
        break;
    default:
        break;
    }
}

void LoginGUI::GetCode()
{
    ui->frame_err_2->show();
    ui->frame_err_3->show();
    ui->frame_err_4->show();

    if (ui->email_edit->text().isEmpty() && ui->email_edit_2->text().isEmpty()
        && ui->email_edit_3->text().isEmpty())
    {
        ui->err_msg_2->setText(QString::fromLocal8Bit("邮箱不能为空!"));
        ui->err_msg_3->setText(QString::fromLocal8Bit("邮箱不能为空!"));
        ui->err_msg_4->setText(QString::fromLocal8Bit("邮箱不能为空!"));
        return;
    }

    const QValidator* v1 = ui->email_edit->validator();
    const QValidator* v2 = ui->email_edit_2->validator();
    const QValidator* v3 = ui->email_edit_3->validator();
    int pos = 0;
    QString qemail_1 = ui->email_edit->text();
    QString qemail_2 = ui->email_edit_2->text();
    QString qemail_3 = ui->email_edit_3->text();
    if (v1->validate(qemail_1, pos) != QValidator::Acceptable
        && v2->validate(qemail_2, pos) != QValidator::Acceptable
        && v3->validate(qemail_3, pos) != QValidator::Acceptable)
    {
        ui->err_msg_2->setText(QString::fromLocal8Bit("邮箱格式不正确!"));
        ui->err_msg_3->setText(QString::fromLocal8Bit("邮箱格式不正确!"));
        ui->err_msg_4->setText(QString::fromLocal8Bit("邮箱格式不正确!"));
        return;
    }

    ui->frame_err_2->hide();
    ui->frame_err_3->hide();
    ui->frame_err_4->hide();

    int index = ui->frame_login->currentIndex();
    string email = "";
    switch (index)
    {
    case 1: /// 邮箱登陆
        email = ui->email_edit_2->text().toStdString();
        break;
    case 2: /// 注册
        email = ui->email_edit->text().toStdString();
        break;
    case 3: /// 忘记密码
        email = ui->email_edit_3->text().toStdString();
        break;
    default:
        break;
    }       

    AuthClient::GetInstance()->GetAuthCodeReq(email);

    // 开始倒计时
    ui->getcodeButton_2->setDisabled(true);
    ui->getcodeButton_3->setDisabled(true);
    ui->getcodeButton->setDisabled(true);
    countdown_timer_->start(1000); // 每秒更新一次
    remaining_time_ = 60; // 重置倒计时时间
    ui->getcodeButton->setText(QString::number(remaining_time_) + QString::fromLocal8Bit(" 秒后重试"));
    ui->getcodeButton_2->setText(QString::number(remaining_time_) + QString::fromLocal8Bit(" 秒后重试"));
    ui->getcodeButton_3->setText(QString::number(remaining_time_) + QString::fromLocal8Bit(" 秒后重试"));
}

void LoginGUI::EmailLogin()
{
    ui->frame_err_3->show();
    if (ui->code_edit_2->text().isEmpty())
    {
        ui->err_msg_3->setText(QString::fromLocal8Bit("验证码不能为空!"));
        return;
    }

    ui->frame_err_3->hide();
    ui->btn_email_login->setText(QString::fromLocal8Bit("正在登陆..."));
    ui->btn_email_login->setEnabled(false);

    string email = ui->email_edit_2->text().toUtf8().constData();
    string code = ui->code_edit_2->text().toUtf8().constData();

    AuthClient::GetInstance()->EmailLoginReq(email, code);

    QCoreApplication::processEvents(); // 允许事件处理，以便定时器能够更新

    auto ret = AuthClient::GetInstance()->GetEmailLogin(3000);

    QCoreApplication::processEvents(); // 再次处理事件，以确保超时处理逻辑可以执行

    ui->btn_email_login->setText(QString::fromLocal8Bit("登陆"));
    ui->frame_err_3->show();
    ui->btn_email_login->setEnabled(true);
    switch (ret)
    {
    case 0:
        ui->err_msg_3->setText(QString::fromLocal8Bit("登陆超时!"));
        return;
    case 1:
        ui->err_msg_3->setText(QString::fromLocal8Bit("登陆成功!"));
        break;
    case 3:
        ui->err_msg_3->setText(QString::fromLocal8Bit("验证码错误!"));
        return;
    case 4:
        ui->err_msg_3->setText(QString::fromLocal8Bit("该邮箱未绑定用户!"));
        return;
    default:
        return;
    }

    ui->frame_err_3->hide();
    QDialog::accept();
}

void LoginGUI::ForgetPassword()
{
    ui->frame_err_4->show();
    if (ui->user_name_edit_2->text().isEmpty()
        || ui->pwd_edit_2->text().isEmpty())
    {
        ui->err_msg_4->setText(QString::fromLocal8Bit("用户名或密码不能为空!"));
        return;
    }

    if (ui->code_edit_3->text().isEmpty())
    {
        ui->err_msg_4->setText(QString::fromLocal8Bit("验证码不能为空!"));
        return;
    }

    ui->frame_err_4->hide();
    ui->btn_submit->setText(QString::fromLocal8Bit("正在提交..."));
    ui->btn_submit->setEnabled(false);

    string username = ui->user_name_edit_2->text().toUtf8().constData();
    string password = ui->pwd_edit_2->text().toUtf8().constData();
    string email = ui->email_edit_3->text().toUtf8().constData();
    string code = ui->code_edit_3->text().toUtf8().constData();

    msg::RegisterUserReq req;
    req.set_username(username);
    req.set_password(password);
    req.set_email(email);
    req.set_code(code);

    AuthClient::GetInstance()->ForgetPasswordReq(req);

    QCoreApplication::processEvents(); // 允许事件处理，以便定时器能够更新

    auto ret = AuthClient::GetInstance()->GetResult(3000);

    QCoreApplication::processEvents(); // 再次处理事件，以确保超时处理逻辑可以执行

    ui->btn_submit->setText(QString::fromLocal8Bit("提交"));
    ui->frame_err_4->show();
    ui->btn_submit->setEnabled(true);
    switch (ret)
    {
    case 0:
        ui->err_msg_4->setText(QString::fromLocal8Bit("提交超时!"));
        break;
    case 1:
        ui->err_msg_4->setText(QString::fromLocal8Bit("密码修改成功，请登陆!"));
        break;
    case 2:
        ui->err_msg_4->setText(QString::fromLocal8Bit("验证码错误!"));
        break;
    case 3:
        ui->err_msg_4->setText(QString::fromLocal8Bit("该用户不存在!"));
        break;
    case 4:
        ui->err_msg_4->setText(QString::fromLocal8Bit("该用户绑定邮箱不正确!"));
        break;
    default:
        break;
    }

}

void LoginGUI::LoginPage()
{
    ui->frame_err->hide();
    ui->frame_err_2->hide();
    ui->frame_err_3->hide();
    ui->frame_err_4->hide();
    ui->frame_login->setCurrentIndex(0);
}

void LoginGUI::RegisterPage()
{
    ui->frame_err->hide();
    ui->frame_err_2->hide();
    ui->frame_err_3->hide();
    ui->frame_err_4->hide();
    ui->frame_login->setCurrentIndex(2);
}

void LoginGUI::EmailPage()
{
    ui->frame_err->hide();
    ui->frame_err_2->hide();
    ui->frame_err_3->hide();
    ui->frame_err_4->hide();
    ui->frame_login->setCurrentIndex(1);
}

void LoginGUI::ForgetPage()
{
    ui->frame_err->hide();
    ui->frame_err_2->hide();
    ui->frame_err_3->hide();
    ui->frame_err_4->hide();
    ui->frame_login->setCurrentIndex(3);
}

void LoginGUI::UpdateButton()
{
    remaining_time_--;
    if (remaining_time_ <= 0)
    {
        countdown_timer_->stop();
        ui->getcodeButton->setEnabled(true);
        ui->getcodeButton_2->setEnabled(true);
        ui->getcodeButton_3->setEnabled(true);
        ui->getcodeButton->setText(QString::fromLocal8Bit("获取验证码"));
        ui->getcodeButton_2->setText(QString::fromLocal8Bit("获取验证码"));
        ui->getcodeButton_3->setText(QString::fromLocal8Bit("获取验证码"));
    }
    else 
    {
        ui->getcodeButton->setText(QString::number(remaining_time_) + QString::fromLocal8Bit(" 秒后重试"));
        ui->getcodeButton_2->setText(QString::number(remaining_time_) + QString::fromLocal8Bit(" 秒后重试"));
        ui->getcodeButton_3->setText(QString::number(remaining_time_) + QString::fromLocal8Bit(" 秒后重试"));
    }
}

/* 
* 槽函数-皮肤设置
*/
QPushButton* btn;
void LoginGUI::set_style()
{
    btn = qobject_cast<QPushButton*>(sender());//获取发射信号的对象
    QString filePath;
    if("btn_1" == btn->objectName())        //粉色
    {
        filePath = ":/res/qss/style-1.qss";
    }else if("btn_2" == btn->objectName())  //黄蓝
    {
        filePath = ":/res/qss/style-2.qss";
    }else if("btn_3" == btn->objectName())  //浅紫
    {
        filePath = ":/res/qss/style-3.qss";
    }else if("btn_4" == btn->objectName())  //青绿
    {
        filePath = ":/res/qss/style-4.qss";
    }

    /*皮肤设置*/
    QFile file(filePath);/*QSS文件所在的路径*/
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    ui->frame_background->setStyleSheet("");
    ui->frame_background->update();
    ui->frame_background->setStyleSheet(stylesheet);
    ui->frame_background->update();
    file.close();
}

LoginGUI::~LoginGUI()
{
    delete ui;
}

static bool mouse_press = false;
static QPoint mouse_point;

void LoginGUI::mouseMoveEvent(QMouseEvent * ev)
{
    /// 没有按下，处理原事件
    if (!mouse_press)
    {
        QWidget::mouseMoveEvent(ev);
        return;
    }
    auto cur_pos = ev->globalPos();
    this->move(cur_pos - mouse_point);

}

void LoginGUI::mousePressEvent(QMouseEvent* ev)
{
    /// 鼠标左键按下，记录位置
    if (ev->button() == Qt::LeftButton)
    {
        mouse_press = true;
        mouse_point = ev->pos();
    }
}

void LoginGUI::mouseReleaseEvent(QMouseEvent* ev)
{
    Q_UNUSED(ev);
    mouse_press = false;
}

