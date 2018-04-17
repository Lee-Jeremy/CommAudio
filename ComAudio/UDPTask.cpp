/*-----------------------------------------------------------------------------------------
--	SOURCE FILE:	UDPTask.cpp
--
--	PROGRAM:		CommAudio
--
--	FUNCTIONS:		UDPTask()
--					UDPTask()
--					~UDPTask()
--					connectToHost()
--					startVOIP()
--					endVOIP()
--					startMulticastSend()
--					startMulticastListen()
--					handleError()
--					playData()
--					sendDatagram()
--
--	DATE:			Apr. 14, 2018
--
--	REVISION:		Apr. 15, 2018
--					Apr. 16, 2018
--
--	DESIGNER:		W. Hu, D. Elliot, J. Lee, J. Chou
--
--	PROGRAMMER:		W. Hu, D. Elliot
--
--	NOTES:
--	This class contains the methods used to perform UDP related program tasks:
--		i) 1..1 VOIP chat
--		ii) 1..* multicast VOIP
--
--	The slot callback functions are used to handle reading or sending data when
--	data is received at their respective QIODevice.
-----------------------------------------------------------------------------------------*/

#include "UDPTask.h"

/*-----------------------------------------------------------------------------------------
--
--	FUNCTION:	UDPTask
--
--	DATE:		Apr. 14, 2018
--
--	REVISIONS:	Apr. 15, 2018
--					- Moved format initialization to constructor
--
--	DESIGNER:	W. Hu, D. Elliot, J. Lee, J. Chou
--
--	PROGRAMMER:	W. Hu, D. Elliot
--
--	INTERFACE:	UDPTask::UDPTask(QObject* parent, QUdpSocket* socket, TaskType task, QTcpSocket* tcp)
--
--	RETURNS:
--
--	NOTES:
--	This is a parameterized constructor used to initialize the UDPTask object for
--	1..1 VOIP chat. It sets the QAudioFormat used to create a QAudioInput/Output object.
--
--	This constructor initializes the second QUdpSocket used to send VOIP datagrams to the
--	other connected host.
-----------------------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------------------
--
--	FUNCTION:	UDPTask
--
--	DATE:		Apr. 14, 2018
--
--	REVISIONS:	Apr. 15, 2018
--
--	DESIGNER:	W. Hu, D. Elliot, J. Lee, J. Chou
--
--	PROGRAMMER:	W. Hu, D. Elliot
--
--	INTERFACE:	UDPTask::UDPTask(QObject* parent)
--
--	RETURNS:	
--
--	NOTES:
--	This is a 1 parameter constructor used to initialize the UDPTask object for
--	listening or sending to a multicast address. It initializes the QAudioFormat
--  object used to create QAudioInput/Output objects.
--
-----------------------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------------------
--
--	FUNCTION:	~UDPTask
--
--	DATE:		Apr. 14, 2018
--
--	REVISIONS:	Apr. 15, 2018
--
--	DESIGNER:	W. Hu, D. Elliot, J. Lee, J. Chou
--
--	PROGRAMMER:	W. Hu, D. Elliot
--
--	INTERFACE:	~UDPTask()
--
--	RETURNS:
--
--	NOTES:
--	This detructor is used to delete the UDPTask object and its member variables from
--	memory. Delete should be called when the object's associated task completes.
--
-----------------------------------------------------------------------------------------*/
UDPTask::~UDPTask()
{
	if (mSocket != nullptr)
		delete mSocket;
	//delete mSocketIPv6;
	if (mOutputSocket != nullptr)
		delete mOutputSocket;
	if (mGroupAddr4 != nullptr)
		delete mGroupAddr4;
	if (mGroupAddr6 != nullptr)
		delete mGroupAddr6;
	if (mDestAddr4 != nullptr)
		delete mDestAddr4;
	if (mDestAddr6 != nullptr)
		delete mDestAddr6;
	if (mBuffer != nullptr)
		delete mBuffer;
	if (mByteArray != nullptr)
		delete mByteArray;
	if (mFormat != nullptr)
		delete mFormat;
	if (mAudioOutput != nullptr)
		delete mAudioOutput;
	if (mAudioInput != nullptr)
		delete mAudioInput;
	if (mDevice != nullptr)
		delete mDevice;
}

/*-----------------------------------------------------------------------------------------
--
--	FUNCTION:	startVOIP
--
--	DATE:		Apr. 14, 2018
--
--	REVISIONS:	Apr. 15, 2018
--
--	DESIGNER:	W. Hu, D. Elliot, J. Lee, J. Chou
--
--	PROGRAMMER:	W. Hu, D. Elliot
--
--	INTERFACE:	bool UDPTask::startVOIP(QAudioOutput* output, QAudioInput* input, QAudioFormat* format)
--
--	RETURNS:	
--
--	NOTES:
--
--
-----------------------------------------------------------------------------------------*/
void UDPTask::startVOIP(QAudioOutput* output, QAudioInput* input, QAudioFormat* format)
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
}


/*-----------------------------------------------------------------------------------------
--
--	FUNCTION:	endVOIP
--
--	DATE:		Apr. 14, 2018
--
--	REVISIONS:	Apr. 15, 2018
--
--	DESIGNER:	W. Hu, D. Elliot, J. Lee, J. Chou
--
--	PROGRAMMER:	W. Hu, D. Elliot
--
--	INTERFACE:	bool UDPTask::endVOIP()
--
--	RETURNS:	Returns boolean indicating success or failure of the close operation.
--
--	NOTES:
--	This function is used to terminate the VOIP session. It should be called when the user
--	chooses to end the task.
--
-----------------------------------------------------------------------------------------*/
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


