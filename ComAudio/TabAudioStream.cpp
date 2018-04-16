#include "TabAudioStream.h"

TabAudioStream::TabAudioStream(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TabAudioStream)
{
	ui->setupUi(this);

	QObject::connect(ui->pushButton_connect, &QPushButton::pressed, this, &TabAudioStream::connect);
	QObject::connect(ui->pushButton_start, &QPushButton::pressed, this, &TabAudioStream::start);
	QObject::connect(ui->pushButton_stop, &QPushButton::pressed, this, &TabAudioStream::stop);
	QObject::connect(ui->pushButton_close, &QPushButton::pressed, this, &TabAudioStream::closeWindow);
}

TabAudioStream::~TabAudioStream()
{
	delete ui;
}

void TabAudioStream::connect()
{
	
}

void TabAudioStream::start()
{

}

void TabAudioStream::stop()
{

}

void TabAudioStream::closeWindow()
{
	emit sigCloseTab(this);
	this->close();
}
