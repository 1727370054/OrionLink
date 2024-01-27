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
#include <QtGui/QIcon>
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

class Ui_LoginGUI
{
public:
    QGridLayout *gridLayout_6;
    QFrame *frame_title;
    QPushButton *closeButton;
    QPushButton *minButton;
    QLabel *logo;
    QLabel *titlelabel;
    QLabel *headlabel;
    QWidget *line;
    QLabel *nickname_;
    QLabel *svip;
    QFrame *frame_background;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_17;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QFrame *frame_login;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_login;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_26;
    QFrame *frame_err;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_17;
    QSpacerItem *horizontalSpacer_27;
    QLabel *err_logo;
    QLabel *err_msg;
    QSpacerItem *horizontalSpacer_28;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_20;
    QFrame *frame_user_name;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_21;
    QLabel *label_user_name;
    QLineEdit *lineE_user_name;
    QSpacerItem *horizontalSpacer_22;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_6;
    QFrame *frame_pwd;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_pwd;
    QLineEdit *lineE_pwd;
    QSpacerItem *horizontalSpacer_19;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *btn_register;
    QSpacerItem *horizontalSpacer_16;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *btn_forget;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *btn_login;
    QSpacerItem *horizontalSpacer_14;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *btn_wx;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *btn_qq;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *btn_wb;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_4;
    QFrame *frame_pic;
    QSpacerItem *horizontalSpacer_18;
    QSpacerItem *verticalSpacer_10;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_1;
    QSpacerItem *horizontalSpacer_23;
    QPushButton *btn_2;
    QSpacerItem *horizontalSpacer_24;
    QPushButton *btn_3;
    QSpacerItem *horizontalSpacer_25;
    QPushButton *btn_4;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *LoginGUI)
    {
        if (LoginGUI->objectName().isEmpty())
            LoginGUI->setObjectName(QString::fromUtf8("LoginGUI"));
        LoginGUI->resize(1300, 800);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginGUI->sizePolicy().hasHeightForWidth());
        LoginGUI->setSizePolicy(sizePolicy);
        LoginGUI->setMinimumSize(QSize(800, 450));
        LoginGUI->setStyleSheet(QString::fromUtf8(""));
        gridLayout_6 = new QGridLayout(LoginGUI);
        gridLayout_6->setSpacing(0);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        frame_title = new QFrame(LoginGUI);
        frame_title->setObjectName(QString::fromUtf8("frame_title"));
        frame_title->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_title->sizePolicy().hasHeightForWidth());
        frame_title->setSizePolicy(sizePolicy1);
        frame_title->setMinimumSize(QSize(1300, 50));
        frame_title->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 127);"));
        frame_title->setFrameShape(QFrame::StyledPanel);
        frame_title->setFrameShadow(QFrame::Raised);
        closeButton = new QPushButton(frame_title);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(1200, 10, 81, 31));
        closeButton->setStyleSheet(QString::fromUtf8("QPushButton { border: none; }\n"
"QPushButton:hover {\n"
"background-color: rgb(235, 156, 117);\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/pic/btn_sys_close.png"), QSize(), QIcon::Normal, QIcon::Off);
        closeButton->setIcon(icon);
        closeButton->setIconSize(QSize(81, 31));
        minButton = new QPushButton(frame_title);
        minButton->setObjectName(QString::fromUtf8("minButton"));
        minButton->setGeometry(QRect(1110, 10, 81, 31));
        minButton->setStyleSheet(QString::fromUtf8("QPushButton { border: none; }\n"
"QPushButton:hover {\n"
"background-color: rgb(235, 156, 117);\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/pic/btn_sys_minimize.png"), QSize(), QIcon::Normal, QIcon::Off);
        minButton->setIcon(icon1);
        minButton->setIconSize(QSize(81, 31));
        logo = new QLabel(frame_title);
        logo->setObjectName(QString::fromUtf8("logo"));
        logo->setGeometry(QRect(0, -10, 71, 71));
        logo->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        logo->setPixmap(QPixmap(QString::fromUtf8(":/res/pic/logo3.png")));
        logo->setScaledContents(true);
        titlelabel = new QLabel(frame_title);
        titlelabel->setObjectName(QString::fromUtf8("titlelabel"));
        titlelabel->setGeometry(QRect(70, 10, 91, 31));
        titlelabel->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\215\216\346\226\207\347\220\245\347\217\200\";\n"
