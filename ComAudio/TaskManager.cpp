#include "TaskManager.h"



TaskManager::TaskManager(QObject *parent, short port)
	: QObject(parent)
{
	isConnecting = false;
	tcpConnections = new QVector<QTcpSocket *>();
	portToConn = port;
}

TaskManager::~TaskManager()
{
}

void TaskManager::start(short port)
{
	server = new TcpServer(this);
	server->listen(QHostAddress::Any, port);

	connect(server, &TcpServer::newConnection, this, &TaskManager::onConnect, Qt::QueuedConnection);
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

	char buffer[sizeof(struct StartPacket)];
	memset(buffer, 0, sizeof(struct StartPacket));
	qint64 bytesRead = sock->read(buffer, sizeof(struct StartPacket));


	int sockerror;
	int sockstate;
	int numWritten;
	bool bindresult;
	

	switch (buffer[0])
	{
	case SONG_STREAM:
		sock->write(buffer, sizeof(struct StartPacket));
		emit clientConnectedStream(sock);
		resetConnectionState();
		break;
	case VOICE_STREAM:
		udp = new QUdpSocket(this->parent());

		sockerror = udp->error();
		sockstate = udp->state();
		numWritten = sock->write(buffer, sizeof(struct StartPacket));
		emit clientConnectedVoip(udp, sock);
		resetConnectionState();
		break;
	case FILE_LIST:
		sock->write(buffer, sizeof(struct StartPacket));
		emit clientConnectedFileList(sock);
		resetConnectionState();
		break;
	case FILE_TX:
		sock->write(buffer, sizeof(struct StartPacket));
		emit clientConnectedFileTx(sock);
		resetConnectionState();
		break;
	default:
		break;
	}


	return false;
}

void TaskManager::resetConnectionState()
{
	isConnecting = false;
	currentConnectingSocket = nullptr;
}

bool TaskManager::SendHandshake(QTcpSocket * s, TaskType t)
{
	char buffer[sizeof(struct StartPacket)];
	memset(buffer, t, sizeof(struct StartPacket));
	s->write(buffer, 10);

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

		connect(currentConnectingSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
			this, &TaskManager::displayError);
		return true;
	}

	resetConnectionState();

	return false;
}

void TaskManager::displayError(QAbstractSocket::SocketError socketError)
{
	switch (socketError) {
	case QAbstractSocket::RemoteHostClosedError:
		break;
	case QAbstractSocket::HostNotFoundError:
		QMessageBox::information((QWidget*)this->parent(), tr("Task manager"),
			tr("The host was not found. Please check the "
				"host name and port settings."));
		break;
	case QAbstractSocket::ConnectionRefusedError:
		QMessageBox::information((QWidget*)this->parent(), tr("task Manager"),
			tr("The connection was refused by the peer. "));
		break;
	default:
		QMessageBox::information((QWidget*)this->parent(), tr("task Manager"),
			tr("The following error occurred: %1.")
			.arg(currentConnectingSocket->errorString()));
	}

	resetConnectionState();

}

void TaskManager::connectedToServer()
{
	this->tcpConnections->push_back(currentConnectingSocket);
	QUdpSocket * sock;
	QHostAddress a;
	quint16 port;
	SendHandshake(currentConnectingSocket, currentConnectingType);
	char buffer[sizeof(struct StartPacket)];
	switch (currentConnectingType)
	{
	case TaskType::VOICE_STREAM:
		sock = new QUdpSocket();

		if (!currentConnectingSocket->waitForReadyRead(30000))
		{
			//timeout error
			break;
		}
		else
		{
			currentConnectingSocket->read(buffer, sizeof(struct StartPacket));
			emit connectedToServerVoip(sock, currentConnectingSocket);
		}

		break;
	case TaskType::FILE_LIST:
		if (!currentConnectingSocket->waitForReadyRead(5000))
		{
			//timeout error
			break;
		}
		else
		{
			currentConnectingSocket->read(buffer, sizeof(struct StartPacket));
			emit connectedToServerFileList(currentConnectingSocket);
		}
		break;
	case TaskType::FILE_TX:
		if (!currentConnectingSocket->waitForReadyRead(5000))
		{
			//timeout error
			break;
		}
		else
		{
			currentConnectingSocket->read(buffer, sizeof(struct StartPacket));
			emit connectedToServerFileTx(currentConnectingSocket);
		}
		break;
	case TaskType::SONG_STREAM:
		if (!currentConnectingSocket->waitForReadyRead(5000))
		{
			//timeout error
			break;
		}
		else
		{
			currentConnectingSocket->read(buffer, sizeof(struct StartPacket));
			emit connectedToServerStream(currentConnectingSocket);
		}
		break;
	}

	resetConnectionState();
}


void TaskManager::onConnect()
{
	QTcpSocket * socket = server->nextPendingConnection();

	AcceptHandshake(socket);
}





