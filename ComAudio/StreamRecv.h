#pragma once

#include <QObject>
#include <QFile>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QTcpSocket>
#include <QByteArray>
#include <QAudioOutput>
#include <QBuffer>
#include "Task.h"

class StreamRecv : public QObject, Task
{
	Q_OBJECT

public:
	StreamRecv(QObject *parent, QTcpSocket*);
	~StreamRecv();

	void stop();


public slots:
	void readBytes();

private:
	QFile outputFile;
	QFile inputFile;
	QTcpSocket* tcp;
	QByteArray data;
	QByteArray * data2;
	QBuffer* buffer;
	QAudioOutput* aOutput;
	bool firstRun;
	QObject* audioParent;
};