"color: rgb(255, 255, 255);"));
        titlelabel->setScaledContents(true);
        headlabel = new QLabel(frame_title);
        headlabel->setObjectName(QString::fromUtf8("headlabel"));
        headlabel->setGeometry(QRect(860, 0, 52, 52));
        headlabel->setPixmap(QPixmap(QString::fromUtf8(":/res/pic/head.png")));
        headlabel->setScaledContents(true);
        line = new QWidget(frame_title);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(1100, 5, 3, 40));
        line->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        nickname_ = new QLabel(frame_title);
        nickname_->setObjectName(QString::fromUtf8("nickname_"));
        nickname_->setGeometry(QRect(910, 15, 81, 21));
        nickname_->setStyleSheet(QString::fromUtf8("font: 10pt \"\351\273\221\344\275\223\";\n"
"color: rgb(255, 255, 255);"));
        svip = new QLabel(frame_title);
        svip->setObjectName(QString::fromUtf8("svip"));
        svip->setGeometry(QRect(1010, 0, 91, 51));
        svip->setPixmap(QPixmap(QString::fromUtf8(":/res/pic/ToastSVipBg.png")));
        svip->setScaledContents(true);

        gridLayout_6->addWidget(frame_title, 1, 0, 1, 1);

        frame_background = new QFrame(LoginGUI);
        frame_background->setObjectName(QString::fromUtf8("frame_background"));
        frame_background->setEnabled(true);
        sizePolicy.setHeightForWidth(frame_background->sizePolicy().hasHeightForWidth());
        frame_background->setSizePolicy(sizePolicy);
        frame_background->setFrameShape(QFrame::StyledPanel);
        frame_background->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_background);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_9 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_9);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_17);

        frame = new QFrame(frame_background);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        frame_login = new QFrame(frame);
        frame_login->setObjectName(QString::fromUtf8("frame_login"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame_login->sizePolicy().hasHeightForWidth());
        frame_login->setSizePolicy(sizePolicy2);
        frame_login->setMinimumSize(QSize(500, 600));
        frame_login->setMaximumSize(QSize(500, 600));
        frame_login->setFrameShape(QFrame::StyledPanel);
        frame_login->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame_login);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_login = new QLabel(frame_login);
        label_login->setObjectName(QString::fromUtf8("label_login"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(22);
        label_login->setFont(font);

        horizontalLayout->addWidget(label_login);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_7);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalSpacer_26 = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_26);

        frame_err = new QFrame(frame_login);
        frame_err->setObjectName(QString::fromUtf8("frame_err"));
        frame_err->setStyleSheet(QString::fromUtf8("#frame_user_name::!hover{\n"
"\n"
"      border: 1px solid #c7c7c7;\n"
"      border-radius: 2px;\n"
"	  margin-top: 0ex\n"
"\n"
"}\n"
"#frame_user_name::hover{\n"
"      border: 1px solid #58a6ee;\n"
"      border-radius: 2px;\n"
"	  margin-top: 0ex\n"
"}"));
        frame_err->setFrameShape(QFrame::StyledPanel);
        frame_err->setFrameShadow(QFrame::Raised);
        gridLayout_7 = new QGridLayout(frame_err);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalSpacer_27 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_27);

        err_logo = new QLabel(frame_err);
        err_logo->setObjectName(QString::fromUtf8("err_logo"));
        sizePolicy1.setHeightForWidth(err_logo->sizePolicy().hasHeightForWidth());
        err_logo->setSizePolicy(sizePolicy1);
        err_logo->setMinimumSize(QSize(30, 30));
        err_logo->setMaximumSize(QSize(30, 30));
        err_logo->setPixmap(QPixmap(QString::fromUtf8(":/res/pic/icon_error_tip.png")));
        err_logo->setScaledContents(true);

        horizontalLayout_17->addWidget(err_logo);

        err_msg = new QLabel(frame_err);
        err_msg->setObjectName(QString::fromUtf8("err_msg"));
        err_msg->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);\n"
