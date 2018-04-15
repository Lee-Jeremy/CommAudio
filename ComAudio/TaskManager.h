#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QVector>
#include <QList>
#include <TcpServer.h>
#include <global.h>
#include <qdebug.h>
#include <cstring>


class TaskManager : public QObject
{
	Q_OBJECT

public:
	TaskManager(QObject *parent, short port);
	~TaskManager();

	TcpServer * server;
	QTcpSocket * OpenTcpSocket();
	bool AcceptHandshake(QTcpSocket * sock);
	bool SendHandshake(QTcpSocket * s, TaskType t);
	bool ConnectTo(QString ipaddr, short port, TaskType t);

	
	
public slots:
	void onConnect();
	void connectedToServer();

signals:
	
	void clientConnectedVoip(QUdpSocket *);
	void clientConnectedStream(QTcpSocket *);
	void clientConnectedFileTransfer(QTcpSocket *);

	void connectedToServerFileTransfer(QTcpSocket * sock);
	void connectedToServerVoip(QUdpSocket * sock);
	void connectedToServerStream(QTcpSocket * sock);

private:
	QTcpSocket * currentConnectingSocket;
	TaskType currentConnectingType;
	bool isConnecting;
	QVector<QTcpSocket *> * tcpConnections;
};
