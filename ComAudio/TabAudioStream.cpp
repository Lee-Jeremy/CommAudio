/*----------------------------------------------------------------------
-- SOURCE FILE:	TabAudioStream.cpp	- File that contains a definition of
--									  TabAudioStream class to enables UI
--									  functionalities of tab for audio
--									  streaming.
--
-- PROGRAM:		ComAudio
--
-- FUNCTIONS:
--				TabAudioStream(QWidget *parent)
--				~TabAudioStream()
--				void connect()
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
-- A class definition of TabAudioStream class.
-- This is a QWidget class to make the tab GUI for audio streaming
-- functional and allow UI components to call functions that connects
-- to server, start the audio streaming task, stop the task, and close
-- the tab.
----------------------------------------------------------------------*/
#include "TabAudioStream.h"

/*----------------------------------------------------------------------
-- FUNCTION:	TabAudioStream
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee
--
-- INTERFACE:	TabAudioStream(QWidget *parent)
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
----------------------------------------------------------------------*/
TabAudioStream::TabAudioStream(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TabAudioStream)
{
	ui->setupUi(this);

	QObject::connect(ui->pushButton_connect, &QPushButton::pressed, this, &TabAudioStream::connect);
	QObject::connect(ui->pushButton_start, &QPushButton::pressed, this, &TabAudioStream::start);
	QObject::connect(ui->pushButton_stop, &QPushButton::pressed, this, &TabAudioStream::stop);
	QObject::connect(ui->pushButton_close, &QPushButton::pressed, this, &TabAudioStream::closeWindow);
}

/*----------------------------------------------------------------------
-- FUNCTION:	~TabAudioStream
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee
--
-- INTERFACE:	~TabAudioStream()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
----------------------------------------------------------------------*/
TabAudioStream::~TabAudioStream()
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
void TabAudioStream::connect()
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
void TabAudioStream::start()
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
void TabAudioStream::stop()
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
void TabAudioStream::closeWindow()
{
	emit sigCloseTab(this);
	this->close();
}