"font: 12pt \"\351\273\221\344\275\223\";"));

        horizontalLayout_17->addWidget(err_msg);


        gridLayout_7->addLayout(horizontalLayout_17, 1, 0, 1, 1);


        horizontalLayout_16->addWidget(frame_err);

        horizontalSpacer_28 = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_28);


        verticalLayout->addLayout(horizontalLayout_16);

        verticalSpacer = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_20 = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_20);

        frame_user_name = new QFrame(frame_login);
        frame_user_name->setObjectName(QString::fromUtf8("frame_user_name"));
        frame_user_name->setStyleSheet(QString::fromUtf8("#frame_user_name::!hover{\n"
"\n"
"      border: 1px solid #c7c7c7;\n"
"      border-radius: 2px;\n"
"	  margin-top: 0ex\n"
"\n"
"}\n"
"#frame_user_name::hover{\n"
"      border: 1px solid #58a6ee;\n"
"      border-radius: 2px;\n"
"	  margin-top: 0ex\n"
"}"));
        frame_user_name->setFrameShape(QFrame::StyledPanel);
        frame_user_name->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_user_name);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalSpacer_21 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_21);

        label_user_name = new QLabel(frame_user_name);
        label_user_name->setObjectName(QString::fromUtf8("label_user_name"));
        sizePolicy1.setHeightForWidth(label_user_name->sizePolicy().hasHeightForWidth());
        label_user_name->setSizePolicy(sizePolicy1);
        label_user_name->setMinimumSize(QSize(30, 30));
        label_user_name->setMaximumSize(QSize(30, 30));

        horizontalLayout_11->addWidget(label_user_name);

        lineE_user_name = new QLineEdit(frame_user_name);
        lineE_user_name->setObjectName(QString::fromUtf8("lineE_user_name"));
        lineE_user_name->setStyleSheet(QString::fromUtf8(""));
        lineE_user_name->setClearButtonEnabled(true);

        horizontalLayout_11->addWidget(lineE_user_name);


        gridLayout_4->addLayout(horizontalLayout_11, 1, 0, 1, 1);


        horizontalLayout_10->addWidget(frame_user_name);

        horizontalSpacer_22 = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_22);


        verticalLayout->addLayout(horizontalLayout_10);

        verticalSpacer_3 = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_6 = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        frame_pwd = new QFrame(frame_login);
        frame_pwd->setObjectName(QString::fromUtf8("frame_pwd"));
        frame_pwd->setStyleSheet(QString::fromUtf8("#frame_pwd::!hover{\n"
"\n"
"      border: 1px solid #c7c7c7;\n"
"      border-radius: 2px;\n"
"	  margin-top: 0ex\n"
"\n"
"}\n"
"#frame_pwd::hover{\n"
"      border: 1px solid #58a6ee;\n"
"      border-radius: 2px;\n"
"	  margin-top: 0ex\n"
"}"));
        frame_pwd->setFrameShape(QFrame::StyledPanel);
        frame_pwd->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_pwd);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        label_pwd = new QLabel(frame_pwd);
        label_pwd->setObjectName(QString::fromUtf8("label_pwd"));
        sizePolicy1.setHeightForWidth(label_pwd->sizePolicy().hasHeightForWidth());
        label_pwd->setSizePolicy(sizePolicy1);
        label_pwd->setMinimumSize(QSize(30, 30));
        label_pwd->setMaximumSize(QSize(30, 30));

        horizontalLayout_3->addWidget(label_pwd);

        lineE_pwd = new QLineEdit(frame_pwd);
        lineE_pwd->setObjectName(QString::fromUtf8("lineE_pwd"));
        lineE_pwd->setStyleSheet(QString::fromUtf8(""));
        lineE_pwd->setClearButtonEnabled(true);

        horizontalLayout_3->addWidget(lineE_pwd);


        gridLayout->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        horizontalLayout_2->addWidget(frame_pwd);

        horizontalSpacer_19 = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_19);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_11 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_11);

        btn_register = new QPushButton(frame_login);
        btn_register->setObjectName(QString::fromUtf8("btn_register"));
        btn_register->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    text-decoration: underline;\n"
