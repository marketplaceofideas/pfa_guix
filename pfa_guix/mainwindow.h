#pragma once

#include <QtWidgets/QMainWindow>
//#include <QVector>
#include "player.h"

#include <QtWidgets>

class PLWindow : public QMainWindow
{
	Q_OBJECT

public:
	PLWindow(QWidget *parent = Q_NULLPTR);
	~PLWindow();
};

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

	QStackedWidget *mainStk;
	QString pfilename;
	Player *player0;

	bool pflag;

	PLWindow *plWin;

public slots:
	void openPlayer();
};
