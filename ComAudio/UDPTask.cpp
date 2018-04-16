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

bool UDPTask::start()
{
	switch (mTask)
	{
		case VOICE_STREAM:
			// call startVOIP
			return true;
		case MULTICAST_SEND:
			// call startMulticastSend
			return true;
		case MULTICAST_LISTEN:
			// call startMulticastListen
			return true;
		default:
			break;
	}
	return false;
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

	//QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
	//if (!info.isFormatSupported(*format))
	//	format = info.nearestFormat(*format);

	mAudioOutput = new QAudioOutput(*format, this->parent());
	mAudioInput = new QAudioInput(*format);
	
	mAudioOutput->setBufferSize(VOIP_BUFFERSIZE);
	mAudioInput->setBufferSize(VOIP_BUFFERSIZE);

	//mBuffer = new QBuffer();
	//mBuffer->open(QBuffer::ReadWrite);

	//mAudioInput->start(mSocket);
	mAudioOutput->start(mSocket);

	//int sockstate = mSocket->state();
	//int sockerror = mSocket->error();

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