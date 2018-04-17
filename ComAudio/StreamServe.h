#pragma once

#include <QObject>
#include <QFile>
#include <QTcpSocket>
#include "Task.h"

class StreamServe : public QObject, Task
{
	Q_OBJECT

public:
	StreamServe(QTcpSocket*, QString);
	~StreamServe();

	void stop();

	void sendFile();

signals:
	void finished();

private:
	QFile* outgoing;
	QTcpSocket* tcp;
	QString path;
	bool running;
};
