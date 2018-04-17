#pragma once

#include <QWidget>
#include "ComAudio.h"
#include "ui_TabMulticast.h"

class TabMulticast : public QWidget
{
	Q_OBJECT

public:
	enum Mode { client, server };

	TabMulticast(Mode mode, QWidget *parent = Q_NULLPTR);
	~TabMulticast();

	Ui::TabMulticast *ui;

	const QString TAB_NAME = "Multicast";

signals:
	void sigCloseTab(QWidget* tab);


private:
	void connect();
	void accept();
	void start();
	void stop();
	void closeWindow();
	QString IP;
};
