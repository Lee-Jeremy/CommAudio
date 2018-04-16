/********************************************************************************
** Form generated from reading UI file 'TabAudioStream.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABAUDIOSTREAM_H
#define UI_TABAUDIOSTREAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TabAudioStream
{
public:
    QWidget *verticalLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_stop;
    QPushButton *pushButton_close;
    QPushButton *pushButton_start;
    QLineEdit *lineEdit_ip;
    QLineEdit *lineEdit_port;
    QPushButton *pushButton_connect;
    QSpacerItem *horizontalSpacer1;
    QListView *listView_files;

    void setupUi(QWidget *TabAudioStream)
    {
        if (TabAudioStream->objectName().isEmpty())
            TabAudioStream->setObjectName(QStringLiteral("TabAudioStream"));
        TabAudioStream->resize(320, 360);
        verticalLayoutWidget = new QWidget(TabAudioStream);
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

        lineEdit_ip = new QLineEdit(verticalLayoutWidget);
        lineEdit_ip->setObjectName(QStringLiteral("lineEdit_ip"));

        gridLayout->addWidget(lineEdit_ip, 2, 0, 1, 1);

        lineEdit_port = new QLineEdit(verticalLayoutWidget);
        lineEdit_port->setObjectName(QStringLiteral("lineEdit_port"));

        gridLayout->addWidget(lineEdit_port, 2, 1, 1, 1);

        pushButton_connect = new QPushButton(verticalLayoutWidget);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        pushButton_connect->setMaximumSize(QSize(70, 16777215));

        gridLayout->addWidget(pushButton_connect, 2, 2, 1, 2);

        horizontalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer1, 0, 2, 1, 1);

        listView_files = new QListView(verticalLayoutWidget);
        listView_files->setObjectName(QStringLiteral("listView_files"));

        gridLayout->addWidget(listView_files, 3, 0, 1, 4);

        gridLayout->setColumnStretch(0, 4);

        retranslateUi(TabAudioStream);

        QMetaObject::connectSlotsByName(TabAudioStream);
    } // setupUi

    void retranslateUi(QWidget *TabAudioStream)
    {
        TabAudioStream->setWindowTitle(QApplication::translate("TabAudioStream", "TabAudioStream", nullptr));
        pushButton_stop->setText(QApplication::translate("TabAudioStream", "Stop", nullptr));
        pushButton_close->setText(QApplication::translate("TabAudioStream", "X", nullptr));
        pushButton_start->setText(QApplication::translate("TabAudioStream", "Start", nullptr));
        lineEdit_ip->setPlaceholderText(QApplication::translate("TabAudioStream", "IP", nullptr));
        lineEdit_port->setInputMask(QString());
        lineEdit_port->setText(QString());
        lineEdit_port->setPlaceholderText(QApplication::translate("TabAudioStream", "Port", nullptr));
        pushButton_connect->setText(QApplication::translate("TabAudioStream", "Connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TabAudioStream: public Ui_TabAudioStream {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABAUDIOSTREAM_H
