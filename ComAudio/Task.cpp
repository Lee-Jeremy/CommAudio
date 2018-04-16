#include "Task.h"

Task::Task(QObject *parent, QTcpSocket * socket)
	: QThread(parent)
{
}

Task::~Task()
{
}
