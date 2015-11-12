#ifndef FRIENDS_H
#define FRIENDS_H

#include <QObject>
#include <QComboBox>
#include <QMessageBox>
#include <QHash>
#include "session.h"
#include "vkdatareceiver.h"

#define FRIENDS_NUMBER 50

class Friends : public QObject
{
	Q_OBJECT

public:
	Friends(QComboBox *list);
	~Friends();

	void loadFriends(QComboBox *list);
	QPixmap & getPhoto(unsigned int id) const;
	bool containsPhoto(unsigned int id) const;

private:
	QHash<unsigned int, QPair<QString, QPixmap> > friends;
};

#endif // FRIENDS_H
