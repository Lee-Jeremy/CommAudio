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
	}
}

TCPTask::~TCPTask()
{
	mSocket = new QTcpSocket(mParent);
}

int TCPTask::connect(QString& address, quint16 port)
{
	// Connect request
	// Receive list of filenames
	QHostAddress addr(address);
	mSocket->connectToHost(addr, port);

	QByteArray temp = mSocket->read(1024);
	fileList = QString(temp).split('/');
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
	
}


int TCPTask::transmit(QString filename, QMainWindow* parent, QAudioOutput* ao)
{
	file = new QFile(filename);
	char* buffer = (char*)malloc(1000 * sizeof(char));

	bool ioresult = file->open(QIODevice::ReadOnly);
	QDataStream in(file);


	mByteArray = new QByteArray();
	mBuffer = new QBuffer(mByteArray);
	mBuffer->open(QIODevice::ReadWrite);

	int numBytesRead;
	int result;

	for (int i = 0; i < 200; i++)
	{
		numBytesRead = in.readRawData(buffer, 1000);
		mByteArray->append(buffer, 1000);
	}

	QAudioFormat format;
	format.setSampleRate(96000);
	format.setChannelCount(1);
	format.setSampleSize(16);
	format.setCodec("audio/pcm");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);
	ao = new QAudioOutput(format);

	QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
	if (!info.isFormatSupported(format)) {
		qWarning() << "Raw audio format not supported by backend, cannot play audio.";
		format = info.nearestFormat(format);
	}
	ao->setVolume(1.0);
	ao->start(mBuffer);

	int state = ao->state();
	qDebug() << ao->error();
	int error = ao->error();


	while (!in.atEnd())
	{
		numBytesRead = in.readRawData(buffer, 1000);
		mByteArray->append(buffer, 1000);
	}
	
	return 0;
}

int TCPTask::receive()
{
	if (mTask == TRANSFER)
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
