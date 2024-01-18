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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginUI
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer;
    QFrame *login_frame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_8;
    QLabel *label_logo;
    QLabel *label_title;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_name;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit_pwd;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_7;
    QVBoxLayout *verticalLayout_2;
    QPushButton *login_Button;
    QSpacerItem *verticalSpacer_5;
    QPushButton *regilaster_Button;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *LoginUI)
    {
        if (LoginUI->objectName().isEmpty())
            LoginUI->setObjectName(QString::fromUtf8("LoginUI"));
        LoginUI->resize(1200, 700);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginUI->sizePolicy().hasHeightForWidth());
        LoginUI->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(LoginUI);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer_4, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        login_frame = new QFrame(LoginUI);
        login_frame->setObjectName(QString::fromUtf8("login_frame"));
        sizePolicy.setHeightForWidth(login_frame->sizePolicy().hasHeightForWidth());
        login_frame->setSizePolicy(sizePolicy);
        login_frame->setMinimumSize(QSize(680, 600));
        login_frame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        login_frame->setFrameShape(QFrame::StyledPanel);
        login_frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(login_frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_8);

        label_logo = new QLabel(login_frame);
        label_logo->setObjectName(QString::fromUtf8("label_logo"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_logo->sizePolicy().hasHeightForWidth());
        label_logo->setSizePolicy(sizePolicy1);
        label_logo->setMinimumSize(QSize(80, 100));
        label_logo->setLayoutDirection(Qt::LeftToRight);
        label_logo->setAutoFillBackground(false);
        label_logo->setStyleSheet(QString::fromUtf8(""));
        label_logo->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_logo);

        label_title = new QLabel(login_frame);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        label_title->setEnabled(true);
        label_title->setLayoutDirection(Qt::LeftToRight);
        label_title->setStyleSheet(QString::fromUtf8("font: 25 22pt \"\345\276\256\350\275\257\351\233\205\351\273\221 Light\";"));
        label_title->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_title);

        verticalSpacer_2 = new QSpacerItem(17, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineEdit_name = new QLineEdit(login_frame);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        sizePolicy.setHeightForWidth(lineEdit_name->sizePolicy().hasHeightForWidth());
        lineEdit_name->setSizePolicy(sizePolicy);
        lineEdit_name->setMinimumSize(QSize(500, 50));
        lineEdit_name->setFocusPolicy(Qt::StrongFocus);
        lineEdit_name->setStyleSheet(QString::fromUtf8(""));
        lineEdit_name->setClearButtonEnabled(true);

        verticalLayout->addWidget(lineEdit_name);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        lineEdit_pwd = new QLineEdit(login_frame);
        lineEdit_pwd->setObjectName(QString::fromUtf8("lineEdit_pwd"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_pwd->sizePolicy().hasHeightForWidth());
        lineEdit_pwd->setSizePolicy(sizePolicy2);
        lineEdit_pwd->setMinimumSize(QSize(500, 50));
        lineEdit_pwd->setStyleSheet(QString::fromUtf8(""));
        lineEdit_pwd->setClearButtonEnabled(true);

        verticalLayout->addWidget(lineEdit_pwd);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);


        verticalLayout_3->addLayout(verticalLayout);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_7);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        login_Button = new QPushButton(login_frame);
        login_Button->setObjectName(QString::fromUtf8("login_Button"));
        sizePolicy1.setHeightForWidth(login_Button->sizePolicy().hasHeightForWidth());
        login_Button->setSizePolicy(sizePolicy1);
        login_Button->setMinimumSize(QSize(500, 50));
        login_Button->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(login_Button);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_5);

        regilaster_Button = new QPushButton(login_frame);
        regilaster_Button->setObjectName(QString::fromUtf8("regilaster_Button"));
        regilaster_Button->setMinimumSize(QSize(500, 50));

        verticalLayout_2->addWidget(regilaster_Button);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_6);


        verticalLayout_3->addLayout(verticalLayout_2);


        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer_4 = new QSpacerItem(66, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout->addWidget(login_frame, 0, 1, 1, 1);


        retranslateUi(LoginUI);
        QObject::connect(login_Button, SIGNAL(clicked()), LoginUI, SLOT(Login()));

        QMetaObject::connectSlotsByName(LoginUI);
    } // setupUi

    void retranslateUi(QWidget *LoginUI)
    {
        LoginUI->setWindowTitle(QApplication::translate("LoginUI", "Form", nullptr));
        label_logo->setText(QString());
        label_title->setText(QApplication::translate("LoginUI", "LOGIN", nullptr));
        lineEdit_name->setText(QString());
        lineEdit_pwd->setText(QString());
        login_Button->setText(QApplication::translate("LoginUI", "Login", nullptr));
        regilaster_Button->setText(QApplication::translate("LoginUI", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginUI: public Ui_LoginUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_GUI_H
