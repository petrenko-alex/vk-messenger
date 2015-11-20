#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include <QObject>
#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QColor>
#include <QMovie>

#define ANIMATION_PATH "./Application Resources/Loading/blue-circle.gif"
#define LOADING_TEXT "Идёт загрузка..."

class LoadingScreen : public QObject
{
	Q_OBJECT

public:
	LoadingScreen();
	~LoadingScreen();

	/* Активировать экран ожидания */
	void activate(QWidget *widget);

	/* Деактивировать экран ожидания */
	void deactivate();

private:
	/* Фильтр событий */
	bool eventFilter(QObject *object, QEvent *event);

	/* Показать текстовую информацию */
	void showInfoTextBlock();

	/* Показать анимацию */
	void showAnimationBlock();

	/* Настроить позицию */
	void infoBlockPositioning();

	QLabel *glass;
	QMovie *movie;
	QLabel *infoTextContaiter;
	QLabel *animationContainer;
	QGraphicsOpacityEffect *effect;
};

#endif // LOADINGSCREEN_H
