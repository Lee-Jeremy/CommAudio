/*----------------------------------------------------------------------
-- SOURCE FILE:	TabMulticast.cpp	- File that contains a definition of
--									  TabMulticast class to enables UI
--									  functionalities of tab for multicast.
--
-- PROGRAM:		ComAudio
--
-- FUNCTIONS:
--				TabMulticast(Mode mode, QWidget *parent)
--				~TabMulticast()
--				void connect()
--				void accept()
--				void start()
--				void stop()
--				void closeWindow()
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee
--
-- NOTES:
-- A class definition of TabMulticast class.
-- This is a QWidget class to make the tab GUI for multicast functional
-- and allow UI components to call functions that connects to server or
-- accepts incoming connection request, start the multicast task, stop
-- the task, and close the tab.
----------------------------------------------------------------------*/
#include "TabMulticast.h"

/*----------------------------------------------------------------------
-- FUNCTION:	TabMulticast
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee
--
-- INTERFACE:	TabMulticast(Mode mode, QWidget *parent)
--
-- ARGUMENT:    mode						- 
--				parent						- 
--
-- RETURNS:	    void
--
-- NOTES:
----------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------
-- FUNCTION:	~TabMulticast
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee
--
-- INTERFACE:	~TabMulticast()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
----------------------------------------------------------------------*/
TabMulticast::~TabMulticast()
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
void TabMulticast::connect()
{

}

/*----------------------------------------------------------------------
-- FUNCTION:	accept
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee
--
-- INTERFACE:	void accept()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
----------------------------------------------------------------------*/
void TabMulticast::accept()
{

}

/*----------------------------------------------------------------------
-- FUNCTION:	start
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee
--
-- INTERFACE:	void start()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
----------------------------------------------------------------------*/
void TabMulticast::start()
{

}

/*----------------------------------------------------------------------
-- FUNCTION:	stop
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee
--
-- INTERFACE:	void stop()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
----------------------------------------------------------------------*/
void TabMulticast::stop()
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
void TabMulticast::closeWindow()
{
	emit sigCloseTab(this);
	this->close();
}
