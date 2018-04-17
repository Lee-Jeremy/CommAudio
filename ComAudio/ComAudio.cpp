/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: ComAudio.cpp -  A General Use Audio Client/Server Application
--
-- PROGRAM:	ComAudio.exe
--
-- FUNCTIONS:
--		ComAudio(QWidget *parent = Q_NULLPTR);
--		~ComAudio();
--		void startPlaying(qint64 sizeTotal);
--		void feedAudio(QByteArray segment);
--		void setDir();
--		void selectDir();
--		void selectFile();
--		void playAudio();
--		void setVolume();
--		void metaDataChanged();
--		void initTab(Task::Type task);
--		void closeTab(QWidget* tab);
--		void startServer();
--		void serverPortValueChanged();
--		void initTabFileTx();
--		QString getFileList();
--		void initTabAudioStream();
--		void initTabAudioChat();
--		void connectedToServerVoip(QUdpSocket * sock, QTcpSocket *);
--		void connectedToServerStream(QTcpSocket * sock);
--		void connectedToServerFileList(QTcpSocket * sock);
--		void connectedToServerStreamFileList(QTcpSocket * sock);
--		void connectedToServerFileTx(QTcpSocket * sock);
--		void clientConnectedStream(QTcpSocket *);
--		void clientConnectedFileList(QTcpSocket *);
--		void clientConnectedStreamFileList(QTcpSocket *);
--		void clientConnectedFileTx(QTcpSocket *);
--		void clientConnectedVoip(QUdpSocket *, QTcpSocket *);
--		void startStream();
--		void startVoip();
--		void startFileList();
--		void startStreamFileList();
--		void startFileTx();
--		void stopCurrentTask();
--		void initTabMulticast();
--		void setIp(const QString&);
--		void setPort(const QString&);
--		void startMulticastTx();
--		void startMulticastRx();
--		int initUi(); // initializes UI components
--		void setTrackInfo(const QString &info);
--
-- DATE: April 15th 2018
--
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu, Jeff Chou
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- NOTES:
-- This is the QT main UI class. As such, there are a lot of "connect" calls here.
--
-- Our high level design uses the TaskManager class to handle connecting to clients and then signal call back functions
-- which handle the higher level logic. Each of the call back functions (E.G. clientConnectedStream) receives the connected 
-- socket - the implicit contract is that these callbacks will only receive a connected socket, otherwise they will not 
-- be called.
----------------------------------------------------------------------------------------------------------------------*/

