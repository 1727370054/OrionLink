#ifndef QUIHELPER2_H
#define QUIHELPER2_H

#include "head.h"

class QUIHelper
{
public:
    //��ȡ��ǰ���������Ļ����/����ߴ�/����ϵ��
    static int getScreenIndex();
    static QRect getScreenRect(bool available = true);
    static qreal getScreenRatio(bool devicePixel = false);
    //������ǰ���������Ļ���гߴ�
    static QRect checkCenterRect(QRect &rect, bool available = true);

    //��ȡ�����ȸ߶�+������ʾ
    static int deskWidth();
    static int deskHeight();
    static QSize deskSize();

    //������ʾ����
    //�����־λָ����������Ϊ���ջ������������Ϊ����
    static QWidget *centerBaseForm;
    static void setFormInCenter(QWidget *form);
    static void showForm(QWidget *form);

    //�����ļ�����+��ǰ����·��
    static QString appName();
    static QString appPath();

    //��ȡ��������IP����
    static QStringList getLocalIPs();

    //��ȡ������ɫ����
    static QList<QColor> colors;
    static QList<QColor> getColorList();
    static QStringList getColorNames();
    //�����ȡ��ɫ�����е���ɫ
    static QColor getRandColor();

    //��ʼ�����������
    static void initRand();
    //��ȡ���С��
    static float getRandFloat(float min, float max);
    //��ȡ�����,ָ����Сֵ�����ֵ
    static double getRandValue(int min, int max, bool contansMin = false, bool contansMax = false);
    //��ȡ��Χֵ�����γ�ȼ���
    static QStringList getRandPoint(int count, float mainLng, float mainLat, float dotLng, float dotLat);
    //���ݾɵķ�Χֵ��ֵ�����µķ�Χֵ��Ӧ��ֵ
    static int getRangeValue(int oldMin, int oldMax, int oldValue, int newMin, int newMax);

    //��ȡuuid
    static QString getUuid();
    //У��Ŀ¼
    static void checkPath(const QString &dirName);
    //��ʱ
    static void sleep(int msec);

    //����Qt�Դ���ʽ
    static void setStyle();
    //��������
    static QFont addFont(const QString &fontFile, const QString &fontName);
    static void setFont(int fontSize = 12);
    //���ñ���
    static void setCode(bool utf8 = true);
    //���÷����ļ�
    static void setTranslator(const QString &qmFile);

    //��̬����Ȩ��
    static bool checkPermission(const QString &permission);
    //���밲׿Ȩ��
    static void initAndroidPermission();

    //һ�����������а���������ʽ�����
    static void initAll(bool utf8 = true, bool style = true, int fontSize = 13);
    //��ʼ��main������ǰ��ִ�е�һ�δ���
    static void initMain(bool desktopSettingsAware = true, bool useOpenGLES = false);

    //������Ϣ
    static QVector<int> msgTypes;
    static QVector<QString> msgKeys;
    static QVector<QColor> msgColors;
    static QString appendMsg(QTextEdit *textEdit, int type, const QString &data,
                             int maxCount, int &currentCount,
                             bool clear = false, bool pause = false);

    //�����ޱ߿�
    static void setFramelessForm(QWidget *widgetMain, bool tool = false, bool top = false, bool menu = true);

    //������
    static int showMessageBox(const QString &text, int type = 0, int closeSec = 0, bool exec = false);
    //������Ϣ��
    static void showMessageBoxInfo(const QString &text, int closeSec = 0, bool exec = false);
    //���������
    static void showMessageBoxError(const QString &text, int closeSec = 0, bool exec = false);
    //����ѯ�ʿ�
    static int showMessageBoxQuestion(const QString &text);

    //Ϊʲô��Ҫ�Զ���Ի�����Ϊ�ɿؿ�ߺͺ�����Ӧ�ı���
    //��ʼ���Ի����ı�
    static void initDialog(QFileDialog *dialog, const QString &title, const QString &acceptName,
                           const QString &dirName, bool native, int width, int height);
    //�õ��Ի�����
    static QString getDialogResult(QFileDialog *dialog);
    //ѡ���ļ��Ի���
    static QString getOpenFileName(const QString &filter = QString(),
                                   const QString &dirName = QString(),
                                   const QString &fileName = QString(),
                                   bool native = false, int width = 900, int height = 600);
    //�����ļ��Ի���
    static QString getSaveFileName(const QString &filter = QString(),
                                   const QString &dirName = QString(),
                                   const QString &fileName = QString(),
                                   bool native = false, int width = 900, int height = 600);
    //ѡ��Ŀ¼�Ի���
    static QString getExistingDirectory(const QString &dirName = QString(),
                                        bool native = false, int width = 900, int height = 600);

    //������-ֻ֧���ַ�,�����������Ҫ����ת��base64����
    static QString getXorEncryptDecrypt(const QString &value, char key);
    //���У��
    static quint8 getOrCode(const QByteArray &data);
    //����У����
    static quint8 getCheckCode(const QByteArray &data);

    //��ʼ�����
    static void initTableView(QTableView *tableView, int rowHeight = 25,
                              bool headVisible = false, bool edit = false,
                              bool stretchLast = true);
    //���ļ�����ʾ��
    static void openFile(const QString &fileName, const QString &msg);

    //���ini�����ļ�
    static bool checkIniFile(const QString &iniFile);

    //��β�ض��ַ�����ʾ
    static QString cutString(const QString &text, int len, int left, int right, bool file, const QString &mid = "...");

    //����ͼƬ�ߴ�ʹ������򼰱߿��С���ؾ�������(scaleMode: 0-�Զ����� 1-�ȱ����� 2-�������)
    static QRect getCenterRect(const QSize &imageSize, const QRect &widgetRect, int borderWidth = 2, int scaleMode = 0);
    //����ͼƬ�ߴ�ʹ���ߴ缰���Ų��Է��غ��ʳߴ�(scaleMode: 0-�Զ����� 1-�ȱ����� 2-�������)
    static void getScaledImage(QImage &image, const QSize &widgetSize, int scaleMode = 0, bool fast = true);

    //������תʱ�� 00:00
    static QString getTimeString(qint64 time);
    //��ʱʱ��ת����
    static QString getTimeString(QElapsedTimer timer);
    //�ļ���Сת KB MB GB TB
    static QString getSizeString(quint64 size);
};

#endif // QUIHELPER2_H
