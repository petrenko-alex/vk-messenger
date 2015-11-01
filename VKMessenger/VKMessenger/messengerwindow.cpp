#include "messengerwindow.h"

MessengerWindow::MessengerWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	userDialogs = nullptr;
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
	connect(this, SIGNAL(userInfoLoaded()), this, SLOT(loadDialogs()));
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
	// #TODO: Реализовать слот
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
	emit userInfoLoaded();
}

void MessengerWindow::loadDialogs()
{
	userDialogs = new Dialogs(currentSession);
	connect(userDialogs, SIGNAL(dialogLoaded(DialogInfo *)), this, SLOT(dialogReceived(DialogInfo *)));
	userDialogs->loadDialogs();
}

void MessengerWindow::dialogReceived(DialogInfo *dialogInfo)
{
// 	QVBoxLayout *layout = new QVBoxLayout(ui.dialogsInfoArea);
// 	ui.dialogsInfoArea->setLayout(layout);
// 	dialogInfo->setMinimumSize(ui.dialogsInfoArea->minimumSize());
// 	layout->addWidget(dialogInfo);
// 	
// 	ui.dialogsInfoArea->show();
// 	dialogInfo->show();
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
