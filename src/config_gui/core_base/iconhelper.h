#ifndef ICONHELPER_H
#define ICONHELPER_H

/**
 * 1. �ɴ������ͼ�������ļ���һ����ͨ������ͼ�����塣
 * 2. Ĭ���Ѿ������˰���Ͱ�ͼ������FontAliBaBa������֪��ͼ������FontAwesome������ͼ������FontWeather��
 * 3. ������ QLabel��QAbstractButton �ı�Ϊͼ�����塣
 * 4. ������ͼ��������Ϊ QAbstractButton ��ťͼ�ꡣ
 * 5. �������ܵķ��� getPixmap ��ͼ������ֵת��ΪͼƬ��
 * 6. �����������ı���ͼ�ꡢͼƬ�ȶ���������ͼ��Ĵ�С���ߴ硢��ɫ�Ȳ�����
 * 7. ���ó�����������ʽ���ã���ͼ��������Ϊͼ�����õ���ť��
 * 8. ֧�ָ�����ɫ���ñ���������ɫ����ͣ��ɫ��������ɫ��ѡ����ɫ��
 * 9. �����õ�����λ��Ϊ left��right��top��bottom ���֡�
 * 10. �����õ�������߿���ɫ�ʹ�ϸ��С��
 * 11. �������ĸ����л�Ч�����������ͣ�����¡�ѡ�еȶ��Զ��������ʽ���á�
 * 12. ȫ�־�̬�������ӿڷḻ��ʹ�ü���򵥷��㡣
 */

#include <QtGui>
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
#include <QtWidgets>
#endif

#ifdef quc
class Q_DECL_EXPORT IconHelper : public QObject
#else
class IconHelper : public QObject
#endif

