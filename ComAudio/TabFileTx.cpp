#include "TabFileTx.h"

TabFileTx::TabFileTx(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TabFileTx)
{
	ui->setupUi(this);

	QObject::connect(ui->pushButton_connect, &QPushButton::pressed, this, &TabFileTx::connect);
	QObject::connect(ui->pushButton_download, &QPushButton::pressed, this, &TabFileTx::download);
	QObject::connect(ui->pushButton_close, &QPushButton::pressed, this, &TabFileTx::closeWindow);
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

void TabFileTx::closeWindow()
{
	emit sigCloseTab(this);
	this->close();
}
