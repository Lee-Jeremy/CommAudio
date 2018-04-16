#include "UDPTask.h"

UDPTask::UDPTask(QUdpSocket* socket, TaskType task)
	: mSocket(socket)
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

bool UDPTask::startVOIP(QAudioOutput* output, QAudioInput* input)
{
	QAudioFormat format;
	format.setSampleRate(VOIP_SAMPLERATE);
	format.setSampleSize(VOIP_SAMPLESIZE);
	format.setChannelCount(VOIP_NUMCHANNEL);
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);

	mAudioOutput = output;
	mAudioInput = input;
	
	mAudioOutput->setBufferSize(VOIP_BUFFERSIZE);
	mAudioInput->setBufferSize(VOIP_BUFFERSIZE);

	mAudioOutput = new QAudioOutput(format);
	mAudioInput = new QAudioInput(format);

	if (mAudioOutput->state() == 2 && mAudioInput->state() == 2)
	{
		mAudioOutput->start(mSocket);
		mAudioInput->start(mSocket);
		return true;
	}
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

void handleError()
{
}