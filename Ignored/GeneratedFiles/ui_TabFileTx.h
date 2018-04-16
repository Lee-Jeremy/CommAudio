/********************************************************************************
** Form generated from reading UI file 'TabFileTx.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABFILETX_H
#define UI_TABFILETX_H

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

class Ui_TabFileTx
{
public:
    QWidget *verticalLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_port;
    QLineEdit *lineEdit_ip;
    QPushButton *pushButton_download;
    QPushButton *pushButton_close;
    QListView *listView_files;
    QSpacerItem *horizontalSpacer1;
    QPushButton *pushButton_connect;

    void setupUi(QWidget *TabFileTx)
    {
        if (TabFileTx->objectName().isEmpty())
            TabFileTx->setObjectName(QStringLiteral("TabFileTx"));
        TabFileTx->resize(319, 360);
        verticalLayoutWidget = new QWidget(TabFileTx);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 301, 341));
        gridLayout = new QGridLayout(verticalLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_port = new QLineEdit(verticalLayoutWidget);
        lineEdit_port->setObjectName(QStringLiteral("lineEdit_port"));

        gridLayout->addWidget(lineEdit_port, 2, 1, 1, 1);

        lineEdit_ip = new QLineEdit(verticalLayoutWidget);
        lineEdit_ip->setObjectName(QStringLiteral("lineEdit_ip"));

        gridLayout->addWidget(lineEdit_ip, 2, 0, 1, 1);

        pushButton_download = new QPushButton(verticalLayoutWidget);
        pushButton_download->setObjectName(QStringLiteral("pushButton_download"));

        gridLayout->addWidget(pushButton_download, 4, 0, 1, 4);

        pushButton_close = new QPushButton(verticalLayoutWidget);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        pushButton_close->setMaximumSize(QSize(25, 16777215));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButton_close->setFont(font);

        gridLayout->addWidget(pushButton_close, 0, 3, 1, 1);

        listView_files = new QListView(verticalLayoutWidget);
        listView_files->setObjectName(QStringLiteral("listView_files"));

        gridLayout->addWidget(listView_files, 3, 0, 1, 4);

        horizontalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer1, 0, 2, 1, 1);

        pushButton_connect = new QPushButton(verticalLayoutWidget);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        pushButton_connect->setMaximumSize(QSize(70, 16777215));

        gridLayout->addWidget(pushButton_connect, 2, 2, 1, 2);

        gridLayout->setColumnStretch(0, 4);
        gridLayout->setColumnStretch(1, 2);
        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnStretch(3, 1);

        retranslateUi(TabFileTx);

        QMetaObject::connectSlotsByName(TabFileTx);
    } // setupUi

    void retranslateUi(QWidget *TabFileTx)
    {
        TabFileTx->setWindowTitle(QApplication::translate("TabFileTx", "TabFileTx", nullptr));
        lineEdit_port->setInputMask(QString());
        lineEdit_port->setText(QString());
        lineEdit_port->setPlaceholderText(QApplication::translate("TabFileTx", "Port", nullptr));
        lineEdit_ip->setPlaceholderText(QApplication::translate("TabFileTx", "IP", nullptr));
        pushButton_download->setText(QApplication::translate("TabFileTx", "Download", nullptr));
        pushButton_close->setText(QApplication::translate("TabFileTx", "X", nullptr));
        pushButton_connect->setText(QApplication::translate("TabFileTx", "Connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TabFileTx: public Ui_TabFileTx {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABFILETX_H
