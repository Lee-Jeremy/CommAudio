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
-- PROGRAMMER:	Jeremy Lee, Delan Elliot
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
-- PROGRAMMER:	Jeremy Lee, Delan Elliot
--
-- INTERFACE:	TabAudioChat(Mode mode, QWidget *parent)
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
-- Class constructor.
-- Sets a mode (client or server) and connects UI components to
-- corresponding functions.
----------------------------------------------------------------------*/
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

	QObject::connect(ui->lineEdit_ip, &QLineEdit::textChanged, qobject_cast<ComAudio*>(this->parent()), &ComAudio::setIp);
	QObject::connect(ui->lineEdit_port, &QLineEdit::textChanged, qobject_cast<ComAudio*>(this->parent()), &ComAudio::setPort);

	QObject::connect(ui->pushButton_start, &QPushButton::pressed, qobject_cast<ComAudio*>(this->parent()), &ComAudio::startVoip);

	QObject::connect(ui->pushButton_stop, &QPushButton::pressed, qobject_cast<ComAudio*>(this->parent()), &ComAudio::stopCurrentTask);
	QObject::connect(ui->pushButton_close, &QPushButton::pressed, this, &TabAudioChat::closeWindow);
}

/*----------------------------------------------------------------------
-- FUNCTION:	TabAudioChat
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee, Delan Elliot
--
-- INTERFACE:	~TabAudioChat()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
-- Class desctructor.
-- Releases memory allocated for members.
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
-- PROGRAMMER:	Jeremy Lee, Delan Elliot
--
-- INTERFACE:	void accept()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
-- Function called by the "Accept" push button.
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
-- PROGRAMMER:	Jeremy Lee, Delan Elliot
--
-- INTERFACE:	void start()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
-- Function called by the "Start" push button.
----------------------------------------------------------------------*/
void TabAudioChat::start()
{

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
void TabAudioChat::closeWindow()
{
	emit sigCloseTab(this);
	this->close();
}
