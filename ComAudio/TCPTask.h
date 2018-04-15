#pragma once
#include <QAudioOutput>
#include <QByteArray>
#include <QIODevice>
#include <QObject>
#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <stdlib.h>
#include "CircBuffer.h"
#include "ComAudio.h"

#define  TRANSFER		5
#define  RX_STREAM		6
#define	 RX_TRANSFER	7

typedef struct metadata
{
	QString filename;
	QString artist;
	QString album;
	QString genre;
	QString encoding;
	float filesize;
	int bitrate;
	int sampleRate;
	int duration;
};

class TCPTask
{
public:
	TCPTask(int task, ComAudio* parent);
	~TCPTask();
	int connect(QString& address, quint16 port);
	int requestFile(QString filename);
	int transmit(QString filename, QMainWindow* ptr, QAudioOutput* ao);
	int receive();
	int complete();
	int handleMetadata(QString mdata);

public slots:


private:
	ComAudio *		mParent;
	QTcpSocket*		mSocket;
	QBuffer*		mBuffer;
	QByteArray*		mByteArray;
	CircBuffer*		mCircBuffer;
	metadata*		metadata;
	QStringList 	fileList;
	QFile*			file;

	int mTask;
	
};