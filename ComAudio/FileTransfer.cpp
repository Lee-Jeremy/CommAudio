#include "FileTransfer.h"

FileTransfer::FileTransfer(QObject *parent, QTcpSocket * tcp, QString fileName)
	: QObject(parent)
	, tcp(tcp)
{
	outputPath = "./" + fileName;
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


void FileTransfer::readBytes()
{
	data = tcp->readAll();
	qDebug() << outputPath;

	int i = 0;
	if (!outputFile.isOpen())
	{
		outputFile.open(QFile::WriteOnly | QIODevice::Append);
		qDebug() << "wrote" << QString::number(i++);
	}

	outputFile.write(data);
	outputFile.close();
}