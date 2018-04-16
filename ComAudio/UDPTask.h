#pragma once
#include <QUdpSocket>
#include <QBuffer>
#include <QByteArray>
#include <QUdpSocket>
#include "CircBuffer.h"
#include "ComAudio.h"
#include "global.h"

class UDPTask
{
public:
	UDPTask(QUdpSocket* socket, TaskType task);
	~UDPTask();
	bool connectToHost();
	int sendTo();
	int recvFrom();
	bool start();
	bool startVOIP(QAudioOutput* output, QAudioInput* input);
	bool endVOIP();
	int startMulticast();
	int endMulticast();

public slots:
	void handleError();

private:
	ComAudio*		mParent;
	QUdpSocket*		mSocket;
	QBuffer*		mBuffer;
	QByteArray*		mByteArray;
	QUdpSocket*		mSocket;
	QAudioOutput*	mAudioOutput;
	QAudioInput*	mAudioInput;

	TaskType mTask;
};