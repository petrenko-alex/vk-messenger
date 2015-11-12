#include "messengerwindow.h"

MessengerWindow::MessengerWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	userDialogs = nullptr;
	dataReceiver = new VKDataReceiver;
	friendList = new QComboBox(this);
	friendList->hide();
	friends = new Friends(friendList);
	authorization = new Authorization(this);

	setConnections();

	ui.dialogsInfoArea->setWidgetResizable(true);
	ui.dialogArea->setWidgetResizable(true);
	dialogsScrollWidget = new QWidget;
	dialogsScrollWidget->setLayout(new QVBoxLayout);
	ui.dialogsInfoArea->setWidget(dialogsScrollWidget);


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
	delete userDialogs;
	delete friendList;
	delete friends;
}

void MessengerWindow::setConnections()
{
	connect(authorization, SIGNAL(authorizationCompleted()), this, SLOT(authorizationCompleted()));
	connect(authorization, SIGNAL(authorizationFailed()), this, SLOT(authorizationFailed()));
	connect(this, SIGNAL(userInfoLoaded()), this, SLOT(loadDialogs()));
	connect(ui.dialogArea->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), this, SLOT(moveScrollBarToBotton(int,int)));
	connect(ui.logoutB, SIGNAL(clicked()), this, SLOT(logout()));
	connect(ui.sendMessageB, SIGNAL(clicked()), this, SLOT(sendMessage()));
	connect(ui.newDialogB, SIGNAL(clicked()), this, SLOT(showFriends()));
}

void MessengerWindow::closeEvent(QCloseEvent *event)
{
	event->ignore();
	if (saveData())
	{
		emit stopTracing();
		event->accept();
	}
}

void MessengerWindow::authorizationCompleted()
{
	authorization->closeBrowser();
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
	/* Загружаем друзей */
	friends->loadFriends(friendList);
	connect(friendList, SIGNAL(currentIndexChanged(int)), this, SLOT(newDialog(int)));
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
	connect(this, SIGNAL(stopTracing()), userDialogs, SLOT(stopTracing ()));
	connect(this, SIGNAL(newMessage(QString &)), userDialogs, SLOT(newMessage(QString &)));
	connect(this, SIGNAL(newDialog(unsigned int)), userDialogs, SLOT(newDialog(unsigned int)));
	connect(userDialogs, SIGNAL(canExit()), this, SLOT(closeProgram()));
	connect(userDialogs, SIGNAL(changeDialogPosition(QWidget *)), this, SLOT(changeDialogPosition(QWidget *)));
	userDialogs->loadDialogs();
}

void MessengerWindow::messagesReceived(QWidget *scrollWidget, QString &username)
{
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

void MessengerWindow::changeDialogPosition(QWidget *dialog)
{
	//ui.dialogsInfoArea->ensureWidgetVisible(dialog);
	QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui.dialogsInfoArea->widget()->layout());
	layout->removeWidget(dialog);
	layout->insertWidget(0, dialog);
}

void MessengerWindow::sendMessage()
{
	QString msg = ui.message->toPlainText();
	
	if (!msg.isEmpty())
	{
		ui.message->clear();
		emit newMessage(msg);
	}
}

void MessengerWindow::showFriends()
{
	int xPos = ui.userName->x();
	int yPos = ui.newDialogB->y();
	friendList->move(xPos, yPos);
	friendList->showPopup();
	friendList->show();
}

void MessengerWindow::logout()
{
	emit stopTracing();
	Session::getInstance().deleteSession();
	QFile dataFile(DATA_FILENAME);
	dataFile.remove();
}

void MessengerWindow::closeProgram()
{
	exit(EXIT_SUCCESS);
}

void MessengerWindow::newDialog(int user)
{
	friendList->hide();
	unsigned int id = friendList->itemData(user).toUInt();
	emit newDialog(id);
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