#pragma once

#include <QThread>
#include <QTcpSocket>


class Task : public QThread
{
	Q_OBJECT

public:
	Task(QObject *parent, QTcpSocket * socket);
	~Task();
};
