#ifndef APPDATA_H
#define APPDATA_H

#include "head.h"

class AppData
{
public:
    static QString TitleFlag;       //�����ʶ
    static int RowHeight;           //�и�
    static int RightWidth;          //�Ҳ���
    static int FormWidth;           //������
    static int FormHeight;          //����߶�

    static void checkRatio();       //У��ֱ���    
};

#endif // APPDATA_H
