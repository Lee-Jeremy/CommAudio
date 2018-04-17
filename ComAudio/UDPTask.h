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
#include <QNetworkInterface>
#include "global.h"


class UDPTask : public QObject
{
	Q_OBJECT
public:
	UDPTask(QObject* parent, QUdpSocket* socket, TaskType task, QTcpSocket* tcp);
	UDPTask(QObject* parent);
	~UDPTask();
	void startVOIP(QAudioOutput* output, QAudioInput* input, QAudioFormat* format);
	bool endVOIP();
	bool startMulticastSend();
	bool startMulticastListen();

public slots:
	void playData();
	void sendDatagram();

private:
	QUdpSocket*		mSocket;
	QUdpSocket*		mSocketIPv6;
	QUdpSocket*		mOutputSocket;
	QHostAddress*	mGroupAddr4;
	QHostAddress*	mGroupAddr6;
	QHostAddress*	mDestAddr4;
	QHostAddress*	mDestAddr6;
	QBuffer*		mBuffer;
	QByteArray*		mByteArray;
	QAudioFormat*	mFormat;
	QAudioOutput*	mAudioOutput;
	QAudioInput*	mAudioInput;
	QIODevice*		mDevice;

	TaskType mTask;
};