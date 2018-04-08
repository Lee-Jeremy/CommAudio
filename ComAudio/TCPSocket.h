#pragma once

#include <QTcpSocket>
#include "AbstractSocket.h"

class TCPSocket :
	public AbstractSocket
{
public:
	TCPSocket();
	~TCPSocket();

	int recv(const char* buffer, int len);
	int send(const char * buffer, int len);

	int listen();
	int accept();
	bool connect(QString hostAddr, quint16 port);
	int stream();
	int close();

private:
	QTcpSocket socket;

};

