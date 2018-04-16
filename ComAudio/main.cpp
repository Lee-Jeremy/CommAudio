#include "ComAudio.h"
#include "TCPTask.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{

	

	QApplication a(argc, argv);
	ComAudio w;
	
	w.show();
	return a.exec();

	//TCPTask* task = new TCPTask(5);
	//task->transmit("Dave Brubeck - Take Five.mp3");

	return 0;
}
