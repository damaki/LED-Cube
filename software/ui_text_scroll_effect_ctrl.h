/********************************************************************************
** Form generated from reading UI file 'text_scroll_effect_ctrl.ui'
**
** Created: Sat 16. Apr 21:22:25 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXT_SCROLL_EFFECT_CTRL_H
#define UI_TEXT_SCROLL_EFFECT_CTRL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *Speed;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *edit_text;
    QPushButton *btn_start;
    QSlider *slider_speed;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(400, 94);
        verticalLayout_3 = new QVBoxLayout(Form);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(label);

        Speed = new QLabel(Form);
        Speed->setObjectName(QString::fromUtf8("Speed"));
        Speed->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(Speed);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        edit_text = new QLineEdit(Form);
        edit_text->setObjectName(QString::fromUtf8("edit_text"));

        horizontalLayout->addWidget(edit_text);

        btn_start = new QPushButton(Form);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));

        horizontalLayout->addWidget(btn_start);


        verticalLayout->addLayout(horizontalLayout);

        slider_speed = new QSlider(Form);
        slider_speed->setObjectName(QString::fromUtf8("slider_speed"));
        slider_speed->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(slider_speed);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Form", "Text", 0, QApplication::UnicodeUTF8));
        Speed->setText(QApplication::translate("Form", "Speed", 0, QApplication::UnicodeUTF8));
        edit_text->setText(QApplication::translate("Form", "HELLO WORLD", 0, QApplication::UnicodeUTF8));
        btn_start->setText(QApplication::translate("Form", "Start", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXT_SCROLL_EFFECT_CTRL_H
