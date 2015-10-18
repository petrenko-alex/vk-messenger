#include "messengerwindow.h"

MessengerWindow::MessengerWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	currentSession = NULL;

	/* Авторизируем пользователя */
	authorization = new Authorization(this);
	authorization->loadAuthorizationPage();

	setConnections();
}

MessengerWindow::~MessengerWindow()
{
	delete authorization;
}



void MessengerWindow::setConnections()
{
	connect(authorization, SIGNAL(authorizationCompleted(Session &)), this, SLOT(authorizationCompleted(Session &)));
	connect(authorization, SIGNAL(authorizationFailed()), this, SLOT(authorizationFailed()));
}

void MessengerWindow::authorizationCompleted(Session &currentSession)
{
	currentSession = currentSession;
	int a = 32;
}

void MessengerWindow::authorizationFailed()
{
	
}
