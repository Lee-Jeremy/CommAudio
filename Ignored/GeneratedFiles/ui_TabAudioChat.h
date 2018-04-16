/********************************************************************************
** Form generated from reading UI file 'TabAudioChat.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABAUDIOCHAT_H
#define UI_TABAUDIOCHAT_H

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

class Ui_TabAudioChat
{
public:
    QWidget *verticalLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_stop;
    QLineEdit *lineEdit_ip;
    QPushButton *pushButton_connect;
    QLineEdit *lineEdit_port;
    QPushButton *pushButton_close;
    QPushButton *pushButton_start;
    QSpacerItem *horizontalSpacer1;
    QPlainTextEdit *plainTextEdit_monitor;

    void setupUi(QWidget *TabAudioChat)
    {
        if (TabAudioChat->objectName().isEmpty())
            TabAudioChat->setObjectName(QStringLiteral("TabAudioChat"));
        TabAudioChat->resize(322, 361);
        verticalLayoutWidget = new QWidget(TabAudioChat);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 301, 341));
        gridLayout = new QGridLayout(verticalLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_stop = new QPushButton(verticalLayoutWidget);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));

        gridLayout->addWidget(pushButton_stop, 5, 0, 1, 4);

        lineEdit_ip = new QLineEdit(verticalLayoutWidget);
        lineEdit_ip->setObjectName(QStringLiteral("lineEdit_ip"));

        gridLayout->addWidget(lineEdit_ip, 2, 0, 1, 1);

        pushButton_connect = new QPushButton(verticalLayoutWidget);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        pushButton_connect->setMaximumSize(QSize(70, 16777215));

        gridLayout->addWidget(pushButton_connect, 2, 2, 1, 2);

        lineEdit_port = new QLineEdit(verticalLayoutWidget);
        lineEdit_port->setObjectName(QStringLiteral("lineEdit_port"));

        gridLayout->addWidget(lineEdit_port, 2, 1, 1, 1);

        pushButton_close = new QPushButton(verticalLayoutWidget);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        pushButton_close->setMaximumSize(QSize(25, 16777215));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButton_close->setFont(font);

        gridLayout->addWidget(pushButton_close, 0, 3, 1, 1);

        pushButton_start = new QPushButton(verticalLayoutWidget);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));

        gridLayout->addWidget(pushButton_start, 4, 0, 1, 4);

        horizontalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer1, 0, 2, 1, 1);

        plainTextEdit_monitor = new QPlainTextEdit(verticalLayoutWidget);
        plainTextEdit_monitor->setObjectName(QStringLiteral("plainTextEdit_monitor"));

        gridLayout->addWidget(plainTextEdit_monitor, 3, 0, 1, 4);

        gridLayout->setColumnStretch(0, 4);

        retranslateUi(TabAudioChat);

        QMetaObject::connectSlotsByName(TabAudioChat);
    } // setupUi

    void retranslateUi(QWidget *TabAudioChat)
    {
        TabAudioChat->setWindowTitle(QApplication::translate("TabAudioChat", "TabAudioChat", nullptr));
        pushButton_stop->setText(QApplication::translate("TabAudioChat", "Stop", nullptr));
        lineEdit_ip->setPlaceholderText(QApplication::translate("TabAudioChat", "IP", nullptr));
        pushButton_connect->setText(QApplication::translate("TabAudioChat", "Connect", nullptr));
        lineEdit_port->setInputMask(QString());
        lineEdit_port->setText(QString());
        lineEdit_port->setPlaceholderText(QApplication::translate("TabAudioChat", "Port", nullptr));
        pushButton_close->setText(QApplication::translate("TabAudioChat", "X", nullptr));
        pushButton_start->setText(QApplication::translate("TabAudioChat", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TabAudioChat: public Ui_TabAudioChat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABAUDIOCHAT_H
