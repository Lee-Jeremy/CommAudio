#include "TabMulticast.h"

TabMulticast::TabMulticast(Mode mode, QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TabMulticast)
	, IP("231.123.123.123")
{
	ui->setupUi(this);

	if (mode == Mode::client) // client mode
	{
		QObject::connect(ui->pushButton_connect, &QPushButton::pressed, this, &TabMulticast::connect);
	}
	else if (mode == Mode::server) // server mode
	{
		ui->lineEdit_ip->setDisabled(true);
		ui->lineEdit_port->setDisabled(true);
		ui->pushButton_connect->setText("Start Broadcasting");
		QObject::connect(ui->pushButton_start, &QPushButton::pressed, qobject_cast<ComAudio*>(this->parent()), &ComAudio::startMulticastTx);

	}

	QObject::connect(ui->pushButton_stop, &QPushButton::pressed, qobject_cast<ComAudio*>(this->parent()), &ComAudio::stopCurrentTask);
	QObject::connect(ui->pushButton_close, &QPushButton::pressed, this, &TabMulticast::closeWindow);
}

TabMulticast::~TabMulticast()
{
	delete ui;
}

void TabMulticast::connect()
{

}

void TabMulticast::accept()
{

}

void TabMulticast::start()
{

}

void TabMulticast::stop()
{

}

void TabMulticast::closeWindow()
{
	emit sigCloseTab(this);
	this->close();
}
