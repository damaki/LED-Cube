/********************************************************************************
** Form generated from reading UI file 'test_effect_ctrl.ui'
**
** Created: Sat 16. Apr 21:22:25 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_EFFECT_CTRL_H
#define UI_TEST_EFFECT_CTRL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDial>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestEffectCtrls
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSlider *slider_speed;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDial *dial_brightness;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *TestEffectCtrls)
    {
        if (TestEffectCtrls->objectName().isEmpty())
            TestEffectCtrls->setObjectName(QString::fromUtf8("TestEffectCtrls"));
        TestEffectCtrls->resize(400, 100);
        TestEffectCtrls->setMinimumSize(QSize(400, 100));
        TestEffectCtrls->setMaximumSize(QSize(16777215, 100));
        verticalLayout = new QVBoxLayout(TestEffectCtrls);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(TestEffectCtrls);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        slider_speed = new QSlider(TestEffectCtrls);
        slider_speed->setObjectName(QString::fromUtf8("slider_speed"));
        slider_speed->setMaximum(60);
        slider_speed->setValue(30);
        slider_speed->setOrientation(Qt::Horizontal);
        slider_speed->setInvertedAppearance(true);

        horizontalLayout->addWidget(slider_speed);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(TestEffectCtrls);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        dial_brightness = new QDial(TestEffectCtrls);
        dial_brightness->setObjectName(QString::fromUtf8("dial_brightness"));
        dial_brightness->setMinimum(20);
        dial_brightness->setMaximum(127);
        dial_brightness->setSingleStep(16);
        dial_brightness->setPageStep(1);
        dial_brightness->setValue(127);
        dial_brightness->setSliderPosition(127);
        dial_brightness->setNotchTarget(3.7);
        dial_brightness->setNotchesVisible(true);

        horizontalLayout_2->addWidget(dial_brightness);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(TestEffectCtrls);

        QMetaObject::connectSlotsByName(TestEffectCtrls);
    } // setupUi

    void retranslateUi(QWidget *TestEffectCtrls)
    {
        TestEffectCtrls->setWindowTitle(QApplication::translate("TestEffectCtrls", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TestEffectCtrls", "Speed", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TestEffectCtrls", "Brightness", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TestEffectCtrls: public Ui_TestEffectCtrls {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_EFFECT_CTRL_H
