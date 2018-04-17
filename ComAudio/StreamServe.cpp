#include "StreamServe.h"

StreamServe::StreamServe(QTcpSocket* tcp, QString path)
	: QObject(nullptr)
	, tcp(tcp)
	, path(path)
{
}



StreamServe::~StreamServe()
{
}


void StreamServe::sendFile()
{
	outgoing = new QFile();
	outgoing->setFileName(path);
	qDebug() << path;
	if (!outgoing->open(QIODevice::ReadOnly))
	{
		qDebug() << "failed to send";
		return;
	}

	while (!outgoing->atEnd())
	{
		qDebug() << "sent";
		QByteArray line = outgoing->readLine();
		tcp->write(line);
	}

	outgoing->close();
	emit finished();
}
