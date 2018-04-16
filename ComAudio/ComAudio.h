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
#include "TaskManager.h"
#include "ui_ComAudio.h"
#include "windows.h"

namespace Task
{
	enum Type { fileTx, stream, chat, multicast };
}

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

	// File transfer
	void initTabFileTx();
	QString getFileList();

	// Audio stream
	void initTabAudioStream();

	// Audio chat
	void initTabAudioChat();
	void connectedToServerVoip(QUdpSocket * sock, QTcpSocket *);
	void connectedToServerStream(QTcpSocket * sock);
	void connectedToServerFileTransfer(QTcpSocket * sock);

	void clientConnectedStream(QTcpSocket * );
	void clientConnectedFileTransfer(QTcpSocket * );
	void clientConnectedVoip(QUdpSocket *, QTcpSocket *);

	void portValueChanged();
	void ipValueChanged();

	void startStream();
	void startVoip();
	void startFileTransfer();

	// Multicast
	void initTabMulticast();

signals:

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
	short port;
	QString ipAddr;

	TaskManager * taskManager;

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

	void ComAudio::debug(QString str);

	// constants
	const QString PATH_LOCAL_INIT = QDir::currentPath();
	const QStringList FILE_FILTER = QStringList{ "*.wav" };
	const qint64 SIZE_SEGMENT = 1024;
	const int SLIDER_DIVISOR = 10;
};
