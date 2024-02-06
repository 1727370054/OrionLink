#include "config_client.h"
#include "frmmain.h"
#include "appinit.h"
#include "quihelper.h"
#include "login_gui.h"
#include "auth_client.h"
#include "tools.h"

int main(int argc, char *argv[])
{
    std::string gateway_ip = GetHostByName(OL_GATEWAY_SERVER_NAME);
    AuthClient::GetInstance()->set_server_ip(gateway_ip.c_str());
    AuthClient::GetInstance()->set_server_port(API_GATEWAY_PORT);
    AuthClient::GetInstance()->set_auto_connect(true);
    AuthClient::GetInstance()->StartConnect();
    /// 初始化配置中心客户端，创建线程池
    ConfigClient::GetInstance()->set_auto_connect(true);
    ConfigClient::GetInstance()->StartGetConf(gateway_ip.c_str(), API_GATEWAY_PORT, 0, 0, 0);

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

    LoginUI gui;
    if (gui.exec() != QDialog::Accepted)
    {
        return 1;
    }

    frmMain w;
    w.resize(800, 600);
    QUIHelper::setFormInCenter(&w);
    w.show();

    return a.exec();
}
