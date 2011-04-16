/********************************************************************************
** Form generated from reading UI file 'rain_effect_ctrl.ui'
**
** Created: Sat 16. Apr 21:22:25 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RAIN_EFFECT_CTRL_H
#define UI_RAIN_EFFECT_CTRL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_form_controls
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout;
    QSlider *slider_spawnRate;
    QSlider *slider_fallRate;
    QSlider *slider_decayRate;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *form_controls)
    {
        if (form_controls->objectName().isEmpty())
            form_controls->setObjectName(QString::fromUtf8("form_controls"));
        form_controls->resize(400, 104);
        verticalLayout_3 = new QVBoxLayout(form_controls);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(form_controls);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(form_controls);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(form_controls);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        slider_spawnRate = new QSlider(form_controls);
        slider_spawnRate->setObjectName(QString::fromUtf8("slider_spawnRate"));
        slider_spawnRate->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(slider_spawnRate);

        slider_fallRate = new QSlider(form_controls);
        slider_fallRate->setObjectName(QString::fromUtf8("slider_fallRate"));
        slider_fallRate->setValue(50);
        slider_fallRate->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(slider_fallRate);

        slider_decayRate = new QSlider(form_controls);
        slider_decayRate->setObjectName(QString::fromUtf8("slider_decayRate"));
        slider_decayRate->setValue(50);
        slider_decayRate->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(slider_decayRate);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 4, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        retranslateUi(form_controls);

        QMetaObject::connectSlotsByName(form_controls);
    } // setupUi

    void retranslateUi(QWidget *form_controls)
    {
        form_controls->setWindowTitle(QApplication::translate("form_controls", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("form_controls", "Spawn Rate", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("form_controls", "Fall Rate", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("form_controls", "Decay Rate", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class form_controls: public Ui_form_controls {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RAIN_EFFECT_CTRL_H
