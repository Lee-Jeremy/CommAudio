#pragma once
#include "global.h"




class Socket
{
public:
	Socket(int type);
	~Socket();

	int bind();
	int listen();
	int accept();

	int getType();
	int send();
	int sendto(const char *);
	int recv();
	int recvfrom();

private:
	int mType;
};

