/********************************************************************************
** Form generated from reading UI file 'task_list_gui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASK_LIST_GUI_H
#define UI_TASK_LIST_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskListGUI
{
public:
    QWidget *backwidget;
    QWidget *leftwidget;
    QPushButton *downButton;
    QPushButton *upButton;
    QPushButton *okButton;
    QLabel *downlabel;
    QLabel *oklabel;
    QLabel *uplabel;
    QTableWidget *tasktableWidget;

    void setupUi(QWidget *TaskListGUI)
    {
        if (TaskListGUI->objectName().isEmpty())
            TaskListGUI->setObjectName(QString::fromUtf8("TaskListGUI"));
        TaskListGUI->resize(999, 613);
        TaskListGUI->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);"));
        backwidget = new QWidget(TaskListGUI);
        backwidget->setObjectName(QString::fromUtf8("backwidget"));
        backwidget->setGeometry(QRect(0, 0, 10000, 10000));
        backwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);"));
        leftwidget = new QWidget(backwidget);
        leftwidget->setObjectName(QString::fromUtf8("leftwidget"));
        leftwidget->setGeometry(QRect(0, -10, 171, 621));
        leftwidget->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QPushButton:checked {\n"
"      border-image: url(:/XMSDiskClientGui/Resources/task_bak.png);\n"
"font: 11pt \"Adobe Arabic\";\n"
"	color: rgb(6, 181, 253);\n"
"}\n"
"\n"
"QPushButton:!checked {\n"
"font: 11pt \"Adobe Arabic\";\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
"QWidget\n"
"{\n"
"background-color: rgb(249, 250, 251);\n"
"}"));
        downButton = new QPushButton(leftwidget);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        downButton->setEnabled(true);
        downButton->setGeometry(QRect(0, 4, 171, 40));
        downButton->setStyleSheet(QString::fromUtf8("qproperty-icon: url(:/XMSDiskClientGui/Resources/img/down1.png) off, url(:/XMSDiskClientGui/Resources/img/down2.png) on;"));
        downButton->setCheckable(true);
        downButton->setChecked(true);
        downButton->setAutoExclusive(true);
        downButton->setAutoDefault(false);
        downButton->setFlat(true);
        upButton = new QPushButton(leftwidget);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        upButton->setEnabled(true);
        upButton->setGeometry(QRect(0, 42, 171, 40));
        upButton->setStyleSheet(QString::fromUtf8("qproperty-icon: url(:/XMSDiskClientGui/Resources/img/upload1.png) off, url(:/XMSDiskClientGui/Resources/img/upload2.png) on;"));
        upButton->setCheckable(true);
        upButton->setChecked(false);
        upButton->setAutoExclusive(true);
        upButton->setFlat(true);
        okButton = new QPushButton(leftwidget);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setEnabled(true);
        okButton->setGeometry(QRect(0, 84, 171, 40));
        okButton->setStyleSheet(QString::fromUtf8("qproperty-icon: url(:/XMSDiskClientGui/Resources/img/succ1.png) off, url(:/XMSDiskClientGui/Resources/img/succ2.png) on;"));
        okButton->setCheckable(true);
        okButton->setChecked(false);
        okButton->setAutoExclusive(true);
        okButton->setFlat(true);
        downlabel = new QLabel(leftwidget);
        downlabel->setObjectName(QString::fromUtf8("downlabel"));
        downlabel->setGeometry(QRect(130, 13, 41, 21));
        downlabel->setStyleSheet(QString::fromUtf8("font: 12pt \"\346\200\235\346\272\220\351\273\221\344\275\223 CN Normal\";\n"
"color: rgb(255, 0, 4);\n"
"background-color: rgba(0, 0, 0, 0);"));
        oklabel = new QLabel(leftwidget);
        oklabel->setObjectName(QString::fromUtf8("oklabel"));
        oklabel->setGeometry(QRect(130, 91, 41, 21));
        oklabel->setStyleSheet(QString::fromUtf8("font: 12pt \"\346\200\235\346\272\220\351\273\221\344\275\223 CN Normal\";\n"
"color: rgb(255, 0, 4);\n"
"background-color: rgba(0, 0, 0, 0);"));
        uplabel = new QLabel(leftwidget);
        uplabel->setObjectName(QString::fromUtf8("uplabel"));
        uplabel->setGeometry(QRect(130, 51, 41, 21));
        uplabel->setStyleSheet(QString::fromUtf8("font: 12pt \"\346\200\235\346\272\220\351\273\221\344\275\223 CN Normal\";\n"
"color: rgb(255, 0, 4);\n"
"background-color: rgba(0, 0, 0, 0);"));
        downButton->raise();
        okButton->raise();
        downlabel->raise();
        oklabel->raise();
        upButton->raise();
        uplabel->raise();
        tasktableWidget = new QTableWidget(backwidget);
        if (tasktableWidget->columnCount() < 1)
            tasktableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tasktableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tasktableWidget->setObjectName(QString::fromUtf8("tasktableWidget"));
        tasktableWidget->setGeometry(QRect(170, 0, 831, 611));
        tasktableWidget->setMouseTracking(true);
        tasktableWidget->setTabletTracking(true);
        tasktableWidget->setFocusPolicy(Qt::NoFocus);
        tasktableWidget->setAutoFillBackground(true);
        tasktableWidget->setStyleSheet(QString::fromUtf8("QHeaderView::section {\n"
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
"    spacing: 3px;\n"
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
"QTableView::item {\n"
"\n"
"      border-bottom-width: 1px;\n"
"      border-style: solid;\n"
"      border-color: #f0f0f0;\n"
"      padding-left: 10px;\n"
"	  border-right: none;\n"
"border-left: none;\n"
""
                        "border-top: none;\n"
"	\n"
"\n"
"}"));
        tasktableWidget->setFrameShape(QFrame::NoFrame);
        tasktableWidget->setFrameShadow(QFrame::Plain);
        tasktableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tasktableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tasktableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        tasktableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tasktableWidget->setTabKeyNavigation(false);
        tasktableWidget->setProperty("showDropIndicator", QVariant(false));
        tasktableWidget->setDragEnabled(false);
        tasktableWidget->setDragDropOverwriteMode(false);
        tasktableWidget->setAlternatingRowColors(false);
        tasktableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tasktableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tasktableWidget->setTextElideMode(Qt::ElideLeft);
        tasktableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        tasktableWidget->setShowGrid(true);
        tasktableWidget->setGridStyle(Qt::NoPen);
        tasktableWidget->setSortingEnabled(true);
        tasktableWidget->setWordWrap(true);
        tasktableWidget->setCornerButtonEnabled(false);
        tasktableWidget->setColumnCount(1);
        tasktableWidget->horizontalHeader()->setVisible(false);
        tasktableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tasktableWidget->horizontalHeader()->setMinimumSectionSize(100);
        tasktableWidget->horizontalHeader()->setHighlightSections(true);
        tasktableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tasktableWidget->horizontalHeader()->setStretchLastSection(true);
        tasktableWidget->verticalHeader()->setVisible(false);
        tasktableWidget->verticalHeader()->setCascadingSectionResizes(false);
        tasktableWidget->verticalHeader()->setDefaultSectionSize(55);
        tasktableWidget->verticalHeader()->setHighlightSections(true);
        tasktableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tasktableWidget->verticalHeader()->setStretchLastSection(false);

        retranslateUi(TaskListGUI);
        QObject::connect(tasktableWidget, SIGNAL(clicked(QModelIndex)), TaskListGUI, SLOT(Select(QModelIndex)));
        QObject::connect(downButton, SIGNAL(clicked()), TaskListGUI, SLOT(DownTask()));
        QObject::connect(upButton, SIGNAL(clicked()), TaskListGUI, SLOT(UpTask()));
        QObject::connect(okButton, SIGNAL(clicked()), TaskListGUI, SLOT(OkTask()));
        QObject::connect(downButton, SIGNAL(clicked()), TaskListGUI, SLOT(RefreshUploadTask()));

        downButton->setDefault(false);
        upButton->setDefault(false);
        okButton->setDefault(false);


        QMetaObject::connectSlotsByName(TaskListGUI);
    } // setupUi

    void retranslateUi(QWidget *TaskListGUI)
    {
        TaskListGUI->setWindowTitle(QApplication::translate("TaskListGUI", "TaskListGUI", nullptr));
        downButton->setText(QApplication::translate("TaskListGUI", "\346\255\243\345\234\250\344\270\213\350\275\275", nullptr));
#ifndef QT_NO_SHORTCUT
        downButton->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        upButton->setText(QApplication::translate("TaskListGUI", "\346\255\243\345\234\250\344\270\212\344\274\240", nullptr));
#ifndef QT_NO_SHORTCUT
        upButton->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        okButton->setText(QApplication::translate("TaskListGUI", "\344\274\240\350\276\223\345\256\214\346\210\220", nullptr));
#ifndef QT_NO_SHORTCUT
        okButton->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        downlabel->setText(QApplication::translate("TaskListGUI", "(0)", nullptr));
        oklabel->setText(QApplication::translate("TaskListGUI", "(0)", nullptr));
        uplabel->setText(QApplication::translate("TaskListGUI", "(0)", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tasktableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("TaskListGUI", "\346\226\207\344\273\266\345\220\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TaskListGUI: public Ui_TaskListGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASK_LIST_GUI_H
