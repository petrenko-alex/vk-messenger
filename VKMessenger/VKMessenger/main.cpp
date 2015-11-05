#include "messengerwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MessengerWindow w;
	return a.exec();
}
