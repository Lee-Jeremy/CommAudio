#pragma once
#include <QAudioOutput>
#include <QByteArray>
#include <QIODevice>
#include <QObject>
#include <QTcpSocket>
#include <QMainWindow>
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
	TCPTask(int task);
	~TCPTask();
	int connect();
	int requestFile(QString filename);
	int transmit(QString filename, QMainWindow* ptr, QAudioOutput* ao);
	int receive();
	int complete();
	int handleMetadata(QString mdata);

public slots:
	void handleError();


private:
	QTcpSocket*		mSocket;
	QBuffer*		mBuffer;
	QByteArray*		mByteArray;
	CircBuffer*		mCircBuffer;
	metadata*		metadata;
	QString*		fileList;
	QFile*			file;
	//QAudioOutput*	ao;

	int mTask;
	
};