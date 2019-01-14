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
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QStackedWidget *mainStack;
    QWidget *pgMain;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QWidget *pgGm;
    QGridLayout *gridLayout_3;
    QWidget *pgPr;
    QGridLayout *gridLayout_4;
    QGridLayout *idk;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *skillBox;
    QStackedWidget *stackedWidget;
    QWidget *pgSkills;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *skillNames;
    QVBoxLayout *skillRanks;
    QWidget *pg00;
    QGridLayout *gridLayout_5;
    QGridLayout *inventory;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(854, 957);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mainStack = new QStackedWidget(centralWidget);
        mainStack->setObjectName(QString::fromUtf8("mainStack"));
        pgMain = new QWidget();
        pgMain->setObjectName(QString::fromUtf8("pgMain"));
        gridLayout_2 = new QGridLayout(pgMain);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        gridLayout_2->addLayout(horizontalLayout, 0, 1, 1, 1);

        mainStack->addWidget(pgMain);
        pgGm = new QWidget();
        pgGm->setObjectName(QString::fromUtf8("pgGm"));
        gridLayout_3 = new QGridLayout(pgGm);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        mainStack->addWidget(pgGm);
        pgPr = new QWidget();
        pgPr->setObjectName(QString::fromUtf8("pgPr"));
        gridLayout_4 = new QGridLayout(pgPr);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        idk = new QGridLayout();
        idk->setSpacing(6);
        idk->setObjectName(QString::fromUtf8("idk"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        idk->addItem(horizontalSpacer, 0, 0, 1, 1);


        gridLayout_4->addLayout(idk, 0, 1, 1, 1);

        skillBox = new QHBoxLayout();
        skillBox->setSpacing(6);
        skillBox->setObjectName(QString::fromUtf8("skillBox"));
        skillBox->setSizeConstraint(QLayout::SetDefaultConstraint);
        stackedWidget = new QStackedWidget(pgPr);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        pgSkills = new QWidget();
        pgSkills->setObjectName(QString::fromUtf8("pgSkills"));
        horizontalLayout_2 = new QHBoxLayout(pgSkills);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        skillNames = new QVBoxLayout();
        skillNames->setSpacing(6);
        skillNames->setObjectName(QString::fromUtf8("skillNames"));

        horizontalLayout_2->addLayout(skillNames);

        skillRanks = new QVBoxLayout();
        skillRanks->setSpacing(6);
        skillRanks->setObjectName(QString::fromUtf8("skillRanks"));

        horizontalLayout_2->addLayout(skillRanks);

        stackedWidget->addWidget(pgSkills);
        pg00 = new QWidget();
        pg00->setObjectName(QString::fromUtf8("pg00"));
        gridLayout_5 = new QGridLayout(pg00);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        stackedWidget->addWidget(pg00);

        skillBox->addWidget(stackedWidget);


        gridLayout_4->addLayout(skillBox, 0, 0, 2, 1);

        inventory = new QGridLayout();
        inventory->setSpacing(6);
        inventory->setObjectName(QString::fromUtf8("inventory"));

        gridLayout_4->addLayout(inventory, 1, 1, 1, 1);

        mainStack->addWidget(pgPr);

        gridLayout->addWidget(mainStack, 0, 0, 1, 1);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 854, 21));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        retranslateUi(MainWindowClass);

        mainStack->setCurrentIndex(2);
        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
