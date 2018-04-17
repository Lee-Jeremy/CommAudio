/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: ComAudio.cpp -  A General Use Audio Client/Server Application
--
-- PROGRAM: ComAudio.exe
--
-- FUNCTIONS:
--		void startPlaying(qint64 sizeTotal);
--		void feedAudio(QByteArray segment);
--		void setDir();/
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
-- PROGRAMMER: Delan Elliot, Jeremy Lee, Wilson Hu, Jeff Chou
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

ComAudio::~ComAudio()
{
	delete ui;
}

#pragma region
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

void ComAudio::feedAudio(QByteArray segment)
{
	//audioData->resize(sizeTotal + 1);
	audioData->insert(pos, segment);
	pos += segment.size();
}

#pragma endregion Public functions

#pragma region
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


	//connect(ui->pushButton_tasks_audioStream, &QPushButton::pressed, this, &ComAudio::startStream);
	//connect(ui->pushButton_tasks_audioChat, &QPushButton::pressed, this, &ComAudio::startVoip);
	// -----------------------------------------------------------------






	// task tab view ---------------------------------------------------
	ui->tabWidget_taskViews->removeTab(0);
	ui->tabWidget_taskViews->removeTab(0);




	connect(ui->pushButton_tasks_audioStream, &QPushButton::pressed, this, &ComAudio::initTabAudioStream);
	connect(ui->pushButton_tasks_fileTransfer, &QPushButton::pressed, this, &ComAudio::initTabFileTx);
	connect(ui->pushButton_tasks_audioChat, &QPushButton::pressed, this, &ComAudio::initTabAudioChat);
	connect(ui->pushButton_tasks_multicast, &QPushButton::pressed, this, &ComAudio::initTabMulticast);

	return 0;
}



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


void ComAudio::connectedToServerVoip(QUdpSocket * udp, QTcpSocket * tcp)
{
	clientVoip = new UDPTask(nullptr, udp, VOICE_STREAM, tcp);
	currentTask = clientVoip;
	clientVoip->startVOIP(mAudioOutput, mAudioInput, mFormat);
}

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

void ComAudio::connectedToServerFileList(QTcpSocket * sock)
{
	QString data = QString(sock->readAll());
	QStringList list = data.split('\n');
	fileListModel->setStringList(list);
	qobject_cast<TabFileTx*>(fileSelectionTab)->ui->listView_files->setModel(fileListModel);
}

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

void ComAudio::clientConnectedFileList(QTcpSocket * sock)
{
	//StreamServe* stream = new StreamServe(sock, pathFile);
	//currentTask = stream;
	sock->write(getFileList().toUtf8());
}

void ComAudio::clientConnectedStreamFileList(QTcpSocket * sock)
{
	//StreamServe* stream = new StreamServe(sock, pathFile);
	//currentTask = stream;
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

void ComAudio::clientConnectedVoip(QUdpSocket * udp, QTcpSocket * tcp)
{
	serverVoip = new UDPTask(nullptr, udp, VOICE_STREAM, tcp);
	currentTask = serverVoip;
	serverVoip->startVOIP(mAudioOutput, mAudioInput, mFormat);
}

void ComAudio::stopCurrentTask()
{
	if (currentTask != nullptr)
	{
		currentTask->stop();
		currentTask = nullptr;
	}
}

void ComAudio::serverPortValueChanged()
{
	serverPort = ui->lineEdit_main_server_port->text().toInt();
}

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


void ComAudio::startMulticastTx()
{
	qDebug() << "start sending multicast";
}

void ComAudio::startMulticastRx()
{
	qDebug() << "start receiveing multicast";
}



void ComAudio::startFileTx()
{
	if (taskManager->ConnectTo(ipAddr, clientPort, TaskType::FILE_TX))
	{
		//grey out other options
	}
}


void ComAudio::setDir()
{
	// TODO: fix bug -- showing directories on the list view.
	ui->listView_dir_list->setRootIndex(fileModel->setRootPath(pathLocal));
	ui->lineEdit_dir_path->setText(pathLocal);
}

void ComAudio::selectDir()
{
	QString pathTemp = QFileDialog::getExistingDirectory(this, tr("Open Directory"), pathLocal, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if (!pathTemp.isEmpty())
	{
		pathLocal = pathTemp;
		setDir();
	}
}

void ComAudio::selectFile()
{
	pathFile = fileModel->filePath(ui->listView_dir_list->currentIndex());
	playMode = PlayMode::Type::test;
}

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

void ComAudio::setVolume()
{
	player->setVolume(player->volume());
}

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

void ComAudio::closeTab(QWidget* tab)
{
	ui->tabWidget_taskViews->removeTab(ui->tabWidget_taskViews->indexOf(tab));
}

void ComAudio::initTabFileTx()
{
	initTab(Task::Type::fileTx);
}

void ComAudio::initTabAudioStream()
{
	initTab(Task::Type::stream);
}

void ComAudio::initTabAudioChat()
{
	initTab(Task::Type::chat);
}

void ComAudio::initTabMulticast()
{
	initTab(Task::Type::multicast);
}

void ComAudio::setIp(const QString& addr)
{
	ipAddr = addr;
}

void ComAudio::setPort(const QString& port)
{
	clientPort = port.toInt();
}

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

//void ComAudio::debug(QString str)
//{
//	QMessageBox::information(this, tr("Debug"), str);
//	return fileList.join('\n');
//
//}