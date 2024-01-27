#ifndef BASE64HELPER_H
#define BASE64HELPER_H

/**
 * base64����ת���� ����:feiyangqingyun(QQ:517216493) 2016-12-16
 * 1. ͼƬתbase64�ַ�����
 * 2. base64�ַ���תͼƬ��
 * 3. �ַ�תbase64�ַ�����
 * 4. base64�ַ���ת�ַ���
 * 5. ������������ѹ����
 * 6. Qt6��base64����ת����������дЧ����������200%��
 */

#include <QImage>

#ifdef quc
class Q_DECL_EXPORT Base64Helper
#else
class Base64Helper
#endif

{
public:
    //ͼƬתbase64�ַ���
    static QString imageToBase64(const QImage &image);
    static QByteArray imageToBase64x(const QImage &image);

    //base64�ַ���תͼƬ
    static QImage base64ToImage(const QString &data);
    static QImage base64ToImagex(const QByteArray &data);

    //�ַ�����base64��ת
    static QString textToBase64(const QString &text);
    static QString base64ToText(const QString &text);
};

#endif // BASE64HELPER_H
