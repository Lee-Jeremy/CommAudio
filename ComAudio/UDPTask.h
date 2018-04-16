#pragma once
#include <QUdpSocket>
#include <QBuffer>
#include <QByteArray>
#include <QUdpSocket>
#include <QAudioOutput>
#include <QAudioInput>
#include <QDataStream>
#include <QIODevice>
#include <QTcpSocket>
#include "global.h"


class UDPTask : public QObject
{
	Q_OBJECT
public:
	UDPTask(QObject* parent, QUdpSocket* socket, TaskType task, QTcpSocket* tcp);
	~UDPTask();
	bool connectToHost();
	int sendTo();
	int recvFrom();
	bool start();
	bool startVOIP(QAudioOutput* output, QAudioInput* input, QAudioFormat* format);
	bool endVOIP();

public slots:
	void handleError();
	void playData();

private:
	QUdpSocket*		mSocket;
	QUdpSocket*		mOutputSocket;
	QBuffer*		mBuffer;
	QByteArray*		mByteArray;
	QAudioOutput*	mAudioOutput;
	QAudioInput*	mAudioInput;
	QIODevice*		mDevice;

	TaskType mTask;
};