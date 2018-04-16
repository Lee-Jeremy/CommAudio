#include "TabMulticast.h"

TabMulticast::TabMulticast(Mode mode, QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TabMulticast)
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
		ui->pushButton_connect->setText("Accept");
		QObject::connect(ui->pushButton_connect, &QPushButton::pressed, this, &TabMulticast::accept);
	}

	QObject::connect(ui->pushButton_start, &QPushButton::pressed, this, &TabMulticast::start);
	QObject::connect(ui->pushButton_stop, &QPushButton::pressed, this, &TabMulticast::stop);
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
