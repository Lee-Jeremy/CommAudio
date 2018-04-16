#include "StreamRecv.h"

StreamRecv::StreamRecv(QObject *parent, QTcpSocket* tcp)
	: QObject(parent)
	, tcp(tcp)
	, audioParent(parent)
	, data2(new QByteArray())
{

	firstRun = true;
	connect(tcp, &QAbstractSocket::readyRead, this, &StreamRecv::readBytes);
	//TODO add disconnection handling
}

StreamRecv::~StreamRecv()
{
}



void StreamRecv::readBytes()
{
	data = tcp->readAll();

	data2->append(data);


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
		
		buffer = new QBuffer(data2);
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