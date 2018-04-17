/*----------------------------------------------------------------------
-- SOURCE FILE:	FileTransfer.cpp	- Reads from and sends a file over a
--									- tcp socket
--
-- PROGRAM:		ComAudio
--
-- FUNCTIONS:
--					FileTransfer(QObject *parent, QTcpSocket * tcp, QString fileName);
--					~FileTransfer();
--					void setOutputFile(QString path);
--					void stop();
--					void start();
--					void readBytes();
--
--
-- DATE:		April 10, 2018
--
-- DESIGNER:	Delan Elliot
--
-- PROGRAMMER:	Delan Elliot
--
-- NOTES:
-- Opens a file and reads from the socket until the socket closes.
----------------------------------------------------------------------*/

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



/*-----------------------------------------------------------------------------------------
--	FUNCTION:	setOutputFile
--
--	DATE:		Apr. 10, 2018
--
--	DESIGNER:	D. Elliot
--
--	PROGRAMMER:	D. Elliot
--
--	INTERFACE:	void FileTransfer::setOutputFile(QString path)
--					QString path: the file path to read from
--	RETURNS:
--
--	NOTES:
--	It sets the variable.
-----------------------------------------------------------------------------------------*/
void FileTransfer::setOutputFile(QString path)
{
	outputPath = path;
}


/*-----------------------------------------------------------------------------------------
--	FUNCTION:	stop
--
--	DATE:		Apr. 10, 2018
--
--	DESIGNER:	D. Elliot
--
--	PROGRAMMER:	D. Elliot
--
--	INTERFACE:	void FileTransfer::stop()
--	RETURNS:
--
--	NOTES:
--	Stops an inprogress file transfer. disconnects the socket.
-----------------------------------------------------------------------------------------*/
void FileTransfer::stop()
{
	disconnect(tcp, 0, 0, 0);
	tcp->close();
	outputFile.close();
}


void FileTransfer::start()
{

}

/*-----------------------------------------------------------------------------------------
--	FUNCTION:	readBytes
--
--	DATE:		Apr. 10, 2018
--
--	DESIGNER:	D. Elliot
--
--	PROGRAMMER:	D. Elliot
--
--	INTERFACE:	void FileTransfer::stop()
--	RETURNS:
--
--	NOTES:
--	Reads from the socket into the file.
-----------------------------------------------------------------------------------------*/
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
