#include "TaskManager.h"



TaskManager::TaskManager(QObject *parent, short port)
	: QObject(parent)
{
	isConnecting = false;
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
		emit clientConnectedStream(sock);
		resetConnectionState();
		break;
	case VOICE_STREAM:
		udp = new QUdpSocket();
		//udp->bind(QHostAddress::Any, DEFAULT_UDP_PORT);
		//bindresult = udp->bind(QHostAddress::Any, DEFAULT_UDP_PORT);
		//udp->connectToHost(QHostAddress::Any, DEFAULT_UDP_PORT);
		/*DEBUG*/
		//udp->open(QIODevice::ReadWrite);
		sockerror = udp->error();
		sockstate = udp->state();
		numWritten = sock->write(buffer, sizeof(struct StartPacket));
		emit clientConnectedVoip(udp, sock);
		resetConnectionState();
		break;
	case FILE_TRANSFER:
		emit clientConnectedFileTransfer(sock);
		resetConnectionState();
		break;
	default:
		break;
	}


	return false;
}

void TaskManager::resetConnectionState()
{
	//if (currentConnectingSocket != nullptr)
	//{
	//	disconnect(currentConnectingSocket, &QTcpSocket::connected, this, &TaskManager::connectedToServer);
	//}
	isConnecting = false;
	currentConnectingSocket = nullptr;
}

bool TaskManager::SendHandshake(QTcpSocket * s, TaskType t)
{
	char buffer[sizeof(struct StartPacket)];
	memset(buffer, t, sizeof(struct StartPacket));
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
		QMessageBox::information((QWidget*) this->parent(), tr("Task manager"),
			tr("The host was not found. Please check the "
				"host name and port settings."));
		break;
	case QAbstractSocket::ConnectionRefusedError:
		QMessageBox::information((QWidget*)this->parent(), tr("task Manager"),
			tr("The connection was refused by the peer. "
				"Make sure the fortune server is running, "
				"and check that the host name and port "
				"settings are correct."));
		break;
	default:
		QMessageBox::information((QWidget*) this->parent(), tr("task Manager"),
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

	switch (currentConnectingType)
	{
	case TaskType::VOICE_STREAM:
		sock = new QUdpSocket();
		char buffer[sizeof(struct StartPacket)];
		if (!currentConnectingSocket->waitForReadyRead(30000))
		{
			//timeout error
			break;
		}
		else
		{
			currentConnectingSocket->read(buffer, sizeof(struct StartPacket));
			a = currentConnectingSocket->peerAddress();
			port = currentConnectingSocket->peerPort();
			sock->connectToHost(a, 42069);
			emit connectedToServerVoip(sock, currentConnectingSocket);
		}
		
		break;
	case TaskType::FILE_TRANSFER:
		emit connectedToServerFileTransfer(currentConnectingSocket);
		break;
	case TaskType::SONG_STREAM:
		emit connectedToServerStream(currentConnectingSocket);
		break;
	}

	resetConnectionState();
}


void TaskManager::onConnect()
{
	QTcpSocket * socket = server->nextPendingConnection();

	AcceptHandshake(socket);
}