/*-----------------------------------------------------------------------------------------
--
--	FUNCTION:	startMulticastSend
--
--	DATE:		Apr. 14, 2018
--
--	REVISIONS:	Apr. 15, 2018
--
--	DESIGNER:	W. Hu, D. Elliot, J. Lee, J. Chou
--
--	PROGRAMMER:	W. Hu, D. Elliot
--
--	INTERFACE:	bool UDPTask::startMulticastSend()
--
--	RETURNS:	Returns boolean value indicating success or failure in connecting to
--					a multicast address
--
--	NOTES:
--	This function is used to connect to a multicast address for transmission, and
--	is called when the user presses the 'Multicast Tx' button. 
--
--	This function binds two QUdpSockets to an IPv4 and IPv6 address, initializes
--  a QAudioInput object, and connects the QAudioInput object to the sendDatagram()
--  callback function. The sendDatagram function is used to handle data read by the
--	QAudioInput object.
--
--	The multicast address and port are currently hard-coded.
--
--	It is based in part on Qt's Multicast example documentation. 
--
-----------------------------------------------------------------------------------------*/
bool UDPTask::startMulticastSend()
{
	mSocket = new QUdpSocket();
	//mSocketIPv6 = new QUdpSocket();

	mSocket->bind(QHostAddress(QHostAddress::AnyIPv4), 0);
	//mSocketIPv6->bind(QHostAddress(QHostAddress::AnyIPv6), mSocket->localPort());

	mDestAddr4 = new QHostAddress(QStringLiteral("231.123.123.123"));

	mSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 5);

	mAudioInput = new QAudioInput(*mFormat, this->parent());

	mAudioInput->setBufferSize(VOIP_BUFFERSIZE);
	mAudioInput->setNotifyInterval(1);

	mDevice = mAudioInput->start();

	/*mByteArray = new QByteArray();
	mBuffer = new QBuffer(mByteArray);
	mBuffer->open(QBuffer::ReadWrite);*/

	connect(mDevice, SIGNAL(readyRead()), this, SLOT(sendDatagram()));

	return true;
}

/*-----------------------------------------------------------------------------------------
--
--	FUNCTION:	startMulticastListen
--
--	DATE:		Apr. 14, 2018
--
--	REVISIONS:	Apr. 15, 2018
--
--	DESIGNER:	W. Hu, D. Elliot, J. Lee, J. Chou
--
--	PROGRAMMER:	W. Hu
--
--	INTERFACE:	bool UDPTask::startMulticastListen()
--
--	RETURNS:	Returns boolean value indicating success or failure to connect to the
--					multicast address.
--
--	NOTES:
--	This function is used to connect to a multicast address for listening. It is called
--	when the user presses the 'Multicast Rx' button. 
--
--	It initializes an QAudioOutput object and connects it to the playData() callback 
--  function which is used to handle incoming audio data from the socket.
--
-----------------------------------------------------------------------------------------*/
bool UDPTask::startMulticastListen()
{
	mSocket = new QUdpSocket();
	//mSocketIPv6 = new QUdpSocket();

	mGroupAddr4 = new QHostAddress(QStringLiteral("231.123.123.123"));
	//mGroupAddr6 = new QHostAddress(QStringLiteral("ff12::2115"));

	mSocket->bind(QHostAddress::AnyIPv4, DEFAULT_MC_PORT, QUdpSocket::ShareAddress);
	//mSocketIPv6->bind(QHostAddress::AnyIPv6, DEFAULT_MC_PORT, QUdpSocket::ShareAddress);

	mSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 5);
	mSocket->joinMulticastGroup(*mGroupAddr4);
	
	connect(mSocket, SIGNAL(readyRead()), this, SLOT(playData()));

	mAudioOutput = new QAudioOutput(*mFormat, this->parent());

	mAudioOutput->setBufferSize(VOIP_BUFFERSIZE);
	int error = mSocket->error();
	mDevice = mAudioOutput->start();

	return true;
}

/*-----------------------------------------------------------------------------------------
--
--	FUNCTION:	playData
--
--	DATE:		Apr. 14, 2018
--
--	REVISIONS:	Apr. 15, 2018
--
--	DESIGNER:	W. Hu, D. Elliot, J. Lee, J. Chou
--
--	PROGRAMMER:	W. Hu, D. Elliot
--
--	INTERFACE:	void UDPTask::playData()	
--
--	RETURNS:	
--
--	NOTES:
--	This function is a slot (callback) function used to play audio data received from a
--	QUdpSocket.
-----------------------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------------------
--
--	FUNCTION:	sendDatagram
--
--	DATE:		Apr. 14, 2018
--
--	REVISIONS:	Apr. 15, 2018
--
--	DESIGNER:	W. Hu, D. Elliot, J. Lee, J. Chou
--
--	PROGRAMMER:	W. Hu, D. Elliot
--
--	INTERFACE:	void UDPTask::sendDatagram()
--
--	RETURNS:	
--
--	NOTES:
--	This function is a slot (callback) function used to send data read from a QAudioInput
--  object to a multicast address.
--
--	This function is based on Qt's Multicast Example documentation.
-----------------------------------------------------------------------------------------*/
void UDPTask::sendDatagram()
{
	QByteArray datagram = mDevice->readAll();
	mSocket->writeDatagram(datagram, *mDestAddr4, DEFAULT_MC_PORT);
//	mSocket->writeDatagram(datagram, *mDestAddr6, DEFAULT_MC_PORT);
}