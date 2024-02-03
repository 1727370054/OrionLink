/********************************************************************************
** Form generated from reading UI file 'task_item_gui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASK_ITEM_GUI_H
#define UI_TASK_ITEM_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskItemGUI
{
public:
    QLabel *filetype;
    QLabel *filename;
    QLabel *filesize;
    QLabel *filetime;
    QProgressBar *progressBar;

    void setupUi(QWidget *TaskItemGUI)
    {
        if (TaskItemGUI->objectName().isEmpty())
            TaskItemGUI->setObjectName(QString::fromUtf8("TaskItemGUI"));
        TaskItemGUI->resize(900, 51);
        TaskItemGUI->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background-color: rgba(255, 255, 255,0);\n"
"}\n"
""));
        filetype = new QLabel(TaskItemGUI);
        filetype->setObjectName(QString::fromUtf8("filetype"));
        filetype->setGeometry(QRect(30, 10, 31, 31));
        filetype->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0,0);\n"
"background-image: url(:/XMSDiskClientGui/Resources/img/FileType/Middle/DocType.png);"));
        filename = new QLabel(TaskItemGUI);
        filename->setObjectName(QString::fromUtf8("filename"));
        filename->setGeometry(QRect(70, 10, 261, 21));
        filename->setAutoFillBackground(false);
        filename->setStyleSheet(QString::fromUtf8("\n"
"font: 14pt \"\351\273\221\344\275\223\";"));
        filesize = new QLabel(TaskItemGUI);
        filesize->setObjectName(QString::fromUtf8("filesize"));
        filesize->setGeometry(QRect(80, 30, 261, 21));
        filesize->setStyleSheet(QString::fromUtf8("\n"
"font: 9pt \"\351\273\221\344\275\223\";"));
        filetime = new QLabel(TaskItemGUI);
        filetime->setObjectName(QString::fromUtf8("filetime"));
        filetime->setGeometry(QRect(360, 15, 161, 21));
        filetime->setStyleSheet(QString::fromUtf8("font: 11pt \"\351\273\221\344\275\223\";"));
        progressBar = new QProgressBar(TaskItemGUI);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(530, 21, 261, 10));
        progressBar->setLayoutDirection(Qt::LeftToRight);
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"      border: 2px solid grey;\n"
"      border-radius: 2px;\n"
"	  \n"
"	color: rgb(255, 0, 128);\n"
"	  font: 10pt \"\346\245\267\344\275\223\";\n"
"  }\n"
"\n"
"QProgressBar::chunk {\n"
"      background-color: #05B8CC;\n"
"  }"));
        progressBar->setValue(24);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setTextDirection(QProgressBar::TopToBottom);

        retranslateUi(TaskItemGUI);

        QMetaObject::connectSlotsByName(TaskItemGUI);
    } // setupUi

    void retranslateUi(QWidget *TaskItemGUI)
    {
        TaskItemGUI->setWindowTitle(QApplication::translate("TaskItemGUI", "TaskItemGUI", nullptr));
        filetype->setText(QString());
        filename->setText(QApplication::translate("TaskItemGUI", "testasdasd.docx", nullptr));
        filesize->setText(QApplication::translate("TaskItemGUI", "1024KB/102MB", nullptr));
        filetime->setText(QApplication::translate("TaskItemGUI", "19:04", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TaskItemGUI: public Ui_TaskItemGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASK_ITEM_GUI_H
