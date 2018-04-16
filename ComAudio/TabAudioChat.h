#pragma once

#include <QWidget>
#include "ui_TabAudioChat.h"

class TabAudioChat : public QWidget
{
	Q_OBJECT

public:
	enum Mode { client, server };

	TabAudioChat(Mode mode, QWidget *parent = Q_NULLPTR);
	~TabAudioChat();
	
	Ui::TabAudioChat *ui;

	const QString TAB_NAME = "Audio Chat";

signals:
	void sigCloseTab(QWidget* tab);

private:
	void connect();
	void accept();
	void start();
	void stop();
	void closeWindow();
};
