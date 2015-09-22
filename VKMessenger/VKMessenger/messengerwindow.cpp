#include "messengerwindow.h"

MessengerWindow::MessengerWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	authorization = new Authorization(this);
}

MessengerWindow::~MessengerWindow()
{
	delete authorization;
}
