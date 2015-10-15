#include "dialoginfo.h"

DialogInfo::DialogInfo(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

DialogInfo::DialogInfo(const QString &userId, const QString &lastMessage)
{

}

DialogInfo::~DialogInfo()
{

}