{
    Q_OBJECT

private:
    //����Ͱ�ͼ��������
    static IconHelper *iconFontAliBaBa;
    //FontAwesomeͼ��������
    static IconHelper *iconFontAwesome;
    //FontAwesome6ͼ��������
    static IconHelper *iconFontAwesome6;
    //����ͼ��������
    static IconHelper *iconFontWeather;
    //ͼ����������
    static int iconFontIndex;

public:
    //��ʽ��ɫ�ṹ��
    struct StyleColor {
        QString position;           //λ�� left right top bottom
        bool defaultBorder;         //Ĭ���б߿�

        quint32 btnWidth;           //��ť���
        quint32 btnHeight;          //��ť�߶�

        quint32 iconSize;           //ͼ������ߴ�
        quint32 iconWidth;          //ͼ��ͼƬ���
        quint32 iconHeight;         //ͼ��ͼƬ�߶�

        quint32 borderWidth;        //�߿���
        QString borderColor;        //�߿���ɫ

        QString normalBgColor;      //����������ɫ
        QString normalTextColor;    //����������ɫ
        QString hoverBgColor;       //��ͣ������ɫ
        QString hoverTextColor;     //��ͣ������ɫ
        QString pressedBgColor;     //���±�����ɫ
        QString pressedTextColor;   //����������ɫ
        QString checkedBgColor;     //ѡ�б�����ɫ
        QString checkedTextColor;   //ѡ��������ɫ

        StyleColor() {
            position = "left";
            defaultBorder = false;

            btnWidth = 0;
            btnHeight = 0;

            iconSize = 12;
            iconWidth = 15;
            iconHeight = 15;

            borderWidth = 3;
            borderColor = "#029FEA";

            normalBgColor = "#292F38";
            normalTextColor = "#54626F";
            hoverBgColor = "#40444D";
            hoverTextColor = "#FDFDFD";
            pressedBgColor = "#404244";
            pressedTextColor = "#FDFDFD";
            checkedBgColor = "#44494F";
            checkedTextColor = "#FDFDFD";
        }

        //���ó�����ɫ ��ͨ״̬+����״̬
        void setColor(const QString &normalBgColor,
                      const QString &normalTextColor,
                      const QString &darkBgColor,
                      const QString &darkTextColor) {
            this->normalBgColor = normalBgColor;
            this->normalTextColor = normalTextColor;
            this->hoverBgColor = darkBgColor;
            this->hoverTextColor = darkTextColor;
            this->pressedBgColor = darkBgColor;
            this->pressedTextColor = darkTextColor;
            this->checkedBgColor = darkBgColor;
            this->checkedTextColor = darkTextColor;
        }
    };


    //��ʼ��ͼ������
    static void initFont();
    //��������ͼ�������ļ�����
    static void setIconFontIndex(int index);

    //��ȡͼ������
    static QFont getIconFontAliBaBa();
    static QFont getIconFontAwesome();
    static QFont getIconFontAwesome6();
    static QFont getIconFontWeather();

    //����ֵ��ȡͼ��������
    static IconHelper *getIconHelper(int icon);

    //����ͼ�����嵽��ǩ
    static void setIcon(QLabel *lab, int icon, quint32 size = 12);
    //����ͼ�����嵽��ť
    static void setIcon(QAbstractButton *btn, int icon, quint32 size = 12);

    //����ͼ�����嵽ͼ��
    static void setPixmap(QAbstractButton *btn, const QColor &color,
                          int icon, quint32 size = 12,
                          quint32 width = 15, quint32 height = 15,
                          int flags = Qt::AlignCenter);
    //��ȡָ��ͼ������,����ָ�����ִ�С,ͼƬ���,���ֶ���
    static QPixmap getPixmap(const QColor &color, int icon, quint32 size = 12,
                             quint32 width = 15, quint32 height = 15,
                             int flags = Qt::AlignCenter);

    //ָ�����������ʽ,��ͼ���Ч���л�+��ͣ��ɫ+������ɫ+ѡ����ɫ
    static void setStyle(QWidget *widget, QList<QPushButton *> btns, QList<int> icons, const StyleColor &styleColor);
    static void setStyle(QWidget *widget, QList<QToolButton *> btns, QList<int> icons, const StyleColor &styleColor);
    static void setStyle(QWidget *widget, QList<QAbstractButton *> btns, QList<int> icons, const StyleColor &styleColor);

    //Ĭ�Ϲ��캯��,���������ļ�+��������
    explicit IconHelper(const QString &fontFile, const QString &fontName, QObject *parent = 0);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    QFont iconFont;                 //ͼ������
    QList<QAbstractButton *> btns;  //��ť����
    QList<QPixmap> pixNormal;       //����ͼƬ����
    QList<QPixmap> pixHover;        //��ͣͼƬ����
    QList<QPixmap> pixPressed;      //����ͼƬ����
    QList<QPixmap> pixChecked;      //ѡ��ͼƬ����

private slots:
    //��ťѡ��״̬�л�����
    void toggled(bool checked);

public:
    //��ȡͼ������
    QFont getIconFont();

    //����ͼ�����嵽��ǩ
    void setIcon1(QLabel *lab, int icon, quint32 size = 12);
    //����ͼ�����嵽��ť
    void setIcon1(QAbstractButton *btn, int icon, quint32 size = 12);

    //����ͼ�����嵽ͼ��
    void setPixmap1(QAbstractButton *btn, const QColor &color,
                    int icon, quint32 size = 12,
                    quint32 width = 15, quint32 height = 15,
                    int flags = Qt::AlignCenter);
    //��ȡָ��ͼ������,����ָ�����ִ�С,ͼƬ���,���ֶ���
    QPixmap getPixmap1(const QColor &color, int icon, quint32 size = 12,
                       quint32 width = 15, quint32 height = 15,
                       int flags = Qt::AlignCenter);

    //ָ�����������ʽ,��ͼ���Ч���л�+��ͣ��ɫ+������ɫ+ѡ����ɫ
    void setStyle1(QWidget *widget, QList<QPushButton *> btns, QList<int> icons, const StyleColor &styleColor);
    void setStyle1(QWidget *widget, QList<QToolButton *> btns, QList<int> icons, const StyleColor &styleColor);
    void setStyle1(QWidget *widget, QList<QAbstractButton *> btns, QList<int> icons, const StyleColor &styleColor);
};

#endif // ICONHELPER_H
