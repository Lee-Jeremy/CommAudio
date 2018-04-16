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
#include <QSlider>
#include <QPushButton>
#include <QAbstractItemView>
#include <QThread>

#include "StreamServe.h"
#include "StreamRecv.h"
#include "FileTransfer.h"

#include "TaskManager.h"
#include "ui_ComAudio.h"
#include "windows.h"

class ComAudio : public QMainWindow
{
	Q_OBJECT

public:
	ComAudio(QWidget *parent = Q_NULLPTR);
	~ComAudio();
	void startPlaying(qint64 sizeTotal);
	void feedAudio(QByteArray segment);

	public slots:
	void setDir();
	void selectDir();
	void selectFile();
	void playAudio();
	void setVolume();
	QString getFileList();

	void metaDataChanged();

signals:

	public slots:
	void connectedToServerVoip(QUdpSocket * sock, QTcpSocket *);
	void connectedToServerStream(QTcpSocket * sock);
	void connectedToServerFileTransfer(QTcpSocket * sock);

	void clientConnectedStream(QTcpSocket *);
	void clientConnectedFileTransfer(QTcpSocket *);
	void clientConnectedFileList(QTcpSocket *);
	void clientConnectedVoip(QUdpSocket *, QTcpSocket *);

	void portValueChanged();
	void ipValueChanged();

	void startStream();
	void startVoip();
	void startFileTransfer();

private:
	enum PlayMode { local, stream, test };

	int initUi(); // initializes UI components
	void startServer();

	// NEW audio player ----------------------------
	void setTrackInfo(const QString &info);
	// NEW audio player ----------------------------

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
	PlayMode playMode;
	QSlider *slider;

	// NEW audio player ----------------------------
	QFile* audioFile;
	QByteArray* audioData;
	qint64 pos;
	QDataStream* audioStream;

	QMediaPlaylist *playlist;
	QString trackInfo;
	QString statusInfo;
	// NEW audio player ----------------------------

	const QString PATH_LOCAL_INIT = QDir::currentPath();
	const QStringList FILE_FILTER = QStringList{ "*.wav" };
	const qint64 SIZE_SEGMENT = 1024;
	const int SLIDER_DIVISOR = 10;

	QFile* outputFile;
};
