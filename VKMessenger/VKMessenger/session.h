#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QString>
#include <QHash>
#include <QDataStream>

class Session
{
public:
	/* Получить объект класса */
	static Session & getInstance();

	/* Получить значени по ключу key */
	QString get(const QString &key) const;

	/* Добавить значене value с ключом key */
	void add(const QString &key, const QString &value);

	/* Запомнить фото пользователя */
	void setPhoto(const QByteArray &photo);

	/* Получить фото пользователя */
	QByteArray & getPhoto();

	/* Установить текущего собеседника */
	void setCurrentOpponent(const unsigned int id);

	/* Получить id текущего собеседника */
	unsigned int getCurrentOpponent();

	/* Удалить данные сессии */
	void deleteSession();

	/* Загрузить данные в поток */
	friend QDataStream & operator<<(QDataStream &stream, const Session &session);

	/* Выгрузить данные из потока */
	friend QDataStream & operator>>(QDataStream &stream, Session &session);
	

private:
	Session();
	Session(const Session &) = delete;
	Session(const Session &&) = delete;
	void operator=(const Session &) = delete;
	void operator=(const Session &&) = delete;

	/* Данные сессии */
	QHash<QString, QString> sessionData;

	/* Фото пользователя */
	QByteArray photo;

	/* id текущего собеседника */
	unsigned int currentOpponentId;
};

#endif // SESSION_H
