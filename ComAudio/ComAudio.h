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
#include "ui_ComAudio.h"

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

private:
	enum PlayMode { local, stream, test };

	int initUi(); // initializes UI components

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
};
