#include "TcpServer.h"

TcpServer::TcpServer(QObject *parent)
	: QTcpServer(parent)
{
}

TcpServer::~TcpServer()
{
}

void TcpServer::startListening(short port)
{
	listen(QHostAddress::AnyIPv4, port);
}




