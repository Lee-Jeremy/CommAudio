/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: ComAudio.cpp -  A General Use Audio Client/Server Application
--
-- PROGRAM:	ComAudio.exe
--
-- FUNCTIONS:
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
--		void connectedToServerFileTransfer(QTcpSocket * sock);
--		void clientConnectedStream(QTcpSocket * );
--		void clientConnectedFileTransfer(QTcpSocket * );
--		void clientConnectedVoip(QUdpSocket *, QTcpSocket *);
--		void portValueChanged();
--		void ipValueChanged();
--		void startStream();
--		void startVoip();
--		void startFileTransfer();
--		void initTabMulticast();
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
	//taskManager = new TaskManager(this, DEFAULT_PORT);
	connect(taskManager, &TaskManager::clientConnectedVoip, this, &ComAudio::clientConnectedVoip);
	connect(taskManager, &TaskManager::clientConnectedFileTransfer, this, &ComAudio::clientConnectedFileTransfer);
	connect(taskManager, &TaskManager::clientConnectedStream, this, &ComAudio::clientConnectedStream);

	connect(taskManager, &TaskManager::connectedToServerFileTransfer, this, &ComAudio::connectedToServerFileTransfer);
	connect(taskManager, &TaskManager::connectedToServerStream, this, &ComAudio::connectedToServerStream);
	connect(taskManager, &TaskManager::connectedToServerVoip, this, &ComAudio::connectedToServerVoip);

	//connect(ui->pushButton_tasks_audioStream, &QPushButton::pressed, this, &ComAudio::startStream);
	//connect(ui->pushButton_tasks_audioChat, &QPushButton::pressed, this, &ComAudio::startVoip);
	// -----------------------------------------------------------------


	// task tab view ---------------------------------------------------
	ui->tabWidget_taskViews->removeTab(0);
	ui->tabWidget_taskViews->removeTab(0);



	// UI EVENT
	connect(ui->pushButton_tasks_audioStream, &QPushButton::pressed, this, &ComAudio::initTabAudioStream);
	connect(ui->pushButton_tasks_fileTransfer, &QPushButton::pressed, this, &ComAudio::initTabFileTx);
	connect(ui->pushButton_tasks_audioChat, &QPushButton::pressed, this, &ComAudio::initTabAudioChat);
	connect(ui->pushButton_tasks_multicast, &QPushButton::pressed, this, &ComAudio::initTabMulticast);
	// -----------------------------------------------------------------

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


#pragma region

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
	StreamRecv * sRecv = new StreamRecv(this, sock);
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
void ComAudio::connectedToServerFileTransfer(QTcpSocket * sock)
{
	FileTransfer* fileTransfer = new FileTransfer(this, sock);
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
	StreamServe* stream = new StreamServe(sock, pathFile);
	stream->sendFile();
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: clientConnectedFileTransfer
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
void ComAudio::clientConnectedFileTransfer(QTcpSocket * sock)
{
	StreamServe* stream = new StreamServe(sock, pathFile);
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
	serverVoip->startVOIP(mAudioOutput, mAudioInput, mFormat);
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
	if (taskManager->ConnectTo(ipAddr, port, TaskType::SONG_STREAM))

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
	if (taskManager->ConnectTo(ipAddr, port, TaskType::VOICE_STREAM))
	{
		//grey out other options
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: startFileTransfer
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
-- Slot that is called when the File Transfer push button is pressed
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::startFileTransfer()
{
	if (taskManager == nullptr)
	{
		return;
	}
	if (taskManager->ConnectTo(ipAddr, port, TaskType::FILE_TRANSFER))
	{
		//grey out other options
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: startServer
--
-- DATE: April 15th 2018
--
-- DESIGNER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu
--
-- Interface: void ComAudio::startServer()
--
-- Returns:  void
--
-- Notes:
-- Slot that is called when the Start push button is pressed which initializes the server TaskManager
----------------------------------------------------------------------------------------------------------------------*/
void ComAudio::startServer()
{
	taskManager = new TaskManager(this, serverPort);
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
		tabName = ((TabFileTx*)newTab)->TAB_NAME;
		ok = true;
		connect(((TabFileTx*)newTab), &TabFileTx::sigCloseTab, this, &ComAudio::closeTab);
		break;
	case Task::Type::stream:
		newTab = new TabAudioStream(this);
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
	//QString fileName = fileModel->fileName(QModelIndex index())
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