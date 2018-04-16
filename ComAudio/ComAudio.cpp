#include "ComAudio.h"

ComAudio::ComAudio(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::ComAudio)
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
	// -----------------------------------------------------------------

	// task manager ----------------------------------------------------
	taskManager = new TaskManager(this, DEFAULT_PORT);
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
void ComAudio::connectedToServerVoip(QUdpSocket * udp, QTcpSocket * tcp)
{
	udp->write("test data");
}

void ComAudio::connectedToServerStream(QTcpSocket * sock)
{
}

void ComAudio::connectedToServerFileTransfer(QTcpSocket * sock)
{
}

void ComAudio::clientConnectedStream(QTcpSocket * sock)
{
}

void ComAudio::clientConnectedFileTransfer(QTcpSocket * sock)
{
}

void ComAudio::clientConnectedVoip(QUdpSocket * udp, QTcpSocket * tcp)
{
}

void ComAudio::portValueChanged()
{
	//port = ui->lineEditPort->text().toInt();
}

void ComAudio::ipValueChanged()
{
	//ipAddr = ui->lineEditIp->text();
}

void ComAudio::startStream()
{
	if (taskManager->ConnectTo(ipAddr, port, TaskType::VOICE_STREAM))
	{
		//grey out other options
	}
}

void ComAudio::startVoip()
{
	if (taskManager->ConnectTo(ipAddr, port, TaskType::VOICE_STREAM))
	{
		//grey out other options
	}
}

void ComAudio::startFileTransfer()
{
	if (taskManager->ConnectTo(ipAddr, port, TaskType::FILE_TRANSFER))
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
		tabName = ((TabFileTx*)newTab)->TAB_NAME;
		connect(((TabFileTx*)newTab), &TabFileTx::sigCloseTab, this, &ComAudio::closeTab);
		break;
	case Task::Type::stream:
		newTab = new TabAudioStream(this);
		tabName = ((TabAudioStream*)newTab)->TAB_NAME;
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

	ui->tabWidget_taskViews->addTab(newTab, tabName);
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

void ComAudio::debug(QString str)
{
	QMessageBox::information(this, tr("Debug"), str);
}