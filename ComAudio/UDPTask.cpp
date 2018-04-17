/*-----------------------------------------------------------------------------------------
--	SOURCE FILE:	UDPTask.cpp
--
--	PROGRAM:		CommAudio
--
--	FUNCTIONS:		UDPTask()
--					UDPTask()
--					~UDPTask()
--					startVOIP()
--					endVOIP()
--					startMulticastTx()
--					startMulticastRx()
--					playData()
--					sendDatagram()
--
--	DATE:			Apr. 2, 2018
--
--	REVISION:		Apr. 12, 2018
--						- Added VOIP functionality
--					Apr. 16, 2018
--						- Added multicast functionality, fixed VOIP
--
--	DESIGNER:	W. Hu, D. Elliot, J. Chou, J. Lee
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
--	FUNCTION:	UDPTask
--
--	DATE:		Apr. 12, 2018
--
--	REVISIONS:	Apr. 15, 2018
--					- Moved format initialization to constructor
--
--	DESIGNER:	W. Hu, D. Elliot, J. Chou, J. Lee
--
--	PROGRAMMER:	W. Hu, D. Elliot, J. Chou
--
--	INTERFACE:	UDPTask::UDPTask(QObject* parent, QUdpSocket* socket, TaskType task, QTcpSocket* tcp)
--					QObject* parent: parent QObject that owns this object (ComAudio)
--					QUdpSocket* socket: connected recv QUdpSocket
--					TaskType task: (enum) type of task selected by the user
--					QTcpSocket* tcp: QTcpSocket connected to the client
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
--	FUNCTION:	UDPTask
--
--	DATE:		Apr. 10, 2018
--
--	REVISIONS:	Apr. 15, 2018
--					- Modified to use as Multicast constructor
--
--	DESIGNER:	W. Hu, D. Elliot, J. Chou, J. Lee
--
--	PROGRAMMER:	W. Hu, D. Elliot
--
--	INTERFACE:	UDPTask::UDPTask(QObject* parent)
--					QObject* parent: parent QObject that owns this object (ComAudio)
--
--	RETURNS:
--
--	NOTES:
--	This is a 1 parameter constructor used to initialize the UDPTask object for
--	listening or sending to a multicast address. It initializes the QAudioFormat
--  object used to create QAudioInput/Output objects.
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
--	FUNCTION:	~UDPTask
--
--	DATE:		Apr. 10, 2018
--
--	REVISIONS:	Apr. 15, 2018
--					- Added functionality.
--
--	DESIGNER:	W. Hu, D. Elliot, J. Chou, J. Lee
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

void UDPTask::stop()
{
	endVOIP();
	disconnect(this, 0, 0, 0);
}

void UDPTask::start()
{
}


/*-----------------------------------------------------------------------------------------
--	FUNCTION:	startVOIP
--
--	DATE:		Apr. 12, 2018
--
--	REVISIONS:	Apr. 15, 2018
--					- Modified mAudioOutput and mAudioInput parameters so that it works.
--
--	DESIGNER:	W. Hu, D. Elliot, J. Chou, J. Lee
--
--	PROGRAMMER:	W. Hu, D. Elliot, J. Chou
--
--	INTERFACE:	bool UDPTask::startVOIP(QAudioOutput* output, QAudioInput* input, QAudioFormat* format)
--					QAudioOutput* output: QAudioObject pointer owned and passed by the parent ComAudio object.
--					QAudioInput* input: QAudioInput pointer owned and passed by the parent ComAudio object.
--					QAudioFormat* format: ComAudioFormat pointer owned and passed by the parent ComAudio object.
--
--	RETURNS:
--
--	NOTES:
--	This function starts the VOIP task. It is called by both clients to initiate VOIP chat.
--  The function is called the say way by both clients, and uses two QUdpSockets to perform
--  'bidirectional' communication.
--
--	It connects the recv. UDP socket to the playData callback function to handle incoming
--	audio datagrams.
-----------------------------------------------------------------------------------------*/
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

	mAudioOutput = new QAudioOutput(*format, this->parent());
	mAudioInput = new QAudioInput(*format);

	mAudioOutput->setBufferSize(VOIP_BUFFERSIZE);
	mAudioInput->setBufferSize(VOIP_BUFFERSIZE);


	mAudioInput->start(mOutputSocket);
	mDevice = mAudioOutput->start();

	mSocket->bind(QHostAddress::Any, DEFAULT_UDP_PORT);

	connect(mSocket, SIGNAL(readyRead()), this, SLOT(playData()));

	return true;
}


