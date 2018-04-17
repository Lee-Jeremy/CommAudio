#include "ComAudio.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ComAudio w;
	
	w.show();
	return a.exec();

	return 0;
}
