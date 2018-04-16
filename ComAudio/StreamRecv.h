#pragma once

#include <QObject>
#include <QFile>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QTcpSocket>
#include <QByteArray>
#include <QAudioOutput>

class StreamRecv : public QObject
{
	Q_OBJECT

public:
	StreamRecv(QObject *parent, QTcpSocket*);
	~StreamRecv();

	void setupRecv(QString, QWidget*);

public slots:
	void readBytes();

private:
	QFile * outputFile;
	QTcpSocket* tcp;
	QByteArray data;
	QAudioOutput* aOutput;
};
