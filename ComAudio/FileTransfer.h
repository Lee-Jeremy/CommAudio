#pragma once

#include <QObject>
#include <QFile>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QTcpSocket>
#include <QByteArray>
#include <QAudioOutput>
#include <QBuffer>


class FileTransfer : public QObject
{
	Q_OBJECT

public:
	FileTransfer(QObject *parent, QTcpSocket * tcp, QString fileName);
	~FileTransfer();

	void setOutputFile(QString path);

public slots:
	void readBytes();

private:
	QFile outputFile;
	QString outputPath;
	QTcpSocket* tcp;
	QByteArray data;
};
