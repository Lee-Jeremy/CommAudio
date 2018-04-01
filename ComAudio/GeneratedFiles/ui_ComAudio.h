/********************************************************************************
** Form generated from reading UI file 'ComAudio.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMAUDIO_H
#define UI_COMAUDIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ComAudioClass
{
public:
    QAction *actionOutput_Device;
    QAction *actionInput_Device;
    QAction *actionJoin_Multicast;
    QAction *actionCreate_Multicast;
    QAction *actionVoice_Call;
    QAction *actionSet_Upload_Folder;
    QAction *actionDownload_from_Host;
    QAction *actionPlay_Audio_File;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QTreeWidget *treeWidget;
    QGroupBox *selectTaskGroupBox;
    QComboBox *comboBox;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QGroupBox *groupBox_2;
    QMenuBar *menuBar;
    QMenu *menuAudio_Settings;
    QMenu *menuMulticast;
    QMenu *menuCall;
    QMenu *menuFile_Transfer;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ComAudioClass)
    {
        if (ComAudioClass->objectName().isEmpty())
            ComAudioClass->setObjectName(QStringLiteral("ComAudioClass"));
        ComAudioClass->resize(787, 674);
        actionOutput_Device = new QAction(ComAudioClass);
        actionOutput_Device->setObjectName(QStringLiteral("actionOutput_Device"));
        actionInput_Device = new QAction(ComAudioClass);
        actionInput_Device->setObjectName(QStringLiteral("actionInput_Device"));
        actionJoin_Multicast = new QAction(ComAudioClass);
        actionJoin_Multicast->setObjectName(QStringLiteral("actionJoin_Multicast"));
        actionCreate_Multicast = new QAction(ComAudioClass);
        actionCreate_Multicast->setObjectName(QStringLiteral("actionCreate_Multicast"));
        actionVoice_Call = new QAction(ComAudioClass);
        actionVoice_Call->setObjectName(QStringLiteral("actionVoice_Call"));
        actionSet_Upload_Folder = new QAction(ComAudioClass);
        actionSet_Upload_Folder->setObjectName(QStringLiteral("actionSet_Upload_Folder"));
        actionDownload_from_Host = new QAction(ComAudioClass);
        actionDownload_from_Host->setObjectName(QStringLiteral("actionDownload_from_Host"));
        actionPlay_Audio_File = new QAction(ComAudioClass);
        actionPlay_Audio_File->setObjectName(QStringLiteral("actionPlay_Audio_File"));
        centralWidget = new QWidget(ComAudioClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(groupBox, 2, 0, 1, 1);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lineEdit = new QLineEdit(groupBox_3);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        scrollArea = new QScrollArea(groupBox_3);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 351, 384));
        treeWidget = new QTreeWidget(scrollAreaWidgetContents);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(10, 10, 341, 371));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        gridLayout_3->addWidget(groupBox_3, 1, 0, 1, 1);

        selectTaskGroupBox = new QGroupBox(centralWidget);
        selectTaskGroupBox->setObjectName(QStringLiteral("selectTaskGroupBox"));
        selectTaskGroupBox->setMinimumSize(QSize(0, 100));
        comboBox = new QComboBox(selectTaskGroupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(50, 10, 73, 22));

        gridLayout_3->addWidget(selectTaskGroupBox, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout_3);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));

        gridLayout_2->addWidget(groupBox_2, 1, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);

        ComAudioClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ComAudioClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 787, 26));
        menuAudio_Settings = new QMenu(menuBar);
        menuAudio_Settings->setObjectName(QStringLiteral("menuAudio_Settings"));
        menuMulticast = new QMenu(menuBar);
        menuMulticast->setObjectName(QStringLiteral("menuMulticast"));
        menuCall = new QMenu(menuBar);
        menuCall->setObjectName(QStringLiteral("menuCall"));
        menuFile_Transfer = new QMenu(menuBar);
        menuFile_Transfer->setObjectName(QStringLiteral("menuFile_Transfer"));
        ComAudioClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ComAudioClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ComAudioClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ComAudioClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ComAudioClass->setStatusBar(statusBar);

        menuBar->addAction(menuAudio_Settings->menuAction());
        menuBar->addAction(menuMulticast->menuAction());
        menuBar->addAction(menuCall->menuAction());
        menuBar->addAction(menuFile_Transfer->menuAction());
        menuAudio_Settings->addAction(actionOutput_Device);
        menuAudio_Settings->addAction(actionInput_Device);
        menuMulticast->addAction(actionJoin_Multicast);
        menuMulticast->addAction(actionCreate_Multicast);
        menuCall->addAction(actionVoice_Call);
        menuFile_Transfer->addAction(actionSet_Upload_Folder);
        menuFile_Transfer->addAction(actionDownload_from_Host);
        menuFile_Transfer->addAction(actionPlay_Audio_File);

        retranslateUi(ComAudioClass);

        QMetaObject::connectSlotsByName(ComAudioClass);
    } // setupUi

    void retranslateUi(QMainWindow *ComAudioClass)
    {
        ComAudioClass->setWindowTitle(QApplication::translate("ComAudioClass", "ComAudio", nullptr));
        actionOutput_Device->setText(QApplication::translate("ComAudioClass", "Output Device", nullptr));
        actionInput_Device->setText(QApplication::translate("ComAudioClass", "Input Device", nullptr));
        actionJoin_Multicast->setText(QApplication::translate("ComAudioClass", "Join Multicast", nullptr));
        actionCreate_Multicast->setText(QApplication::translate("ComAudioClass", "Create Multicast", nullptr));
        actionVoice_Call->setText(QApplication::translate("ComAudioClass", "Voice Call", nullptr));
        actionSet_Upload_Folder->setText(QApplication::translate("ComAudioClass", "Set Upload Folder", nullptr));
        actionDownload_from_Host->setText(QApplication::translate("ComAudioClass", "Download from Host", nullptr));
        actionPlay_Audio_File->setText(QApplication::translate("ComAudioClass", "Play Audio File", nullptr));
        groupBox->setTitle(QApplication::translate("ComAudioClass", "GroupBox", nullptr));
        groupBox_3->setTitle(QApplication::translate("ComAudioClass", "GroupBox", nullptr));
        selectTaskGroupBox->setTitle(QApplication::translate("ComAudioClass", "GroupBox", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ComAudioClass", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ComAudioClass", "Tab 2", nullptr));
        groupBox_2->setTitle(QApplication::translate("ComAudioClass", "GroupBox", nullptr));
        menuAudio_Settings->setTitle(QApplication::translate("ComAudioClass", "Audio Settings", nullptr));
        menuMulticast->setTitle(QApplication::translate("ComAudioClass", "Multicast", nullptr));
        menuCall->setTitle(QApplication::translate("ComAudioClass", "Call", nullptr));
        menuFile_Transfer->setTitle(QApplication::translate("ComAudioClass", "File Transfer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ComAudioClass: public Ui_ComAudioClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMAUDIO_H
