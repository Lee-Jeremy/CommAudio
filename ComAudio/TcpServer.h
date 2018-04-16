#pragma once

#include <QTcpServer>

class TcpServer : public QTcpServer
{
	Q_OBJECT

public:
	TcpServer(QObject *parent);
	~TcpServer();

	void startListening(short port);


};
