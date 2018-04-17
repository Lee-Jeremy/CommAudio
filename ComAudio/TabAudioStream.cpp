#include "TabAudioStream.h"

TabAudioStream::TabAudioStream(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TabAudioStream)
{
	ui->setupUi(this);

	QObject::connect(ui->pushButton_connect, &QPushButton::pressed, this, &TabAudioStream::connect);
	QObject::connect(ui->pushButton_start, &QPushButton::pressed, qobject_cast<ComAudio*>(this->parent()), &ComAudio::startStream);
	QObject::connect(ui->pushButton_stop, &QPushButton::pressed, qobject_cast<ComAudio*>(this->parent()), &ComAudio::stopCurrentTask);
	QObject::connect(ui->pushButton_close, &QPushButton::pressed, this, &TabAudioStream::closeWindow);

	QObject::connect(ui->lineEdit_ip, &QLineEdit::textChanged, this, &TabAudioStream::ipChanged);
	QObject::connect(ui->lineEdit_port, &QLineEdit::textChanged, this, &TabAudioStream::portChanged);
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

void TabAudioStream::ipChanged()
{
	((ComAudio*)this->parent())->ipAddr = ui->lineEdit_ip->text();
}

void TabAudioStream::portChanged()
{
	((ComAudio*)this->parent())->clientPort = ui->lineEdit_port->text().toInt();
}

void TabAudioStream::closeWindow()
{
	emit sigCloseTab(this);
	this->close();
}
