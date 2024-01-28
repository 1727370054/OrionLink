/********************************************************************************
** Form generated from reading UI file 'disk_client_gui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISK_CLIENT_GUI_H
#define UI_DISK_CLIENT_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DiskClientGUI
{
public:
    QAction *upaction;
    QAction *downaction;
    QAction *refreshaction;
    QAction *action_new_dir;
    QWidget *topwidget;
    QLabel *logolabel;
    QPushButton *closepushButton;
    QPushButton *my_diskpushButton;
    QPushButton *taskpushButton;
    QPushButton *minpushButton;
    QLabel *label_3;
    QWidget *line1widget;
    QWidget *filelistwidget;
    QWidget *menuwidget;
    QPushButton *downpushButton;
    QPushButton *upButton;
    QFrame *line_4;
    QPushButton *delpushButton;
    QFrame *line1frame;
    QFrame *line1frame_2;
    QCheckBox *file_enc;
    QWidget *leftwidget;
    QProgressBar *disk_info_bar;
    QLabel *label;
    QLabel *username_label;
    QLabel *disk_info_text;
    QLabel *label_2;
    QWidget *fileviewwidget;
    QTableWidget *filetableWidget;
    QWidget *pathwidget;
    QPushButton *pathpushButton;
    QPushButton *refreshButton;
    QFrame *line;
    QPushButton *backButton;
    QLabel *dir_label;
    QCheckBox *checkallBox;
    QWidget *pathwidget_2;
    QLabel *label_4;
    QLabel *file_count;

    void setupUi(QWidget *DiskClientGUI)
    {
        if (DiskClientGUI->objectName().isEmpty())
            DiskClientGUI->setObjectName(QString::fromUtf8("DiskClientGUI"));
        DiskClientGUI->resize(999, 700);
        DiskClientGUI->setStyleSheet(QString::fromUtf8("#upButton:hover{\n"
"background-color: rgb(46, 91, 255);\n"
"}"));
        upaction = new QAction(DiskClientGUI);
        upaction->setObjectName(QString::fromUtf8("upaction"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/XMSDiskClientGui/Resources/img/upload1.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/XMSDiskClientGui/Resources/upload.png"), QSize(), QIcon::Normal, QIcon::On);
        upaction->setIcon(icon);
        downaction = new QAction(DiskClientGUI);
        downaction->setObjectName(QString::fromUtf8("downaction"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/XMSDiskClientGui/Resources/img/down1.png"), QSize(), QIcon::Normal, QIcon::Off);
        downaction->setIcon(icon1);
        refreshaction = new QAction(DiskClientGUI);
        refreshaction->setObjectName(QString::fromUtf8("refreshaction"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/XMSDiskClientGui/Resources/img/refresh1.png"), QSize(), QIcon::Normal, QIcon::Off);
        refreshaction->setIcon(icon2);
        action_new_dir = new QAction(DiskClientGUI);
        action_new_dir->setObjectName(QString::fromUtf8("action_new_dir"));
        topwidget = new QWidget(DiskClientGUI);
        topwidget->setObjectName(QString::fromUtf8("topwidget"));
        topwidget->setGeometry(QRect(0, 0, 1000, 80));
        topwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 240, 246);"));
        logolabel = new QLabel(topwidget);
        logolabel->setObjectName(QString::fromUtf8("logolabel"));
        logolabel->setGeometry(QRect(10, 6, 65, 65));
        logolabel->setStyleSheet(QString::fromUtf8(""));
        logolabel->setPixmap(QPixmap(QString::fromUtf8(":/XMSDiskClientGui/Resources/logo.png")));
        logolabel->setScaledContents(true);
        closepushButton = new QPushButton(topwidget);
        closepushButton->setObjectName(QString::fromUtf8("closepushButton"));
        closepushButton->setGeometry(QRect(970, 10, 21, 21));
        closepushButton->setStyleSheet(QString::fromUtf8("\n"
"QPushButton\n"
"{\n"
"\n"
"border-image: url(:/XMSDiskClientGui/Resources/img/common/system/btn_sys_close.png)\n"
" 0 64 0 0 ; \n"
"}\n"
"QPushButton::!hover{\n"
"border-image: url(:/XMSDiskClientGui/Resources/img/common/system/btn_sys_close.png)\n"
" 0 64 0 0 ; \n"
"\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"border-image: url(:/XMSDiskClientGui/Resources/img/common/system/btn_sys_close.png)\n"
" 0 0 0 64 ; \n"
"}"));
        closepushButton->setAutoExclusive(false);
        closepushButton->setFlat(true);
        my_diskpushButton = new QPushButton(topwidget);
        my_diskpushButton->setObjectName(QString::fromUtf8("my_diskpushButton"));
        my_diskpushButton->setGeometry(QRect(230, 20, 81, 41));
        my_diskpushButton->setStyleSheet(QString::fromUtf8("\n"
"#my_diskpushButton:checked {\n"
"      border-image: url(:/XMSDiskClientGui/Resources/mydisk2.png);\n"
"}\n"
"#my_diskpushButton:!checked {\n"
"      border-image: url(:/XMSDiskClientGui/Resources/mydisk1.png);\n"
"}\n"
""));
        my_diskpushButton->setCheckable(true);
        my_diskpushButton->setChecked(true);
        my_diskpushButton->setAutoExclusive(true);
        taskpushButton = new QPushButton(topwidget);
        taskpushButton->setObjectName(QString::fromUtf8("taskpushButton"));
        taskpushButton->setGeometry(QRect(330, 20, 81, 41));
        taskpushButton->setStyleSheet(QString::fromUtf8("#taskpushButton:checked {\n"
"      border-image: url(:/XMSDiskClientGui/Resources/task2.png);\n"
"}\n"
"#taskpushButton:!checked {\n"
"      border-image: url(:/XMSDiskClientGui/Resources/task1.png);\n"
"}\n"
""));
        taskpushButton->setCheckable(true);
        taskpushButton->setChecked(false);
        taskpushButton->setAutoExclusive(true);
        taskpushButton->setFlat(true);
        minpushButton = new QPushButton(topwidget);
        minpushButton->setObjectName(QString::fromUtf8("minpushButton"));
        minpushButton->setGeometry(QRect(940, 10, 21, 21));
        minpushButton->setStyleSheet(QString::fromUtf8("\n"
"QPushButton\n"
"{\n"
"\n"
"border-image: url(:/XMSDiskClientGui/Resources/img/common/system/btn_sys_minimize.png)\n"
" 0 64 0 0 ; \n"
"}\n"
"QPushButton::!hover{\n"
"border-image: url(:/XMSDiskClientGui/Resources/img/common/system/btn_sys_minimize.png)\n"
" 0 64 0 0 ; \n"
"\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"border-image: url(:/XMSDiskClientGui/Resources/img/common/system/btn_sys_minimize.png)\n"
" 0 0 0 64 ; \n"
"}"));
        minpushButton->setAutoExclusive(false);
        minpushButton->setFlat(true);
        label_3 = new QLabel(topwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(670, 10, 101, 61));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/XMSDiskClientGui/res/pic/ToastSVipBg.png")));
        label_3->setScaledContents(true);
        line1widget = new QWidget(DiskClientGUI);
        line1widget->setObjectName(QString::fromUtf8("line1widget"));
        line1widget->setEnabled(true);
        line1widget->setGeometry(QRect(0, 80, 1000, 2));
        line1widget->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);"));
        filelistwidget = new QWidget(DiskClientGUI);
        filelistwidget->setObjectName(QString::fromUtf8("filelistwidget"));
        filelistwidget->setGeometry(QRect(0, 82, 1000, 700));
        filelistwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);"));
        menuwidget = new QWidget(filelistwidget);
        menuwidget->setObjectName(QString::fromUtf8("menuwidget"));
        menuwidget->setGeometry(QRect(160, 0, 1000, 40));
        menuwidget->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(249, 250, 251);"));
        downpushButton = new QPushButton(menuwidget);
        downpushButton->setObjectName(QString::fromUtf8("downpushButton"));
        downpushButton->setGeometry(QRect(100, 4, 71, 31));
        downpushButton->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"\n"
"}\n"
"\n"
"QPushButton::!hover{\n"
"\n"
"background-image: url(:/XMSDiskClientGui/Resources/img/down1.png);\n"
"background-repeat: no-repeat;\n"
"background-position:left;\n"
"border:none;\n"
"\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background-image: url(:/XMSDiskClientGui/Resources/img/down2.png);\n"
"background-repeat: no-repeat;\n"
"background-position:left;\n"
"color:rgb(6, 168, 255);\n"
"\n"
"border-radius:1px;   \n"
"border:1px solid rgb(6, 168, 255); \n"
"}"));
        downpushButton->setCheckable(false);
        downpushButton->setFlat(true);
        upButton = new QPushButton(menuwidget);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        upButton->setGeometry(QRect(10, 4, 71, 31));
        upButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-color:rgb(10,45,110);  \n"
"\n"
"}\n"
"\n"
"QPushButton::!hover{\n"
"\n"
"background-image: url(:/XMSDiskClientGui/Resources/img/upload1.png);\n"
"background-repeat: no-repeat;\n"
"background-position:left;\n"
"border:none;\n"
"\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background-image: url(:/XMSDiskClientGui/Resources/img/upload2.png);\n"
"background-repeat: no-repeat;\n"
"background-position:left;\n"
"color:rgb(6, 168, 255);\n"
"\n"
"border-radius:1px;   \n"
"border:1px solid rgb(6, 168, 255); \n"
"}"));
        upButton->setCheckable(false);
        upButton->setAutoDefault(false);
        upButton->setFlat(true);
        line_4 = new QFrame(menuwidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(-17, 0, 20, 621));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        delpushButton = new QPushButton(menuwidget);
        delpushButton->setObjectName(QString::fromUtf8("delpushButton"));
        delpushButton->setGeometry(QRect(190, 4, 71, 31));
        delpushButton->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"\n"
"}\n"
"\n"
"QPushButton::!hover{\n"
"\n"
"background-image: url(:/XMSDiskClientGui/Resources/img/del1.png);\n"
"background-repeat: no-repeat;\n"
"background-position:left;\n"
"border:none;\n"
"\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background-image: url(:/XMSDiskClientGui/Resources/img/del2.png);\n"
"background-repeat: no-repeat;\n"
"background-position:left;\n"
"color:rgb(6, 168, 255);\n"
"\n"
"border-radius:1px;   \n"
"border:1px solid rgb(6, 168, 255); \n"
"}"));
        delpushButton->setCheckable(false);
        delpushButton->setFlat(true);
        line1frame = new QFrame(menuwidget);
        line1frame->setObjectName(QString::fromUtf8("line1frame"));
        line1frame->setGeometry(QRect(0, 40, 1000, 111));
        line1frame->setStyleSheet(QString::fromUtf8("background-color:#F0F0F0;"));
        line1frame->setFrameShape(QFrame::StyledPanel);
        line1frame->setFrameShadow(QFrame::Raised);
        line1frame_2 = new QFrame(line1frame);
        line1frame_2->setObjectName(QString::fromUtf8("line1frame_2"));
        line1frame_2->setGeometry(QRect(0, 0, 1000, 2));
        line1frame_2->setStyleSheet(QString::fromUtf8("background-color:#F0F0F0;"));
        line1frame_2->setFrameShape(QFrame::StyledPanel);
        line1frame_2->setFrameShadow(QFrame::Raised);
        file_enc = new QCheckBox(menuwidget);
        file_enc->setObjectName(QString::fromUtf8("file_enc"));
        file_enc->setGeometry(QRect(360, 10, 101, 16));
        leftwidget = new QWidget(filelistwidget);
        leftwidget->setObjectName(QString::fromUtf8("leftwidget"));
        leftwidget->setGeometry(QRect(0, 0, 160, 700));
        leftwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(249, 250, 251);\n"
"font: 12pt \"\351\273\221\344\275\223\";"));
        disk_info_bar = new QProgressBar(leftwidget);
        disk_info_bar->setObjectName(QString::fromUtf8("disk_info_bar"));
        disk_info_bar->setGeometry(QRect(20, 500, 121, 31));
        disk_info_bar->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"      border: 2px solid grey;\n"
"      border-radius: 10px;\n"
"	  \n"
"	color: rgb(255, 0, 128);\n"
"	  font: 11pt \"\346\245\267\344\275\223\";\n"
"  }\n"
"\n"
"  QProgressBar::chunk {\n"
"      background-color: #05B8CC;\n"
"      width: 20px;\n"
"	  margin: 0.5px;\n"
"  }"));
        disk_info_bar->setValue(24);
        disk_info_bar->setTextVisible(false);
        label = new QLabel(leftwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 100, 54, 20));
        username_label = new QLabel(leftwidget);
        username_label->setObjectName(QString::fromUtf8("username_label"));
        username_label->setGeometry(QRect(100, 100, 54, 20));
        disk_info_text = new QLabel(leftwidget);
        disk_info_text->setObjectName(QString::fromUtf8("disk_info_text"));
        disk_info_text->setGeometry(QRect(20, 540, 131, 21));
        label_2 = new QLabel(leftwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 10, 81, 81));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/XMSDiskClientGui/res/pic/head.png")));
        label_2->setScaledContents(true);
        fileviewwidget = new QWidget(filelistwidget);
        fileviewwidget->setObjectName(QString::fromUtf8("fileviewwidget"));
        fileviewwidget->setGeometry(QRect(160, 40, 1000, 700));
        fileviewwidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        fileviewwidget->setStyleSheet(QString::fromUtf8("background-color: #F0F0F0"));
        filetableWidget = new QTableWidget(fileviewwidget);
        if (filetableWidget->columnCount() < 5)
            filetableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        filetableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        filetableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        filetableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        filetableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        filetableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        filetableWidget->setObjectName(QString::fromUtf8("filetableWidget"));
        filetableWidget->setGeometry(QRect(0, 43, 811, 501));
        filetableWidget->setStyleSheet(QString::fromUtf8("QHeaderView::section {\n"
"     padding-left: 0px;\n"
" }\n"
"QTableWidget                   \n"
"{\n"
"    background:#FFFFFF;           \n"
"    border:none;                   \n"
" \n"
"    font-size:14px;                \n"
"    font-family:\"Microsoft YaHei\";\n"
"    color:#666666;   \n"
"\n"
" selection-background-color: qlineargradient(x1: 0, y1: 0, x2: 0.5, y2: 0.5,\n"
"                                  stop: 0 #FF92BB, stop: 1 white);              \n"
"}\n"
"QTableWidget::item                \n"
"{\n"
"    background:#ffffff; \n"
"}\n"
"\n"
"QTableView::item::selected    \n"
"{         \n"
"  color:#000000;             \n"
"  background:#e6f6ff; \n"
"}\n"
"\n"
"\n"
"QHeaderView::section {\n"
"background-color:#FFFFFF;\n"
"  border: 1px solid #f0f0f0 ;\n"
"\n"
"}\n"
"\n"
"\n"
"\n"
""));
        filetableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        filetableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        filetableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        filetableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        filetableWidget->setDragEnabled(true);
        filetableWidget->setAlternatingRowColors(true);
        filetableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        filetableWidget->setTextElideMode(Qt::ElideLeft);
        filetableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        filetableWidget->setShowGrid(false);
        filetableWidget->setGridStyle(Qt::SolidLine);
        filetableWidget->setSortingEnabled(true);
        filetableWidget->setWordWrap(true);
        filetableWidget->setCornerButtonEnabled(true);
        filetableWidget->horizontalHeader()->setVisible(true);
        filetableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        filetableWidget->horizontalHeader()->setHighlightSections(true);
        filetableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        filetableWidget->horizontalHeader()->setStretchLastSection(true);
        filetableWidget->verticalHeader()->setVisible(false);
        filetableWidget->verticalHeader()->setCascadingSectionResizes(false);
        filetableWidget->verticalHeader()->setHighlightSections(true);
        filetableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        filetableWidget->verticalHeader()->setStretchLastSection(false);
        pathwidget = new QWidget(fileviewwidget);
        pathwidget->setObjectName(QString::fromUtf8("pathwidget"));
        pathwidget->setGeometry(QRect(0, 2, 1000, 40));
        pathwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        pathpushButton = new QPushButton(pathwidget);
        pathpushButton->setObjectName(QString::fromUtf8("pathpushButton"));
        pathpushButton->setGeometry(QRect(80, 10, 75, 23));
        pathpushButton->setStyleSheet(QString::fromUtf8("QPushButton::!hover{\n"
"color:rgb(0, 0, 0);\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"color:rgb(6, 168, 255);\n"
"}\n"
""));
        pathpushButton->setFlat(true);
        refreshButton = new QPushButton(pathwidget);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));
        refreshButton->setGeometry(QRect(30, 10, 21, 21));
        refreshButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-color:rgb(10,45,110);  \n"
"\n"
"}\n"
"\n"
"QPushButton::!hover{\n"
"\n"
"background-image: url(:/XMSDiskClientGui/Resources/img/refresh1.png);\n"
"background-repeat: no-repeat;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background-image: url(:/XMSDiskClientGui/Resources/img/refresh2.png);\n"
"background-repeat: no-repeat;\n"
"}"));
        refreshButton->setCheckable(false);
        refreshButton->setAutoDefault(false);
        refreshButton->setFlat(true);
        line = new QFrame(pathwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(60, 10, 16, 26));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        backButton = new QPushButton(pathwidget);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(10, 10, 21, 21));
        backButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-color:rgb(10,45,110);  \n"
"\n"
"}\n"
"\n"
"QPushButton::!hover{\n"
"\n"
"background-image: url(:/XMSDiskClientGui/Resources/img/back1.png);\n"
"background-repeat: no-repeat;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"background-image: url(:/XMSDiskClientGui/Resources/img/back2.png);\n"
"background-repeat: no-repeat;\n"
"}"));
        backButton->setCheckable(false);
        backButton->setAutoDefault(false);
        backButton->setFlat(true);
        dir_label = new QLabel(pathwidget);
        dir_label->setObjectName(QString::fromUtf8("dir_label"));
        dir_label->setGeometry(QRect(160, 13, 641, 20));
        checkallBox = new QCheckBox(fileviewwidget);
        checkallBox->setObjectName(QString::fromUtf8("checkallBox"));
        checkallBox->setGeometry(QRect(14, 50, 16, 16));
        pathwidget_2 = new QWidget(fileviewwidget);
        pathwidget_2->setObjectName(QString::fromUtf8("pathwidget_2"));
        pathwidget_2->setGeometry(QRect(0, 546, 991, 30));
        pathwidget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        label_4 = new QLabel(pathwidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(80, 10, 54, 12));
        file_count = new QLabel(pathwidget_2);
        file_count->setObjectName(QString::fromUtf8("file_count"));
        file_count->setGeometry(QRect(20, 10, 54, 12));
        file_count->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(DiskClientGUI);
        QObject::connect(closepushButton, SIGNAL(clicked()), DiskClientGUI, SLOT(close()));
        QObject::connect(minpushButton, SIGNAL(clicked()), DiskClientGUI, SLOT(showMinimized()));
        QObject::connect(refreshButton, SIGNAL(clicked()), DiskClientGUI, SLOT(Refresh()));
        QObject::connect(checkallBox, SIGNAL(clicked()), DiskClientGUI, SLOT(Checkall()));
        QObject::connect(refreshaction, SIGNAL(triggered()), DiskClientGUI, SLOT(Refresh()));
        QObject::connect(action_new_dir, SIGNAL(triggered()), DiskClientGUI, SLOT(NewDir()));
        QObject::connect(filetableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), DiskClientGUI, SLOT(DirRename(QTableWidgetItem*)));
        QObject::connect(backButton, SIGNAL(clicked()), DiskClientGUI, SLOT(Back()));
        QObject::connect(pathpushButton, SIGNAL(clicked()), DiskClientGUI, SLOT(Root()));
        QObject::connect(filetableWidget, SIGNAL(cellDoubleClicked(int,int)), DiskClientGUI, SLOT(DoubleClicked(int,int)));

        downpushButton->setDefault(false);
        upButton->setDefault(false);
        delpushButton->setDefault(false);
        refreshButton->setDefault(false);
        backButton->setDefault(false);


        QMetaObject::connectSlotsByName(DiskClientGUI);
    } // setupUi

    void retranslateUi(QWidget *DiskClientGUI)
    {
        DiskClientGUI->setWindowTitle(QApplication::translate("DiskClientGUI", "XMSDiskClientGui", nullptr));
        upaction->setText(QApplication::translate("DiskClientGUI", "\344\270\212\344\274\240", nullptr));
        downaction->setText(QApplication::translate("DiskClientGUI", "\344\270\213\350\275\275", nullptr));
        refreshaction->setText(QApplication::translate("DiskClientGUI", "\345\210\267\346\226\260", nullptr));
        action_new_dir->setText(QApplication::translate("DiskClientGUI", "\346\226\260\345\273\272\346\226\207\344\273\266\345\244\271", nullptr));
        logolabel->setText(QString());
        closepushButton->setText(QString());
        my_diskpushButton->setText(QString());
        taskpushButton->setText(QString());
        minpushButton->setText(QString());
        label_3->setText(QString());
        downpushButton->setText(QApplication::translate("DiskClientGUI", "  \344\270\213\350\275\275", nullptr));
        upButton->setText(QApplication::translate("DiskClientGUI", "  \344\270\212\344\274\240", nullptr));
        delpushButton->setText(QApplication::translate("DiskClientGUI", "  \345\210\240\351\231\244", nullptr));
        file_enc->setText(QApplication::translate("DiskClientGUI", "\346\226\207\344\273\266\345\212\240\345\257\206\344\270\212\344\274\240", nullptr));
        label->setText(QApplication::translate("DiskClientGUI", "\347\224\250\346\210\267\357\274\232", nullptr));
        username_label->setText(QApplication::translate("DiskClientGUI", "root", nullptr));
        disk_info_text->setText(QApplication::translate("DiskClientGUI", "123G/3000G", nullptr));
        label_2->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = filetableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem->setText(QApplication::translate("DiskClientGUI", "\346\226\207\344\273\266\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = filetableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem1->setText(QApplication::translate("DiskClientGUI", "\344\277\256\346\224\271\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = filetableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem2->setText(QApplication::translate("DiskClientGUI", "\345\244\247\345\260\217", nullptr));
        pathpushButton->setText(QApplication::translate("DiskClientGUI", "\346\210\221\347\232\204\347\275\221\347\233\230  >", nullptr));
        refreshButton->setText(QString());
        backButton->setText(QString());
        dir_label->setText(QString());
        checkallBox->setText(QString());
        label_4->setText(QApplication::translate("DiskClientGUI", "\351\241\271", nullptr));
        file_count->setText(QApplication::translate("DiskClientGUI", "100", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DiskClientGUI: public Ui_DiskClientGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISK_CLIENT_GUI_H
