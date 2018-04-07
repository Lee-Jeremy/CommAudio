#pragma once
#include <QtCore>
#include <QAudio>
#include <QAudioBuffer>
#include <istream>
#include <ostream>

// Buff Size = 2^18 Bytes, ~262kB
#define DEFAULT_BUFFER_SIZE		262144
#define DEFAULT_READ_SIZE		32
#define DEFAULT_WRITE_SIZE		32

class CircBuffer
{
public:
	CircBuffer();
	CircBuffer(uint bufferSize);
	CircBuffer(CircBuffer& other);
	~CircBuffer();
	int write(qint8* src, uint inputSize);
	int read(void* dest, uint numBytes);
	uint getBytesAvailable();
	uint getBytesWritten();
	

private:
	qint8*	mBuffer;
	const qint8* mEndPtr;
	uint	mBufferSize;
	uint	mBytesAvailable;
	uint	mBytesWritten;
	uint	mWriteIndex;	// Might not use, depending on copy implementation
	uint	mReadIndex;		// Might not use, depending on copy implementation 
	qint8*	mWritePtr;
	qint8*	mReadPtr;
};


//FUCK I'LL DEAL WITH THIS LATER WHAT THE FUCK.

qint8* operator<<(qint8* src, CircBuffer rhs);
QAudioBuffer& operator>>(QAudioBuffer& qb, CircBuffer rhs);

void testCircBuffer();

