#include "StreamServe.h"

StreamServe::StreamServe(QObject *parent, QTcpSocket* tcp, QString path)
	: QObject(parent)
	, tcp(tcp)
	, path(path)
{
}



StreamServe::~StreamServe()
{
}


void StreamServe::sendFile()
{
	outgoing = new QFile(path);
	if (outgoing->open(QIODevice::ReadOnly))
	{
		return;
	}

	while (!outgoing->atEnd())
	{
		QByteArray line = outgoing->readLine();
		tcp->write(line);
	}

	outgoing->close();
}
