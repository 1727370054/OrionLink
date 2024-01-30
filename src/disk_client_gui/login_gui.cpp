#include "login_gui.h"
#include "ui_login_gui.h"
#include "auth_client.h"

#include <QFile>
#include <QTextStream>
#include <QMouseEvent>
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

    ui->frame_err->hide();

    timer_ = new QTimer();
    connect(timer_, &QTimer::timeout, this, &LoginGUI::LoginTimeout);
}

void LoginGUI::Login()
{
    ui->frame_err->show();
    ui->err_msg->setText(QString::fromLocal8Bit("正在登陆 ..."));
    string username = ui->lineE_user_name->text().toLocal8Bit();
    string password = ui->lineE_pwd->text().toLocal8Bit();
    if (username.empty() || password.empty()) 
    {
        ui->err_msg->setText(QString::fromLocal8Bit("用户名或密码不能为空!"));
        return;
    }

    timer_->setSingleShot(true);
    timer_->start(3005);  // 设置3秒超时

    QCoreApplication::processEvents(); // 允许事件处理，以便定时器能够更新

    bool loginSuccess = AuthClient::GetInstance()->Login(username, password);

    QCoreApplication::processEvents(); // 再次处理事件，以确保超时处理逻辑可以执行

    if (!loginSuccess) 
    {
        if (!timer_->isActive()) 
        {
            return;
        }
        timer_->stop();  // 停止计时器，以避免超时
        ui->err_msg->setText(QString::fromLocal8Bit("用户名或密码错误!"));
        return;
    }

    ui->err_msg->setText(QString::fromLocal8Bit("登录成功!"));
    QDialog::accept();

    if (timer_->isActive()) 
    {
        timer_->stop();  // 停止计时器
    }
}

void LoginGUI::LoginTimeout()
{
    ui->err_msg->setText(QString::fromLocal8Bit("登录超时!"));
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
    delete timer_;
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

