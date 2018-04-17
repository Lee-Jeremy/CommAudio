/*----------------------------------------------------------------------
-- SOURCE FILE:	TabFileTx.cpp		- File that contains a definition of
--									  TabFileTx class to enables UI
--									  functionalities of tab for file
--									  file transfer.
--
-- PROGRAM:		ComAudio
--
-- FUNCTIONS:
--				TabFileTx(QWidget *parent)
--				~TabFileTx()
--				void connect()
--				void download()
--				void closeWindow()
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee, Delan Elliot
--
-- NOTES:
-- A class definition of TabFileTx class.
-- This is a QWidget class to make the tab GUI for file transfer
-- functional and allow UI components to call functions that connects to
-- server, download files, and close the tab.
----------------------------------------------------------------------*/
#include "TabFileTx.h"

/*----------------------------------------------------------------------
-- FUNCTION:	TabFileTx
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee, Delan Elliot
--
-- INTERFACE:	TabFileTx(QWidget *parent)
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
-- Class constructor.
-- Initializes UI and connects UI components to corresponding functions.
----------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------
-- FUNCTION:	~TabFileTx
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee, Delan Elliot
--
-- INTERFACE:	~TabFileTx()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
-- Class desctructor.
-- Releases memory allocated for members.
----------------------------------------------------------------------*/
TabFileTx::~TabFileTx()
{
	delete ui;
}

/*----------------------------------------------------------------------
-- FUNCTION:	connect
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee, Delan Elliot
--
-- INTERFACE:	void connect()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
-- Function called by the "Connect" push button.
----------------------------------------------------------------------*/
void TabFileTx::connect()
{
	
}

/*----------------------------------------------------------------------
-- FUNCTION:	download
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee, Delan Elliot
--
-- INTERFACE:	void download()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
-- Function called by the "Download" push button.
----------------------------------------------------------------------*/
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


/*----------------------------------------------------------------------
-- FUNCTION:	closeWindow
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee, Delan Elliot
--
-- INTERFACE:	void closeWindow()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
-- Emits a signal to close the corresponding tab and closes itself.
----------------------------------------------------------------------*/
void TabFileTx::closeWindow()
{
	emit sigCloseTab(this);
	this->close();
}
