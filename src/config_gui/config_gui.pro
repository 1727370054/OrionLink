QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = config_gui
TEMPLATE    = app

HEADERS     += head.h \
			   login_gui.h
SOURCES     += main.cpp \
			   login_gui.cpp
FORMS += \
    login_gui.ui

RESOURCES   += other/main.qrc \
			   login_gui.qrc
RESOURCES   += $$PWD/./core_qss/qss.qrc

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/form
include ($$PWD/form/form.pri)
include ($$PWD/form/login_gui.pri)

INCLUDEPATH += $$PWD/./core_base
include ($$PWD/./core_base/core_base.pri)
