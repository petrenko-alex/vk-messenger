#include "messengerwindow.h"

MessengerWindow::MessengerWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	currentSession = NULL;
	dataReceiver = new VKDataReceiver;

	/* Авторизируем пользователя */
	authorization = new Authorization(this);
	authorization->loadAuthorizationPage();



	setConnections();
}

MessengerWindow::~MessengerWindow()
{
	delete authorization;
	delete dataReceiver;
}



void MessengerWindow::setConnections()
{
	connect(authorization, SIGNAL(authorizationCompleted(Session)), this, SLOT(authorizationCompleted(Session)));
	connect(authorization, SIGNAL(authorizationFailed()), this, SLOT(authorizationFailed()));
	connect(dataReceiver, SIGNAL(photoReceived(const QByteArray &)), this, SLOT(userPhotoLoaded(const QByteArray &)));
}

void MessengerWindow::authorizationCompleted(Session receivedSession)
{
	currentSession = &receivedSession;

	ui.userName->setText(currentSession->getUserName());
	dataReceiver->loadPhoto(currentSession->getUserPhotoURL());

}

void MessengerWindow::authorizationFailed()
{
	
}

void MessengerWindow::userPhotoLoaded(const QByteArray &data)
{
	QPixmap photo;
	if (!data.isEmpty() && photo.loadFromData(data))
	{
		ui.userPhoto->setPixmap(photo);
	}
	else
	{
		// #TODO: Попытаться загрузить еще раз?
	}
}
