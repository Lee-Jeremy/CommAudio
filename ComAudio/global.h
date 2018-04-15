#pragma once

#pragma comment(lib, "ws2_32.lib")

#include "Winsock2.h"

#define SOCKET_DGRAM 10
#define SOCKET_STREAM 20

#define DEFAULT_PORT 9898

#define START_SIZE 1000


typedef struct StartPacket {
	char type[10];

} StartPacket;



enum TaskType
{
	SONG_STREAM = 0x10,
	VOICE_STREAM = 0x20,
	MULTICAST_LISTEN = 0x40,
	MULTICAST_SEND = 0x80,
	FILE_TRANSFER = 0xf0
};