#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

// Effects
#include "test_effect.h"
#include "rain_effect.h"
#include "ball_effect.h"
#include "wave_effect.h"

MainWindow::MainWindow(boost::asio::io_service &io, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_effect_driver(io),
    m_pEffect(NULL)
{
    ui->setupUi(this);

    centralWidget()->setLayout(new QVBoxLayout());

    m_pEdit_comPort       = findChild<QLineEdit*>("edit_comPort");
    m_pBtn_portOpen       = findChild<QPushButton*>("btn_portOpen");
    m_pBtn_portClose      = findChild<QPushButton*>("btn_portClose");
    m_pBtn_activateEffect = findChild<QPushButton*>("btn_activateEffect");
    m_pList_effects       = findChild<QListWidget*>("list_effects");
    m_pDock_controls      = findChild<QDockWidget*>("dock_controls");

    connect(m_pBtn_portOpen, SIGNAL(clicked()), this, SLOT(openPort()));
    connect(m_pBtn_portClose, SIGNAL(clicked()), this, SLOT(closePort()));
    connect(m_pBtn_activateEffect, SIGNAL(clicked()), this, SLOT(activateEffect()));

    m_pDock_controls->setLayout(new QVBoxLayout());
    m_pDock_controls->hide();

    m_pList_effects->addItem(new effects::Test());
    m_pList_effects->addItem(new effects::Rain());
    m_pList_effects->addItem(new effects::Ball());
    m_pList_effects->addItem(new effects::Wave());

    m_effect_driver.start();
}

MainWindow::~MainWindow()
{
    // Detach the control panel for the current effect, so that it's not deleted when MainWindow closes.
    // The effect is responsible for clearing up its own mess.
    if (NULL != m_pEffect)
    {
        QWidget *pCtrls = m_pEffect->get_controls();
        if (NULL != pCtrls)
            pCtrls->setParent(NULL);
    }

    try
    {
        m_effect_driver.close_port();
    }
    catch (...)
    {}

    try
    {
        m_effect_driver.stop();
    }
    catch (...)
    {}

    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::openPort()
{
    try
    {
        m_effect_driver.open_port(m_pEdit_comPort->text().toStdString());

        m_pBtn_portClose->setEnabled(m_effect_driver.is_open());
    }
    catch (...)
    {
        m_pBtn_portClose->setEnabled(false);

        QMessageBox msg(QMessageBox::Critical,
                        "Error",
                        QString("Could not open \"") + m_pEdit_comPort->text() + QString("\""),
                        QMessageBox::Ok,
                        this);
        msg.exec();
    }
}

void MainWindow::closePort()
{
    m_effect_driver.close_port();
    m_pBtn_portClose->setEnabled(false);
}

void MainWindow::activateEffect()
{
    try
    {
        QList<QListWidgetItem*> selection = m_pList_effects->selectedItems();

        if (selection.size() > 0)
        {
            // Remove the controls from the current effect from the UI
            if (NULL != m_pEffect)
            {
                QWidget *pCtrls = m_pEffect->get_controls();
                if (NULL != pCtrls)
                    pCtrls->setParent(NULL);
            }

            // Activate the next effect
            m_pEffect = dynamic_cast<effects::BaseEffect*>(selection[0]);
            if (NULL != m_pEffect)
            {
                QWidget *pCtrls = m_pEffect->get_controls();
                if (NULL != pCtrls)
                {
                    m_pDock_controls->setWidget(pCtrls);
                    pCtrls->show();
                    m_pDock_controls->show();
                }
                else
                {
                    m_pDock_controls->hide();
                }

                m_effect_driver.run(m_pEffect);
            }
            else
                m_pDock_controls->hide();
        }
    }
    catch (...)
    {
        QMessageBox msg(QMessageBox::Warning,
                        "Error",
                        QString("Sorry, something went wrong when running that effect"),
                        QMessageBox::Ok,
                        this);
        msg.exec();
    }
}
