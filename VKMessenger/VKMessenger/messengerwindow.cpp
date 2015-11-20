#include "messengerwindow.h"

MessengerWindow::MessengerWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	userDialogs = nullptr;
	screen = new LoadingScreen;
	dataReceiver = new VKDataReceiver;
	ui.message->installEventFilter(this);

	friendList = new QComboBox(this);
	friendList->setIconSize(QSize(40, 40));
	friendList->setMaxVisibleItems(10);
	friendList->setFixedSize(180, 50);
	friendList->hide();

	
	authorization = new Authorization(this);
	
	setConnections();

	ui.dialogsInfoArea->setWidgetResizable(true);
	ui.dialogArea->setWidgetResizable(true);
	dialogsScrollWidget = new QWidget;
	dialogsScrollWidget->setLayout(new QVBoxLayout);
	ui.dialogsInfoArea->setWidget(dialogsScrollWidget);

	this->show();
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
	delete screen;
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
	showLoadingScreen();

	/* Устанавливаем имя пользователя */
	ui.userName->setText(Session::getInstance().get("userName"));

	/* Получаем и устанавливаем фото*/
	QPixmap photo;
	QByteArray photoData = dataReceiver->loadPhoto(QUrl(Session::getInstance().get("userPhoto")));
	if (!photoData.isEmpty() && photo.loadFromData(photoData))
	{
		ui.userPhoto->setPixmap(photo);
		Session::getInstance().setPhoto(photoData);
	}
	else
	{
		qDebug() << "Фото  авторизовавшегося пользователя не загружено";
	}

	/* Загружаем друзей */
	Friends::getInstance().loadFriends(friendList);
	connect(friendList, SIGNAL(activated(int)), this, SLOT(newDialog(int)));

	emit userInfoLoaded();
}

void MessengerWindow::authorizationFailed()
{
	exit(EXIT_FAILURE);
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
	connect(userDialogs, SIGNAL(loadingStarted()), this, SLOT(showLoadingScreen()));

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
	screen->deactivate();
}

void MessengerWindow::dialogsLoaded(QList<DialogInfo *> *userDialogs)
{
	for (auto dialog : *userDialogs)
	{
		dialogsScrollWidget->layout()->addWidget(dialog);
	}
}

void MessengerWindow::moveScrollBarToBotton(int min, int max)
{
	Q_UNUSED(min);
	ui.dialogArea->verticalScrollBar()->setValue(max);
}

void MessengerWindow::changeDialogPosition(QWidget *dialog)
{
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
	int xPos = ui.newDialogB->x() + ui.newDialogB->width ();
	int yPos = ui.newDialogB->y();
	friendList->move(xPos, yPos);
	friendList->showPopup();
	friendList->show();
}

void MessengerWindow::logout()
{
	this->hide();
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
	showLoadingScreen();
	unsigned int id = friendList->itemData(user).toUInt();
	emit newDialog(id);
}

void MessengerWindow::showLoadingScreen()
{
	screen->activate(this);
}

bool MessengerWindow::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == ui.message)
	{
		if (event->type() == QEvent::KeyPress)
		{
			QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
			if ( keyEvent->key() == Qt::Key_Return)
			{
				sendMessage();
				return true;
			}
		}
	}
	return false;
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