"    background: transparent;\n"
"    border: none;\n"
"	color:#e83737;\n"
"}"));

        horizontalLayout_5->addWidget(btn_register);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_16);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_15);

        btn_forget = new QPushButton(frame_login);
        btn_forget->setObjectName(QString::fromUtf8("btn_forget"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setUnderline(true);
        btn_forget->setFont(font1);

        horizontalLayout_5->addWidget(btn_forget);

        horizontalSpacer_12 = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_12);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_5 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_13);

        btn_login = new QPushButton(frame_login);
        btn_login->setObjectName(QString::fromUtf8("btn_login"));
        sizePolicy1.setHeightForWidth(btn_login->sizePolicy().hasHeightForWidth());
        btn_login->setSizePolicy(sizePolicy1);
        btn_login->setMinimumSize(QSize(320, 50));
        btn_login->setMaximumSize(QSize(320, 50));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(12);
        btn_login->setFont(font2);

        horizontalLayout_6->addWidget(btn_login);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_14);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer_6 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_10 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);

        btn_wx = new QPushButton(frame_login);
        btn_wx->setObjectName(QString::fromUtf8("btn_wx"));
        sizePolicy1.setHeightForWidth(btn_wx->sizePolicy().hasHeightForWidth());
        btn_wx->setSizePolicy(sizePolicy1);
        btn_wx->setMinimumSize(QSize(50, 50));
        btn_wx->setMaximumSize(QSize(50, 50));

        horizontalLayout_4->addWidget(btn_wx);

        horizontalSpacer_7 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        btn_qq = new QPushButton(frame_login);
        btn_qq->setObjectName(QString::fromUtf8("btn_qq"));
        sizePolicy1.setHeightForWidth(btn_qq->sizePolicy().hasHeightForWidth());
        btn_qq->setSizePolicy(sizePolicy1);
        btn_qq->setMinimumSize(QSize(50, 50));
        btn_qq->setMaximumSize(QSize(50, 50));

        horizontalLayout_4->addWidget(btn_qq);

        horizontalSpacer_8 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        btn_wb = new QPushButton(frame_login);
        btn_wb->setObjectName(QString::fromUtf8("btn_wb"));
        sizePolicy1.setHeightForWidth(btn_wb->sizePolicy().hasHeightForWidth());
        btn_wb->setSizePolicy(sizePolicy1);
        btn_wb->setMinimumSize(QSize(50, 50));
        btn_wb->setMaximumSize(QSize(50, 50));

        horizontalLayout_4->addWidget(btn_wb);

        horizontalSpacer_9 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_8 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_8);


        gridLayout_5->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_5->addItem(verticalSpacer_4, 1, 0, 1, 1);


        horizontalLayout_8->addWidget(frame_login);

        frame_pic = new QFrame(frame);
        frame_pic->setObjectName(QString::fromUtf8("frame_pic"));
        sizePolicy2.setHeightForWidth(frame_pic->sizePolicy().hasHeightForWidth());
        frame_pic->setSizePolicy(sizePolicy2);
        frame_pic->setMinimumSize(QSize(500, 600));
        frame_pic->setFrameShape(QFrame::StyledPanel);
        frame_pic->setFrameShadow(QFrame::Raised);

        horizontalLayout_8->addWidget(frame_pic);


        gridLayout_2->addLayout(horizontalLayout_8, 0, 0, 1, 1);


        horizontalLayout_9->addWidget(frame);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_18);


        verticalLayout_2->addLayout(horizontalLayout_9);

        verticalSpacer_10 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_10);


        gridLayout_3->addLayout(verticalLayout_2, 1, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalSpacer_3 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_3);

        btn_1 = new QPushButton(frame_background);
        btn_1->setObjectName(QString::fromUtf8("btn_1"));
        sizePolicy1.setHeightForWidth(btn_1->sizePolicy().hasHeightForWidth());
        btn_1->setSizePolicy(sizePolicy1);
        btn_1->setMinimumSize(QSize(100, 30));
        btn_1->setMaximumSize(QSize(100, 30));
        QFont font3;
        font3.setPointSize(10);
        btn_1->setFont(font3);

        horizontalLayout_12->addWidget(btn_1);

        horizontalSpacer_23 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_23);

        btn_2 = new QPushButton(frame_background);
        btn_2->setObjectName(QString::fromUtf8("btn_2"));
        sizePolicy1.setHeightForWidth(btn_2->sizePolicy().hasHeightForWidth());
        btn_2->setSizePolicy(sizePolicy1);
        btn_2->setMinimumSize(QSize(100, 30));
        btn_2->setMaximumSize(QSize(100, 30));
        btn_2->setFont(font3);

        horizontalLayout_12->addWidget(btn_2);

        horizontalSpacer_24 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_24);

        btn_3 = new QPushButton(frame_background);
        btn_3->setObjectName(QString::fromUtf8("btn_3"));
        sizePolicy1.setHeightForWidth(btn_3->sizePolicy().hasHeightForWidth());
        btn_3->setSizePolicy(sizePolicy1);
        btn_3->setMinimumSize(QSize(100, 30));
        btn_3->setMaximumSize(QSize(100, 30));
        btn_3->setFont(font3);

        horizontalLayout_12->addWidget(btn_3);

        horizontalSpacer_25 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_25);

        btn_4 = new QPushButton(frame_background);
        btn_4->setObjectName(QString::fromUtf8("btn_4"));
        sizePolicy1.setHeightForWidth(btn_4->sizePolicy().hasHeightForWidth());
        btn_4->setSizePolicy(sizePolicy1);
        btn_4->setMinimumSize(QSize(100, 30));
        btn_4->setMaximumSize(QSize(100, 30));
        btn_4->setFont(font3);

        horizontalLayout_12->addWidget(btn_4);

        horizontalSpacer_4 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_4);


        gridLayout_3->addLayout(horizontalLayout_12, 0, 0, 1, 1);


        gridLayout_6->addWidget(frame_background, 2, 0, 1, 1);


        retranslateUi(LoginGUI);
        QObject::connect(closeButton, SIGNAL(clicked()), LoginGUI, SLOT(close()));
        QObject::connect(minButton, SIGNAL(clicked()), LoginGUI, SLOT(showMinimized()));
        QObject::connect(btn_login, SIGNAL(clicked()), LoginGUI, SLOT(Login()));

        QMetaObject::connectSlotsByName(LoginGUI);
    } // setupUi

    void retranslateUi(QWidget *LoginGUI)
    {
        LoginGUI->setWindowTitle(QApplication::translate("LoginGUI", "Widget", nullptr));
        closeButton->setText(QString());
        minButton->setText(QString());
        logo->setText(QString());
        titlelabel->setText(QApplication::translate("LoginGUI", "OL\344\272\221\347\233\230", nullptr));
        headlabel->setText(QString());
        nickname_->setText(QApplication::translate("LoginGUI", "\350\266\205\347\272\247\347\224\250\346\210\267\345\223\237", nullptr));
        svip->setText(QString());
        label_login->setText(QApplication::translate("LoginGUI", "LOGIN", nullptr));
        err_logo->setText(QString());
        err_msg->setText(QApplication::translate("LoginGUI", "\347\231\273\351\231\206\345\244\261\350\264\245!", nullptr));
        label_user_name->setText(QString());
        lineE_user_name->setText(QApplication::translate("LoginGUI", "hwk", nullptr));
        lineE_user_name->setPlaceholderText(QString());
        label_pwd->setText(QString());
        lineE_pwd->setText(QApplication::translate("LoginGUI", "123456", nullptr));
        btn_register->setText(QApplication::translate("LoginGUI", "\346\263\250\345\206\214", nullptr));
        btn_forget->setText(QApplication::translate("LoginGUI", "\345\277\230\350\256\260\345\257\206\347\240\201?", nullptr));
        btn_login->setText(QApplication::translate("LoginGUI", "\347\231\273\351\231\206", nullptr));
        btn_wx->setText(QString());
        btn_qq->setText(QString());
        btn_wb->setText(QString());
        btn_1->setText(QApplication::translate("LoginGUI", "\347\262\211\347\272\242", nullptr));
        btn_2->setText(QApplication::translate("LoginGUI", "\351\273\204\350\211\262", nullptr));
        btn_3->setText(QApplication::translate("LoginGUI", "\346\265\205\347\264\253", nullptr));
        btn_4->setText(QApplication::translate("LoginGUI", "\351\235\222\347\273\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginGUI: public Ui_LoginGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_GUI_H
