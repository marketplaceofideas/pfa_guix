#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QtWidgets/QMainWindow>
//#include <QVector>

#include <QtWidgets>
#include "player.h"
#include "plwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

	QStackedWidget *mainStk;

	// player window variables
	bool pflag;
	QString pfilename;
	Player *player0;
	PLWindow *plWin;

public slots:
	void openPlayer();
};

#endif // MAINWINDOW_H
