#include "loadingscreen.h"

LoadingScreen::LoadingScreen()
{
	glass = new QLabel();
	glass->setAutoFillBackground(true);
	infoTextContaiter = new QLabel();
	animationContainer = new QLabel();
	effect = new QGraphicsOpacityEffect();
	effect->setOpacity (0.7);
	
	movie = new QMovie(QString(ANIMATION_PATH), QByteArray(), animationContainer);

	animationContainer->setFixedSize(80, 80);
}

LoadingScreen::~LoadingScreen()
{
	delete glass;
	delete movie;
	delete infoTextContaiter;
	delete animationContainer;
	delete effect;
}

void LoadingScreen::activate(QWidget *widget)
{
	deactivate();
	effect->setEnabled(true);

	glass->setParent(widget);
	widget->installEventFilter(this);
	glass->setGraphicsEffect(effect);
	glass->show();

	showInfoTextBlock();
	showAnimationBlock();

	QEvent event(QEvent::Resize);
	eventFilter(0, &event);
}

void LoadingScreen::deactivate()
{
	if (glass->parentWidget() != 0) 
	{
		glass->parentWidget()->removeEventFilter(this);

		glass->hide();
		glass->setParent(0);
		animationContainer->hide();
		infoTextContaiter->hide();
		animationContainer->setParent(0);
		infoTextContaiter->setParent(0);
		effect->setEnabled(false);
	}
}


bool LoadingScreen::eventFilter(QObject *object, QEvent *event)
{
	if ((event->type() == QEvent::Show) || (event->type() == QEvent::Resize)) 
	{
		glass->resize(glass->parentWidget()->size());
		glass->move(0, 0);
		infoBlockPositioning();
		return true;
	}
	glass->setFocus();
	return false;
}

void LoadingScreen::showInfoTextBlock()
{
	infoTextContaiter->setParent(glass->parentWidget());

	infoTextContaiter->setText(QString(LOADING_TEXT));
	QFont font("Verdana");
	infoTextContaiter->setFont(font);
	infoTextContaiter->setAlignment(Qt::AlignCenter);
	infoTextContaiter->show();
	infoTextContaiter->adjustSize();
	
	infoBlockPositioning();
}

void LoadingScreen::showAnimationBlock()
{
	animationContainer->setParent(glass->parentWidget());

	animationContainer->setMovie(movie);
	animationContainer->show();
	infoBlockPositioning();
	movie->start();
}

void LoadingScreen::infoBlockPositioning()
{
	if (animationContainer->isVisible() && infoTextContaiter->isVisible()) 
	{
		animationContainer->move((glass->width() - animationContainer->width()) / 2,
								  glass->height() / 2 - animationContainer->height());

		infoTextContaiter->move((glass->width() - infoTextContaiter->width()) / 2,
								 glass->height() / 2 + infoTextContaiter->height());
	}
	else 
	{
		if (animationContainer->isVisible())
		{
			animationContainer->move((glass->width() - animationContainer->width()) / 2,
									 (glass->height() - animationContainer->height()) / 2);
		}

		if (infoTextContaiter->isVisible())
		{
			infoTextContaiter->move((glass->width() - infoTextContaiter->width()) / 2,
									(glass->height() - infoTextContaiter->height()) / 2);
		}
	}
}
