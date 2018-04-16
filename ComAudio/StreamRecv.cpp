#include "StreamRecv.h"

StreamRecv::StreamRecv(QObject *parent, QTcpSocket* tcp)
	: QObject(parent)
	, tcp(tcp)
{
	connect(tcp, &QAbstractSocket::readyRead, this, &StreamRecv::readBytes);

	//TODO add disconnection handling
}

StreamRecv::~StreamRecv()
{
}

void StreamRecv::setupRecv(QString path, QWidget* parent)
{
	tcp->waitForReadyRead();

	data = tcp->readAll();

	outputFile = new QFile("./test.wav");

	if (!outputFile->isOpen())
	{
		outputFile->open(QFile::WriteOnly | QIODevice::Append);
	}

	outputFile->write(data);


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

	aOutput = new QAudioOutput(format, this->parent());
	aOutput->start(outputFile);
	outputFile->close();
}

void StreamRecv::readBytes()
{
	data = tcp->readAll();

	if (!outputFile->isOpen())
	{
		outputFile->open(QFile::WriteOnly | QIODevice::Append);
	}

	outputFile->write(data);
	outputFile->close();
}
