#ifndef PLWINDOW_H
#define PLWINDOW_H

//#include <QtWidgets/QMainWindow>
//#include <QVector>

#include <QtWidgets>
#include "player.h"

class PLWindow : public QMainWindow
{
	Q_OBJECT

public:
	PLWindow(Player *player0, QWidget *parent = Q_NULLPTR);
	Player *player0;

	void pexpUp();
	void plvlUp();
	void secondarySkillPage(int index, QString sklpgforms);
	void tertiarySkillPage(QWidget *tskillPg, QGridLayout *tskilllPg, int index);

	void setEqp();

	QStackedWidget *skillStk;

	QStackedWidget *sskillStk[35];
	QWidget *skillPg[35];
	QVBoxLayout *skilllPg[35];

	QLineEdit *pName;
	QComboBox *pSex;
	QPushButton *lvlBtn;
	QPushButton *expCurr;
	QLabel *expMax;

	QComboBox *align;
	QLineEdit *pAge;
	QLineEdit *pWeight;
	QLineEdit *pHeight;
	QLineEdit *pDiety;

	QSpinBox *miscSpb[16];
	QLabel *coreRank[16];

	QLabel *skillRank[35];

	QLabel *eqpHeader[3]; // x, weight/max
	QPushButton *eqpSlot[16];

	QVector<QPushButton*> itemNames;
	QVector<QLabel*> itemWeight;
	QVector<QPushButton*> itemPrice;
};

#endif // PLWINDOW_H
