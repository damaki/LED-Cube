#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include "effect_base.h"
#include "effect_driver.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(boost::asio::io_service &io, QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

public slots:
    void openPort();
    void closePort();
    void activateEffect();

private:
    Ui::MainWindow *ui;

    effects::BaseEffect *m_pEffect;
    EffectDriver m_effect_driver;

    QLineEdit *m_pEdit_comPort;
    QPushButton *m_pBtn_portOpen;
    QPushButton *m_pBtn_portClose;
    QPushButton *m_pBtn_activateEffect;
    QListWidget *m_pList_effects;

    QDockWidget *m_pDock_controls;
};

#endif // MAINWINDOW_H
