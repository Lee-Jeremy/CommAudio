#pragma once

#include <QWidget>
#include "ui_TabFileTx.h"

class TabFileTx : public QWidget
{
	Q_OBJECT

public:
	TabFileTx(QWidget *parent = Q_NULLPTR);
	~TabFileTx();

	Ui::TabFileTx *ui;

	const QString TAB_NAME = "File Tx";

signals:
	void sigCloseTab(QWidget* tab);

private:
	void connect();
	void download();
	void closeWindow();
};
