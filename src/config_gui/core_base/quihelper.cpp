#include "quihelper.h"
#include "qnetworkinterface.h"
#include "qnetworkproxy.h"

#define TIMEMS qPrintable(QTime::currentTime().toString("HH:mm:ss zzz"))

int QUIHelper::getScreenIndex()
{
    //��Ҫ�Զ����Ļ���д���
    int screenIndex = 0;
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    int screenCount = qApp->screens().size();
#else
    int screenCount = qApp->desktop()->screenCount();
#endif

    if (screenCount > 1) {
        //�ҵ���ǰ���������Ļ
        QPoint pos = QCursor::pos();
        for (int i = 0; i < screenCount; ++i) {
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
            if (qApp->screens().at(i)->geometry().contains(pos)) {
#else
            if (qApp->desktop()->screenGeometry(i).contains(pos)) {
#endif
                screenIndex = i;
                break;
            }
        }
    }
    return screenIndex;
}

QRect QUIHelper::getScreenRect(bool available)
{
    QRect rect;
    int screenIndex = QUIHelper::getScreenIndex();
    if (available) {
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
        rect = qApp->screens().at(screenIndex)->availableGeometry();
#else
        rect = qApp->desktop()->availableGeometry(screenIndex);
#endif
    } else {
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
        rect = qApp->screens().at(screenIndex)->geometry();
#else
        rect = qApp->desktop()->screenGeometry(screenIndex);
#endif
    }
    return rect;
}

qreal QUIHelper::getScreenRatio(bool devicePixel)
{
    qreal ratio = 1.0;
    int screenIndex = getScreenIndex();
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    QScreen *screen = qApp->screens().at(screenIndex);
    if (devicePixel) {
        //��Ҫ���� AA_EnableHighDpiScaling ���Բ���������ȡ
        ratio = screen->devicePixelRatio() * 100;
    } else {
        ratio = screen->logicalDotsPerInch();
    }
#else
    //Qt4���ܶ�̬ʶ�����Ÿ��ĺ��ֵ
    ratio = qApp->desktop()->screen(screenIndex)->logicalDpiX();
#endif
    return ratio / 96;
}

QRect QUIHelper::checkCenterRect(QRect &rect, bool available)
{
    QRect deskRect = QUIHelper::getScreenRect(available);
    int formWidth = rect.width();
    int formHeight = rect.height();
    int deskWidth = deskRect.width();
    int deskHeight = deskRect.height();
    int formX = deskWidth / 2 - formWidth / 2 + deskRect.x();
    int formY = deskHeight / 2 - formHeight / 2;
    rect = QRect(formX, formY, formWidth, formHeight);
    return deskRect;
}

int QUIHelper::deskWidth()
{
    return getScreenRect().width();
}

int QUIHelper::deskHeight()
{
    return getScreenRect().height();
}

QSize QUIHelper::deskSize()
{
    return getScreenRect().size();
}

QWidget *QUIHelper::centerBaseForm = 0;
void QUIHelper::setFormInCenter(QWidget *form)
{
    int formWidth = form->width();
    int formHeight = form->height();

    //���=0��ʾ����ϵͳ������ĻΪ����
    QRect rect;
    if (centerBaseForm == 0) {
        rect = getScreenRect();
    } else {
        rect = centerBaseForm->geometry();
    }

    int deskWidth = rect.width();
    int deskHeight = rect.height();
    QPoint movePoint(deskWidth / 2 - formWidth / 2 + rect.x(), deskHeight / 2 - formHeight / 2 + rect.y());
    form->move(movePoint);
}

void QUIHelper::showForm(QWidget *form)
{
    setFormInCenter(form);
    form->show();

    //�жϿ���Ƿ񳬹�����Ļ�ֱ���,�������������ʾ
    //qDebug() << TIMEMS << form->size() << deskSize();
    if (form->width() + 20 > deskWidth() || form->height() + 50 > deskHeight()) {
        QMetaObject::invokeMethod(form, "showMaximized", Qt::QueuedConnection);
    }
}

QString QUIHelper::appName()
{
    //û�б�Ҫÿ�ζ���ȡ,ֻ�е�����Ϊ��ʱ��ȥ��ȡһ��
    static QString name;
    if (name.isEmpty()) {
        name = qApp->applicationFilePath();
        //����ķ�����ҪΪ�˹��˰�׿��·�� lib������_armeabi-v7a/lib������_arm64-v8a
        QStringList list = name.split("/");
        name = list.at(list.size() - 1).split(".").at(0);
        name.replace("_armeabi-v7a", "");
        name.replace("_arm64-v8a", "");
    }

    return name;
}

QString QUIHelper::appPath()
{
    static QString path;
    if (path.isEmpty()) {
#ifdef Q_OS_ANDROID
        //Ĭ�ϰ�׿��Ŀ¼
        path = "/storage/emulated/0";
        //���ϳ���������ΪĿ¼ ǰ��Ӹ�0��������
        path = path + "/0" + appName();
#else
        path = qApp->applicationDirPath();
#endif
    }

    return path;
}

QStringList QUIHelper::getLocalIPs()
{
    static QStringList ips;
    if (ips.size() == 0) {
#ifdef Q_OS_WASM
        ips << "127.0.0.1";
#else
        QList<QNetworkInterface> netInterfaces = QNetworkInterface::allInterfaces();
        foreach (QNetworkInterface netInterface, netInterfaces) {
            //�Ƴ��������ץ�����ߵ���������
            QString humanReadableName = netInterface.humanReadableName().toLower();
            if (humanReadableName.startsWith("vmware network adapter") || humanReadableName.startsWith("npcap loopback adapter")) {
                continue;
            }

            //���˵�ǰ����ӿ�
            bool flag = (netInterface.flags() == (QNetworkInterface::IsUp | QNetworkInterface::IsRunning | QNetworkInterface::CanBroadcast | QNetworkInterface::CanMulticast));
            if (!flag) {
                continue;
            }

            QList<QNetworkAddressEntry> addrs = netInterface.addressEntries();
            foreach (QNetworkAddressEntry addr, addrs) {
                //ֻȡ��IPV4�ĵ�ַ
                if (addr.ip().protocol() != QAbstractSocket::IPv4Protocol) {
                    continue;
                }

                QString ip4 = addr.ip().toString();
                if (ip4 != "127.0.0.1") {
                    ips << ip4;
                }
            }
        }
#endif
    }

    return ips;
}

QList<QColor> QUIHelper::colors = QList<QColor>();
QList<QColor> QUIHelper::getColorList()
{
    //������ɫ���� �����������
    if (colors.size() == 0) {
        colors << QColor(0, 176, 180) << QColor(0, 113, 193) << QColor(255, 192, 0);
        colors << QColor(72, 103, 149) << QColor(185, 87, 86) << QColor(0, 177, 125);
        colors << QColor(214, 77, 84) << QColor(71, 164, 233) << QColor(34, 163, 169);
        colors << QColor(59, 123, 156) << QColor(162, 121, 197) << QColor(72, 202, 245);
        colors << QColor(0, 150, 121) << QColor(111, 9, 176) << QColor(250, 170, 20);
    }

    return colors;
}

QStringList QUIHelper::getColorNames()
{
    QList<QColor> colors = getColorList();
    QStringList colorNames;
    foreach (QColor color, colors) {
        colorNames << color.name();
    }
    return colorNames;
}

QColor QUIHelper::getRandColor()
{
    QList<QColor> colors = getColorList();
    int index = getRandValue(0, colors.size(), true);
    return colors.at(index);
}

void QUIHelper::initRand()
{
    //��ʼ�����������
    QTime t = QTime::currentTime();
    srand(t.msec() + t.second() * 1000);
}

float QUIHelper::getRandFloat(float min, float max)
{
    double diff = fabs(max - min);
    double value = (double)(rand() % 100) / 100;
    value = min + value * diff;
    return value;
}

double QUIHelper::getRandValue(int min, int max, bool contansMin, bool contansMax)
{
    int value;
#if (QT_VERSION <= QT_VERSION_CHECK(5,10,0))
    //ͨ�ù�ʽ a����ʼֵ,n�������ķ�Χ
    //int value = a + rand() % n;
    if (contansMin) {
        if (contansMax) {
            value = min + 0 + (rand() % (max - min + 1));
        } else {
            value = min + 0 + (rand() % (max - min + 0));
        }
    } else {
        if (contansMax) {
            value = min + 1 + (rand() % (max - min + 0));
        } else {
            value = min + 1 + (rand() % (max - min - 1));
        }
    }
#else
    if (contansMin) {
        if (contansMax) {
            value = QRandomGenerator::global()->bounded(min + 0, max + 1);
        } else {
            value = QRandomGenerator::global()->bounded(min + 0, max + 0);
        }
    } else {
        if (contansMax) {
            value = QRandomGenerator::global()->bounded(min + 1, max + 1);
        } else {
            value = QRandomGenerator::global()->bounded(min + 1, max + 0);
        }
    }
#endif
    return value;
}

QStringList QUIHelper::getRandPoint(int count, float mainLng, float mainLat, float dotLng, float dotLat)
{
    //������ɵ�����
    QStringList points;
    for (int i = 0; i < count; ++i) {
        //0.00881415 0.000442928
#if (QT_VERSION >= QT_VERSION_CHECK(5,10,0))
        float lngx = QRandomGenerator::global()->bounded(dotLng);
        float latx = QRandomGenerator::global()->bounded(dotLat);
#else
        float lngx = getRandFloat(dotLng / 10, dotLng);
        float latx = getRandFloat(dotLat / 10, dotLat);
#endif
        //��Ҫ���þ���ת�����ַ���
        QString lng2 = QString::number(mainLng + lngx, 'f', 8);
        QString lat2 = QString::number(mainLat + latx, 'f', 8);
        QString point = QString("%1,%2").arg(lng2).arg(lat2);
        points << point;
    }

    return points;
}

int QUIHelper::getRangeValue(int oldMin, int oldMax, int oldValue, int newMin, int newMax)
{
    return (((oldValue - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
}

QString QUIHelper::getUuid()
{
    QString uuid = QUuid::createUuid().toString();
    uuid.replace("{", "");
    uuid.replace("}", "");
    return uuid;
}

void QUIHelper::checkPath(const QString &dirName)
{
    //���·����Ҫ��ȫ����·��
    QString path = dirName;
    if (path.startsWith("./")) {
        path.replace(".", "");
        path = QUIHelper::appPath() + path;
    } else if (!path.startsWith("/") && !path.contains(":/")) {
        path = QUIHelper::appPath() + "/" + path;
    }

    //Ŀ¼���������½�
    QDir dir(path);
    if (!dir.exists()) {
        dir.mkpath(path);
    }
}

void QUIHelper::sleep(int msec)
{
    if (msec <= 0) {
        return;
    }

#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    QThread::msleep(msec);
#else
    QTime endTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < endTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
#endif
}

void QUIHelper::setStyle()
{
    //��ӡ���������÷�������
    qDebug() << TIMEMS << "QStyleFactory::keys" << QStyleFactory::keys();
    //�������÷��
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    qApp->setStyle(QStyleFactory::create("Fusion"));
#else
    qApp->setStyle(QStyleFactory::create("Cleanlooks"));
#endif

    //����ָ����ɫ
    QPalette palette;
    palette.setBrush(QPalette::Window, QColor("#F0F0F0"));
    qApp->setPalette(palette);
}

QFont QUIHelper::addFont(const QString &fontFile, const QString &fontName)
{
    //�ж�ͼ�������Ƿ����,�����������
    QFontDatabase fontDb;
    if (!fontDb.families().contains(fontName)) {
        int fontId = fontDb.addApplicationFont(fontFile);
        QStringList listName = fontDb.applicationFontFamilies(fontId);
        if (listName.size() == 0) {
            qDebug() << QString("load %1 error").arg(fontName);
        }
    }

    //�ٴ��ж��Ƿ�����������Ʒ�ֹ����ʧ��
    QFont font;
    if (fontDb.families().contains(fontName)) {
        font = QFont(fontName);
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,0))
        font.setHintingPreference(QFont::PreferNoHinting);
#endif
    }

    return font;
}

void QUIHelper::setFont(int fontSize)
{
#ifdef rk3399
    return;
#endif
    //��׿�׼�����Щ�ֻ���Ĭ�����岻�ÿ���Ҫ������������
    //��ҳ�׼���Ҫ�������������������������ʾ����
#if (defined Q_OS_ANDROID) || (defined Q_OS_WASM)
    QString fontFile = ":/font/DroidSansFallback.ttf";
    QString fontName = "Droid Sans Fallback";
    qApp->setFont(addFont(fontFile, fontName));
    return;
#endif

#ifdef __arm__
    fontSize = 25;
#endif
#ifdef Q_OS_ANDROID
    fontSize = 15;
#endif

    QFont font;
    font.setFamily("MicroSoft Yahei");
    font.setPixelSize(fontSize);
    qApp->setFont(font);
}

void QUIHelper::setCode(bool utf8)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    //�����Ҫ����̨��ӡ��Ϣ����������ע�͵��������
    if (utf8) {
        QTextCodec *codec = QTextCodec::codecForName("utf-8");
        QTextCodec::setCodecForLocale(codec);
    }
#else
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#endif
}

void QUIHelper::setTranslator(const QString &qmFile)
{
    //�����²����ڵľͲ���������
    if (!QFile(qmFile).exists()) {
        return;
    }

    QTranslator *translator = new QTranslator(qApp);
    if (translator->load(qmFile)) {
        qApp->installTranslator(translator);
    }
}

#ifdef Q_OS_ANDROID
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
#include <QtAndroidExtras>
#else
//Qt6�н�������Ƶ���coreģ��������ֱ���
#include <QtCore/private/qandroidextras_p.h>
#endif
#endif

bool QUIHelper::checkPermission(const QString &permission)
{
#ifdef Q_OS_ANDROID
#if (QT_VERSION >= QT_VERSION_CHECK(5,10,0) && QT_VERSION < QT_VERSION_CHECK(6,0,0))
    QtAndroid::PermissionResult result = QtAndroid::checkPermission(permission);
    if (result == QtAndroid::PermissionResult::Denied) {
        QtAndroid::requestPermissionsSync(QStringList() << permission);
        result = QtAndroid::checkPermission(permission);
        if (result == QtAndroid::PermissionResult::Denied) {
            return false;
        }
    }
#else
    QFuture<QtAndroidPrivate::PermissionResult> result = QtAndroidPrivate::requestPermission(permission);
    if (result.resultAt(0) == QtAndroidPrivate::PermissionResult::Denied) {
        return false;
    }
#endif
#endif
    return true;
}

void QUIHelper::initAndroidPermission()
{
    //���԰�����Ҫ��̬�����Ȩ�޶�д������
    checkPermission("android.permission.CALL_PHONE");
    checkPermission("android.permission.SEND_SMS");
    checkPermission("android.permission.CAMERA");
    checkPermission("android.permission.READ_EXTERNAL_STORAGE");
    checkPermission("android.permission.WRITE_EXTERNAL_STORAGE");

    checkPermission("android.permission.ACCESS_COARSE_LOCATION");
    checkPermission("android.permission.BLUETOOTH");
    checkPermission("android.permission.BLUETOOTH_SCAN");
    checkPermission("android.permission.BLUETOOTH_CONNECT");
    checkPermission("android.permission.BLUETOOTH_ADVERTISE");
}

void QUIHelper::initAll(bool utf8, bool style, int fontSize)
{
    //��ʼ����׿Ȩ��
    QUIHelper::initAndroidPermission();
    //��ʼ�����������
    QUIHelper::initRand();
    //���ñ���
    QUIHelper::setCode(utf8);
    //��������
    QUIHelper::setFont(fontSize);
    //������ʽ���
    if (style) {
        QUIHelper::setStyle();
    }

    //���÷����ļ�֧�ֶ��
    QUIHelper::setTranslator(":/qm/widgets.qm");
    QUIHelper::setTranslator(":/qm/qt_zh_CN.qm");
    QUIHelper::setTranslator(":/qm/designer_zh_CN.qm");

    //���ò�ʹ�ñ���ϵͳ������������
    QNetworkProxyFactory::setUseSystemConfiguration(false);
}

void QUIHelper::initMain(bool desktopSettingsAware, bool useOpenGLES)
{
    //�����Ƿ�Ӧ�ò���ϵͳ���ñ�������
    QApplication::setDesktopSettingsAware(desktopSettingsAware);

#ifdef Q_OS_ANDROID
#if (QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    //�����߷�������֧��
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
#else
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    //��Ӧ���κ�����
    QApplication::setAttribute(Qt::AA_Use96Dpi);
#endif
#endif

#if (QT_VERSION >= QT_VERSION_CHECK(5,14,0))
    //�߷������Ų���
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
#endif

#if (QT_VERSION >= QT_VERSION_CHECK(5,4,0))
    //win�ϻ�ȡ�Կ��Ƿ񱻽���(�������������OpenGLES)
#ifdef Q_OS_WIN
    QProcess p;
    QStringList args;
    args << "path" << "win32_VideoController" << "get" << "name,Status";
    p.start("wmic", args);
    p.waitForFinished(1000);
    QString result = QString::fromLocal8Bit(p.readAllStandardOutput());
    result.replace("\r", "");
    result.replace("\n", "");
    result = result.simplified();
    result = result.trimmed();
    //Name Status Intel(R) UHD Graphics 630 OK
    //Name Status Intel(R) UHD Graphics 630 Error
    //QStringList list = result.split(" ");
    if (result.contains("Error")) {
        useOpenGLES = true;
    }
#endif

    //����openglģʽ AA_UseDesktopOpenGL(Ĭ��) AA_UseOpenGLES AA_UseSoftwareOpenGL
    //��һЩ�ܾɵ��豸�ϻ��߶�opengl֧�ֺܵ͵��豸����Ҫʹ��AA_UseOpenGLES��ʾ����Ӳ������
    //�����������AA_UseOpenGLES���޷�ʹ��Ӳ�����ٱ���ffmpeg��dxva2
    if (useOpenGLES) {
        QApplication::setAttribute(Qt::AA_UseOpenGLES);
    }

    //����opengl����������
    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
#endif
}

QVector<int> QUIHelper::msgTypes = QVector<int>() << 0 << 1 << 2 << 3 << 4;
QVector<QString> QUIHelper::msgKeys = QVector<QString>() << QString::fromUtf8("����") << QString::fromUtf8("����") << QString::fromUtf8("����") << QString::fromUtf8("����") << QString::fromUtf8("��ʾ");
QVector<QColor> QUIHelper::msgColors = QVector<QColor>() << QColor("#3BA372") << QColor("#EE6668") << QColor("#9861B4") << QColor("#FA8359") << QColor("#22A3A9");
QString QUIHelper::appendMsg(QTextEdit *textEdit, int type, const QString &data, int maxCount, int &currentCount, bool clear, bool pause)
{
    if (clear) {
        textEdit->clear();
        currentCount = 0;
        return QString();
    }

    if (pause) {
        return QString();
    }

    if (currentCount >= maxCount) {
        textEdit->clear();
        currentCount = 0;
    }

    //��ͬ���Ͳ�ͬ��ɫ��ʾ
    QString strType;
    int index = msgTypes.indexOf(type);
    if (index >= 0) {
        strType = msgKeys.at(index);
        textEdit->setTextColor(msgColors.at(index));
    }

    //���˻س����з�
    QString strData = data;
    strData.replace("\r", "");
    strData.replace("\n", "");
    strData = QString("ʱ��[%1] %2: %3").arg(TIMEMS).arg(strType).arg(strData);
    textEdit->append(strData);
    currentCount++;
    return strData;
}

void QUIHelper::setFramelessForm(QWidget *widgetMain, bool tool, bool top, bool menu)
{
    widgetMain->setProperty("form", true);
    widgetMain->setProperty("canMove", true);

    //�����趨���׷������
#ifdef __arm__
    widgetMain->setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
#else
    widgetMain->setWindowFlags(Qt::FramelessWindowHint);
#endif
    if (tool) {
        widgetMain->setWindowFlags(widgetMain->windowFlags() | Qt::Tool);
    }
    if (top) {
        widgetMain->setWindowFlags(widgetMain->windowFlags() | Qt::WindowStaysOnTopHint);
    }
    if (menu) {
        //���������ϵͳ����neokylin�����ϵͳ�߿�
#ifdef Q_OS_WIN
        widgetMain->setWindowFlags(widgetMain->windowFlags() | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
#endif
    }
}

int QUIHelper::showMessageBox(const QString &text, int type, int closeSec, bool exec)
{
    int result = 0;
    if (type == 0) {
        showMessageBoxInfo(text, closeSec, exec);
    } else if (type == 1) {
        showMessageBoxError(text, closeSec, exec);
    } else if (type == 2) {
        result = showMessageBoxQuestion(text);
    }

    return result;
}

void QUIHelper::showMessageBoxInfo(const QString &text, int closeSec, bool exec)
{
    QMessageBox box(QMessageBox::Information, "��ʾ", text);
    box.setStandardButtons(QMessageBox::Yes);
    box.setButtonText(QMessageBox::Yes, QString("ȷ ��"));
    box.exec();
    //QMessageBox::information(0, "��ʾ", info, QMessageBox::Yes);
}

void QUIHelper::showMessageBoxError(const QString &text, int closeSec, bool exec)
{
    QMessageBox box(QMessageBox::Critical, "����", text);
    box.setStandardButtons(QMessageBox::Yes);
    box.setButtonText(QMessageBox::Yes, QString("ȷ ��"));
    box.exec();
    //QMessageBox::critical(0, "����", info, QMessageBox::Yes);
}

int QUIHelper::showMessageBoxQuestion(const QString &text)
{
    QMessageBox box(QMessageBox::Question, "ѯ��", text);
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setButtonText(QMessageBox::Yes, QString("ȷ ��"));
    box.setButtonText(QMessageBox::No, QString("ȡ ��"));
    return box.exec();
    //return QMessageBox::question(0, "ѯ��", info, QMessageBox::Yes | QMessageBox::No);
}

void QUIHelper::initDialog(QFileDialog *dialog, const QString &title, const QString &acceptName,
                           const QString &dirName, bool native, int width, int height)
{
    //���ñ���
    dialog->setWindowTitle(title);
    //���ñ�ǩ�ı�
    dialog->setLabelText(QFileDialog::Accept, acceptName);
    dialog->setLabelText(QFileDialog::Reject, "ȡ��(&C)");
    dialog->setLabelText(QFileDialog::LookIn, "�鿴");
    dialog->setLabelText(QFileDialog::FileName, "����");
    dialog->setLabelText(QFileDialog::FileType, "����");

    //����Ĭ����ʾĿ¼
    if (!dirName.isEmpty()) {
        dialog->setDirectory(dirName);
    }

    //���öԻ�����
    if (width > 0 && height > 0) {
#ifdef Q_OS_ANDROID
        bool horizontal = (QUIHelper::deskWidth() > QUIHelper::deskHeight());
        if (horizontal) {
            width = QUIHelper::deskWidth() / 2;
            height = QUIHelper::deskHeight() - 50;
        } else {
            width = QUIHelper::deskWidth() - 10;
            height = QUIHelper::deskHeight() / 2;
        }
#endif
        dialog->setFixedSize(width, height);
    }

    //�����Ƿ���ñ��ضԻ���
    dialog->setOption(QFileDialog::DontUseNativeDialog, !native);
    //����ֻ������ȡ�����Ͻǵ��½���ť
    //dialog->setReadOnly(true);
}

QString QUIHelper::getDialogResult(QFileDialog *dialog)
{
    QString result;
    if (dialog->exec() == QFileDialog::Accepted) {
        result = dialog->selectedFiles().first();
    }
    return result;
}

QString QUIHelper::getOpenFileName(const QString &filter, const QString &dirName, const QString &fileName,
                                   bool native, int width, int height)
{
    QFileDialog dialog;
    initDialog(&dialog, "���ļ�", "ѡ��(&S)", dirName, native, width, height);

    //�����ļ�����
    if (!filter.isEmpty()) {
        dialog.setNameFilter(filter);
    }

    //����Ĭ���ļ�����
    dialog.selectFile(fileName);
    return getDialogResult(&dialog);
}

QString QUIHelper::getSaveFileName(const QString &filter, const QString &dirName, const QString &fileName,
                                   bool native, int width, int height)
{
    QFileDialog dialog;
    initDialog(&dialog, "�����ļ�", "����(&S)", dirName, native, width, height);

    //�����ļ�����
    if (!filter.isEmpty()) {
        dialog.setNameFilter(filter);
    }

    //����Ĭ���ļ�����
    dialog.selectFile(fileName);
    //����ģ̬������������
    dialog.setWindowModality(Qt::WindowModal);
    //�����ö���ʾ
    dialog.setWindowFlags(dialog.windowFlags() | Qt::WindowStaysOnTopHint);
    return getDialogResult(&dialog);
}

QString QUIHelper::getExistingDirectory(const QString &dirName, bool native, int width, int height)
{
    QFileDialog dialog;
    initDialog(&dialog, "ѡ��Ŀ¼", "ѡ��(&S)", dirName, native, width, height);
    dialog.setOption(QFileDialog::ReadOnly);
    //����ֻ��ʾĿ¼
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
    dialog.setFileMode(QFileDialog::DirectoryOnly);
#endif
    dialog.setOption(QFileDialog::ShowDirsOnly);
    return getDialogResult(&dialog);
}

QString QUIHelper::getXorEncryptDecrypt(const QString &value, char key)
{
    //������Χ�������
    if (key < 0 || key >= 127) {
        key = 127;
    }

    //��Ŵ�5.9�汾����ļ��������ַ���ǰ������ @String �ַ�
    QString result = value;
    if (result.startsWith("@String")) {
        result = result.mid(8, result.length() - 9);
    }

    int size = result.size();
    for (int i = 0; i < size; ++i) {
        result[i] = QChar(result.at(i).toLatin1() ^ key);
    }
    return result;
}

quint8 QUIHelper::getOrCode(const QByteArray &data)
{
    int len = data.length();
    quint8 result = 0;
    for (int i = 0; i < len; ++i) {
        result ^= data.at(i);
    }

    return result;
}

quint8 QUIHelper::getCheckCode(const QByteArray &data)
{
    int len = data.length();
    quint8 temp = 0;
    for (int i = 0; i < len; ++i) {
        temp += data.at(i);
    }

    return temp % 256;
}

void QUIHelper::initTableView(QTableView *tableView, int rowHeight, bool headVisible, bool edit, bool stretchLast)
{
    //��������������Ӧ��qss������ʽ
    tableView->setProperty("model", true);
    //ȡ���Զ�����
    tableView->setWordWrap(false);
    //�����ı�����ʾʡ�Ժ�
    tableView->setTextElideMode(Qt::ElideNone);
    //����ż������ɫ����
    tableView->setAlternatingRowColors(false);
    //��ֱ��ͷ�Ƿ�ɼ�
    tableView->verticalHeader()->setVisible(headVisible);
    //ѡ��һ�б�ͷ�Ƿ�Ӵ�
    tableView->horizontalHeader()->setHighlightSections(false);
    //���һ���������
    tableView->horizontalHeader()->setStretchLastSection(stretchLast);
    //�б�����С��ȳߴ�
    tableView->horizontalHeader()->setMinimumSectionSize(0);
    //�б�����С�߶�,��ͬ�ں�Ĭ���и�һ��
    tableView->horizontalHeader()->setFixedHeight(rowHeight);
    //Ĭ���и�
    tableView->verticalHeader()->setDefaultSectionSize(rowHeight);
    //ѡ��ʱһ������ѡ��
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ֻ����ѡ�񵥸�
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    //��ͷ���ɵ���
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    tableView->horizontalHeader()->setSectionsClickable(false);
#else
    tableView->horizontalHeader()->setClickable(false);
#endif

    //��갴�¼�����༭ģʽ
    if (edit) {
        tableView->setEditTriggers(QAbstractItemView::CurrentChanged | QAbstractItemView::DoubleClicked);
    } else {
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

void QUIHelper::openFile(const QString &fileName, const QString &msg)
{
#ifdef __arm__
    return;
#endif
    //�ļ����������ô���
    if (!QFile(fileName).exists()) {
        return;
    }
    if (QUIHelper::showMessageBoxQuestion(msg + "�ɹ�, ȷ�����ھʹ���?") == QMessageBox::Yes) {
        QString url = QString("file:///%1").arg(fileName);
        QDesktopServices::openUrl(QUrl(url, QUrl::TolerantMode));
    }
}

bool QUIHelper::checkIniFile(const QString &iniFile)
{
    //��������ļ���СΪ0,���Գ�ʼֵ��������,�����������ļ�
    QFile file(iniFile);
    if (file.size() == 0) {
        return false;
    }

    //��������ļ�������,���Գ�ʼֵ��������,�����������ļ�
    if (file.open(QFile::ReadOnly)) {
        bool ok = true;
        while (!file.atEnd()) {
            QString line = file.readLine();
            line.replace("\r", "");
            line.replace("\n", "");
            QStringList list = line.split("=");

            if (list.size() == 2) {
                QString key = list.at(0);
                QString value = list.at(1);
                if (value.isEmpty()) {
                    qDebug() << TIMEMS << "ini node no value" << key;
                    ok = false;
                    break;
                }
            }
        }

        if (!ok) {
            return false;
        }
    } else {
        return false;
    }

    return true;
}

QString QUIHelper::cutString(const QString &text, int len, int left, int right, bool file, const QString &mid)
{
    //���ָ�����ַ����ָ����ʾ���ļ�����Ҫȥ����չ��
    QString result = text;
    if (file && result.contains(".")) {
        int index = result.lastIndexOf(".");
        result = result.mid(0, index);
    }

    //�����ַ�����ʽΪ ǰ׺�ַ�...��׺�ַ�
    if (result.length() > len) {
        result = QString("%1%2%3").arg(result.left(left)).arg(mid).arg(result.right(right));
    }

    return result;
}

QRect QUIHelper::getCenterRect(const QSize &imageSize, const QRect &widgetRect, int borderWidth, int scaleMode)
{
    QSize newSize = imageSize;
    QSize widgetSize = widgetRect.size() - QSize(borderWidth * 1, borderWidth * 1);

    if (scaleMode == 0) {
        if (newSize.width() > widgetSize.width() || newSize.height() > widgetSize.height()) {
            newSize.scale(widgetSize, Qt::KeepAspectRatio);
        }
    } else if (scaleMode == 1) {
        newSize.scale(widgetSize, Qt::KeepAspectRatio);
    } else {
        newSize = widgetSize;
    }

    int x = widgetRect.center().x() - newSize.width() / 2;
    int y = widgetRect.center().y() - newSize.height() / 2;
    //����2�ı�����Ҫƫ��1����
    x += (x % 2 == 0 ? 1 : 0);
    y += (y % 2 == 0 ? 1 : 0);
    return QRect(x, y, newSize.width(), newSize.height());
}

void QUIHelper::getScaledImage(QImage &image, const QSize &widgetSize, int scaleMode, bool fast)
{
    Qt::TransformationMode mode = fast ? Qt::FastTransformation : Qt::SmoothTransformation;
    if (scaleMode == 0) {
        if (image.width() > widgetSize.width() || image.height() > widgetSize.height()) {
            image = image.scaled(widgetSize, Qt::KeepAspectRatio, mode);
        }
    } else if (scaleMode == 1) {
        image = image.scaled(widgetSize, Qt::KeepAspectRatio, mode);
    } else {
        image = image.scaled(widgetSize, Qt::IgnoreAspectRatio, mode);
    }
}

QString QUIHelper::getTimeString(qint64 time)
{
    time = time / 1000;
    QString min = QString("%1").arg(time / 60, 2, 10, QChar('0'));
    QString sec = QString("%2").arg(time % 60, 2, 10, QChar('0'));
    return QString("%1:%2").arg(min).arg(sec);
}

QString QUIHelper::getTimeString(QElapsedTimer timer)
{
    return QString::number((float)timer.elapsed() / 1000, 'f', 3);
}

QString QUIHelper::getSizeString(quint64 size)
{
    float num = size;
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";

    QString unit("bytes");
    QStringListIterator i(list);
    while (num >= 1024.0 && i.hasNext()) {
        unit = i.next();
        num /= 1024.0;
    }

    return QString("%1 %2").arg(QString::number(num, 'f', 2)).arg(unit);
}
