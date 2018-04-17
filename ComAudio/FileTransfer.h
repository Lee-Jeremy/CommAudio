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


class FileTransfer : public QObject, public Task
{
	Q_OBJECT

public:
	FileTransfer(QObject *parent, QTcpSocket* tcp);
	~FileTransfer();


	void setOutputFile(QString path);

	void stop();

	void start();

public slots:
	void readBytes();

private:
	QFile outputFile;
	QString outputPath;
	QTcpSocket* tcp;
	QByteArray data;
};
