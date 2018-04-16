#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QMessageBox>
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
	void resetConnectionState();

	void startMulticastServer();
	void connectedToMulticastServer();
	
public slots:
	void onConnect();
	void connectedToServer();
	void displayError(QAbstractSocket::SocketError);

signals:
	
	void clientConnectedVoip(QUdpSocket *, QTcpSocket *);
	void clientConnectedStream(QTcpSocket *);
	void clientConnectedFileTransfer(QTcpSocket *);

	void connectedToServerFileTransfer(QTcpSocket * sock);
	void connectedToServerVoip(QUdpSocket * udp, QTcpSocket * tcp);
	void connectedToServerStream(QTcpSocket * sock);

private:
	QTcpSocket * currentConnectingSocket;
	TaskType currentConnectingType;
	bool isConnecting;
	QVector<QTcpSocket *> * tcpConnections;
};
