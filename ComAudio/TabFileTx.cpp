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
-- PROGRAMMER:	Jeremy Lee
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
-- PROGRAMMER:	Jeremy Lee
--
-- INTERFACE:	TabFileTx(QWidget *parent)
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
----------------------------------------------------------------------*/
TabFileTx::TabFileTx(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TabFileTx)
{
	ui->setupUi(this);

	QObject::connect(ui->pushButton_connect, &QPushButton::pressed, this, &TabFileTx::connect);
	QObject::connect(ui->pushButton_download, &QPushButton::pressed, this, &TabFileTx::download);
	QObject::connect(ui->pushButton_close, &QPushButton::pressed, this, &TabFileTx::closeWindow);
}

/*----------------------------------------------------------------------
-- FUNCTION:	~TabFileTx
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee
--
-- INTERFACE:	~TabFileTx()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
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
-- PROGRAMMER:	Jeremy Lee
--
-- INTERFACE:	void connect()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
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
-- PROGRAMMER:	Jeremy Lee
--
-- INTERFACE:	void download()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
----------------------------------------------------------------------*/
void TabFileTx::download()
{

}

/*----------------------------------------------------------------------
-- FUNCTION:	closeWindow
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee
--
-- INTERFACE:	void closeWindow()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
----------------------------------------------------------------------*/
void TabFileTx::closeWindow()
{
	emit sigCloseTab(this);
	this->close();
}
