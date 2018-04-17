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
	bool startMulticastTx();
	bool startMulticastRx();

public slots:
	void playData();
	void sendDatagram();

private:
	QUdpSocket*		mSocket = nullptr;
	//QUdpSocket*		mSocketIPv6;
	QUdpSocket*		mOutputSocket = nullptr;
	QHostAddress*	mGroupAddr4 = nullptr;
	QHostAddress*	mGroupAddr6 = nullptr;
	QHostAddress*	mDestAddr4 = nullptr;
	QHostAddress*	mDestAddr6 = nullptr;
	QBuffer*		mBuffer = nullptr;
	QByteArray*		mByteArray = nullptr;
	QAudioFormat*	mFormat = nullptr;
	QAudioOutput*	mAudioOutput = nullptr;
	QAudioInput*	mAudioInput = nullptr;
	QIODevice*		mDevice = nullptr;

	TaskType mTask;
};