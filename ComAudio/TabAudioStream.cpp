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
-- PROGRAMMER:	Jeremy Lee, Delan Elliot
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
-- PROGRAMMER:	Jeremy Lee, Delan Elliot
--
-- INTERFACE:	TabAudioStream(QWidget *parent)
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
-- Class constructor.
-- Initializes UI and connects UI components to corresponding functions.
----------------------------------------------------------------------*/
TabAudioStream::TabAudioStream(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TabAudioStream)
{
	ui->setupUi(this);

	QObject::connect(ui->pushButton_connect, &QPushButton::pressed, qobject_cast<ComAudio*>(this->parent()), &ComAudio::getFileList);

	QObject::connect(ui->pushButton_start, &QPushButton::pressed, qobject_cast<ComAudio*>(this->parent()), &ComAudio::startStream);
	QObject::connect(ui->pushButton_stop, &QPushButton::pressed, qobject_cast<ComAudio*>(this->parent()), &ComAudio::stopCurrentTask);
	QObject::connect(ui->pushButton_close, &QPushButton::pressed, this, &TabAudioStream::closeWindow);

	QObject::connect(ui->lineEdit_ip, &QLineEdit::textChanged, qobject_cast<ComAudio*>(this->parent()), &ComAudio::setIp);
	QObject::connect(ui->lineEdit_port, &QLineEdit::textChanged, qobject_cast<ComAudio*>(this->parent()), &ComAudio::setPort);
}

/*----------------------------------------------------------------------
-- FUNCTION:	~TabAudioStream
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Jeremy Lee
--
-- PROGRAMMER:	Jeremy Lee, Delan Elliot
--
-- INTERFACE:	~TabAudioStream()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
-- Class desctructor.
-- Releases memory allocated for members.
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
-- PROGRAMMER:	Jeremy Lee, Delan Elliot
--
-- INTERFACE:	void stop()
--
-- ARGUMENT:    void
--
-- RETURNS:	    void
--
-- NOTES:
-- Function called by the "Stop" push button.
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
void TabAudioStream::closeWindow()
{
	emit sigCloseTab(this);
	this->close();
}
