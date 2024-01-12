/********************************************************************************
** Form generated from reading UI file 'login_gui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_GUI_H
#define UI_LOGIN_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_LoginGUI
{
public:
    QFrame *frame;
    QToolButton *toolButton;

    void setupUi(QDialog *LoginGUI)
    {
        if (LoginGUI->objectName().isEmpty())
            LoginGUI->setObjectName(QString::fromUtf8("LoginGUI"));
        LoginGUI->resize(400, 503);
        LoginGUI->setStyleSheet(QString::fromUtf8("*{\n"
"font-size:24px;\n"
"font-family:Century Gothic;\n"
"}\n"
"QFrame{\n"
"background:rgba(0,0,0,0.8);\n"
"border-radius:15px;\n"
"}\n"
"#Widget{\n"
"background:url(D:/pictures/sunrise.jpg);\n"
"}\n"
"\n"
"QToolButton{\n"
"background:red;\n"
"border-radius:60px;\n"
"}\n"
"QLabel{\n"
"color:white;\n"
"background:transparent;\n"
"}\n"
"QPushButton{\n"
"background:white;\n"
"border-radius:15px;\n"
"}\n"
"QPushButton:hover{\n"
"background:#333;\n"
"border-radius:15px;\n"
"background:#49ebff;\n"
"}\n"
"QLineEdit{\n"
"background:transparent;\n"
"border:none;\n"
"color:#717072;\n"
"border-bottom:1px solid #717072;\n"
"}"));
        frame = new QFrame(LoginGUI);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(90, 70, 161, 211));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        toolButton = new QToolButton(LoginGUI);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(110, 350, 61, 61));

        retranslateUi(LoginGUI);

        QMetaObject::connectSlotsByName(LoginGUI);
    } // setupUi

    void retranslateUi(QDialog *LoginGUI)
    {
        LoginGUI->setWindowTitle(QApplication::translate("LoginGUI", "Dialog", nullptr));
        toolButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginGUI: public Ui_LoginGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_GUI_H
