/*-----------------------------------------------------------------------------------------
--	SOURCE FILE:	StreamRecv.cpp
--
--	PROGRAM:		CommAudio
--
--	FUNCTIONS:			
--				StreamRecv(QObject *parent, QTcpSocket*);
--				~StreamRecv();
--				void stop();
--				void start();
--				void readBytes();
--
--	DATE:			Apr. 14, 2018
--
--	REVISION:
--
--	DESIGNER:		D. Elliot, J. Chou, J. Lee, W. Hu
--
--	PROGRAMMER:		D. Elliot, J. Chou
--
--	NOTES:
--	This class is used to receive and playback a song sent over TCP.
-----------------------------------------------------------------------------------------*/
#include "StreamRecv.h"

StreamRecv::StreamRecv(QObject *parent, QTcpSocket* tcp)
	: QObject(parent)
	, tcp(tcp)
	, audioParent(parent)
	, tmpData(new QByteArray())
{

	firstRun = true;
	connect(tcp, &QAbstractSocket::readyRead, this, &StreamRecv::readBytes);
}

StreamRecv::~StreamRecv()
{
}


void StreamRecv::stop()
{
	disconnect(this, 0, 0, 0);
	aOutput->suspend();
}

void StreamRecv::start()
{
}



/*-----------------------------------------------------------------------------------------
--	FUNCTION:	readBytes
--
--	DATE:		Apr. 14, 2018
--
--	DESIGNER:	D. Elliot, J. Chou, J. Lee, W. Hu
--
--	PROGRAMMER:	D. Elliot, J. Chou
--
--	INTERFACE:	void StreamRecv::readBytes()
--	RETURNS:
--
--	NOTES:
--	A slot called when data is ready on the socket. reads all bytes into QBuffer. 
--	the QBuffer is attached to a QAudioOutput which plays the audio as the data is read in
--	off the socket.
-----------------------------------------------------------------------------------------*/
void StreamRecv::readBytes()
{
	data = tcp->readAll();

	tmpData->append(data);


	if (firstRun)
	{
		firstRun = false;

		QAudioFormat format;
		format.setChannelCount(1);
		format.setSampleRate(44100);
		format.setSampleSize(16);
		format.setCodec("audio/pcm");
		format.setByteOrder(QAudioFormat::LittleEndian);
		format.setSampleType(QAudioFormat::SignedInt);

		QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
		if (!info.isFormatSupported(format))
		{
			format = info.nearestFormat(format);
		}

		aOutput = new QAudioOutput(format, audioParent);
		aOutput->setVolume(1);
		
		buffer = new QBuffer(tmpData);
		buffer->open(QIODevice::ReadOnly);

		connect(aOutput, &QAudioOutput::stateChanged, [](QAudio::State newState)
		{
			if (newState == QAudio::IdleState)   // finished playing (i.e., no more data)
			{
				qDebug() << "finished playing sound";
				
			}

			if (newState == QAudio::ActiveState)   // finished playing (i.e., no more data)
			{
				qDebug() << "started playing sound";

			}

			if (newState == QAudio::StoppedState)
			{
				qDebug() << "stopped unexepctedly playing sound";
			}
		});

		aOutput->start(buffer);
	}
}
