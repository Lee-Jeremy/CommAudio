#include "FileTransfer.h"

FileTransfer::FileTransfer(QObject *parent, QTcpSocket * tcp)
	: QObject(parent)
	, outputPath("./write-test.wav")
	, tcp(tcp)
{
	outputFile.setFileName(outputPath);
	connect(tcp, &QAbstractSocket::readyRead, this, &FileTransfer::readBytes);
}

FileTransfer::~FileTransfer()
{
}

void FileTransfer::setOutputFile(QString path)
{
	outputPath = path;
}

void FileTransfer::stop()
{
	disconnect(tcp, 0, 0, 0);
	outputFile.close();
}


void FileTransfer::readBytes()
{
	data = tcp->readAll();
	
	if (!outputFile.isOpen())
	{
		outputFile.open(QFile::WriteOnly | QIODevice::Append);
	}

	outputFile.write(data);
	outputFile.close();
}