#include "ComAudio.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ComAudio
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: ComAudio::ComAudio(QWidget *parent)
--				QWidget *parent: Pointer to the parent QWidget
--
-- Returns:  
--
-- Notes:
-- Com Audio constructor.
----------------------------------------------------------------------------------------------------------------------*/
ComAudio::ComAudio(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::ComAudio)
	, taskManager(nullptr)
	, currentTask(nullptr)
{
	int resultInitUi;

	if ((resultInitUi = initUi()) != 0)
	{
		// TODO: error msg
		exit(EXIT_FAILURE);
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: ~ComAudio
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: ComAudio::ComAudio(QWidget *parent)
--
-- Returns:  
--
-- Notes:
-- Com Audio destructor.
----------------------------------------------------------------------------------------------------------------------*/
ComAudio::~ComAudio()
{
	delete ui;
}

#pragma region
/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: startPlaying
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::startPlaying(qint64 sizeTotal)
--				qint64 sizeTotal: the size of the audio file
--
-- Returns:  void
--
-- Notes:
-- Starts audio playback
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::startPlaying(qint64 sizeTotal)
{
	if (audioData != nullptr)
		audioData->clear();
	if (audioStream != nullptr)
		delete audioStream;

	audioData = new QByteArray();
	audioData->resize(1);
	pos = 0;
	audioStream = new QDataStream(audioData, QIODevice::ReadWrite);
	player->setMedia(QMediaContent(), audioStream->device());
	player->play();
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: feedAudio
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::feedAudio(QByteArray segment)
--				QByteArray segment: a segment of an audio file to be added
--
-- Returns:  void
--
-- Notes:
-- Inserts the audio segment into the audio data array and updates the playback position by the segment size
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::feedAudio(QByteArray segment)
{
	//audioData->resize(sizeTotal + 1);
	audioData->insert(pos, segment);
	pos += segment.size();
}

#pragma endregion Public functions

#pragma region
/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: initUi
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: int ComAudio::initUi()
--
-- Returns:  0 on completion
--
-- Notes:
-- Initializes the UI for the the program and connects all of the button signals to their slots
----------------------------------------------------------------------------------------------------------------------*/
int ComAudio::initUi()
{
	ui->setupUi(this);

	serverPort = DEFAULT_PORT;
	// file browser ----------------------------------------------------
	pathLocal = PATH_LOCAL_INIT;
	fileModel = new QFileSystemModel(this);
	fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
	fileModel->setNameFilters(FILE_FILTER);
	fileModel->setNameFilterDisables(false);
	ui->listView_dir_list->setModel(fileModel);
	ui->listView_dir_list->setSelectionMode(QAbstractItemView::ExtendedSelection);
	setDir();

	// UI EVENTS
	connect(ui->pushButton_dir_browse, &QPushButton::pressed, this, &ComAudio::selectDir);
	connect(ui->listView_dir_list, &QAbstractItemView::clicked, this, &ComAudio::selectFile);
	// -----------------------------------------------------------------

	// audio player ----------------------------------------------------
	player = new QMediaPlayer(this);
	playlist = new QMediaPlaylist();
	player->setPlaylist(playlist);
	player->setVolume(75);

	// EVENTS
	connect(player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
	connect(player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
	connect(player, SIGNAL(metaDataChanged()), SLOT(metaDataChanged()));
	connect(playlist, SIGNAL(currentIndexChanged(int)), SLOT(playlistPositionChanged(int)));
	connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
		this, SLOT(statusChanged(QMediaPlayer::MediaStatus)));
	connect(player, SIGNAL(bufferStatusChanged(int)), this, SLOT(bufferingProgress(int)));
	connect(player, SIGNAL(videoAvailableChanged(bool)), this, SLOT(videoAvailableChanged(bool)));
	connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(displayErrorMessage()));

	// UI EVENTS
	connect(ui->pushButton_player_play, &QPushButton::pressed, this, &ComAudio::playAudio);
	// -----------------------------------------------------------------

	// audio slider ----------------------------------------------------
	ui->horizontalSlider_player_progress->setRange(0, player->duration() / SLIDER_DIVISOR);
	// -----------------------------------------------------------------

	// audio volume slider ---------------------------------------------
	connect(ui->horizontalSlider_player_volume, &QSlider::sliderMoved, this, &ComAudio::setVolume);
	// -----------------------------------------------------------------

	// connection ------------------------------------------------------
	//connect(ui->lineEditIp, &QLineEdit::textChanged, this, &ComAudio::ipValueChanged);
	//connect(ui->lineEditPort, &QLineEdit::textChanged, this, &ComAudio::portValueChanged);
	connect(ui->lineEdit_main_server_port, &QLineEdit::textChanged, this, &ComAudio::serverPortValueChanged);
	// -----------------------------------------------------------------

	// task manager ----------------------------------------------------
	taskManager = new TaskManager(this, DEFAULT_PORT);
	connect(ui->pushButton_main_server_start, &QPushButton::pressed, this, &ComAudio::startServer);
	connect(taskManager, &TaskManager::clientConnectedVoip, this, &ComAudio::clientConnectedVoip);
	connect(taskManager, &TaskManager::clientConnectedFileList, this, &ComAudio::clientConnectedFileList);
	connect(taskManager, &TaskManager::clientConnectedStreamFileList, this, &ComAudio::clientConnectedStreamFileList);
	connect(taskManager, &TaskManager::clientConnectedFileTx, this, &ComAudio::clientConnectedFileTx);
	connect(taskManager, &TaskManager::clientConnectedStream, this, &ComAudio::clientConnectedStream);

	connect(taskManager, &TaskManager::connectedToServerFileList, this, &ComAudio::connectedToServerFileList);
	connect(taskManager, &TaskManager::connectedToServerStreamFileList, this, &ComAudio::connectedToServerStreamFileList);
	connect(taskManager, &TaskManager::connectedToServerFileTx, this, &ComAudio::connectedToServerFileTx);
	connect(taskManager, &TaskManager::connectedToServerStream, this, &ComAudio::connectedToServerStream);
	connect(taskManager, &TaskManager::connectedToServerVoip, this, &ComAudio::connectedToServerVoip);

	// task tab view ---------------------------------------------------
	ui->tabWidget_taskViews->removeTab(0);
	ui->tabWidget_taskViews->removeTab(0);
	
	connect(ui->pushButton_tasks_audioStream, &QPushButton::pressed, this, &ComAudio::initTabAudioStream);
	connect(ui->pushButton_tasks_fileTransfer, &QPushButton::pressed, this, &ComAudio::initTabFileTx);
	connect(ui->pushButton_tasks_audioChat, &QPushButton::pressed, this, &ComAudio::initTabAudioChat);
	connect(ui->pushButton_tasks_multicast, &QPushButton::pressed, this, &ComAudio::initTabMulticast);

	return 0;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setTrackInfo
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::setTrackInfo(const QString &info)
--				const QString &info: the track info 
--
-- Returns:  void
--
-- Notes:
-- Sets the window title to the track and the player status if there is any
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::setTrackInfo(const QString &info)
{
	trackInfo = info;
	if (!statusInfo.isEmpty())
	{

		setWindowTitle(QString("%1 | %2").arg(trackInfo).arg(statusInfo));
		QMessageBox::information(this, tr("Size 1:"), QString("%1 | %2").arg(trackInfo).arg(statusInfo));
	}
	else
	{
		setWindowTitle(trackInfo);
		QMessageBox::information(this, tr("Size 1:"), trackInfo);
	}
}
#pragma endregion Private functions




void ComAudio::startServer()
{
	double port = (ui->lineEdit_main_server_port->text()).toDouble();
	taskManager->start(port);
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: connectedToServerVoip
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::connectedToServerVoip(QUdpSocket * udp, QTcpSocket * tcp)
--				QUdpSocket * udp: Pointer to a udp socket, which is used to send and receive voice chat datagrams
--				QTcpSocket * tcp: Pointer to a tcp socket, which is used to initiate voice chat between client and server
--
-- Returns:  void
--
-- Notes:
-- Slot used by client to begin a voice chat session with the server
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::connectedToServerVoip(QUdpSocket * udp, QTcpSocket * tcp)
{
	clientVoip = new UDPTask(nullptr, udp, VOICE_STREAM, tcp);
	currentTask = clientVoip;
	clientVoip->startVOIP(mAudioOutput, mAudioInput, mFormat);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: connectedToServerStream
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::connectedToServerStream(QTcpSocket * sock)
--				QTcpSocket * sock: Pointer to a tcp socket that sends and receive streaming packets
--
-- Returns:  void
--
-- Notes:
-- Slot used by client to begin a streaming session with the server.
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::connectedToServerStream(QTcpSocket * sock)
{
	
	QModelIndex index = qobject_cast<TabAudioStream *>(fileSelectionTab)->ui->listView_files->currentIndex();
	QString fileName = index.data(Qt::DisplayRole).toString();

	
	fileName.remove('\r');
	QByteArray buf = QByteArray(fileName.toUtf8());
	buf.resize(255);
	sock->write(buf, 255);



	StreamRecv * sRecv = new StreamRecv(this, sock);
	currentTask = sRecv;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: connectedToServerFileTransfer
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::connectedToServerFileTransfer(QTcpSocket * sock)
--				QTcpSocket * sock: Pointer to a tcp socket that sends and receive streaming packets
--
-- Returns:  void
--
-- Notes:
-- Slot used by client to begin a file transfer session session with the server.
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::connectedToServerFileList(QTcpSocket * sock)
{
	QString data = QString(sock->readAll());
	QStringList list = data.split('\n');
	fileListModel->setStringList(list);
	qobject_cast<TabFileTx*>(fileSelectionTab)->ui->listView_files->setModel(fileListModel);
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: connectedToServerStreamFileTransfer
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::connectedToServerStreamFileTransfer(QTcpSocket * sock)
--				QTcpSocket * sock: Pointer to a tcp socket that sends and receive streaming packets
--
-- Returns:  void
--
-- Notes:
-- Slot used by client to begin a file streaming session session with the server.
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::connectedToServerStreamFileList(QTcpSocket * sock)
{
	QString data = QString(sock->readAll());
	QStringList list = data.split('\n');
	fileListModel->setStringList(list);
	qobject_cast<TabAudioStream*>(fileSelectionTab)->ui->listView_files->setModel(fileListModel);
}

void ComAudio::connectedToServerFileTx(QTcpSocket * sock)
{
	QModelIndex index = qobject_cast<TabFileTx *>(fileSelectionTab)->ui->listView_files->currentIndex();
	QString fileName = index.data(Qt::DisplayRole).toString();

	qDebug() << "filename: " << fileName;
	fileName.remove('\r');
	QByteArray buf = QByteArray(fileName.toUtf8());
	buf.resize(255);
	sock->write(buf, 255);
	FileTransfer* fileTransfer = new FileTransfer(this, sock, fileName);
	currentTask = fileTransfer;

}




/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: clientConnectedStream
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::clientConnectedStream(QTcpSocket * sock)
--				QTcpSocket * sock: Pointer to a tcp socket that sends and receive streaming packets
--
-- Returns:  void
--
-- Notes:
-- Slot used by server to begin a streaming session when a client starts a streaming session
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::clientConnectedStream(QTcpSocket * sock)
{
	QByteArray buf;
	if (sock->waitForReadyRead(30000))
	{
		buf = sock->read(255);
	}

	QString f = QString(buf);
	StreamServe* stream = new StreamServe(sock, f);
	currentTask = stream;
	stream->sendFile();
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: clientConnectedFileList
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::clientConnectedFileTransfer(QTcpSocket * sock)
--				QTcpSocket * sock: Pointer to a tcp socket that sends and receive streaming packets
--
-- Returns:  void
--
-- Notes:
-- Slot used by server to begin a file transfer session when a client starts a streaming session
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::clientConnectedFileList(QTcpSocket * sock)
{
	sock->write(getFileList().toUtf8());
}

void ComAudio::clientConnectedStreamFileList(QTcpSocket * sock)
{
	sock->write(getFileList().toUtf8());
}


void ComAudio::clientConnectedFileTx(QTcpSocket * sock)
{
	QByteArray buf;
	if (sock->waitForReadyRead(30000))
	{
		buf = sock->read(255);
	}
	
	QString f = QString(buf);
	//buf = sock->read(255);
	QString fileToSend = buf;
	qDebug() << "File name received: " << f;
	StreamServe* stream = new StreamServe(sock, f);
	stream->sendFile();
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: clientConnectedVoip
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::clientConnectedVoip(QUdpSocket * udp, QTcpSocket * tcp)
--				QUdpSocket * udp: Pointer to a udp socket, which is used to send and receive voice chat datagrams
--				QTcpSocket * tcp: Pointer to a tcp socket, which is used to initiate voice chat between client and server
--
-- Returns:  void
--
-- Notes:
-- Slot used by server to begin a voice chat session when a client starts a voice chat
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::clientConnectedVoip(QUdpSocket * udp, QTcpSocket * tcp)
{
	serverVoip = new UDPTask(nullptr, udp, VOICE_STREAM, tcp);
	currentTask = serverVoip;
	serverVoip->startVOIP(mAudioOutput, mAudioInput, mFormat);
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: stopCurrentTask
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::stopCurrentTask()
--
-- Returns:  void
--
-- Notes:
-- Ends current task, if it exists
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::stopCurrentTask()
{
	if (currentTask != nullptr)
	{
		currentTask->stop();
		currentTask = nullptr;
	}
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: serverPortValueChanged
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::serverPortValueChanged()
--
-- Returns:  void
--
-- Notes:
-- Slot that grabs changes from the port edit text input
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::serverPortValueChanged()
{
	serverPort = ui->lineEdit_main_server_port->text().toInt();
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: startStream
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::startStream()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called when the Audio Stream push button is pressed
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::startStream()
{

	if (taskManager == nullptr)
	{
		return;
	}
	if (taskManager->ConnectTo(ipAddr, clientPort, TaskType::SONG_STREAM))

	{
		//grey out other options
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: startVoip
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::startVoip()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called when the Audio Chat push button is pressed
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::startVoip()
{
	if (taskManager == nullptr)
	{
		return;
	}
	if (taskManager->ConnectTo(ipAddr, clientPort, TaskType::VOICE_STREAM))
	{
		//grey out other options

	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: startFileList
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::startFileList()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called when the File Transfer push button is pressed
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::startFileList()
{

	if (taskManager == nullptr)
	{
		return;
	}

	if (taskManager->ConnectTo(ipAddr, clientPort, TaskType::FILE_LIST))

	{
		//grey out other options
	}
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: startMulticastTx
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::startMulticastTx()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called to begin sending multicast audio
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::startMulticastTx()
{
	serverVoip = new UDPTask(this);
	serverVoip->startMulticastTx();
	currentTask = serverVoip;
}



/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: startMulticastRx
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::startMulticastRx()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called to begin receiving multicast audio
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::startMulticastRx()
{
	serverVoip = new UDPTask(this);
	serverVoip->startMulticastRx();
	currentTask = serverVoip;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: startStreamFileList
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::startStreamFileList()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called when the Start push button is pressed which initializes the server TaskManager
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::startStreamFileList()
{

	if (taskManager == nullptr)
	{
		return;
	}

	if (taskManager->ConnectTo(ipAddr, clientPort, TaskType::STREAM_FILE_LIST))

	{
		//grey out other options
	}
}




/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: startFileTx
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::startFileTx()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called when the Start push button is pressed which initializes the server TaskManager
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::startFileTx()
{
	if (taskManager->ConnectTo(ipAddr, clientPort, TaskType::FILE_TX))
	{
		//grey out other options
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setDir
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::setDir()
--
-- Returns:  void
--
-- Notes:
-- Function that sets the directory for the local file list view
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::setDir()
{
	// TODO: fix bug -- showing directories on the list view.
	ui->listView_dir_list->setRootIndex(fileModel->setRootPath(pathLocal));
	ui->lineEdit_dir_path->setText(pathLocal);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: selectDir
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::selectDir()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called when the select_dir push button is pressed.
--
-- Starts a file dialog that changes the local path on completion
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::selectDir()
{
	QString pathTemp = QFileDialog::getExistingDirectory(this, tr("Open Directory"), pathLocal, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if (!pathTemp.isEmpty())
	{
		pathLocal = pathTemp;
		setDir();
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: selectFile
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::selectFile()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called when the selection on list view has changed
--
-- Changes the path of the file to the new file and changes the play mode to test
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::selectFile()
{
	pathFile = fileModel->filePath(ui->listView_dir_list->currentIndex());
	playMode = PlayMode::Type::test;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: playAudio
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::playAudio()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called when the play push button is pressed.
--
-- Starts the media player based on the current play mode
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::playAudio()
{
	switch (playMode)
	{
	case PlayMode::Type::local:
		player->setMedia(QUrl::fromLocalFile(pathFile));
		player->play();
		break;
	case PlayMode::Type::stream:

		break;
	case PlayMode::Type::test:
		audioFile = new QFile(pathFile);
		audioFile->open(QIODevice::ReadOnly);
		startPlaying(audioFile->size());
		while (!(audioFile->atEnd()))
		{
			QByteArray seg(audioFile->read(SIZE_SEGMENT));
			feedAudio(seg);
			seg.clear();
		}
		break;
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setVolume
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::setVolume()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called when the volume bar is changed
--
-- Changes the volume of the player based on the position of the bar
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::setVolume()
{
	player->setVolume(player->volume());
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setVolume
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::setVolume()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called when the meta data has changed
--
-- Changes the meta data of the player to the new meta data
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::metaDataChanged()
{
	if (player->isMetaDataAvailable()) {
		setTrackInfo(QString("%1 - %2")
			.arg(player->metaData(QMediaMetaData::AlbumArtist).toString())
			.arg(player->metaData(QMediaMetaData::Title).toString()));

		if (ui->label_player_artist) {
			QUrl url = player->metaData(QMediaMetaData::CoverArtUrlLarge).value<QUrl>();

			ui->label_player_artist->setPixmap(!url.isEmpty() ? QPixmap(url.toString()) : QPixmap());
		}
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: initTab
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::initTab(Task::Type task)
--				Task::Type task: an Enum to denote the type of task that was started
--
-- Returns:  void
--
-- Notes:
--
-- Initializes the tab of the ui based on the task being run
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::initTab(Task::Type task)
{
	const QString modeCli = QString("Client");
	const QString modeSrv = QString("Server");

	QWidget *newTab;
	QString tabName;
	QStringList modes;
	QString mode;
	bool ok;

	switch (task)
	{
	case Task::Type::fileTx:
		newTab = new TabFileTx(this);
		fileSelectionTab = newTab;

		// file transfer list
		fileListModel = new QStringListModel();
		(qobject_cast<TabFileTx*>(newTab))->ui->listView_files->setSelectionMode(QAbstractItemView::ExtendedSelection);

		tabName = ((TabFileTx*)newTab)->TAB_NAME;
		ok = true;
		connect(((TabFileTx*)newTab), &TabFileTx::sigCloseTab, this, &ComAudio::closeTab);
		break;
	case Task::Type::stream:
		newTab = new TabAudioStream(this);
		fileSelectionTab = newTab;

		fileListModel = new QStringListModel();
		(qobject_cast<TabAudioStream*>(newTab))->ui->listView_files->setSelectionMode(QAbstractItemView::ExtendedSelection);

		tabName = ((TabAudioStream*)newTab)->TAB_NAME;
		ok = true;
		connect(((TabAudioStream*)newTab), &TabAudioStream::sigCloseTab, this, &ComAudio::closeTab);
		break;
	case Task::Type::chat:
		modes << modeCli << modeSrv;
		mode = QInputDialog::getItem(this, tr("Mode"), tr("Choose mode:"), modes, 0, false, &ok);
		if (ok && !mode.isEmpty())
		{
			if (mode == modeCli)
			{
				newTab = new TabAudioChat(TabAudioChat::Mode::client, this);
				tabName = ((TabAudioChat*)newTab)->TAB_NAME + " (Cli)";
			}
			else if (mode == modeSrv)
			{
				newTab = new TabAudioChat(TabAudioChat::Mode::server, this);
				tabName = ((TabAudioChat*)newTab)->TAB_NAME + " (Srv)";
			}
			connect(((TabAudioChat*)newTab), &TabAudioChat::sigCloseTab, this, &ComAudio::closeTab);
		}
		break;
	case Task::Type::multicast:
		modes << modeCli << modeSrv;
		mode = QInputDialog::getItem(this, tr("Mode"), tr("Choose mode:"), modes, 0, false, &ok);
		if (ok && !mode.isEmpty())
		{
			if (mode == modeCli)
			{
				newTab = new TabMulticast(TabMulticast::Mode::client, this);
				tabName = ((TabMulticast*)newTab)->TAB_NAME + " (Cli)";
			}
			else if (mode == modeSrv)
			{
				newTab = new TabMulticast(TabMulticast::Mode::server, this);
				tabName = ((TabMulticast*)newTab)->TAB_NAME + " (Srv)";
			}
			connect(((TabMulticast*)newTab), &TabMulticast::sigCloseTab, this, &ComAudio::closeTab);
		}
		break;
	}
	if (ok)
	{
		ui->tabWidget_taskViews->addTab(newTab, tabName);
	}	
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: closeTab
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::closeTab(QWidget* tab)
--				QWidget* tab: the tab that will be removed
--
-- Returns:  void
--
-- Notes:
-- Slot that is called when the close tab signal is emitted
--
-- Closes the tab on the main ui when the appropriate close tab signal is emitted
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::closeTab(QWidget* tab)
{
	ui->tabWidget_taskViews->removeTab(ui->tabWidget_taskViews->indexOf(tab));
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: initTabFile
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::initTabFileTx()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called when the File Transfer push button is pressed
--
-- Calls the initTab function to generate a tab for the File Transfer task
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::initTabFileTx()
{
	initTab(Task::Type::fileTx);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: initTabAudioStream
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::initAudioStream()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called when the Audio Stream push button is pressed
--
-- Calls the initTab function to generate a tab for the File Audio Stream task
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::initTabAudioStream()
{
	initTab(Task::Type::stream);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: initTabAudioChat
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::initTabFileAudioChat()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called when the Audio Chat push button is pressed
--
-- Calls the initTab function to generate a tab for the Audio Chat task
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::initTabAudioChat()
{
	initTab(Task::Type::chat);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: initTabMulticast
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::initTabMulticast()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called when the Multicast push button is pressed
--
-- Calls the initTab function to generate a tab for the Multicast task
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::initTabMulticast()
{
	initTab(Task::Type::multicast);
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setIp
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::setIp(const QString& addr)
--
-- Returns: 
--
-- Notes:
-- Slot setter - called from tabs
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::setIp(const QString& addr)
{
	ipAddr = addr;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setPort
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::setPort(const QString& addr)
--
-- Returns:
--
-- Notes:
-- Slot setter - called from tabs
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::setPort(const QString& port)
{
	clientPort = port.toInt();
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getFileList
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: QString ComAudio::getFileList()
--
-- Returns:  A QString representation of the files that the server has
--
-- Notes:
-- Appends all of the files on the server into one string
----------------------------------------------------------------------------------------------------------------------*/

QString ComAudio::getFileList()
{
	QDir a(pathLocal);
	QStringList filters;
	QStringList fileList;

	filters << "*.wav";

	a.setNameFilters(filters);
	a.setFilter(QDir::Files);

	fileList = a.entryList();

	return fileList.join('\n') + '\r';
}
#pragma endregion Slot functions


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: debug
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::debug(QString str)
--				QString str: the error message to be displayed
--
-- Returns:  void
--
-- Notes:
-- Prints an error message onto a message box
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::debug(QString str)
{
	QMessageBox::information(this, tr("Debug"), str);
}

