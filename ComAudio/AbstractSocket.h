#pragma once
class AbstractSocket
{
public:
	AbstractSocket();
	virtual ~AbstractSocket();


	virtual int recv(const char * buffer, int len) = 0;
	virtual int send(const char * buffer, int len) = 0;

	virtual int close() = 0;
	virtual int listen() = 0;
};

