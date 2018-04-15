#include "TaskManager.h"



TaskManager::TaskManager(QObject *parent, short port)
	: QObject(parent)
{
	tcpConnections = new QVector<QTcpSocket *>();

	server = new TcpServer(this);
	server->listen(QHostAddress::Any, port);

	connect(server, &TcpServer::newConnection, this, &TaskManager::onConnect, Qt::QueuedConnection);
	qDebug() << "task manager created and socket connected to callback";
}

TaskManager::~TaskManager()
{
}

QTcpSocket * TaskManager::OpenTcpSocket()
{
	return nullptr;
}

bool TaskManager::AcceptHandshake(QTcpSocket * sock)
{
	QUdpSocket * udp;
	QHostAddress a;
	quint16 port;

	sock->waitForReadyRead();
	qDebug() << sock->bytesAvailable();

	char buffer[START_SIZE];
	memset(buffer, 0, START_SIZE);
	qint64 bytesRead = sock->read(buffer, sizeof(struct StartPacket));

	

	switch (buffer[0])
	{
	case SONG_STREAM:
		emit clientConnectedStream(sock);
		break;
	case VOICE_STREAM:
		udp = new QUdpSocket();
		a = udp->peerAddress();
		port = udp->peerPort();
		udp->bind(QHostAddress::Any, DEFAULT_PORT);
		emit clientConnectedVoip(udp);
		break;
	case FILE_TRANSFER:
		emit clientConnectedFileTransfer(sock);
		break;
	default:
		break;
	}


	return false;
}

bool TaskManager::SendHandshake(QTcpSocket * s, TaskType t)
{
	char buffer[10];
	memset(buffer, t, START_SIZE);
	s->write(buffer);
	
	return true;
}

bool TaskManager::ConnectTo(QString ipaddr, short port, TaskType t)
{
	if (!isConnecting)
	{
		currentConnectingSocket = new QTcpSocket();
		isConnecting = true;
		currentConnectingType = t;
		currentConnectingSocket->connectToHost(ipaddr, port);
		connect(currentConnectingSocket, &QTcpSocket::connected, this, &TaskManager::connectedToServer);
		return true;
	}
	

	return false;
}

void TaskManager::connectedToServer()
{
	this->tcpConnections->push_back(currentConnectingSocket);
	QUdpSocket * sock;
	QHostAddress a;
	quint16 port;
	SendHandshake(currentConnectingSocket, currentConnectingType);

	switch (currentConnectingType)
	{
	case TaskType::VOICE_STREAM:
		sock = new QUdpSocket();
		a = currentConnectingSocket->peerAddress();
		port = currentConnectingSocket->peerPort();
		sock->bind(QHostAddress::Any, DEFAULT_PORT);
		emit connectedToServerVoip(sock);
		break;
	case TaskType::FILE_TRANSFER:
		emit connectedToServerFileTransfer(currentConnectingSocket);
		break;
	case TaskType::SONG_STREAM:
		emit connectedToServerStream(currentConnectingSocket);
		break;
	}

	disconnect(currentConnectingSocket, &QTcpSocket::connected, this, &TaskManager::connectedToServer);
	currentConnectingSocket = nullptr;
	isConnecting = false;
}



void TaskManager::onConnect()
{
	QTcpSocket * socket = server->nextPendingConnection();

	AcceptHandshake(socket);
}





