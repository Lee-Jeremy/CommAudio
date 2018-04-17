#pragma once

#include <QtWidgets/QMainWindow>
#include <QDialog>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QByteArray>
#include <QBuffer>
#include <QMediaPlaylist>
#include <QMediaMetaData>
#include <QUdpSocket>
#include <QLineEdit>
#include <QInputDialog>
#include <QSlider>

#include "TabAudioChat.h"
#include "TabAudioStream.h"
#include "TabFileTx.h"
#include "TabMulticast.h"

#include <QAudioOutput>
#include <QAudioInput>

#include <QPushButton>
#include <QAbstractItemView>
#include <QThread>
#include <QStringListModel>

#include "StreamServe.h"
#include "StreamRecv.h"
#include "FileTransfer.h"

#include "TaskManager.h"
#include "UDPTask.h"
#include <QDebug>
#include "ui_ComAudio.h"
#include "windows.h"

namespace PlayMode
{
	enum Type { local, stream, test };
}

class ComAudio : public QMainWindow
{
	Q_OBJECT

public:
	ComAudio(QWidget *parent = Q_NULLPTR);
	~ComAudio();

	// audio player
	void startPlaying(qint64 sizeTotal);
	void feedAudio(QByteArray segment);

	QString ipAddr;
	short clientPort;

public slots:
	// file browser
	void setDir();
	void selectDir();
	void selectFile();

	// audio player
	void playAudio();
	void setVolume();
	void metaDataChanged();

	// task tabs
	// General
	void initTab(Task::Type task);
	void closeTab(QWidget* tab);
	void startServer();
	void serverPortValueChanged();

	// File transfer
	void initTabFileTx();
	QString getFileList();

	// Audio stream
	void initTabAudioStream();

	// Audio chat
	void initTabAudioChat();

	void connectedToServerVoip(QUdpSocket * sock, QTcpSocket *);
	void connectedToServerStream(QTcpSocket * sock);
	void connectedToServerFileList(QTcpSocket * sock);
	void connectedToServerStreamFileList(QTcpSocket * sock);
	void connectedToServerFileTx(QTcpSocket * sock);

	void clientConnectedStream(QTcpSocket *);
	void clientConnectedFileList(QTcpSocket *);
	void clientConnectedStreamFileList(QTcpSocket *);
	void clientConnectedFileTx(QTcpSocket *);
	void clientConnectedVoip(QUdpSocket *, QTcpSocket *);


	void startStream();
	void startVoip();

	void startFileList();
	void startStreamFileList();
	void startFileTx();


	void stopCurrentTask();

	// Multicast
	void initTabMulticast();
	
	void setIp(const QString&);
	void setPort(const QString&);

	void startMulticastTx();
	void startMulticastRx();


private:
	int initUi(); // initializes UI components
	void setTrackInfo(const QString &info);

	Ui::ComAudio *ui;

	// file browser
	QFileSystemModel *dirModel;
	QFileSystemModel *fileModel;
	QString fileListString;
	QString pathLocal;
	QString pathFile;

	short serverPort;


	QAudioOutput*	mAudioOutput;
	QAudioInput*	mAudioInput;
	QAudioFormat*	mFormat;

	TaskManager * taskManager;
	UDPTask* serverVoip;
	UDPTask* clientVoip;


	// audio player
	QMediaPlayer *player;
	PlayMode::Type playMode;
	QSlider *slider;
	QFile* audioFile;
	QByteArray* audioData;
	qint64 pos;
	QDataStream* audioStream;
	QMediaPlaylist *playlist;
	QString trackInfo;
	QString statusInfo;

	QWidget* fileSelectionTab;


	void ComAudio::debug(QString str);

	// constants

	// file Tx
	QStringListModel *fileListModel;
	QString fileToRecv;


	const QString PATH_LOCAL_INIT = QDir::currentPath();
	const QStringList FILE_FILTER = QStringList{ "*.wav" };
	const qint64 SIZE_SEGMENT = 1024;
	const int SLIDER_DIVISOR = 10;

	Task* currentTask;
	QFile* outputFile;

};
