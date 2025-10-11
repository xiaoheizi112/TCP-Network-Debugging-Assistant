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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEditRev;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEditIPAddr;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLineEdit *lineEditPort;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QPushButton *btnConnect;
    QPushButton *btnDiscon;
    QHBoxLayout *horizontalLayout;
    QTextEdit *textEditSend;
    QPushButton *btnSend;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/client.png"), QSize(), QIcon::Normal, QIcon::Off);
        Widget->setWindowIcon(icon);
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 801, 601));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        textEditRev = new QTextEdit(layoutWidget);
        textEditRev->setObjectName(QString::fromUtf8("textEditRev"));

        verticalLayout_2->addWidget(textEditRev);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEditIPAddr = new QLineEdit(layoutWidget);
        lineEditIPAddr->setObjectName(QString::fromUtf8("lineEditIPAddr"));

        horizontalLayout_2->addWidget(lineEditIPAddr);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEditPort = new QLineEdit(layoutWidget);
        lineEditPort->setObjectName(QString::fromUtf8("lineEditPort"));

        horizontalLayout_2->addWidget(lineEditPort);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnConnect = new QPushButton(layoutWidget);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));

        verticalLayout->addWidget(btnConnect);

        btnDiscon = new QPushButton(layoutWidget);
        btnDiscon->setObjectName(QString::fromUtf8("btnDiscon"));

        verticalLayout->addWidget(btnDiscon);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        textEditSend = new QTextEdit(layoutWidget);
        textEditSend->setObjectName(QString::fromUtf8("textEditSend"));

        horizontalLayout->addWidget(textEditSend);

        btnSend = new QPushButton(layoutWidget);
        btnSend->setObjectName(QString::fromUtf8("btnSend"));
        btnSend->setMinimumSize(QSize(80, 80));

        horizontalLayout->addWidget(btnSend);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(0, 3);
        verticalLayout_2->setStretch(1, 2);
        verticalLayout_2->setStretch(2, 2);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\347\275\221\347\273\234\350\260\203\350\257\225\345\212\251\346\211\213\345\256\242\346\210\267\347\253\257-\345\255\246\346\270\243\345\207\272\345\223\201", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\346\234\215\345\212\241\347\253\257IP", nullptr));
        lineEditIPAddr->setText(QCoreApplication::translate("Widget", "192.168.31.158", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\346\234\215\345\212\241\347\253\257\347\253\257\345\217\243", nullptr));
        lineEditPort->setText(QCoreApplication::translate("Widget", "8888", nullptr));
        btnConnect->setText(QCoreApplication::translate("Widget", "\350\277\236\346\216\245", nullptr));
        btnDiscon->setText(QCoreApplication::translate("Widget", "\345\205\263\351\227\255", nullptr));
        btnSend->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