/*-----------------------------------------------------------------------------------------
--	FUNCTION:	endVOIP
--
--	DATE:		Apr. 12, 2018
--
--	REVISIONS:
--
--	DESIGNER:	W. Hu, D. Elliot, J. Chou, J. Lee
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
-----------------------------------------------------------------------------------------*/
bool UDPTask::endVOIP()
{
	if (mAudioInput != nullptr)
	{
		mAudioInput->stop();
	}

	if (mAudioOutput != nullptr)
	{
		mAudioOutput->stop();
	}


	if (mAudioInput != nullptr &&  mAudioOutput != nullptr && mAudioOutput->state() == QAudio::StoppedState
		&& mAudioInput->state() == QAudio::StoppedState)
	{
		delete mAudioOutput;
		delete mAudioInput;
		return true;
	}

	return false;
}


/*-----------------------------------------------------------------------------------------
--
--	FUNCTION:	startMulticastTx
--
--	DATE:		Apr. 14, 2018
--
--	REVISIONS:
--
--	DESIGNER:	W. Hu, D. Elliot, J. Chou, J. Lee
--
--	PROGRAMMER:	W. Hu, D. Elliot, J. Chou
--
--	INTERFACE:	bool UDPTask::startMulticastTx()
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
bool UDPTask::startMulticastTx()
{
	mSocket = new QUdpSocket();

	mSocket->bind(QHostAddress(QHostAddress::AnyIPv4), 0);

	mDestAddr4 = new QHostAddress(QStringLiteral("231.123.123.123"));

	mSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 5);

	mAudioInput = new QAudioInput(*mFormat, this->parent());

	mAudioInput->setBufferSize(VOIP_BUFFERSIZE);
	mAudioInput->setNotifyInterval(1);

	mDevice = mAudioInput->start();

	connect(mDevice, SIGNAL(readyRead()), this, SLOT(sendDatagram()));

	return true;
}


/*-----------------------------------------------------------------------------------------
--
--	FUNCTION:	startMulticastRx
--
--	DATE:		Apr. 14, 2018
--
--	REVISIONS:	Apr. 15, 2018
--					- Fixed multicast IP issue
--
--	DESIGNER:	W. Hu, D. Elliot, J. Chou, J. Lee
--
--	PROGRAMMER:	W. Hu, D. Elliot, J. Chou
--
--	INTERFACE:	bool UDPTask::startMulticastRx()
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
bool UDPTask::startMulticastRx()
{
	mSocket = new QUdpSocket();

	mGroupAddr4 = new QHostAddress(QStringLiteral("231.123.123.123"));

	mSocket->bind(QHostAddress::AnyIPv4, DEFAULT_MC_PORT, QUdpSocket::ShareAddress);

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
--	FUNCTION:	playData
--
--	DATE:		Apr. 12, 2018
--
--	REVISIONS:
--
--	DESIGNER:	W. Hu, D. Elliot, J. Chou, J. Lee
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
	while (mSocket->hasPendingDatagrams())
	{
		QByteArray data;
		data.resize(mSocket->pendingDatagramSize());
		mSocket->readDatagram(data.data(), data.size());
		mDevice->write(data.data(), data.size());
	}
}

/*-----------------------------------------------------------------------------------------
--	FUNCTION:	sendDatagram
--
--	DATE:		Apr. 15, 2018
--
--	REVISIONS:
--
--	DESIGNER:	W. Hu, D. Elliot, J. Chou, J. Lee
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
}
