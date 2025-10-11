/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mycombobox.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEditRev;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QComboBox *comboBoxProt;
    QLabel *label_2;
    QComboBox *comboBoxAddr;
    QLabel *label_3;
    QLineEdit *lineEditPort;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnStartListen;
    QPushButton *btnStopListen;
    QPushButton *btnLineOut;
    QSpacerItem *horizontalSpacer_4;
    MyComboBox *comboBoxChildren;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *textEditSend;
    QPushButton *btnSend;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(771, 631);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/server.png"), QSize(), QIcon::Normal, QIcon::Off);
        Widget->setWindowIcon(icon);
        Widget->setToolTipDuration(-3);
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 771, 631));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        textEditRev = new QTextEdit(layoutWidget);
        textEditRev->setObjectName(QString::fromUtf8("textEditRev"));

        verticalLayout->addWidget(textEditRev);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBoxProt = new QComboBox(layoutWidget);
        comboBoxProt->addItem(QString());
        comboBoxProt->addItem(QString());
        comboBoxProt->setObjectName(QString::fromUtf8("comboBoxProt"));

        horizontalLayout->addWidget(comboBoxProt);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBoxAddr = new QComboBox(layoutWidget);
        comboBoxAddr->setObjectName(QString::fromUtf8("comboBoxAddr"));

        horizontalLayout->addWidget(comboBoxAddr);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        lineEditPort = new QLineEdit(layoutWidget);
        lineEditPort->setObjectName(QString::fromUtf8("lineEditPort"));

        horizontalLayout->addWidget(lineEditPort);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        btnStartListen = new QPushButton(layoutWidget);
        btnStartListen->setObjectName(QString::fromUtf8("btnStartListen"));

        horizontalLayout_2->addWidget(btnStartListen);

        btnStopListen = new QPushButton(layoutWidget);
        btnStopListen->setObjectName(QString::fromUtf8("btnStopListen"));

        horizontalLayout_2->addWidget(btnStopListen);

        btnLineOut = new QPushButton(layoutWidget);
        btnLineOut->setObjectName(QString::fromUtf8("btnLineOut"));

        horizontalLayout_2->addWidget(btnLineOut);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        comboBoxChildren = new MyComboBox(layoutWidget);
        comboBoxChildren->addItem(QString());
        comboBoxChildren->setObjectName(QString::fromUtf8("comboBoxChildren"));

        verticalLayout->addWidget(comboBoxChildren);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        textEditSend = new QTextEdit(layoutWidget);
        textEditSend->setObjectName(QString::fromUtf8("textEditSend"));

        horizontalLayout_3->addWidget(textEditSend);

        btnSend = new QPushButton(layoutWidget);
        btnSend->setObjectName(QString::fromUtf8("btnSend"));
        btnSend->setMinimumSize(QSize(100, 100));

        horizontalLayout_3->addWidget(btnSend);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalLayout->setStretch(0, 5);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(4, 3);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\347\275\221\347\273\234\350\260\203\350\257\225\345\212\251\346\211\213\346\234\215\345\212\241\347\253\257-\345\255\246\346\270\243\345\207\272\345\223\201", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\351\200\232\344\277\241\345\215\217\350\256\256", nullptr));
        comboBoxProt->setItemText(0, QCoreApplication::translate("Widget", "TCP", nullptr));
        comboBoxProt->setItemText(1, QCoreApplication::translate("Widget", "UDP", nullptr));

        label_2->setText(QCoreApplication::translate("Widget", "\346\234\215\345\212\241\345\231\250IP\345\234\260\345\235\200", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\347\253\257\345\217\243\345\217\267", nullptr));
        lineEditPort->setText(QCoreApplication::translate("Widget", "8888", nullptr));
        btnStartListen->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213\347\233\221\345\220\254", nullptr));
        btnStopListen->setText(QCoreApplication::translate("Widget", "\345\201\234\346\255\242\347\233\221\345\220\254", nullptr));
        btnLineOut->setText(QCoreApplication::translate("Widget", "\351\200\200\345\207\272", nullptr));
        comboBoxChildren->setItemText(0, QString());

        btnSend->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
