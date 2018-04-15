#pragma once

#include <QtWidgets/QMainWindow>
#include <QDialog>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QAudioOutput>
#include "TCPTask.h"
#include "ui_ComAudio.h"

class ComAudio : public QMainWindow
{
	Q_OBJECT

public:
	ComAudio(QWidget *parent = Q_NULLPTR);
	~ComAudio();

	public slots:
	void setDir();
	void selectDir();

public slots:
	
	void startTCPTask();

private:
	int initUi(); // initializes UI components

	Ui::ComAudio *ui;
	QFileSystemModel *dirModel;
	QFileSystemModel *fileModel;
	QString pathLocal;
	QString pathFile;
	QAudioOutput* ao;

	const QString pathLocalInitial = QDir::currentPath();
	const QStringList fileFilter = QStringList{ "*.aac" ,"*.wmv" ,"*.avi" ,"*.mpeg" ,"*.mov" ,"*.3gp" ,"*.flv" ,"*.mp3", "*.wav" };
};
