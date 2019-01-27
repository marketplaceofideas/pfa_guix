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
	Player *p0;

	void pexpUp();
	void plvlUp();

	void setEqp(QPushButton *button);

	QScrollArea *createSkill(QWidget *par);
	QStackedWidget *secondarySkillPage(int index, QStackedWidget *upperStk);
	QWidget *tertiarySkillPage(int upper, int lower, QStackedWidget *upperStk);

	QVBoxLayout *createInv(QWidget *parent);
	QGridLayout *createCore(QWidget *parent);
	QScrollArea *createSpell(QWidget *parent);
	QScrollArea *createFeat(QWidget *parent);

	QString getString(QString key, int index);

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

//public slots:
	void skillDC(QString str, QString &mod, bool check = true);
};

#endif // PLWINDOW_H
