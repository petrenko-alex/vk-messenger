#include "messengerwindow.h"

MessengerWindow::MessengerWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	authorization = new Authorization(this);
	setConnections();
}

MessengerWindow::~MessengerWindow()
{
	delete authorization;
}

void MessengerWindow::dialogsLoaded(const QByteArray &data)
{
	int a = 32;
}

void MessengerWindow::setConnections()
{
	connect(authorization, SIGNAL(dialogsLoaded(const QByteArray &)), this, SLOT(dialogsLoaded(const QByteArray &)));
}
