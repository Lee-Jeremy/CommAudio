/*----------------------------------------------------------------------
-- SOURCE FILE:	TabAudioChat.cpp	- File that contains a definition of
--									  TabAudioChat class to enables UI
--									  functionalities of tab for audio chat.
--
-- PROGRAM:		ComAudio
--
-- FUNCTIONS:
--				TabAudioChat(Mode mode, QWidget *parent)
--				~TabAudioChat()
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
-- A class definition of TabAudioChat class.
-- This is a QWidget class to make the tab GUI for audio chat functional
-- and allow UI components to call functions that connects to server or
-- accepts incoming connection request, start the audio chat task, stop
-- the task, and close the tab.
----------------------------------------------------------------------*/
#include "TabAudioChat.h"

/*----------------------------------------------------------------------
-- FUNCTION:	TabAudioChat
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee
--
-- INTERFACE:	TabAudioChat(Mode mode, QWidget *parent)
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
----------------------------------------------------------------------*/
TabAudioChat::TabAudioChat(Mode mode, QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TabAudioChat)
{
	ui->setupUi(this);

	if (mode == Mode::client) // client mode
	{
		QObject::connect(ui->pushButton_connect, &QPushButton::pressed, this, &TabAudioChat::connect);
	} 
	else if (mode == Mode::server) // server mode
	{
		ui->lineEdit_ip->setDisabled(true);
		ui->lineEdit_port->setDisabled(true);
		ui->pushButton_connect->setText("Accept");
		QObject::connect(ui->pushButton_connect, &QPushButton::pressed, this, &TabAudioChat::accept);
	}

	QObject::connect(ui->pushButton_start, &QPushButton::pressed, this, &TabAudioChat::start);
	QObject::connect(ui->pushButton_stop, &QPushButton::pressed, this, &TabAudioChat::stop);
	QObject::connect(ui->pushButton_close, &QPushButton::pressed, this, &TabAudioChat::closeWindow);
}

/*----------------------------------------------------------------------
-- FUNCTION:	TabAudioChat
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee
--
-- INTERFACE:	~TabAudioChat()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
----------------------------------------------------------------------*/
TabAudioChat::~TabAudioChat()
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
void TabAudioChat::connect()
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
void TabAudioChat::accept()
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
void TabAudioChat::start()
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
void TabAudioChat::stop()
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
void TabAudioChat::closeWindow()
{
	emit sigCloseTab(this);
	this->close();
}
