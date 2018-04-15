#include "TCPTask.h"

TCPTask::TCPTask(int task)
	: mTask(task)
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

}

int TCPTask::connect()
{
	// Connect request
	// Receive list of filenames
	fileList = new QString[5];
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
	// open file
	// while !eof
	// read n bytes of file into temp buffer, send

	file = new QFile(filename);
	//char* buffer = (char*)malloc(10000 * sizeof(char));

	bool ioresult = file->open(QIODevice::ReadOnly);
	//QDataStream in(file);
	//int result = in.readRawData(buffer, 1000);

	//while (!in.atEnd())
	//{

	//}



	//while (!mCircBuffer->isReadable())
	//{
	//	int result = in.readRawData(buffer, 1000);
	//	mCircBuffer->write((qint8*) buffer, 1000);
	//}

	QAudioFormat format;
	format.setSampleRate(44100);
	format.setChannelCount(1);
	format.setSampleSize(16);
	format.setCodec("audio/pcm");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);
	ao = new QAudioOutput(format);
	//connect(ao, QAudioOutput::error, this, &TCPTask::handleError);

	QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
	if (!info.isFormatSupported(format)) {
		qWarning() << "Raw audio format not supported by backend, cannot play audio.";
		format = info.nearestFormat(format);
	}
	ao->setVolume(1.0);
	ao->start(file);
	
	int state = ao->state();
	qDebug() << ao->error();
	int error = ao->error();
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

void TCPTask::handleError()
{
	//qDebug() << ao->error();
}