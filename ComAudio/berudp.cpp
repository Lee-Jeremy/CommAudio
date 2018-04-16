#include "BerUdp.h"
#include <QUdpSocket>

BerUdp::BerUdp(QObject *parent)
	: QIODevice(parent)
{
	startup();
}

// Initialization
void BerUdp::startup()
{
	dev_write = new QUdpSocket(this);
	dev_read = new QUdpSocket(this);

	m_buffer.open(QIODevice::ReadWrite);
	open(QIODevice::ReadWrite);
}

// Set a virtual connection to "host"
void BerUdp::setHostToWrite(const QHostAddress &address, quint16 port)
{
	dev_write->connectToHost(address, port);
	dev_write->waitForConnected();
}

// Bind a port for receive datagrams
void BerUdp::setPortToRead(quint16 port)
{
	dev_read->bind(port);
	dev_read->open(QIODevice::ReadOnly);

	connect(dev_read, &QIODevice::readyRead,
		this, &QIODevice::readyRead);
	connect(dev_read, &QIODevice::readyRead,
		this, &BerUdp::onReceive);
}

// Flush written data
bool BerUdp::flush()
{
	return dev_write->flush();
}

// Returns the number of bytes that are available for reading.
// Subclasses that reimplement this function must call 
// the base implementation in order to include the size of the buffer of QIODevice.
qint64 BerUdp::bytesAvailable() const
{
	qint64 my_size = m_buffer.size();
	qint64 builtin_size = QIODevice::bytesAvailable();

	return (my_size + builtin_size);
}

bool BerUdp::waitForReadyRead(int msecs)
{
	return dev_read->waitForReadyRead(msecs);
}

// Socket device should give sequential access
bool BerUdp::isSequential() const
{
	return true;
}

// This function is called by QIODevice. 
// It is main function for provide access to read data from QIODevice-derived class.
// (Should be reimplemented when creating a subclass of QIODevice).
qint64 BerUdp::readData(char *data, qint64 maxSize)
{
	int n = m_buffer.read(data, maxSize);

	// clear the data which has already been read
	QByteArray& ba = m_buffer.buffer();
	ba.remove(0, n);
	m_buffer.seek(0);

	return n;
}

// This function is called by QIODevice.
// It is main function for provide access to write data to QIODevice-derived class.
// (Should be reimplemented when creating a subclass of QIODevice).
qint64 BerUdp::writeData(const char *data, qint64 maxSize)
{
	return dev_write->write(data, maxSize);
}

// Read new available datagram
void BerUdp::read_udp_datagram()
{
	int dSize = dev_read->pendingDatagramSize();
	QByteArray dtg(dSize, 0);
	dev_read->readDatagram(dtg.data(), dtg.size());

	write_new_data_to_buffer(dtg);
}

// Write received data to the end of internal intermediate buffer
void BerUdp::write_new_data_to_buffer(QByteArray dtg)
{
	int buf_read_pos = m_buffer.pos();
	m_buffer.seek(m_buffer.size());
	m_buffer.write(dtg);
	m_buffer.seek(buf_read_pos);
}

// Is called on readyRead signal
void BerUdp::onReceive()
{
	bool available = dev_read->hasPendingDatagrams();
	if (available)
	{
		read_udp_datagram();
	}
}