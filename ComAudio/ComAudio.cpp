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

int ComAudio::initUi()
{
	ui->setupUi(this);

	// file browser
	pathLocal = PATH_LOCAL_INIT;
	fileModel = new QFileSystemModel(this);
	fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
	fileModel->setNameFilters(FILE_FILTER);
	fileModel->setNameFilterDisables(false);
	ui->listView_dir_list->setModel(fileModel);
	ui->listView_dir_list->setSelectionMode(QAbstractItemView::ExtendedSelection);
	setDir();


	// audio player
	player = new QMediaPlayer(this);
	playlist = new QMediaPlaylist();
	player->setPlaylist(playlist);
	player->setVolume(75);

	connect(player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
	connect(player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
	connect(player, SIGNAL(metaDataChanged()), SLOT(metaDataChanged()));
	connect(playlist, SIGNAL(currentIndexChanged(int)), SLOT(playlistPositionChanged(int)));
	connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
		this, SLOT(statusChanged(QMediaPlayer::MediaStatus)));
	connect(player, SIGNAL(bufferStatusChanged(int)), this, SLOT(bufferingProgress(int)));
	connect(player, SIGNAL(videoAvailableChanged(bool)), this, SLOT(videoAvailableChanged(bool)));
	connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(displayErrorMessage()));

	// audio slider
	ui->horizontalSlider_player_progress->setRange(0, player->duration() / SLIDER_DIVISOR);

	// UI components
	// button: browse

	connect(ui->lineEditIp, &QLineEdit::textChanged, this, &ComAudio::ipValueChanged);
	connect(ui->lineEditPort, &QLineEdit::textChanged, this, &ComAudio::portValueChanged);


	taskManager = new TaskManager(this, DEFAULT_PORT);
	connect(ui->pushButton_main_server_start, &QPushButton::pressed, this, &ComAudio::startServer);
	connect(taskManager, &TaskManager::clientConnectedVoip, this, &ComAudio::clientConnectedVoip);
	connect(taskManager, &TaskManager::clientConnectedFileList, this, &ComAudio::clientConnectedFileList);
	connect(taskManager, &TaskManager::clientConnectedFileTx, this, &ComAudio::clientConnectedFileTx);
	connect(taskManager, &TaskManager::clientConnectedStream, this, &ComAudio::clientConnectedStream);
	connect(taskManager, &TaskManager::connectedToServerFileList, this, &ComAudio::connectedToServerFileList);
	connect(taskManager, &TaskManager::connectedToServerFileTx, this, &ComAudio::connectedToServerFileTx);
	connect(taskManager, &TaskManager::connectedToServerStream, this, &ComAudio::connectedToServerStream);
	connect(taskManager, &TaskManager::connectedToServerVoip, this, &ComAudio::connectedToServerVoip);

	connect(ui->pushButton_tasks_audioStream, &QPushButton::pressed, this, &ComAudio::startStream);
	connect(ui->pushButton_tasks_audioChat, &QPushButton::pressed, this, &ComAudio::startVoip);
	connect(ui->pushButton_tasks_fileTransfer, &QPushButton::pressed, this, &ComAudio::startFileList);
	connect(ui->pushButton_fileTx_download, &QPushButton::pressed, this, &ComAudio::startFileTx);

	connect(ui->pushButton_dir_browse, &QPushButton::pressed, this, &ComAudio::selectDir);
	// list: file
	connect(ui->listView_dir_list, &QAbstractItemView::clicked, this, &ComAudio::selectFile);
	// button: play
	connect(ui->pushButton_player_play, &QPushButton::pressed, this, &ComAudio::playAudio);
	// slider: volume
	connect(ui->horizontalSlider_player_volume, &QSlider::sliderMoved, this, &ComAudio::setVolume);

	// file transfer list
	fileListModel = new QStringListModel();
	ui->listView_fileTx_list->setSelectionMode(QAbstractItemView::ExtendedSelection);

	return 0;
}


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

void ComAudio::startServer()
{
	double port = (ui->lineEdit_main_server_port->text()).toDouble();
	taskManager->start(port);
}

void ComAudio::connectedToServerVoip(QUdpSocket * udp, QTcpSocket * tcp)
{
	udp->write("test data");
}

void ComAudio::connectedToServerStream(QTcpSocket * sock)
{
	StreamRecv * sRecv = new StreamRecv(this, sock);
}

void ComAudio::connectedToServerFileList(QTcpSocket * sock)
{
	QString data = QString(sock->readAll());
	QStringList list = data.split('\n');
	fileListModel->setStringList(list);
	ui->listView_fileTx_list->setModel(fileListModel);
}

void ComAudio::connectedToServerFileTx(QTcpSocket * sock)
{
	QModelIndex index = ui->listView_fileTx_list->currentIndex();
	QString fileName = index.data(Qt::DisplayRole).toString();
	sock->write(fileName.toUtf8());
	FileTransfer* fileTransfer = new FileTransfer(this, sock, fileToRecv);
}

void ComAudio::clientConnectedStream(QTcpSocket * sock)
{
	StreamServe* stream = new StreamServe(sock, pathFile);
	stream->sendFile();
}

void ComAudio::clientConnectedFileList(QTcpSocket * sock)
{
	sock->write(getFileList().toUtf8());
}

void ComAudio::clientConnectedFileTx(QTcpSocket * sock)
{
	QString fileToSend = QString(sock->readAll());
	StreamServe* stream = new StreamServe(sock, fileToSend);
	stream->sendFile();
}

void ComAudio::clientConnectedVoip(QUdpSocket * udp, QTcpSocket * tcp)
{
}

void ComAudio::portValueChanged()
{
	port = ui->lineEditPort->text().toInt();
}

void ComAudio::ipValueChanged()
{
	ipAddr = ui->lineEditIp->text();
}

void ComAudio::startStream()
{
	if (taskManager->ConnectTo(ipAddr, port, TaskType::SONG_STREAM))
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

void ComAudio::startFileList()
{
	if (taskManager->ConnectTo(ipAddr, port, TaskType::FILE_LIST))
	{
		//grey out other options
	}
}

void ComAudio::startFileTx()
{
	if (taskManager->ConnectTo(ipAddr, port, TaskType::FILE_TX))
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
	playMode = test;
	//QMessageBox::information(this, tr(""), pathFile);
}

void ComAudio::playAudio()
{
	switch (playMode)
	{
	case local:
		player->setMedia(QUrl::fromLocalFile(pathFile));
		player->play();
		break;
	case stream:

		break;
	case test:
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

QString ComAudio::getFileList()
{
	QDir a(pathLocal);
	QStringList filters;
	QStringList fileList;

	filters << "*.wav";

	a.setNameFilters(filters);
	a.setFilter(QDir::Files);

	fileList = a.entryList();

	return fileList.join('\n');
}