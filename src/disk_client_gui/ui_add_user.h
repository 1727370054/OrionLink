/********************************************************************************
** Form generated from reading UI file 'add_user.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_USER_H
#define UI_ADD_USER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddUser
{
public:
    QFrame *user_frame;
    QLineEdit *userEdit;
    QLabel *userlogo;
    QPushButton *pushButton;
    QFrame *pass_frame;
    QLineEdit *passwordEdit;
    QLabel *passlogo;
    QFrame *email_frame;
    QLineEdit *emailEdit;
    QLabel *passlogo_2;

    void setupUi(QDialog *AddUser)
    {
        if (AddUser->objectName().isEmpty())
            AddUser->setObjectName(QString::fromUtf8("AddUser"));
        AddUser->resize(550, 200);
        AddUser->setMinimumSize(QSize(550, 160));
        AddUser->setMaximumSize(QSize(580, 200));
        user_frame = new QFrame(AddUser);
        user_frame->setObjectName(QString::fromUtf8("user_frame"));
        user_frame->setGeometry(QRect(40, 20, 311, 40));
        user_frame->setStyleSheet(QString::fromUtf8("\n"
"\n"
"#user_frame::!hover{\n"
"\n"
"      border: 1px solid #c7c7c7;\n"
"      border-radius: 2px;\n"
"	  margin-top: 0ex\n"
"\n"
"}\n"
"#user_frame::hover{\n"
"      border: 1px solid #58a6ee;\n"
"      border-radius: 2px;\n"
"	  margin-top: 0ex\n"
"}"));
        user_frame->setFrameShape(QFrame::StyledPanel);
        user_frame->setFrameShadow(QFrame::Raised);
        userEdit = new QLineEdit(user_frame);
        userEdit->setObjectName(QString::fromUtf8("userEdit"));
        userEdit->setGeometry(QRect(40, 5, 251, 30));
        userEdit->setStyleSheet(QString::fromUtf8("font: 12pt"));
        userEdit->setFrame(false);
        userEdit->setEchoMode(QLineEdit::Normal);
        userEdit->setClearButtonEnabled(false);
        userlogo = new QLabel(user_frame);
        userlogo->setObjectName(QString::fromUtf8("userlogo"));
        userlogo->setGeometry(QRect(10, 12, 18, 18));
        userlogo->setStyleSheet(QString::fromUtf8("background-image: url(:/XMSDiskClientGui/Resources/person.png);"));
        pushButton = new QPushButton(AddUser);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(370, 150, 171, 41));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"background-repeat: no-repeat;\n"
"background-position:left;\n"
"border-radius:4px;   \n"
"color:rgb(255, 255, 255);\n"
"font: 12pt \"\351\273\221\344\275\223\";\n"
"}\n"
"QPushButton::!hover{\n"
"background-color: rgb(6, 168, 255);\n"
"\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background-color: #059bec;\n"
"}"));
        pushButton->setFlat(false);
        pass_frame = new QFrame(AddUser);
        pass_frame->setObjectName(QString::fromUtf8("pass_frame"));
        pass_frame->setGeometry(QRect(40, 80, 311, 40));
        pass_frame->setStyleSheet(QString::fromUtf8("#pass_frame::!hover{\n"
"\n"
"      border: 1px solid #c7c7c7;\n"
"      border-radius: 2px;\n"
"	  margin-top: 0ex\n"
"\n"
"}\n"
"#pass_frame::hover{\n"
"      border: 1px solid #58a6ee;\n"
"      border-radius: 2px;\n"
"	  margin-top: 0ex\n"
"}"));
        pass_frame->setFrameShape(QFrame::StyledPanel);
        pass_frame->setFrameShadow(QFrame::Raised);
        passwordEdit = new QLineEdit(pass_frame);
        passwordEdit->setObjectName(QString::fromUtf8("passwordEdit"));
        passwordEdit->setGeometry(QRect(40, 5, 251, 30));
        passwordEdit->setStyleSheet(QString::fromUtf8("font: 12pt"));
        passwordEdit->setFrame(false);
        passwordEdit->setEchoMode(QLineEdit::Password);
        passwordEdit->setClearButtonEnabled(false);
        passlogo = new QLabel(pass_frame);
        passlogo->setObjectName(QString::fromUtf8("passlogo"));
        passlogo->setGeometry(QRect(10, 12, 18, 18));
        passlogo->setStyleSheet(QString::fromUtf8("background-image: url(:/XMSDiskClientGui/Resources/passwd.png);"));
        email_frame = new QFrame(AddUser);
        email_frame->setObjectName(QString::fromUtf8("email_frame"));
        email_frame->setGeometry(QRect(40, 140, 311, 40));
        email_frame->setStyleSheet(QString::fromUtf8("#email_frame::!hover{\n"
"\n"
"      border: 1px solid #c7c7c7;\n"
"      border-radius: 2px;\n"
"	  margin-top: 0ex\n"
"\n"
"}\n"
"#email_frame::hover{\n"
"      border: 1px solid #58a6ee;\n"
"      border-radius: 2px;\n"
"	  margin-top: 0ex\n"
"}"));
        email_frame->setFrameShape(QFrame::StyledPanel);
        email_frame->setFrameShadow(QFrame::Raised);
        emailEdit = new QLineEdit(email_frame);
        emailEdit->setObjectName(QString::fromUtf8("emailEdit"));
        emailEdit->setGeometry(QRect(40, 5, 251, 30));
        emailEdit->setStyleSheet(QString::fromUtf8("font: 12pt"));
        emailEdit->setFrame(false);
        emailEdit->setEchoMode(QLineEdit::Normal);
        emailEdit->setClearButtonEnabled(false);
        passlogo_2 = new QLabel(email_frame);
        passlogo_2->setObjectName(QString::fromUtf8("passlogo_2"));
        passlogo_2->setGeometry(QRect(10, 10, 31, 18));
        passlogo_2->setStyleSheet(QString::fromUtf8(""));
        passlogo_2->setTextFormat(Qt::AutoText);

        retranslateUi(AddUser);
        QObject::connect(pushButton, SIGNAL(clicked()), AddUser, SLOT(accept()));

        pushButton->setDefault(true);


        QMetaObject::connectSlotsByName(AddUser);
    } // setupUi

    void retranslateUi(QDialog *AddUser)
    {
        AddUser->setWindowTitle(QApplication::translate("AddUser", "\346\267\273\345\212\240\347\275\221\347\233\230\347\224\250\346\210\267", nullptr));
        userEdit->setText(QString());
        userlogo->setText(QString());
        pushButton->setText(QApplication::translate("AddUser", "\346\267\273\345\212\240", nullptr));
        passwordEdit->setText(QString());
        passlogo->setText(QString());
        emailEdit->setText(QString());
        passlogo_2->setText(QApplication::translate("AddUser", "\351\202\256\347\256\261", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddUser: public Ui_AddUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_USER_H
