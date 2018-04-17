#pragma once

#pragma comment(lib, "ws2_32.lib")

#include "Winsock2.h"

#define SOCKET_DGRAM		10
#define SOCKET_STREAM		20


#define DEFAULT_PORT		9898
#define DEFAULT_UDP_PORT	42069
#define DEFAULT_TCP_PORT	42070

#define START_SIZE			1000

#define VOIP_SAMPLERATE		48000
#define VOIP_SAMPLESIZE		16
#define VOIP_NUMCHANNEL		2
#define VOIP_BUFFERSIZE		16384


typedef struct StartPacket {
	char type[10];

} StartPacket;

enum TaskType
{
	STREAM_FILE_LIST = 0x09,
	SONG_STREAM = 0x10,
	VOICE_STREAM = 0x11,
	MULTICAST_LISTEN = 0x12,
	MULTICAST_SEND = 0x13,
	FILE_LIST = 0x14,
	FILE_TX = 0x15
};