#include "TabAudioChat.h"

TabAudioChat::TabAudioChat(Mode mode, QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TabAudioChat)
{
	ui->setupUi(this);

	if (mode == Mode::client) // client mode
	{
		QObject::connect(ui->pushButton_start, &QPushButton::pressed, this, &TabAudioChat::connect);
	} 
	else if (mode == Mode::server) // server mode
	{
		ui->lineEdit_ip->setDisabled(true);
		ui->lineEdit_port->setDisabled(true);
		ui->pushButton_start->setText("Accept");
		QObject::connect(ui->pushButton_start, &QPushButton::pressed, this, &TabAudioChat::accept);
	}

	QObject::connect(ui->pushButton_start, &QPushButton::pressed, this, &TabAudioChat::start);
	QObject::connect(ui->pushButton_start, &QPushButton::pressed, qobject_cast<ComAudio*>(this->parent()), &ComAudio::startVoip);

	QObject::connect(ui->pushButton_stop, &QPushButton::pressed, this, &TabAudioChat::stop);
	QObject::connect(ui->pushButton_close, &QPushButton::pressed, this, &TabAudioChat::closeWindow);
}

TabAudioChat::~TabAudioChat()
{
	delete ui;
}

void TabAudioChat::connect()
{

}

void TabAudioChat::accept()
{

}

void TabAudioChat::start()
{

}

void TabAudioChat::stop()
{

}

void TabAudioChat::ipChanged()
{
	((ComAudio*)this->parent())->ipAddr = ui->lineEdit_ip->text();
}

void TabAudioChat::portChanged()
{
	((ComAudio*)this->parent())->clientPort = ui->lineEdit_port->text().toInt();
}

void TabAudioChat::closeWindow()
{
	emit sigCloseTab(this);
	this->close();
}
