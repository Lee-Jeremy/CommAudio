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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ComAudio
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
    QAction *actionDevice;
    QAction *actionNetwork;
    QAction *actionExit;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_6;
    QTabWidget *tabWidget_main;
    QWidget *tab_main_taskManager;
    QGridLayout *gridLayout_main_client;
    QGroupBox *groupBox_dir;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_dir_browse;
    QListView *listView_dir_list;
    QLineEdit *lineEdit_dir_path;
    QTabWidget *tabWidget_taskViews;
    QWidget *tab_taskViews_filler1;
    QWidget *tab_taskViews_filler2;
    QGroupBox *groupBox_tasks;
    QGridLayout *gridLayout_taskButtons;
    QPushButton *pushButton_tasks_audioStream;
    QPushButton *pushButton_tasks_fileTransfer;
    QPushButton *pushButton_tasks_audioChat;
    QPushButton *pushButton_tasks_multicast;
    QGridLayout *gridLayout_player;
    QLabel *label_player_title;
    QPushButton *pushButton_player_play;
    QSlider *horizontalSlider_player_progress;
    QLabel *label_player_artist;
    QGraphicsView *graphicsView_player_wave;
    QPushButton *pushButton_player_pause;
    QLCDNumber *lcdNumber_player_passed;
    QLCDNumber *lcdNumber_player_remaining;
    QSlider *horizontalSlider_player_volume;
    QPushButton *pushButton_player_rewind;
    QLabel *label_player_volume;
    QWidget *tab_main_serverMonitor;
    QGridLayout *gridLayout_main_server;
    QLabel *label_main_server_port;
    QLineEdit *lineEdit_main_server_port;
    QPushButton *pushButton_main_server_start;
    QPlainTextEdit *plainTextEdit_main_server_console;
    QListView *listView_main_server_clients;
    QPushButton *pushButton_main_server_stop;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ComAudio)
    {
        if (ComAudio->objectName().isEmpty())
            ComAudio->setObjectName(QStringLiteral("ComAudio"));
        ComAudio->resize(616, 608);
        actionOutput_Device = new QAction(ComAudio);
        actionOutput_Device->setObjectName(QStringLiteral("actionOutput_Device"));
        actionInput_Device = new QAction(ComAudio);
        actionInput_Device->setObjectName(QStringLiteral("actionInput_Device"));
        actionJoin_Multicast = new QAction(ComAudio);
        actionJoin_Multicast->setObjectName(QStringLiteral("actionJoin_Multicast"));
        actionCreate_Multicast = new QAction(ComAudio);
        actionCreate_Multicast->setObjectName(QStringLiteral("actionCreate_Multicast"));
        actionVoice_Call = new QAction(ComAudio);
        actionVoice_Call->setObjectName(QStringLiteral("actionVoice_Call"));
        actionSet_Upload_Folder = new QAction(ComAudio);
        actionSet_Upload_Folder->setObjectName(QStringLiteral("actionSet_Upload_Folder"));
        actionDownload_from_Host = new QAction(ComAudio);
        actionDownload_from_Host->setObjectName(QStringLiteral("actionDownload_from_Host"));
        actionPlay_Audio_File = new QAction(ComAudio);
        actionPlay_Audio_File->setObjectName(QStringLiteral("actionPlay_Audio_File"));
        actionDevice = new QAction(ComAudio);
        actionDevice->setObjectName(QStringLiteral("actionDevice"));
        actionNetwork = new QAction(ComAudio);
        actionNetwork->setObjectName(QStringLiteral("actionNetwork"));
        actionExit = new QAction(ComAudio);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(ComAudio);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_6 = new QVBoxLayout(centralWidget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        tabWidget_main = new QTabWidget(centralWidget);
        tabWidget_main->setObjectName(QStringLiteral("tabWidget_main"));
        tab_main_taskManager = new QWidget();
        tab_main_taskManager->setObjectName(QStringLiteral("tab_main_taskManager"));
        gridLayout_main_client = new QGridLayout(tab_main_taskManager);
        gridLayout_main_client->setSpacing(6);
        gridLayout_main_client->setContentsMargins(11, 11, 11, 11);
        gridLayout_main_client->setObjectName(QStringLiteral("gridLayout_main_client"));
        groupBox_dir = new QGroupBox(tab_main_taskManager);
        groupBox_dir->setObjectName(QStringLiteral("groupBox_dir"));
        gridLayout_3 = new QGridLayout(groupBox_dir);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        pushButton_dir_browse = new QPushButton(groupBox_dir);
        pushButton_dir_browse->setObjectName(QStringLiteral("pushButton_dir_browse"));
        pushButton_dir_browse->setMaximumSize(QSize(65, 16777215));

        gridLayout_3->addWidget(pushButton_dir_browse, 0, 1, 1, 1);

        listView_dir_list = new QListView(groupBox_dir);
        listView_dir_list->setObjectName(QStringLiteral("listView_dir_list"));

        gridLayout_3->addWidget(listView_dir_list, 1, 0, 1, 2);

        lineEdit_dir_path = new QLineEdit(groupBox_dir);
        lineEdit_dir_path->setObjectName(QStringLiteral("lineEdit_dir_path"));

        gridLayout_3->addWidget(lineEdit_dir_path, 0, 0, 1, 1);

        gridLayout_3->setColumnStretch(0, 8);
        gridLayout_3->setColumnStretch(1, 2);

        gridLayout_main_client->addWidget(groupBox_dir, 1, 0, 1, 1);

        tabWidget_taskViews = new QTabWidget(tab_main_taskManager);
        tabWidget_taskViews->setObjectName(QStringLiteral("tabWidget_taskViews"));
        tab_taskViews_filler1 = new QWidget();
        tab_taskViews_filler1->setObjectName(QStringLiteral("tab_taskViews_filler1"));
        tabWidget_taskViews->addTab(tab_taskViews_filler1, QString());
        tab_taskViews_filler2 = new QWidget();
        tab_taskViews_filler2->setObjectName(QStringLiteral("tab_taskViews_filler2"));
        tabWidget_taskViews->addTab(tab_taskViews_filler2, QString());

        gridLayout_main_client->addWidget(tabWidget_taskViews, 0, 1, 2, 1);

        groupBox_tasks = new QGroupBox(tab_main_taskManager);
        groupBox_tasks->setObjectName(QStringLiteral("groupBox_tasks"));
        gridLayout_taskButtons = new QGridLayout(groupBox_tasks);
        gridLayout_taskButtons->setSpacing(6);
        gridLayout_taskButtons->setContentsMargins(11, 11, 11, 11);
        gridLayout_taskButtons->setObjectName(QStringLiteral("gridLayout_taskButtons"));
        pushButton_tasks_audioStream = new QPushButton(groupBox_tasks);
        pushButton_tasks_audioStream->setObjectName(QStringLiteral("pushButton_tasks_audioStream"));

        gridLayout_taskButtons->addWidget(pushButton_tasks_audioStream, 1, 0, 1, 1);

        pushButton_tasks_fileTransfer = new QPushButton(groupBox_tasks);
        pushButton_tasks_fileTransfer->setObjectName(QStringLiteral("pushButton_tasks_fileTransfer"));

        gridLayout_taskButtons->addWidget(pushButton_tasks_fileTransfer, 1, 1, 1, 1);

        pushButton_tasks_audioChat = new QPushButton(groupBox_tasks);
        pushButton_tasks_audioChat->setObjectName(QStringLiteral("pushButton_tasks_audioChat"));

        gridLayout_taskButtons->addWidget(pushButton_tasks_audioChat, 2, 0, 1, 1);

        pushButton_tasks_multicast = new QPushButton(groupBox_tasks);
        pushButton_tasks_multicast->setObjectName(QStringLiteral("pushButton_tasks_multicast"));

        gridLayout_taskButtons->addWidget(pushButton_tasks_multicast, 2, 1, 1, 1);


        gridLayout_main_client->addWidget(groupBox_tasks, 0, 0, 1, 1);

        gridLayout_player = new QGridLayout();
        gridLayout_player->setSpacing(6);
        gridLayout_player->setObjectName(QStringLiteral("gridLayout_player"));
        label_player_title = new QLabel(tab_main_taskManager);
        label_player_title->setObjectName(QStringLiteral("label_player_title"));

        gridLayout_player->addWidget(label_player_title, 1, 0, 1, 1);

        pushButton_player_play = new QPushButton(tab_main_taskManager);
        pushButton_player_play->setObjectName(QStringLiteral("pushButton_player_play"));

        gridLayout_player->addWidget(pushButton_player_play, 1, 2, 1, 1);

        horizontalSlider_player_progress = new QSlider(tab_main_taskManager);
        horizontalSlider_player_progress->setObjectName(QStringLiteral("horizontalSlider_player_progress"));
        horizontalSlider_player_progress->setOrientation(Qt::Horizontal);
        horizontalSlider_player_progress->setInvertedAppearance(false);
        horizontalSlider_player_progress->setInvertedControls(false);

        gridLayout_player->addWidget(horizontalSlider_player_progress, 20, 1, 1, 3);

        label_player_artist = new QLabel(tab_main_taskManager);
        label_player_artist->setObjectName(QStringLiteral("label_player_artist"));

        gridLayout_player->addWidget(label_player_artist, 0, 0, 1, 1);

        graphicsView_player_wave = new QGraphicsView(tab_main_taskManager);
        graphicsView_player_wave->setObjectName(QStringLiteral("graphicsView_player_wave"));
        graphicsView_player_wave->setMaximumSize(QSize(16777215, 20));
        graphicsView_player_wave->setInteractive(false);

        gridLayout_player->addWidget(graphicsView_player_wave, 0, 1, 1, 3);

        pushButton_player_pause = new QPushButton(tab_main_taskManager);
        pushButton_player_pause->setObjectName(QStringLiteral("pushButton_player_pause"));

        gridLayout_player->addWidget(pushButton_player_pause, 1, 3, 1, 1);

        lcdNumber_player_passed = new QLCDNumber(tab_main_taskManager);
        lcdNumber_player_passed->setObjectName(QStringLiteral("lcdNumber_player_passed"));

        gridLayout_player->addWidget(lcdNumber_player_passed, 20, 0, 1, 1);

        lcdNumber_player_remaining = new QLCDNumber(tab_main_taskManager);
        lcdNumber_player_remaining->setObjectName(QStringLiteral("lcdNumber_player_remaining"));

        gridLayout_player->addWidget(lcdNumber_player_remaining, 20, 4, 1, 1);

        horizontalSlider_player_volume = new QSlider(tab_main_taskManager);
        horizontalSlider_player_volume->setObjectName(QStringLiteral("horizontalSlider_player_volume"));
        horizontalSlider_player_volume->setOrientation(Qt::Horizontal);
        horizontalSlider_player_volume->setTickPosition(QSlider::TicksBelow);
        horizontalSlider_player_volume->setTickInterval(5);

        gridLayout_player->addWidget(horizontalSlider_player_volume, 1, 4, 1, 1);

        pushButton_player_rewind = new QPushButton(tab_main_taskManager);
        pushButton_player_rewind->setObjectName(QStringLiteral("pushButton_player_rewind"));

        gridLayout_player->addWidget(pushButton_player_rewind, 1, 1, 1, 1);

        label_player_volume = new QLabel(tab_main_taskManager);
        label_player_volume->setObjectName(QStringLiteral("label_player_volume"));

        gridLayout_player->addWidget(label_player_volume, 0, 4, 1, 1);

        gridLayout_player->setColumnStretch(0, 2);
        gridLayout_player->setColumnStretch(1, 2);
        gridLayout_player->setColumnStretch(2, 2);
        gridLayout_player->setColumnStretch(3, 2);
        gridLayout_player->setColumnStretch(4, 2);

        gridLayout_main_client->addLayout(gridLayout_player, 2, 0, 1, 2);

        gridLayout_main_client->setRowStretch(0, 2);
        gridLayout_main_client->setRowStretch(1, 6);
        gridLayout_main_client->setRowStretch(2, 2);
        gridLayout_main_client->setColumnStretch(0, 4);
        gridLayout_main_client->setColumnStretch(1, 6);
        tabWidget_main->addTab(tab_main_taskManager, QString());
        tab_main_serverMonitor = new QWidget();
        tab_main_serverMonitor->setObjectName(QStringLiteral("tab_main_serverMonitor"));
        gridLayout_main_server = new QGridLayout(tab_main_serverMonitor);
        gridLayout_main_server->setSpacing(6);
        gridLayout_main_server->setContentsMargins(11, 11, 11, 11);
        gridLayout_main_server->setObjectName(QStringLiteral("gridLayout_main_server"));
        label_main_server_port = new QLabel(tab_main_serverMonitor);
        label_main_server_port->setObjectName(QStringLiteral("label_main_server_port"));
        label_main_server_port->setMaximumSize(QSize(20, 16777215));

        gridLayout_main_server->addWidget(label_main_server_port, 0, 0, 1, 1);

        lineEdit_main_server_port = new QLineEdit(tab_main_serverMonitor);
        lineEdit_main_server_port->setObjectName(QStringLiteral("lineEdit_main_server_port"));
        lineEdit_main_server_port->setMaximumSize(QSize(60, 16777215));

        gridLayout_main_server->addWidget(lineEdit_main_server_port, 0, 1, 1, 1);

        pushButton_main_server_start = new QPushButton(tab_main_serverMonitor);
        pushButton_main_server_start->setObjectName(QStringLiteral("pushButton_main_server_start"));
        pushButton_main_server_start->setMaximumSize(QSize(50, 16777215));

        gridLayout_main_server->addWidget(pushButton_main_server_start, 0, 2, 1, 1);

        plainTextEdit_main_server_console = new QPlainTextEdit(tab_main_serverMonitor);
        plainTextEdit_main_server_console->setObjectName(QStringLiteral("plainTextEdit_main_server_console"));

        gridLayout_main_server->addWidget(plainTextEdit_main_server_console, 1, 4, 1, 1);

        listView_main_server_clients = new QListView(tab_main_serverMonitor);
        listView_main_server_clients->setObjectName(QStringLiteral("listView_main_server_clients"));

        gridLayout_main_server->addWidget(listView_main_server_clients, 1, 0, 1, 4);

        pushButton_main_server_stop = new QPushButton(tab_main_serverMonitor);
        pushButton_main_server_stop->setObjectName(QStringLiteral("pushButton_main_server_stop"));
        pushButton_main_server_stop->setMaximumSize(QSize(50, 16777215));

        gridLayout_main_server->addWidget(pushButton_main_server_stop, 0, 3, 1, 1);

        gridLayout_main_server->setColumnStretch(0, 1);
        gridLayout_main_server->setColumnStretch(1, 1);
        gridLayout_main_server->setColumnStretch(2, 1);
        gridLayout_main_server->setColumnStretch(3, 1);
        gridLayout_main_server->setColumnStretch(4, 6);
        tabWidget_main->addTab(tab_main_serverMonitor, QString());

        verticalLayout_6->addWidget(tabWidget_main);

        ComAudio->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ComAudio);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 616, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        ComAudio->setMenuBar(menuBar);
        statusBar = new QStatusBar(ComAudio);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ComAudio->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionDevice);
        menuFile->addAction(actionNetwork);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(ComAudio);

        tabWidget_main->setCurrentIndex(0);
        tabWidget_taskViews->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ComAudio);
    } // setupUi

    void retranslateUi(QMainWindow *ComAudio)
    {
        ComAudio->setWindowTitle(QApplication::translate("ComAudio", "CommAudio", nullptr));
        actionOutput_Device->setText(QApplication::translate("ComAudio", "Output Device", nullptr));
        actionInput_Device->setText(QApplication::translate("ComAudio", "Input Device", nullptr));
        actionJoin_Multicast->setText(QApplication::translate("ComAudio", "Join Multicast", nullptr));
        actionCreate_Multicast->setText(QApplication::translate("ComAudio", "Create Multicast", nullptr));
        actionVoice_Call->setText(QApplication::translate("ComAudio", "Voice Call", nullptr));
        actionSet_Upload_Folder->setText(QApplication::translate("ComAudio", "Set Upload Folder", nullptr));
        actionDownload_from_Host->setText(QApplication::translate("ComAudio", "Download from Host", nullptr));
        actionPlay_Audio_File->setText(QApplication::translate("ComAudio", "Play Audio File", nullptr));
        actionDevice->setText(QApplication::translate("ComAudio", "Device", nullptr));
        actionNetwork->setText(QApplication::translate("ComAudio", "Network", nullptr));
        actionExit->setText(QApplication::translate("ComAudio", "Exit", nullptr));
        groupBox_dir->setTitle(QApplication::translate("ComAudio", "Local Directory", nullptr));
        pushButton_dir_browse->setText(QApplication::translate("ComAudio", "Browse", nullptr));
        lineEdit_dir_path->setText(QString());
        tabWidget_taskViews->setTabText(tabWidget_taskViews->indexOf(tab_taskViews_filler1), QApplication::translate("ComAudio", "Task 1", nullptr));
        tabWidget_taskViews->setTabText(tabWidget_taskViews->indexOf(tab_taskViews_filler2), QApplication::translate("ComAudio", "Task 2", nullptr));
        groupBox_tasks->setTitle(QApplication::translate("ComAudio", "Tasks", nullptr));
        pushButton_tasks_audioStream->setText(QApplication::translate("ComAudio", "Audio Stream", nullptr));
        pushButton_tasks_fileTransfer->setText(QApplication::translate("ComAudio", "File Transfer", nullptr));
        pushButton_tasks_audioChat->setText(QApplication::translate("ComAudio", "Audio Chat", nullptr));
        pushButton_tasks_multicast->setText(QApplication::translate("ComAudio", "Multicast", nullptr));
        label_player_title->setText(QString());
        pushButton_player_play->setText(QApplication::translate("ComAudio", "Play", nullptr));
        label_player_artist->setText(QString());
        pushButton_player_pause->setText(QApplication::translate("ComAudio", "Pause", nullptr));
        pushButton_player_rewind->setText(QApplication::translate("ComAudio", "Rewind", nullptr));
        label_player_volume->setText(QString());
        tabWidget_main->setTabText(tabWidget_main->indexOf(tab_main_taskManager), QApplication::translate("ComAudio", "Task Manager", nullptr));
#ifndef QT_NO_ACCESSIBILITY
        tab_main_serverMonitor->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        label_main_server_port->setText(QApplication::translate("ComAudio", "Port", nullptr));
        pushButton_main_server_start->setText(QApplication::translate("ComAudio", "Start", nullptr));
        pushButton_main_server_stop->setText(QApplication::translate("ComAudio", "Stop", nullptr));
        tabWidget_main->setTabText(tabWidget_main->indexOf(tab_main_serverMonitor), QApplication::translate("ComAudio", "Server Monitor", nullptr));
        menuFile->setTitle(QApplication::translate("ComAudio", "File", nullptr));
        menuAbout->setTitle(QApplication::translate("ComAudio", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ComAudio: public Ui_ComAudio {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMAUDIO_H
