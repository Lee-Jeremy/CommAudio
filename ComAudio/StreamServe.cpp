#include "StreamServe.h"

StreamServe::StreamServe(QTcpSocket* tcp, QString path)
	: QObject(nullptr)
	, tcp(tcp)
	, path(path)
	, running(true)
{
}



StreamServe::~StreamServe()
{
}


void StreamServe::stop()
{
	running = false;
}

void StreamServe::start()
{

}

void StreamServe::sendFile()
{
	outgoing = new QFile();
	outgoing->setFileName(path);
	if (!outgoing->open(QIODevice::ReadOnly))
	{
		return;
	}

	while (!outgoing->atEnd() && running)
	{
		QByteArray line = outgoing->readLine();
		tcp->write(line);
	}

	outgoing->close();
	emit finished();
}
