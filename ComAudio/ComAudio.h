#pragma once

#include <QtWidgets/QMainWindow>
#include <QDialog>
#include <QFileSystemModel>
#include <QFileDialog>
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

signals:

private:
	int initUi(); // initializes UI components

	Ui::ComAudio *ui;
	QFileSystemModel *dirModel;
	QFileSystemModel *fileModel;
	QString pathLocal;
	QString pathFile;

	const QString pathLocalInitial = QDir::currentPath();
	const QStringList fileFilter = QStringList{ "*.aac" ,"*.wmv" ,"*.avi" ,"*.mpeg" ,"*.mov" ,"*.3gp" ,"*.flv" ,"*.mp3" };
};
