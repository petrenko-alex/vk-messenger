#include "dialoginfo.h"

DialogInfo::DialogInfo(/*QWidget *parent, */unsigned int userId, unsigned int messageId, QString &title, QString &lastMessage, QDateTime &lastMessageDateTime, bool out) /*: QWidget(parent)*/
{
	ui.setupUi(this);
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	this->setMinimumSize(WIDTH, HEIGHT);

	this->userId = userId;
	this->messageId = messageId;
	this->title = title;
	this->lastMessage = lastMessage;
	ui.lastMessage->setText(lastMessage);
	this->lastMessageDateTime = lastMessageDateTime;
	ui.lastMessageDateTime->setDateTime(lastMessageDateTime);
	this->out = out;
}

DialogInfo::~DialogInfo()
{

}

DialogInfo & DialogInfo::operator=(const DialogInfo &other)
{
	this->userId = other.userId;
	this->messageId = other.messageId;
	this->title = other.title;
	this->lastMessage = other.lastMessage;
	this->username = other.username;
	this->lastMessageDateTime = other.lastMessageDateTime;
	this->out = other.out;

	return *this;
}
