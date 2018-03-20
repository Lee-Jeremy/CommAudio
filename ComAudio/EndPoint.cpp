#include "EndPoint.h"
#include "global.h"

EndPoint::EndPoint(const char * ipAddr, short port)
	:port(port)
{
	addr = inet_addr(ipAddr);
}