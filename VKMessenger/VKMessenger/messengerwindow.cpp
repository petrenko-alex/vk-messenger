#include "messengerwindow.h"

MessengerWindow::MessengerWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//currentSession = NULL;
	dataReceiver = new VKDataReceiver;

	if (!loadData())
	{

	}


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

void MessengerWindow::closeEvent(QCloseEvent *event)
{
	event->ignore();
	if (saveData())
	{
		event->accept();
	}
	else
	{
		event->ignore();
		// #TODO: попытаться еще раз?
	}
}

void MessengerWindow::authorizationCompleted(Session receivedSession)
{
	currentSession = receivedSession;

	ui.userName->setText(currentSession.getUserName());
	dataReceiver->loadPhoto(currentSession.getUserPhotoURL());

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

bool MessengerWindow::saveData()
{
	QFile dataFile(QString(DATA_FILENAME));
	if (dataFile.open(QIODevice::WriteOnly))
	{
		QDataStream stream(&dataFile);
		stream << currentSession;
		dataFile.close();
		return true;
	}
	return false;
}

bool MessengerWindow::loadData()
{
	QFile dataFile(QString(DATA_FILENAME));
	if (dataFile.open(QIODevice::ReadOnly))
	{
		QDataStream stream(&dataFile);
		stream >> currentSession;
		dataFile.close();
		return true;
	}
	return false;
}
