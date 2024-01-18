#include "config_client.h"
#include "frmmain.h"
#include "appinit.h"
#include "quihelper.h"
#include "login_gui.h"
#include "auth_client.h"

int main(int argc, char *argv[])
{
    AuthClient::GetInstance()->RegisterMsgCallback();
    AuthClient::GetInstance()->set_server_ip("127.0.0.1");
    AuthClient::GetInstance()->set_server_port(AUTH_PORT);
    AuthClient::GetInstance()->StartConnect();
    /// 初始化配置中心客户端，创建线程池
    ConfigClient::GetInstance()->StartGetConf("127.0.0.1",CONFIG_PORT, 0, 0, 0);

    QUIHelper::initMain();
    QApplication a(argc, argv);
    AppInit::Instance()->start();

    QUIHelper::setFont();
    QUIHelper::setCode();

    //加载样式表
    QFile file(":/qss/blacksoft.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
    frmMain w;
    w.resize(800, 600);
    QUIHelper::setFormInCenter(&w);
    w.show();

    return a.exec();
}
