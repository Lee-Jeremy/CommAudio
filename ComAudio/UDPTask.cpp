#include "UDPTask.h"


UDPTask::UDPTask(QObject* parent, QUdpSocket* socket, TaskType task)
	: QObject(parent)
	, mSocket(socket)
	, mTask(task)
{	
}

UDPTask::~UDPTask()
{

}

bool UDPTask::connectToHost()
{
	return false;
}

int UDPTask::sendTo()
{
	return 0;
}

int UDPTask::recvFrom()
{
	return 0;
}


bool UDPTask::startVOIP(QAudioOutput* output, QAudioInput* input, QAudioFormat* format)
{
	

	format = new QAudioFormat();
	format->setSampleRate(VOIP_SAMPLERATE);
	format->setSampleSize(VOIP_SAMPLESIZE);
	format->setChannelCount(VOIP_NUMCHANNEL);
	format->setCodec("audio/pcm");
	format->setByteOrder(QAudioFormat::LittleEndian);
	format->setSampleType(QAudioFormat::UnSignedInt);

	mAudioOutput = output;
	mAudioInput = input;

	int sockstatus = mSocket->state();
	int sockerror = mSocket->error();
	bool valid = mSocket->isValid();


	//QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
	//if (!info.isFormatSupported(*format))
	//	format = info.nearestFormat(*format);

	mAudioOutput = new QAudioOutput(*format, this->parent());
	mAudioInput = new QAudioInput(*format);
	
	mAudioOutput->setBufferSize(VOIP_BUFFERSIZE);
	mAudioInput->setBufferSize(VOIP_BUFFERSIZE);

	mAudioInput->start(mSocket);
	mDevice = mAudioOutput->start();

	playData();
	connect(mSocket, SIGNAL(readyRead()), this, SLOT(playData()));
	//bool bindresult = mSocket->bind(QHostAddress::Any, DEFAULT_UDP_PORT);

	/*if (mAudioOutput->state() == 2 && mAudioInput->state() == 2)
	{
		mAudioOutput->start(mSocket);
		mAudioInput->start(mSocket);
		return true;
	}*/
	return false;
}

bool UDPTask::endVOIP()
{
	mAudioOutput->stop();
	mAudioInput->stop();
	if (mAudioOutput->state() == QAudio::StoppedState && mAudioInput->state() == QAudio::StoppedState)
	{
		delete mAudioOutput;
		delete mAudioInput;
		return true;
	}
	return false;
}

void UDPTask::handleError()
{
}

void UDPTask::playData()
{
	//You need to read datagrams from the udp socket
	while (mSocket->hasPendingDatagrams())
	{
		QByteArray data;
		data.resize(mSocket->pendingDatagramSize());
		mSocket->readDatagram(data.data(), data.size());
		mDevice->write(data.data(), data.size());
	}
}