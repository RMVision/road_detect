/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_video;
    QPushButton *pushButton_start_line;
    QPushButton *pushButton_open;
    QPushButton *pushButton_pause;
    QPushButton *pushButton_stop;
    QLabel *label_sign_1;
    QPushButton *pushButton_start_sign;
    QLabel *label_sign_2;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(808, 400);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label_video = new QLabel(centralWidget);
        label_video->setObjectName(QString::fromUtf8("label_video"));
        label_video->setGeometry(QRect(190, 30, 576, 324));
        pushButton_start_line = new QPushButton(centralWidget);
        pushButton_start_line->setObjectName(QString::fromUtf8("pushButton_start_line"));
        pushButton_start_line->setGeometry(QRect(40, 30, 111, 41));
        pushButton_pause = new QPushButton(centralWidget);
        pushButton_pause->setObjectName(QString::fromUtf8("pushButton_pause"));
        pushButton_pause->setGeometry(QRect(40, 150, 111, 41));
        pushButton_stop = new QPushButton(centralWidget);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));
        pushButton_stop->setGeometry(QRect(40, 210, 111, 41));
        pushButton_start_sign = new QPushButton(centralWidget);
        pushButton_start_sign->setObjectName(QString::fromUtf8("pushButton_start_sign"));
        pushButton_start_sign->setGeometry(QRect(40, 90, 111, 41));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 808, 30));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label_video->setText(QApplication::translate("MainWindow", "", nullptr));
        pushButton_start_line->setText(QApplication::translate("MainWindow", "车道线识别", nullptr));
        pushButton_pause->setText(QApplication::translate("MainWindow", "暂停", nullptr));
        pushButton_stop->setText(QApplication::translate("MainWindow", "结束", nullptr));
        pushButton_start_sign->setText(QApplication::translate("MainWindow", "路牌识别", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "感谢HezeLao-RuiweiXie", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
