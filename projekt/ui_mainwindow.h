/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QPushButton *btn_rotate;
    QPushButton *btn_addPlayer;
    QPlainTextEdit *plainTextEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(740, 510);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(10, 10, 420, 420));
        graphicsView->setBaseSize(QSize(0, 0));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        btn_rotate = new QPushButton(centralWidget);
        btn_rotate->setObjectName(QStringLiteral("btn_rotate"));
        btn_rotate->setGeometry(QRect(50, 440, 50, 23));
        btn_addPlayer = new QPushButton(centralWidget);
        btn_addPlayer->setObjectName(QStringLiteral("btn_addPlayer"));
        btn_addPlayer->setGeometry(QRect(150, 440, 75, 23));
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(450, 10, 280, 460));
        MainWindow->setCentralWidget(centralWidget);
        //menuBar = new QMenuBar(MainWindow);
        //menuBar->setObjectName(QStringLiteral("menuBar"));
        //menuBar->setGeometry(QRect(0, 0, 947, 21));
        //MainWindow->setMenuBar(menuBar);
        //mainToolBar = new QToolBar(MainWindow);
        //mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        //MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        //statusBar = new QStatusBar(MainWindow);
        //statusBar->setObjectName(QStringLiteral("statusBar"));
        //MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Labyrinth", 0));
        btn_rotate->setText(QApplication::translate("MainWindow", "Rotate", 0));
        btn_addPlayer->setText(QApplication::translate("MainWindow", "Add player", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
