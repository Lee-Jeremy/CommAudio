#include "TCPSocket.h"



TCPSocket::TCPSocket()
{

}


TCPSocket::~TCPSocket()
{
}

int TCPSocket::recv(const char * buffer, int len)
{
	return 0;
}

int TCPSocket::send(const char * buffer, int len)
{
	return 0;
}



int TCPSocket::listen()
{

}

int TCPSocket::accept()
{

}

bool TCPSocket::connect(QString hostAddr, quint16 port)
{
	socket.connectToHost(hostAddr, port);
	return socket.waitForConnected();
}

int TCPSocket::stream()
{

}

int TCPSocket::close()
{
	socket.close();
}
