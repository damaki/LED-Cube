/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat 16. Apr 21:22:25 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Exit;
    QAction *action_Controls;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QMenu *menuView;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *edit_comPort;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_portOpen;
    QPushButton *btn_portClose;
    QListWidget *list_effects;
    QPushButton *btn_activateEffect;
    QDockWidget *dock_controls;
    QWidget *dockWidgetContents_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(799, 525);
        MainWindow->setDockNestingEnabled(true);
        action_Exit = new QAction(MainWindow);
        action_Exit->setObjectName(QString::fromUtf8("action_Exit"));
        action_Controls = new QAction(MainWindow);
        action_Controls->setObjectName(QString::fromUtf8("action_Controls"));
        action_Controls->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 799, 21));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(dockWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        edit_comPort = new QLineEdit(dockWidgetContents);
        edit_comPort->setObjectName(QString::fromUtf8("edit_comPort"));

        horizontalLayout_2->addWidget(edit_comPort);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btn_portOpen = new QPushButton(dockWidgetContents);
        btn_portOpen->setObjectName(QString::fromUtf8("btn_portOpen"));
        btn_portOpen->setEnabled(true);

        horizontalLayout->addWidget(btn_portOpen);

        btn_portClose = new QPushButton(dockWidgetContents);
        btn_portClose->setObjectName(QString::fromUtf8("btn_portClose"));
        btn_portClose->setEnabled(false);

        horizontalLayout->addWidget(btn_portClose);


        verticalLayout->addLayout(horizontalLayout);

        list_effects = new QListWidget(dockWidgetContents);
        list_effects->setObjectName(QString::fromUtf8("list_effects"));

        verticalLayout->addWidget(list_effects);

        btn_activateEffect = new QPushButton(dockWidgetContents);
        btn_activateEffect->setObjectName(QString::fromUtf8("btn_activateEffect"));
        btn_activateEffect->setEnabled(true);

        verticalLayout->addWidget(btn_activateEffect);


        verticalLayout_2->addLayout(verticalLayout);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);
        dock_controls = new QDockWidget(MainWindow);
        dock_controls->setObjectName(QString::fromUtf8("dock_controls"));
        dock_controls->setEnabled(true);
        dock_controls->setFloating(false);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        dock_controls->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dock_controls);

        menuBar->addAction(menuMenu->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuMenu->addAction(action_Exit);
        menuView->addAction(action_Controls);

        retranslateUi(MainWindow);
        QObject::connect(action_Exit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(action_Controls, SIGNAL(triggered(bool)), dockWidget, SLOT(setVisible(bool)));
        QObject::connect(dockWidget, SIGNAL(visibilityChanged(bool)), action_Controls, SLOT(setChecked(bool)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "LED Cube", 0, QApplication::UnicodeUTF8));
        action_Exit->setText(QApplication::translate("MainWindow", "&Exit", 0, QApplication::UnicodeUTF8));
        action_Controls->setText(QApplication::translate("MainWindow", "&Controls", 0, QApplication::UnicodeUTF8));
        menuMenu->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0, QApplication::UnicodeUTF8));
        dockWidget->setWindowTitle(QApplication::translate("MainWindow", "Controls", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "COM Port:", 0, QApplication::UnicodeUTF8));
        btn_portOpen->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        btn_portClose->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
        btn_activateEffect->setText(QApplication::translate("MainWindow", "Activate Effect", 0, QApplication::UnicodeUTF8));
        dock_controls->setWindowTitle(QApplication::translate("MainWindow", "Effect Settings", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
