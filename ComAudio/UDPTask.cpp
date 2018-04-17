#include "UDPTask.h"


UDPTask::UDPTask(QObject* parent, QUdpSocket* socket, TaskType task, QTcpSocket* tcp)
	: QObject(parent)
	, mSocket(socket)
	, mTask(task)
{	
	mOutputSocket = new QUdpSocket(this->parent());
	mOutputSocket->connectToHost(tcp->peerAddress(), DEFAULT_UDP_PORT);

	mFormat = new QAudioFormat();
	mFormat->setSampleRate(VOIP_SAMPLERATE);
	mFormat->setSampleSize(VOIP_SAMPLESIZE);
	mFormat->setChannelCount(VOIP_NUMCHANNEL);
	mFormat->setCodec("audio/pcm");
	mFormat->setByteOrder(QAudioFormat::LittleEndian);
	mFormat->setSampleType(QAudioFormat::UnSignedInt);
}

UDPTask::UDPTask(QObject* parent)
	: QObject(parent)
{
	mFormat = new QAudioFormat();
	mFormat->setSampleRate(VOIP_SAMPLERATE);
	mFormat->setSampleSize(VOIP_SAMPLESIZE);
	mFormat->setChannelCount(VOIP_NUMCHANNEL);
	mFormat->setCodec("audio/pcm");
	mFormat->setByteOrder(QAudioFormat::LittleEndian);
	mFormat->setSampleType(QAudioFormat::UnSignedInt);
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

	//QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
	//if (!info.isFormatSupported(*format))
	//	format = info.nearestFormat(*format);

	mAudioOutput = new QAudioOutput(*format, this->parent());
	mAudioInput = new QAudioInput(*format);
	
	mAudioOutput->setBufferSize(VOIP_BUFFERSIZE);
	mAudioInput->setBufferSize(VOIP_BUFFERSIZE);


	mAudioInput->start(mOutputSocket);
	mDevice = mAudioOutput->start();
	  
	//connect(mSocket, &QAbstractSocket::readyRead, this, &UDPTask::playData);
	bool bindresult = mSocket->bind(QHostAddress::Any, DEFAULT_UDP_PORT);

	connect(mSocket, SIGNAL(readyRead()), this, SLOT(playData()));

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

bool UDPTask::startMulticastSend()
{
	mSocket = new QUdpSocket();
	mSocketIPv6 = new QUdpSocket();

	mSocket->bind(QHostAddress(QHostAddress::AnyIPv4), 0);
	mSocketIPv6->bind(QHostAddress(QHostAddress::AnyIPv6), mSocket->localPort());

	mDestAddr4 = new QHostAddress(QStringLiteral("123.123.123.123"));

	mSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 5);

	for (int i = 0; i < 100; i++)
	{
		QByteArray datagram = "asdfasdfasdfasdfasdfasdf";
		mSocket->writeDatagram(datagram, *mDestAddr4, DEFAULT_MC_PORT);
	}


	int state4 = mSocket->state();
	int state6 = mSocketIPv6->state();

	mAudioInput = new QAudioInput(*mFormat);
	mAudioInput->setBufferSize(VOIP_BUFFERSIZE);
	mAudioInput->setNotifyInterval(1);

	mByteArray = new QByteArray();
	mBuffer = new QBuffer(mByteArray);
	mBuffer->open(QBuffer::ReadWrite);

	connect(mAudioInput, SIGNAL(notify()), this, SLOT(sendDatagram()));

	mAudioInput->start(mBuffer);

	return true;
}
bool UDPTask::startMulticastListen()
{
	mSocket = new QUdpSocket();
	mSocket->bind(QHostAddress(QHostAddress::AnyIPv4), 0);
	mSocketIPv6->bind(QHostAddress(QHostAddress::AnyIPv6), mSocket->localPort());
	
	mSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 5);
	
	for (int i = 0; i < 100; i++)
	{
		QByteArray datagram = "asdfasdfasdfasdfasdfasdf";
		mSocket->writeDatagram(datagram, *mDestAddr4, DEFAULT_MC_PORT);
		mSocket->writeDatagram(datagram, *mDestAddr6, DEFAULT_MC_PORT);
	}

	connect(mSocket, SIGNAL(readyRead()), this, SLOT(playData()));

	mAudioOutput = new QAudioOutput(*mFormat, this->parent());

	mAudioOutput->setBufferSize(VOIP_BUFFERSIZE);
	int error = mSocket->error();
	mDevice = mAudioOutput->start();

	return true;
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

void UDPTask::sendDatagram()
{
	QByteArray datagram = "asdfasdfasdfasdfasdfasdf";
	mSocket->writeDatagram(datagram, *mDestAddr4, DEFAULT_MC_PORT);
	mSocket->writeDatagram(datagram, *mDestAddr6, DEFAULT_MC_PORT);
}