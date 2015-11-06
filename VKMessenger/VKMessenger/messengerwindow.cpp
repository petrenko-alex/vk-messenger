#include "messengerwindow.h"

MessengerWindow::MessengerWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	userDialogs = nullptr;
	dataReceiver = new VKDataReceiver;
	authorization = new Authorization(this);

	setConnections();

	ui.dialogsInfoArea->setWidgetResizable(true);
	dialogsScrollWidget = new QWidget;
	dialogsScrollWidget->setLayout(new QVBoxLayout);
	ui.dialogsInfoArea->setWidget(dialogsScrollWidget);

	ui.dialogArea->setWidgetResizable(true);
	messagesScrollWidget = new QWidget;
	messagesScrollWidget->setLayout(new QVBoxLayout);
	ui.dialogArea->setWidget(messagesScrollWidget);

	/* Если данные с файла успешно загружены и загруженный токен валиден */
	if (loadData() && authorization->isTokenValid(Session::getInstance().get("accessToken")))
	{
		authorization->closeBrowser();
		authorization->loadUserInfo();
	}
	else
	{
		/* Авторизируем пользователя */
		authorization->loadAuthorizationPage();
	}
}

MessengerWindow::~MessengerWindow()
{
	delete authorization;
	delete dataReceiver;
	delete dialogsScrollWidget;
	delete messagesScrollWidget;
	delete userDialogs;
}

void MessengerWindow::setConnections()
{
	connect(authorization, SIGNAL(authorizationCompleted()), this, SLOT(authorizationCompleted()));
	connect(authorization, SIGNAL(authorizationFailed()), this, SLOT(authorizationFailed()));
	connect(this, SIGNAL(userInfoLoaded()), this, SLOT(loadDialogs()));
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
	/* Устанавливаем имя пользователя */
	ui.userName->setText(Session::getInstance().get("userName"));
	/* Получаем и устанавливаем фото*/
	QByteArray photoData = dataReceiver->loadPhoto(QUrl(Session::getInstance().get("userPhoto")));

	QPixmap photo;
	if (!photoData.isEmpty() && photo.loadFromData(photoData))
	{
		ui.userPhoto->setPixmap(photo);
		Session::getInstance().setPhoto(photoData);
	}
	else
	{
		// #TODO: Попытаться загрузить еще раз?
	}

	emit userInfoLoaded();
}

void MessengerWindow::authorizationFailed()
{
	// #TODO: Реализовать слот
}

void MessengerWindow::loadDialogs()
{
	userDialogs = new Dialogs();
	connect(userDialogs, SIGNAL(dialogLoaded(DialogInfo *)), this, SLOT(dialogReceived(DialogInfo *)));
	connect(userDialogs, SIGNAL(messageLoaded(AbstractMessage *, QString &)), this, SLOT(messageReceived(AbstractMessage *, QString &)));
	connect(userDialogs, SIGNAL(dialogsLoaded(bool)), this, SLOT(dialogsLoaded(bool)));
	userDialogs->loadDialogs();
}

void MessengerWindow::dialogReceived(DialogInfo *dialogInfo)
{
	dialogsScrollWidget->layout()->addWidget(dialogInfo);
}

void MessengerWindow::messageReceived(AbstractMessage *message, QString &username)
{
	messagesScrollWidget->layout()->addWidget(message);
	ui.currentOponent->setText(username);
	
}

void MessengerWindow::dialogsLoaded(bool isSuccessful)
{
	if (isSuccessful)
	{
		this->show();
	}
	else
	{
		// #TODO: Решить что делать здесь!
	}
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
