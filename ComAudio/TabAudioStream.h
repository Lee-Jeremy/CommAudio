#pragma once

#include <QWidget>
#include "ui_TabAudioStream.h"
#include "ComAudio.h"

class TabAudioStream : public QWidget
{
	Q_OBJECT

public:
	TabAudioStream(QWidget *parent = Q_NULLPTR);
	~TabAudioStream();

	Ui::TabAudioStream *ui;

	const QString TAB_NAME = "Audio Stream";

signals:
	void sigCloseTab(QWidget* tab);

private:
	void connect();
	void start();
	void stop();
	void ipChanged();
	void portChanged();
	void closeWindow();
};
