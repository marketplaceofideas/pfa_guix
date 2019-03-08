#ifndef PLWINDOW_H
#define PLWINDOW_H

#include <QtWidgets>
#include "player.h"

class PLWindow : public QMainWindow
{
	Q_OBJECT

public:
	PLWindow(Player *player0, QWidget *parent = Q_NULLPTR);
	Player *p0;

	void pexpUp();
	void plvlUp();

	void setEqp(QPushButton *button);

	// layout sections
	QVBoxLayout *infoRows(QWidget*);
	QVBoxLayout *inventory(QWidget*);
	QGridLayout *core(QWidget*);
	QScrollArea *spells(QWidget*);
	QScrollArea *feats(QWidget*);

	QScrollArea *skills(QWidget*);
	QStackedWidget *secondarySkillPage(int index, QStackedWidget *upperStk);
	QWidget *tertiarySkillPage(int upper, int lower, QStackedWidget *upperStk);

//public slots:
	void skillDC(QString str, QString &mod, bool check = true);
};

#endif // PLWINDOW_H
