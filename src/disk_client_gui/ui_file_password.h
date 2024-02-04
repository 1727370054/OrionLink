/********************************************************************************
** Form generated from reading UI file 'file_password.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILE_PASSWORD_H
#define UI_FILE_PASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FilePassword
{
public:
    QFrame *pass_frame;
    QLineEdit *passwordEdit;
    QLabel *passlog;
    QPushButton *pushButton;

    void setupUi(QDialog *FilePassword)
    {
        if (FilePassword->objectName().isEmpty())
            FilePassword->setObjectName(QString::fromUtf8("FilePassword"));
        FilePassword->resize(555, 72);
        FilePassword->setMinimumSize(QSize(555, 72));
        FilePassword->setMaximumSize(QSize(580, 90));
        pass_frame = new QFrame(FilePassword);
        pass_frame->setObjectName(QString::fromUtf8("pass_frame"));
        pass_frame->setGeometry(QRect(40, 20, 311, 40));
        pass_frame->setStyleSheet(QString::fromUtf8("\n"
"\n"
"#pass_frame::!hover{\n"
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
        passlog = new QLabel(pass_frame);
        passlog->setObjectName(QString::fromUtf8("passlog"));
        passlog->setGeometry(QRect(10, 12, 18, 18));
        passlog->setStyleSheet(QString::fromUtf8("background-image: url(:/XMSDiskClientGui/Resources/passwd.png);"));
        pushButton = new QPushButton(FilePassword);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(370, 20, 171, 41));
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

        retranslateUi(FilePassword);
        QObject::connect(pushButton, SIGNAL(clicked()), FilePassword, SLOT(accept()));

        pushButton->setDefault(true);


        QMetaObject::connectSlotsByName(FilePassword);
    } // setupUi

    void retranslateUi(QDialog *FilePassword)
    {
        FilePassword->setWindowTitle(QApplication::translate("FilePassword", "\350\256\276\345\256\232\346\226\207\344\273\266\345\257\206\351\222\245", nullptr));
        passwordEdit->setText(QApplication::translate("FilePassword", "123456", nullptr));
        passlog->setText(QString());
        pushButton->setText(QApplication::translate("FilePassword", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilePassword: public Ui_FilePassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILE_PASSWORD_H
