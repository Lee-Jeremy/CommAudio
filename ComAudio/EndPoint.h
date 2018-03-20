#pragma once

#define MAX_ADDR_LEN 255

class EndPoint {
public:
	int addr;
	char strAddr[MAX_ADDR_LEN];
	short port;

	EndPoint(const char *, short);
};
