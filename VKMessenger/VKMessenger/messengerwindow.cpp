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
	//messagesScrollWidget = new QWidget;
	//messagesScrollWidget->setLayout(new QVBoxLayout);
	//ui.dialogArea->setWidget(messagesScrollWidget);

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
	//delete messagesScrollWidget;
	delete userDialogs;
}

void MessengerWindow::setConnections()
{
	connect(authorization, SIGNAL(authorizationCompleted()), this, SLOT(authorizationCompleted()));
	connect(authorization, SIGNAL(authorizationFailed()), this, SLOT(authorizationFailed()));
	connect(this, SIGNAL(userInfoLoaded()), this, SLOT(loadDialogs()));
	connect(ui.dialogArea->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), this, SLOT(moveScrollBarToBotton(int,int)));
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
	connect(userDialogs, SIGNAL(messagesLoaded(QWidget *, QString &)), this, SLOT(messagesReceived(QWidget *, QString &)));
	connect(userDialogs, SIGNAL(dialogsLoaded(QList<DialogInfo *> *)), this, SLOT(dialogsLoaded(QList<DialogInfo *> *)));
	userDialogs->loadDialogs();
}

void MessengerWindow::messagesReceived(QWidget *scrollWidget, QString &username)
{
	/* Очищаем предыдущее содержимое */
/*
	while (messagesScrollWidget->layout()->count())
	{
		QLayoutItem * item = messagesScrollWidget->layout()->itemAt(0);
		messagesScrollWidget->layout()->removeItem(item);
		messagesScrollWidget->layout()->removeWidget(item->widget());
		delete item->widget();
		delete item;
		messagesScrollWidget->layout()->update();
	}

	auto it = userMessages->cend();
	auto end = userMessages->cbegin();

	while (it != end)
	{
		--it;
		messagesScrollWidget->layout()->addWidget(*it);
	}*/

	if (ui.dialogArea->widget())
	{
		ui.dialogArea->takeWidget();
	}
	ui.dialogArea->setWidget(scrollWidget);
	ui.currentOponent->setText(username);
}

void MessengerWindow::dialogsLoaded(QList<DialogInfo *> *userDialogs)
{
	for (auto dialog : *userDialogs)
	{
		dialogsScrollWidget->layout()->addWidget(dialog);
	}

	this->show();
}

void MessengerWindow::moveScrollBarToBotton(int min, int max)
{
	Q_UNUSED(min);
	ui.dialogArea->verticalScrollBar()->setValue(max);
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
