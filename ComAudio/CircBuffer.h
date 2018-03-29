#pragma once
#include <QtCore>

#define DEFAULT_BUFFER_SIZE		8192

class CircBuffer
{
public:
	CircBuffer();
	CircBuffer(uint bufferSize);
	CircBuffer(CircBuffer& other);
	~CircBuffer();
	int write(qint8* src, uint inputSize);
	int read(qint8* dest, uint numBytes);
	uint getBytesAvailable();
	uint getBytesWritten();

private:
	qint8*	mBuffer;
	const qint8* mEndPtr;
	uint	mBytesAvailable;
	uint	mBytesWritten;
	uint	mWriteIndex;	// Might not use, depending on copy implementation
	uint	mReadIndex;		// Might not use, depending on copy implementation 
	qint8*	mWritePtr;
	qint8*	mReadPtr;
};

