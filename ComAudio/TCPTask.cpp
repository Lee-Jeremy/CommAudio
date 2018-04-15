#include "TCPTask.h"

/*
-- FUNCTION:
--
-- DATE:
--
-- REVISIONS:
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- INTERFACE:
--
-- RETURNS:
--
-- NOTES:
*/

TCPTask::TCPTask(int task, ComAudio* parent)
	: mTask(task)
	, mParent(parent)
{
	mBuffer = new QBuffer();
	mByteArray = new QByteArray();
	mCircBuffer = new CircBuffer();

	metadata = (struct metadata*) malloc(sizeof(struct metadata));
	if (task == TRANSFER)
	{
		// Wait. We initalize a socket anyway.
	}
	else {
		// initialize mSocket
		// connect TCPSocket to this
		QObject::connect(mSocket, SIGNAL(), this, &TCPTask::writeToBuffer);
	}
}

TCPTask::~TCPTask()
{
	mSocket = new QTcpSocket(mParent);
}

int TCPTask::connectToServer(QString& address, quint16 port)
{
	// Connect request
	// Receive list of filenames
	QHostAddress addr(address);
	mSocket->connectToHost(addr, port);

	QByteArray temp = mSocket->read(1024);
	fileList = QString(temp).split('\n');
	return 0;
}

int TCPTask::requestFile(QString filename)
{
	if (mTask == TRANSFER)
		return 0;
	
	// send request
	// wait for reponse, signal rx_metadata, slot handle_metadata (fill metadata struct)
	// return 1 on success, 0 on failure
	// mSocket->
	return 0;
}


int TCPTask::transmit(QString filename, QMainWindow* parent, QAudioOutput* ao)
{
	
	char* buffer = (char*)malloc(1000 * sizeof(char));
	int numBytesSent = 0;
	bool ioresult;
	
	file = new QFile(filename);

	ioresult = file->open(QIODevice::ReadOnly);
	if (ioresult == false)
	{

	}
	QDataStream in(file);

	return 0;
}

int TCPTask::receive(int numBytes)
{
	int numBytesRecv = 0;

	if (mTask == TRANSFER)
		return 0;
	
	while (numBytesRecv < numBytes)
	{

	}


	return 0;
}

int TCPTask::complete()
{
	return 0;
}

int TCPTask::handleMetadata(QString metadata)
{

	return 0;
}

void TCPTask::handleError()
{
	//qDebug() << ao->error();
}

void writeToBuffer()
{

}

void disconnect()
{

}