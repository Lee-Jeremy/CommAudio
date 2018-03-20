#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ComAudio.h"

class ComAudio : public QMainWindow
{
	Q_OBJECT

public:
	ComAudio(QWidget *parent = Q_NULLPTR);

private:
	Ui::ComAudioClass ui;
};
