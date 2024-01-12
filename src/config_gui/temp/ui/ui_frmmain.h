/********************************************************************************
** Form generated from reading UI file 'frmmain.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMAIN_H
#define UI_FRMMAIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmMain
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widgetTitle;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labIco;
    QLabel *labTitle;
    QWidget *widgetTop;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *btnMain;
    QToolButton *btnConfig;
    QToolButton *btnData;
    QToolButton *btnHelp;
    QToolButton *btnExit;
    QSpacerItem *horizontalSpacer;
    QWidget *widgetMenu;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *btnMenu_Min;
    QPushButton *btnMenu_Close;
    QPushButton *btnMenu_Max;
    QStackedWidget *stackedWidget;
    QWidget *page1;
    QLabel *lab1;
    QTableWidget *tableWidget;
    QListWidget *log_list_Widget;
    QWidget *widget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *server_ip_edit;
    QSpinBox *server_port_box;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_2;
    QLabel *label;
    QPushButton *refreshButton;
    QPushButton *deleteButton;
    QPushButton *editButton;
    QWidget *page2;
    QVBoxLayout *verticalLayout_3;
    QFormLayout *formLayout;
    QPushButton *save_pushButton;
    QLabel *label_4;
    QLineEdit *type_lineEdit;
    QLabel *label_3;
    QPushButton *load_proto_pushButton;
    QTextEdit *proto_textEdit;
    QLabel *label_5;
    QLabel *service_nameLabel;
    QLineEdit *service_nameLineEdit;
    QLabel *service_ipLabel;
    QLineEdit *service_ipLineEdit;
    QLabel *service_portLabel;
    QSpinBox *service_portBox;
    QWidget *page3;
    QVBoxLayout *verticalLayout_5;
    QLabel *lab3;
    QWidget *page4;
    QVBoxLayout *verticalLayout_4;
    QLabel *lab4;

    void setupUi(QDialog *frmMain)
    {
        if (frmMain->objectName().isEmpty())
            frmMain->setObjectName(QString::fromUtf8("frmMain"));
        frmMain->resize(883, 637);
        verticalLayout = new QVBoxLayout(frmMain);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        widgetTitle = new QWidget(frmMain);
        widgetTitle->setObjectName(QString::fromUtf8("widgetTitle"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetTitle->sizePolicy().hasHeightForWidth());
        widgetTitle->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(widgetTitle);
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, 0, 0, 0);
        labIco = new QLabel(widgetTitle);
        labIco->setObjectName(QString::fromUtf8("labIco"));
        labIco->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(labIco);

        labTitle = new QLabel(widgetTitle);
        labTitle->setObjectName(QString::fromUtf8("labTitle"));
        labTitle->setStyleSheet(QString::fromUtf8(""));
        labTitle->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(labTitle);

        widgetTop = new QWidget(widgetTitle);
        widgetTop->setObjectName(QString::fromUtf8("widgetTop"));
        horizontalLayout_3 = new QHBoxLayout(widgetTop);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        btnMain = new QToolButton(widgetTop);
        btnMain->setObjectName(QString::fromUtf8("btnMain"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnMain->sizePolicy().hasHeightForWidth());
        btnMain->setSizePolicy(sizePolicy1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/main_main.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMain->setIcon(icon);
        btnMain->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_3->addWidget(btnMain);

        btnConfig = new QToolButton(widgetTop);
        btnConfig->setObjectName(QString::fromUtf8("btnConfig"));
        sizePolicy1.setHeightForWidth(btnConfig->sizePolicy().hasHeightForWidth());
        btnConfig->setSizePolicy(sizePolicy1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/branch_open.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnConfig->setIcon(icon1);
        btnConfig->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_3->addWidget(btnConfig);

        btnData = new QToolButton(widgetTop);
        btnData->setObjectName(QString::fromUtf8("btnData"));
        sizePolicy1.setHeightForWidth(btnData->sizePolicy().hasHeightForWidth());
        btnData->setSizePolicy(sizePolicy1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/main_data.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnData->setIcon(icon2);
        btnData->setChecked(false);
        btnData->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_3->addWidget(btnData);

        btnHelp = new QToolButton(widgetTop);
        btnHelp->setObjectName(QString::fromUtf8("btnHelp"));
        sizePolicy1.setHeightForWidth(btnHelp->sizePolicy().hasHeightForWidth());
        btnHelp->setSizePolicy(sizePolicy1);
        btnHelp->setStyleSheet(QString::fromUtf8(""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/main_person.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnHelp->setIcon(icon3);
        btnHelp->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_3->addWidget(btnHelp);

        btnExit = new QToolButton(widgetTop);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        sizePolicy1.setHeightForWidth(btnExit->sizePolicy().hasHeightForWidth());
        btnExit->setSizePolicy(sizePolicy1);
        btnExit->setStyleSheet(QString::fromUtf8(""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/main_exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnExit->setIcon(icon4);
        btnExit->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_3->addWidget(btnExit);


        horizontalLayout_2->addWidget(widgetTop);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        widgetMenu = new QWidget(widgetTitle);
        widgetMenu->setObjectName(QString::fromUtf8("widgetMenu"));
        gridLayout_2 = new QGridLayout(widgetMenu);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 1, 1, 3);

        btnMenu_Min = new QPushButton(widgetMenu);
        btnMenu_Min->setObjectName(QString::fromUtf8("btnMenu_Min"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnMenu_Min->sizePolicy().hasHeightForWidth());
        btnMenu_Min->setSizePolicy(sizePolicy2);
        btnMenu_Min->setMinimumSize(QSize(30, 30));
        btnMenu_Min->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Min->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(btnMenu_Min, 0, 1, 1, 1);

        btnMenu_Close = new QPushButton(widgetMenu);
        btnMenu_Close->setObjectName(QString::fromUtf8("btnMenu_Close"));
        sizePolicy2.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
        btnMenu_Close->setSizePolicy(sizePolicy2);
        btnMenu_Close->setMinimumSize(QSize(30, 30));
        btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Close->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(btnMenu_Close, 0, 3, 1, 1);

        btnMenu_Max = new QPushButton(widgetMenu);
        btnMenu_Max->setObjectName(QString::fromUtf8("btnMenu_Max"));
        sizePolicy2.setHeightForWidth(btnMenu_Max->sizePolicy().hasHeightForWidth());
        btnMenu_Max->setSizePolicy(sizePolicy2);
        btnMenu_Max->setMinimumSize(QSize(30, 30));
        btnMenu_Max->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(btnMenu_Max, 0, 2, 1, 1);


        horizontalLayout_2->addWidget(widgetMenu);


        verticalLayout->addWidget(widgetTitle);

        stackedWidget = new QStackedWidget(frmMain);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setEnabled(true);
        stackedWidget->setMaximumSize(QSize(16777215, 16777215));
        stackedWidget->setStyleSheet(QString::fromUtf8("QLabel {\n"
"font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(225, 225, 225);\n"
"}"));
        page1 = new QWidget();
        page1->setObjectName(QString::fromUtf8("page1"));
        lab1 = new QLabel(page1);
        lab1->setObjectName(QString::fromUtf8("lab1"));
        lab1->setGeometry(QRect(9, 9, 16, 16));
        lab1->setStyleSheet(QString::fromUtf8(""));
        lab1->setAlignment(Qt::AlignCenter);
        tableWidget = new QTableWidget(page1);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem6);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(-5, 0, 311, 571));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        log_list_Widget = new QListWidget(page1);
        log_list_Widget->setObjectName(QString::fromUtf8("log_list_Widget"));
        log_list_Widget->setGeometry(QRect(305, 0, 291, 571));
        widget = new QWidget(page1);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(600, 0, 281, 561));
        verticalLayoutWidget = new QWidget(widget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(120, 10, 161, 81));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        server_ip_edit = new QLineEdit(verticalLayoutWidget);
        server_ip_edit->setObjectName(QString::fromUtf8("server_ip_edit"));

        verticalLayout_2->addWidget(server_ip_edit);

        server_port_box = new QSpinBox(verticalLayoutWidget);
        server_port_box->setObjectName(QString::fromUtf8("server_port_box"));
        server_port_box->setMinimumSize(QSize(0, 0));
        server_port_box->setMinimum(1);
        server_port_box->setMaximum(65535);
        server_port_box->setValue(20019);

        verticalLayout_2->addWidget(server_port_box);

        verticalLayoutWidget_2 = new QWidget(widget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 10, 122, 81));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(225, 225, 225);"));

        verticalLayout_6->addWidget(label_2);

        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(225, 225, 225);"));

        verticalLayout_6->addWidget(label);

        refreshButton = new QPushButton(widget);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));
        refreshButton->setGeometry(QRect(80, 110, 121, 51));
        refreshButton->setIconSize(QSize(85, 50));
        deleteButton = new QPushButton(widget);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(80, 260, 121, 51));
        deleteButton->setIconSize(QSize(85, 50));
        editButton = new QPushButton(widget);
        editButton->setObjectName(QString::fromUtf8("editButton"));
        editButton->setGeometry(QRect(80, 170, 121, 51));
        editButton->setIconSize(QSize(85, 50));
        stackedWidget->addWidget(page1);
        page2 = new QWidget();
        page2->setObjectName(QString::fromUtf8("page2"));
        page2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"font: 12pt \"\351\273\221\344\275\223\";\n"
"color: rgb(225, 225, 225);\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(page2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        save_pushButton = new QPushButton(page2);
        save_pushButton->setObjectName(QString::fromUtf8("save_pushButton"));

        formLayout->setWidget(0, QFormLayout::FieldRole, save_pushButton);

        label_4 = new QLabel(page2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_4);

        type_lineEdit = new QLineEdit(page2);
        type_lineEdit->setObjectName(QString::fromUtf8("type_lineEdit"));
        type_lineEdit->setClearButtonEnabled(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, type_lineEdit);

        label_3 = new QLabel(page2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        load_proto_pushButton = new QPushButton(page2);
        load_proto_pushButton->setObjectName(QString::fromUtf8("load_proto_pushButton"));

        formLayout->setWidget(3, QFormLayout::FieldRole, load_proto_pushButton);

        proto_textEdit = new QTextEdit(page2);
        proto_textEdit->setObjectName(QString::fromUtf8("proto_textEdit"));

        formLayout->setWidget(4, QFormLayout::FieldRole, proto_textEdit);

        label_5 = new QLabel(page2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        service_nameLabel = new QLabel(page2);
        service_nameLabel->setObjectName(QString::fromUtf8("service_nameLabel"));

        formLayout->setWidget(5, QFormLayout::LabelRole, service_nameLabel);

        service_nameLineEdit = new QLineEdit(page2);
        service_nameLineEdit->setObjectName(QString::fromUtf8("service_nameLineEdit"));
        service_nameLineEdit->setClearButtonEnabled(true);

        formLayout->setWidget(5, QFormLayout::FieldRole, service_nameLineEdit);

        service_ipLabel = new QLabel(page2);
        service_ipLabel->setObjectName(QString::fromUtf8("service_ipLabel"));

        formLayout->setWidget(6, QFormLayout::LabelRole, service_ipLabel);

        service_ipLineEdit = new QLineEdit(page2);
        service_ipLineEdit->setObjectName(QString::fromUtf8("service_ipLineEdit"));
        service_ipLineEdit->setClearButtonEnabled(true);

        formLayout->setWidget(6, QFormLayout::FieldRole, service_ipLineEdit);

        service_portLabel = new QLabel(page2);
        service_portLabel->setObjectName(QString::fromUtf8("service_portLabel"));

        formLayout->setWidget(7, QFormLayout::LabelRole, service_portLabel);

        service_portBox = new QSpinBox(page2);
        service_portBox->setObjectName(QString::fromUtf8("service_portBox"));
        service_portBox->setMinimum(0);
        service_portBox->setMaximum(65535);

        formLayout->setWidget(7, QFormLayout::FieldRole, service_portBox);


        verticalLayout_3->addLayout(formLayout);

        stackedWidget->addWidget(page2);
        page3 = new QWidget();
        page3->setObjectName(QString::fromUtf8("page3"));
        verticalLayout_5 = new QVBoxLayout(page3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        lab3 = new QLabel(page3);
        lab3->setObjectName(QString::fromUtf8("lab3"));
        lab3->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(lab3);

        stackedWidget->addWidget(page3);
        page4 = new QWidget();
        page4->setObjectName(QString::fromUtf8("page4"));
        verticalLayout_4 = new QVBoxLayout(page4);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        lab4 = new QLabel(page4);
        lab4->setObjectName(QString::fromUtf8("lab4"));
        lab4->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(lab4);

        stackedWidget->addWidget(page4);

        verticalLayout->addWidget(stackedWidget);


        retranslateUi(frmMain);
        QObject::connect(refreshButton, SIGNAL(clicked()), frmMain, SLOT(Refresh()));
        QObject::connect(save_pushButton, SIGNAL(clicked()), frmMain, SLOT(Save()));
        QObject::connect(load_proto_pushButton, SIGNAL(clicked()), frmMain, SLOT(LoadProto()));
        QObject::connect(deleteButton, SIGNAL(clicked()), frmMain, SLOT(DelConfig()));
        QObject::connect(editButton, SIGNAL(clicked()), frmMain, SLOT(EditConfig()));
        QObject::connect(tableWidget, SIGNAL(cellDoubleClicked(int,int)), frmMain, SLOT(EditConfig()));

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(frmMain);
    } // setupUi

    void retranslateUi(QDialog *frmMain)
    {
        frmMain->setWindowTitle(QApplication::translate("frmMain", "Form", nullptr));
        labIco->setText(QString());
        labTitle->setText(QString());
        btnMain->setText(QApplication::translate("frmMain", "\344\270\273\347\225\214\351\235\242", nullptr));
        btnConfig->setText(QApplication::translate("frmMain", "\346\267\273\345\212\240\351\205\215\347\275\256", nullptr));
        btnData->setText(QApplication::translate("frmMain", "\346\237\245\350\257\242\351\205\215\347\275\256", nullptr));
        btnHelp->setText(QApplication::translate("frmMain", "\350\260\203\350\257\225\345\270\256\345\212\251", nullptr));
        btnExit->setText(QApplication::translate("frmMain", "\347\224\250\346\210\267\351\200\200\345\207\272", nullptr));
#ifndef QT_NO_TOOLTIP
        btnMenu_Min->setToolTip(QApplication::translate("frmMain", "\346\234\200\345\260\217\345\214\226", nullptr));
#endif // QT_NO_TOOLTIP
        btnMenu_Min->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnMenu_Close->setToolTip(QApplication::translate("frmMain", "\345\205\263\351\227\255", nullptr));
#endif // QT_NO_TOOLTIP
        btnMenu_Close->setText(QString());
        btnMenu_Max->setText(QString());
        lab1->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("frmMain", "\345\276\256\346\234\215\345\212\241\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("frmMain", "IP", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("frmMain", "\347\253\257\345\217\243", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("frmMain", "1", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->item(0, 0);
        ___qtablewidgetitem4->setText(QApplication::translate("frmMain", "dir", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->item(0, 1);
        ___qtablewidgetitem5->setText(QApplication::translate("frmMain", "127.0.0.1", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->item(0, 2);
        ___qtablewidgetitem6->setText(QApplication::translate("frmMain", "8080", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        server_ip_edit->setText(QApplication::translate("frmMain", "127.0.0.1", nullptr));
        label_2->setText(QApplication::translate("frmMain", "\351\205\215\347\275\256\344\270\255\345\277\203IP", nullptr));
        label->setText(QApplication::translate("frmMain", "\351\205\215\347\275\256\344\270\255\345\277\203\347\253\257\345\217\243", nullptr));
        refreshButton->setText(QApplication::translate("frmMain", "\345\210\267\346\226\260", nullptr));
        deleteButton->setText(QApplication::translate("frmMain", "\345\210\240\351\231\244", nullptr));
        editButton->setText(QApplication::translate("frmMain", "\347\274\226\350\276\221\351\205\215\347\275\256", nullptr));
        save_pushButton->setText(QApplication::translate("frmMain", "\344\277\235\345\255\230", nullptr));
        label_4->setText(QApplication::translate("frmMain", "\351\205\215\347\275\256\347\261\273\345\236\213\345\220\215", nullptr));
        label_3->setText(QApplication::translate("frmMain", "\350\275\275\345\205\245proto", nullptr));
        load_proto_pushButton->setText(QApplication::translate("frmMain", "\350\275\275\345\205\245", nullptr));
        label_5->setText(QApplication::translate("frmMain", "protocol", nullptr));
        service_nameLabel->setText(QApplication::translate("frmMain", "\345\276\256\346\234\215\345\212\241\345\220\215\347\247\260", nullptr));
        service_ipLabel->setText(QApplication::translate("frmMain", "\345\276\256\346\234\215\345\212\241IP", nullptr));
        service_portLabel->setText(QApplication::translate("frmMain", "\345\276\256\346\234\215\345\212\241\347\253\257\345\217\243", nullptr));
        lab3->setText(QApplication::translate("frmMain", "\346\237\245\350\257\242\351\205\215\347\275\256", nullptr));
        lab4->setText(QApplication::translate("frmMain", "\350\260\203\350\257\225\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frmMain: public Ui_frmMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMAIN_H
