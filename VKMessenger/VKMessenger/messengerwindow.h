#ifndef MESSENGERWINDOW_H
#define MESSENGERWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_messengerwindow.h"
#include "authorization.h"



class MessengerWindow : public QMainWindow
{
	Q_OBJECT

public:
	MessengerWindow(QWidget *parent = 0);
	~MessengerWindow();

private slots:
	void dialogsLoaded(const QByteArray &data);

private:
	void setConnections();


	Ui::MessengerWindowClass ui;
	Authorization *authorization;
};

#endif // MESSENGERWINDOW_H
