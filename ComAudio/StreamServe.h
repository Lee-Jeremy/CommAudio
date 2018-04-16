#pragma once

#include <QObject>
#include <QFile>
#include <QTcpSocket>

class StreamServe : public QObject
{
	Q_OBJECT

public:
	StreamServe(QObject *parent, QTcpSocket*, QString);
	~StreamServe();

public slots:
	void sendFile();

private:
	QFile* outgoing;
	QTcpSocket* tcp;
	QString path;
};
