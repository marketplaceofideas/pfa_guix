#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "plwindow.h"
#include "miscwindows.h"

#include "player.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

	// layout sections
	QVBoxLayout *charList(QWidget*);
	QVBoxLayout *shop(QWidget*);

	// misc functions
	void createIndex(QString);
	bool getIndex(string, string&);
	bool inputPlayer();

	QVBoxLayout *tempMisc(QWidget*);

	QStackedWidget *mainStk;

	// player window variables
	bool pflag;
	string pfilename;
	Player *player0;
	PLWindow *plWin;

	vector<Player*> plVec;
	vector<Npc*> npcVec;
	vector<Item*> itmVec;
	vector<Weapon*> wpnVec;
	vector<Equipment*> eqpVec;
};

#endif // MAINWINDOW_H
