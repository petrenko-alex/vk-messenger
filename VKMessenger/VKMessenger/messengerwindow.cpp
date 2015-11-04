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

	ui.dialogsInfoArea->setWidgetResizable(true);
	dialogsScrollWidget = new QWidget;
	dialogsScrollWidget->setLayout(new QVBoxLayout);
	ui.dialogsInfoArea->setWidget(dialogsScrollWidget);
}

MessengerWindow::~MessengerWindow()
{
	delete authorization;
	delete dataReceiver;
}

void MessengerWindow::setConnections()
{
	connect(authorization, SIGNAL(authorizationCompleted()), this, SLOT(authorizationCompleted()));
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

void MessengerWindow::authorizationCompleted()
{
	ui.userName->setText(Session::getInstance().get("userName"));
	dataReceiver->loadPhoto(QUrl(Session::getInstance().get("userPhoto")));

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
	userDialogs = new Dialogs();
	connect(userDialogs, SIGNAL(dialogLoaded(DialogInfo *)), this, SLOT(dialogReceived(DialogInfo *)));
	userDialogs->loadDialogs();
}

void MessengerWindow::dialogReceived(DialogInfo *dialogInfo)
{
	dialogsScrollWidget->layout()->addWidget(dialogInfo);
}

bool MessengerWindow::saveData()
{
	QFile dataFile(QString(DATA_FILENAME));
	if (dataFile.open(QIODevice::WriteOnly))
	{
		QDataStream stream(&dataFile);
		stream << Session::getInstance ();
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
		stream >> Session::getInstance ();
		dataFile.close();
		return true;
	}
	return false;
}
