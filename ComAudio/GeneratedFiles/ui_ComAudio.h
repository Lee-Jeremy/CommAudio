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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
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
        ComAudioClass->resize(616, 577);
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
        ComAudioClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ComAudioClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 616, 21));
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
