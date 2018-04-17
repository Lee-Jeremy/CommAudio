#include "TabFileTx.h"

TabFileTx::TabFileTx(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TabFileTx)
{
	ui->setupUi(this);

	QObject::connect(ui->pushButton_connect, &QPushButton::pressed, qobject_cast<ComAudio*>(this->parent()), &ComAudio::startFileTransfer);

	//QObject::connect(ui->pushButton_download, &QPushButton::pressed, this, &TabFileTx::download);
	QObject::connect(ui->pushButton_close, &QPushButton::pressed, this, &TabFileTx::closeWindow);

	QObject::connect(ui->lineEdit_ip, &QLineEdit::textChanged, this, &TabFileTx::ipChanged);
	QObject::connect(ui->lineEdit_port, &QLineEdit::textChanged, this, &TabFileTx::portChanged);

}

TabFileTx::~TabFileTx()
{
	delete ui;
}

void TabFileTx::connect()
{
	
}

void TabFileTx::download()
{

}

void TabFileTx::ipChanged()
{
	((ComAudio*)this->parent())->ipAddr = ui->lineEdit_ip->text();
}

void TabFileTx::portChanged()
{
	((ComAudio*)this->parent())->clientPort = ui->lineEdit_port->text().toInt();
}

void TabFileTx::closeWindow()
{
	emit sigCloseTab(this);
	this->close();
}
