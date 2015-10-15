#include "messengerwindow.h"

MessengerWindow::MessengerWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

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
	connect(authorization, SIGNAL(authorizationCompleted(const QString&, const QString&, const QString&)), this, SLOT(authorizationCompleted(const QString&, const QString&, const QString&)));
	connect(authorization, SIGNAL(authorizationFailed()), this, SLOT(authorizationFailed()));
}

void MessengerWindow::authorizationCompleted(const QString &accessToken, const QString &userId, const QString &expiresIn)
{
	
}

void MessengerWindow::authorizationFailed()
{
	
}
