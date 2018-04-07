#include "CircBuffer.h"

void testCircBuffer()
{
	const int bufsize = 128;

	qint8 input[bufsize];
	qint8 output[bufsize];

	for (int i = 0; i < bufsize; i++)
	{
		input[i] = i;
	}

	CircBuffer* cb = new CircBuffer(32);
	cb->write(input, 16);	//pass
	cb->read(output, 16);	//pass
	cb->write(input + 16, 32); // pass
	cb->read(output + 16, 16); // pass
	cb->read(output + 32, 16); // pass
	delete cb;

	memset(output, 0, bufsize);

	cb = new CircBuffer(32);
	cb->write(input, 27);
	cb->read(output, 12);
	cb->write(input, 14);
	cb->read(output + 12, 29);

	memset(output, 0, bufsize);
	delete cb;
	
	cb = new CircBuffer(bufsize);
	QAudioBuffer* qb = new QAudioBuffer();

	
	cb << input;



}