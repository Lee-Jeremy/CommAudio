#pragma once

#include <QIODevice>
#include <QBuffer>

class QUdpSocket;
class QHostAddress;

class BerUdp : public QIODevice
{
	Q_OBJECT

public:
	BerUdp(QObject *parent = 0);
	void startup();

	void setHostToWrite(const QHostAddress &address, quint16 port);
	void setPortToRead(quint16 port);

	bool flush();
	qint64 bytesAvailable() const;
	bool waitForReadyRead(int msecs);
	bool isSequential() const;

protected: // Main necessary reimplement
	qint64 readData(char *data, qint64 maxSize);
	qint64 writeData(const char *data, qint64 maxSize);

	private slots:
	void onReceive();

private:
	void read_udp_datagram();
	void write_new_data_to_buffer(QByteArray dtg);

private:
	QUdpSocket * dev_write; // One udp socket to write
	QUdpSocket* dev_read;  // Another udp socket to read

						   // intermediate buffer to store received datagrams
						   // and to provide access to read- and QDataStream- operations
	QBuffer     m_buffer;
};