#include "CircBuffer.h"



CircBuffer::CircBuffer()
	: mBytesAvailable(DEFAULT_BUFFER_SIZE)
	, mBytesWritten(0)
	, mWriteIndex(0)
	, mReadIndex(0)
	, mBufferSize(DEFAULT_BUFFER_SIZE)
{
	mBuffer = new qint8[DEFAULT_BUFFER_SIZE];
	mEndPtr = mBuffer + DEFAULT_BUFFER_SIZE;
	mWritePtr = mBuffer;
	mReadPtr = mBuffer;
	std::memset(mBuffer, 0, DEFAULT_BUFFER_SIZE);
}

CircBuffer::CircBuffer(uint bufferSize)
	: mBytesAvailable(bufferSize)
	, mBytesWritten(0)
	, mWriteIndex(0)
	, mReadIndex(0)
	, mBufferSize(bufferSize)
{
	mBuffer = new qint8[bufferSize];
	mEndPtr = mBuffer + bufferSize;
	mWritePtr = mBuffer;
	mReadPtr = mBuffer;
	std::memset(mBuffer, 0, bufferSize);
}

CircBuffer::CircBuffer(CircBuffer& other)
{

}


CircBuffer::~CircBuffer()
{
	delete[] mBuffer;
}

/*
Write to the CircBuffer
Returns 1 on success, 0 on failure
*/
int CircBuffer::write(qint8* src, uint bytesToWrite)
{
	// Haven't handled case where writePtr > readPtr
	if (bytesToWrite > mBytesAvailable || bytesToWrite > (mReadPtr - mWritePtr) && (mReadPtr - mWritePtr) > 0)	// may change last condition logic
	{
		return 0;
	}

	// Case: CircBuffer is empty and readPtr == writePtr == mBuffer
	if (mReadPtr == mWritePtr && mReadPtr == mBuffer && bytesToWrite <= mBytesAvailable)
	{
		std::memcpy(mBuffer, src, bytesToWrite);
		mBytesAvailable -= bytesToWrite;
		mBytesWritten += bytesToWrite;
		mWritePtr += bytesToWrite;
		return 1;
	}
	// Case: writePtr is ahead of readPtr
	if (mWritePtr >= mReadPtr)
	{
		uint diff = mEndPtr - mWritePtr;
		if (bytesToWrite > diff)
		{
			std::memcpy(mWritePtr, src, diff);
			std::memcpy(mBuffer, src + diff, bytesToWrite - diff);
			mBytesAvailable -= bytesToWrite;
			mBytesWritten += bytesToWrite;
			mWritePtr = mBuffer + (bytesToWrite - diff);
			return 1;
		}
		// Case: writePtr is ahead of readPtr and there is enough room
		else
		{
			std::memcpy(mWritePtr, src, bytesToWrite);
			mBytesAvailable -= bytesToWrite;
			mBytesWritten += bytesToWrite;
			mWritePtr += bytesToWrite;
			return 1;
		}
	}
	if (mReadPtr > mWritePtr)	// Case: readPtr is ahead of writePtr
	{
		uint diff = mReadPtr - mWritePtr;
		if (diff > bytesToWrite)
		{
			std::memcpy(mWritePtr, src, bytesToWrite);
			mBytesAvailable -= bytesToWrite;
			mBytesWritten += bytesToWrite;
			mWritePtr += bytesToWrite;
			return 1;
		}
	}

	return 0;
}

/*
Read from the CircBuffer. 
pass in either void* from the QAudioBuffer
ie: 
Returns 1 on success, 0 on failure
*/
int CircBuffer::read(void* dest, uint bytesToRead)
{
	// If trying to read more bytes than written
	int result;
	if (bytesToRead > mBytesWritten || bytesToRead > (mWritePtr - mReadPtr) && (mWritePtr - mReadPtr) > 0) // May change last condition logic
	{
		result = mWritePtr - mReadPtr;
		return 0;
	}

	// Case: writePtr is ahead of readPtr
	if (mWritePtr > mReadPtr)	
	{
		std::memcpy(dest, mBuffer, bytesToRead);
		mBytesAvailable += bytesToRead;
		mBytesWritten -= bytesToRead;
		mReadPtr += bytesToRead;
		return 1;
	}
	// Case: readPtr is ahead of writePtr
	if (mReadPtr >= mWritePtr)	
	{
		uint diff = mEndPtr - mReadPtr;						// Difference betw. endPtr and readPtr
		// Case: reading segment wraps around to beginning
		if (bytesToRead > diff)
		{
			std::memcpy(dest, mReadPtr, diff);				// Copy from readPtr to endPtr
			std::memcpy(dest, mBuffer, bytesToRead - diff);	// Copy remaining bytes from index 0
			mBytesAvailable += bytesToRead;
			mBytesWritten -= bytesToRead;
			mReadPtr = mBuffer + (bytesToRead - diff);
			return 1;
		}
		// Case: reading segment does not reach end of buffer
		else
		{
			std::memcpy(dest, mReadPtr, bytesToRead);
			mBytesAvailable += bytesToRead;
			mBytesWritten -= bytesToRead;
			mReadPtr += bytesToRead;
			return 1;
		}
	}

	return 0;
}

// Pull in, reads a constant 1024 Bytes per pull.
qint8* operator<<(CircBuffer& lhs, qint8* rhs)
{
	lhs.write(rhs, DEFAULT_WRITE_SIZE);
	return rhs;
}

// Push out, pushes a constant 1024 Bytes per push
QAudioBuffer& operator>>(QAudioBuffer& lhs, CircBuffer rhs)
{
	rhs.read(lhs.data(), DEFAULT_READ_SIZE);
	return lhs;
}



uint CircBuffer::getBytesAvailable() { return mBytesAvailable; }

uint CircBuffer::getBytesWritten() { return mBytesWritten; }
