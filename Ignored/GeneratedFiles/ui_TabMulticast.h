/********************************************************************************
** Form generated from reading UI file 'TabMulticast.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABMULTICAST_H
#define UI_TABMULTICAST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TabMulticast
{
public:
    QWidget *verticalLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_ip;
    QLineEdit *lineEdit_port;
    QPushButton *pushButton_stop;
    QPushButton *pushButton_connect;
    QSpacerItem *horizontalSpacer1;
    QPushButton *pushButton_start;
    QPushButton *pushButton_close;
    QPlainTextEdit *plainTextEdit_monitor;

    void setupUi(QWidget *TabMulticast)
    {
        if (TabMulticast->objectName().isEmpty())
            TabMulticast->setObjectName(QStringLiteral("TabMulticast"));
        TabMulticast->resize(323, 364);
        verticalLayoutWidget = new QWidget(TabMulticast);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 301, 341));
        gridLayout = new QGridLayout(verticalLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_ip = new QLineEdit(verticalLayoutWidget);
        lineEdit_ip->setObjectName(QStringLiteral("lineEdit_ip"));

        gridLayout->addWidget(lineEdit_ip, 2, 0, 1, 1);

        lineEdit_port = new QLineEdit(verticalLayoutWidget);
        lineEdit_port->setObjectName(QStringLiteral("lineEdit_port"));

        gridLayout->addWidget(lineEdit_port, 2, 1, 1, 1);

        pushButton_stop = new QPushButton(verticalLayoutWidget);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));

        gridLayout->addWidget(pushButton_stop, 5, 0, 1, 4);

        pushButton_connect = new QPushButton(verticalLayoutWidget);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        pushButton_connect->setMaximumSize(QSize(70, 16777215));

        gridLayout->addWidget(pushButton_connect, 2, 2, 1, 2);

        horizontalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer1, 0, 2, 1, 1);

        pushButton_start = new QPushButton(verticalLayoutWidget);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));

        gridLayout->addWidget(pushButton_start, 4, 0, 1, 4);

        pushButton_close = new QPushButton(verticalLayoutWidget);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        pushButton_close->setMaximumSize(QSize(25, 16777215));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButton_close->setFont(font);

        gridLayout->addWidget(pushButton_close, 0, 3, 1, 1);

        plainTextEdit_monitor = new QPlainTextEdit(verticalLayoutWidget);
        plainTextEdit_monitor->setObjectName(QStringLiteral("plainTextEdit_monitor"));

        gridLayout->addWidget(plainTextEdit_monitor, 3, 0, 1, 4);

        gridLayout->setColumnStretch(0, 4);

        retranslateUi(TabMulticast);

        QMetaObject::connectSlotsByName(TabMulticast);
    } // setupUi

    void retranslateUi(QWidget *TabMulticast)
    {
        TabMulticast->setWindowTitle(QApplication::translate("TabMulticast", "TabMulticast", nullptr));
        lineEdit_ip->setPlaceholderText(QApplication::translate("TabMulticast", "IP", nullptr));
        lineEdit_port->setInputMask(QString());
        lineEdit_port->setText(QString());
        lineEdit_port->setPlaceholderText(QApplication::translate("TabMulticast", "Port", nullptr));
        pushButton_stop->setText(QApplication::translate("TabMulticast", "Stop", nullptr));
        pushButton_connect->setText(QApplication::translate("TabMulticast", "Connect", nullptr));
        pushButton_start->setText(QApplication::translate("TabMulticast", "Start", nullptr));
        pushButton_close->setText(QApplication::translate("TabMulticast", "X", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TabMulticast: public Ui_TabMulticast {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABMULTICAST_H
