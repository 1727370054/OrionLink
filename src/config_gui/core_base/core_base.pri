QT += network
greaterThan(QT_MAJOR_VERSION, 4) {
lessThan(QT_MAJOR_VERSION, 6) {
android {QT += androidextras}
} else {
QT += core-private
}}

#ָ������������ļ����ű���ŵ���ӦĿ¼
MOC_DIR     = temp/moc
RCC_DIR     = temp/rcc
UI_DIR      = temp/ui
OBJECTS_DIR = temp/obj

#ָ���������ɵĿ�ִ���ļ��ŵ�Դ����һ��Ŀ¼�µ�binĿ¼
!android {
!wasm {
DESTDIR = $$PWD/../bin
}}

#�����о��涼�ص��۲���Ϊ��
CONFIG += warn_off
#��������Դ֧��
CONFIG += resources_big
#������Ὣ��ӡ��Ϣ�ÿ���̨���
#CONFIG += console
#�����󲻻����ɿյ� debug release Ŀ¼
#CONFIG -= debug_and_release

#����ȫ־H3оƬ����
include ($$PWD/h3.pri)
#����ǰĿ¼���뵽ͷ�ļ�·��
INCLUDEPATH += $$PWD

HEADERS += $$PWD/appdata.h
SOURCES += $$PWD/appdata.cpp

HEADERS += $$PWD/appinit.h
SOURCES += $$PWD/appinit.cpp

HEADERS += $$PWD/base64helper.h
SOURCES += $$PWD/base64helper.cpp

HEADERS += $$PWD/customstyle.h
SOURCES += $$PWD/customstyle.cpp

HEADERS += $$PWD/iconhelper.h
SOURCES += $$PWD/iconhelper.cpp

HEADERS += $$PWD/quihelper.h
SOURCES += $$PWD/quihelper.cpp

#����ָ�������ض�Ӧ����Դ�ļ�
!contains(DEFINES, no_qrc_image) {
RESOURCES += $$PWD/qrc/image.qrc
}

!contains(DEFINES, no_qrc_qm) {
RESOURCES += $$PWD/qrc/qm.qrc
}

!contains(DEFINES, no_qrc_font) {
RESOURCES += $$PWD/qrc/font.qrc
}
