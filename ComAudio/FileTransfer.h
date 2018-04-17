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


class FileTransfer : public QObject, Task
{
	Q_OBJECT

public:
	FileTransfer(QObject *parent, QTcpSocket* tcp);
	~FileTransfer();


	void setOutputFile(QString path);

	void stop();

public slots:
	void readBytes();

private:
	QFile outputFile;
	QString outputPath;
	QTcpSocket* tcp;
	QByteArray data;
};
