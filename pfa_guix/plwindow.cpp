#include "plwindow.h"

PLWindow::PLWindow(Player *p0, QWidget *parent)
	: QMainWindow(parent)
{
	player0 = p0;
	// size policies
	QSizePolicy mainBtnSize(QSizePolicy::Minimum, QSizePolicy::Minimum);
	QSizePolicy btnSize(QSizePolicy::Fixed, QSizePolicy::Fixed);

	this->resize(1200, 800);
	QWidget *pgPl = new QWidget();
	QGridLayout *pglPl = new QGridLayout(pgPl);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////// player page

	////////////////////////////////////////////////////////////////////////// info row 1

	QHBoxLayout *sRow1 = new QHBoxLayout;

	pName = new QLineEdit(QString::fromStdString(player0->name), pgPl);
	pName->setPlaceholderText("Name");
	pSex = new QComboBox(pgPl);
	pSex->addItem("N");
	pSex->addItem("M");
	pSex->addItem("F");
	QLabel *lvlLbl = new QLabel("lvl:", pgPl);
	lvlBtn = new QPushButton(QString::number(player0->lvl), pgPl);
	QLabel *expLbl = new QLabel("exp:", pgPl);
	expCurr = new QPushButton(QString::number(player0->xp), pgPl);
	expMax = new QLabel("/" + QString::number(player0->xpcap), pgPl);

	// set combo box for sex
	int sexVal = pSex->findText(QString(player0->sex));
	if (sexVal != -1)
		pSex->setCurrentIndex(sexVal);

	connect(lvlBtn, SIGNAL(clicked()), this, SLOT(plvlUp()));

	sRow1->addWidget(pName);
	sRow1->addWidget(pSex);
	sRow1->addWidget(lvlLbl);
	sRow1->addWidget(lvlBtn);
	sRow1->addWidget(expLbl);
	sRow1->addWidget(expCurr);
	sRow1->addWidget(expMax);

	////////////////////////////////////////////////////////////////////////// info row 2

	QHBoxLayout *sRow2 = new QHBoxLayout;

	QLabel *hitDie = new QLabel("d" + QString::number(player0->hp[1]), pgPl);
	align = new QComboBox(pgPl);
	align->addItem("CG");
	align->addItem("NG");
	align->addItem("LG");
	align->addItem("CN");
	align->addItem("NN");
	align->addItem("LN");
	align->addItem("CE");
	align->addItem("NE");
	align->addItem("LE");
	pAge = new QLineEdit(QString::number(player0->age), pgPl);
	pAge->setPlaceholderText("Age");
	pWeight = new QLineEdit(QString::number(player0->weight) + " lbs.", pgPl);
	pWeight->setPlaceholderText("Weight");
	pHeight = new QLineEdit(QString::number(player0->height / 12) + "'" + QString::number(player0->height % 12) + "\"", pgPl);
	pHeight->setPlaceholderText("Height");
	pDiety = new QLineEdit("diety", pgPl);
	pDiety->setPlaceholderText("Diety");

	// set combo box for alignment
	int alnVal = align->findText(QString::fromStdString(player0->align));
	if (alnVal != -1)
		align->setCurrentIndex(alnVal);

	sRow2->addWidget(hitDie);
	sRow2->addWidget(align);
	sRow2->addWidget(pAge);
	sRow2->addWidget(pWeight);
	sRow2->addWidget(pHeight);
	sRow2->addWidget(pDiety);

	////////////////////////////////////////////////////////////////////////// info row 3

	QHBoxLayout *sRow3 = new QHBoxLayout;

	QLabel *pRace = new QLabel(QString::fromStdString(player0->race), pgPl);
	QLabel *pClass = new QLabel(QString::fromStdString(player0->class1), pgPl);
	QPushButton *pFamiliar = new QPushButton("familiar", pgPl);
	QLabel *pLang = new QLabel("language", pgPl);

	sRow3->addWidget(pRace);
	sRow3->addWidget(pClass);
	sRow3->addWidget(pFamiliar);
	sRow3->addWidget(pLang);

	////////////////////////////////////////////////////////////////////////// core skills

	QGridLayout *coreBox = new QGridLayout(); // box

	//QLabel *coreHeader[4];
	QLabel *coreName[16];

	// core grid
	QString coreNList[]{ "HP", "AC", "init", "spd", "STR", "DEX", "CON", "INT", "WIS", "CHA", "BAB", "CMB", "CMD", "fsav", "wsav", "rsav" };
	int coreNList2[]{ p0->hp[3], p0->ac[0], p0->init, p0->spd[0], p0->str, p0->dex, p0->con, p0->int1, p0->wis, p0->cha, p0->bab, p0->cmb, p0->cmd, p0->fsav, p0->wsav, p0->rsav };
	for (int i = 0; i < 16; ++i)
	{
		coreName[i] = new QLabel(coreNList[i], pgPl);
		coreBox->addWidget(coreName[i], i, 0);
		miscSpb[i] = new QSpinBox(pgPl);
		coreBox->addWidget(miscSpb[i], i, 1);
		coreRank[i] = new QLabel(QString::number(coreNList2[i]), pgPl);
		coreBox->addWidget(coreRank[i], i, 2);
	}

	////////////////////////////////////////////////////////////////////////// skills

	QLabel *skillHeader = new QLabel("skills", pgPl); // header

	skillStk = new QStackedWidget(pgPl);

	//////////////////////////////////////////////////////////////////////////

	QScrollArea *skillBoxArea = new QScrollArea();	// skill area
	QWidget *skillMain = new QWidget();					// skillbox
	QGridLayout *skilllMain = new QGridLayout(skillMain);	// skillbox layout

	QPushButton *skillName[35];
	//QSpacerItem *skillSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

	QSignalMapper *skillMap = new QSignalMapper(this);

	// skill grid
	QString skillNList[]{ "Acrobatics", "Appraise", "Bluff", "Climb", "Craft", "Diplomacy", "Disable Device", "Disguise", "Escape Artist", "Fly",
		"Handle Animal", "Heal", "Intimidate", "K. Arcana", "K. Dungeoneering", "K. Engineering", "K. Geography", "K. History", "K. Local", "K. Nature",
		"K. Nobility", "K. Planes", "K. Religion", "Linguistics", "Perception", "Perform", "Profession", "Ride", "Sense Motive", "Sleight of Hand",
		"Spellcraft", "Stealth", "Survival", "Swim", "Use Magic Device" };
	for (int i = 0; i < 35; ++i)
	{
		skillName[i] = new QPushButton(skillNList[i], skillMain);
		skilllMain->addWidget(skillName[i], i, 0);
		connect(skillName[i], SIGNAL(clicked()), skillMap, SLOT(map()));
		skillMap->setMapping(skillName[i], i + 1);

		skillRank[i] = new QLabel(QString::number(player0->skill[i]), skillMain);
		skilllMain->addWidget(skillRank[i], i, 1);
	}

	connect(skillMap, SIGNAL(mapped(int)), skillStk, SLOT(setCurrentIndex(int)));

	skillBoxArea->setWidget(skillMain);
	skillStk->addWidget(skillBoxArea);

	//////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < 35; ++i)
	{
		sskillStk[i] = new QStackedWidget();
		skillStk->addWidget(sskillStk[i]);
		skillPg[i] = new QWidget();
		sskillStk[i]->addWidget(skillPg[i]);

		skilllPg[i] = new QVBoxLayout(skillPg[i]);
	}

	// secondary skillpages (names for buttons):
	QString sklpgforms[]{																			// add strHolder() ?
		"ledge/uneven ground walk; avoid a.o.o.; long jump; high jump; avoid fall dmg",
		"evaluate item; evaluate hoard",
		"lie; feint; secret message",
		"climb",
		"craft",
		"change attitude; request; gather info",
		"disable/rig; break/trigger; unlock",
		"disguise",
		"escape",
		"move",
		"",
		"treat",
		"force; demoralize",
		"question; identify",	// all knowledge checks
		"decipher; forge",
		"detect",				// perc passive ony?
		"perform",
		"profession",
		"ride",
		"sense motive",
		"sleight of hand",
		"spellcraft",
		"stealth",
		"survival",
		"swim",
		"use magic object"
	};

	for (int i = 0; i < 12; ++i) // fix
	{
		secondarySkillPage(i, sklpgforms[i]);
	}

	// tertiary skillpages:
	// c: checkbox, b: button, l: lineedit

	////////////////////////////////////////////////////////////////////////// misc

	QVBoxLayout *miscBox = new QVBoxLayout;

	QPushButton *spells = new QPushButton("spells", pgPl);
	miscBox->addWidget(spells);
	QPushButton *profs = new QPushButton("proficiencies", pgPl);
	miscBox->addWidget(profs);
	QPushButton *classStuff = new QPushButton("class", pgPl);
	miscBox->addWidget(classStuff);

	////////////////////////////////////////////////////////////////////////// inventory

	QVBoxLayout *invlBox = new QVBoxLayout();			// box
	QGridLayout *eqplBox = new QGridLayout();			// equipment box

	QLabel *eqpName[16];

	eqpHeader[0] = new QLabel("x", pgPl);
	eqplBox->addWidget(eqpHeader[0], 0, 0);
	eqpHeader[1] = new QLabel(QString::number(player0->encumb), pgPl);
	eqplBox->addWidget(eqpHeader[1], 0, 2);
	eqpHeader[2] = new QLabel("/" + QString::number(player0->capacity), pgPl);
	eqplBox->addWidget(eqpHeader[2], 0, 3);

	// equipment grid
	QString eqpNList[]{ "R. Hand", "Armor", "Chest", "Feet", "Head", "Neck", "Shoulders", "R. Ring",
		"L. Hand", "Body", "Belt", "Hands", "Headband", "Eyes", "Wrist", "L. Ring" };
	for (int i = 0; i < 8; ++i)
	{
		eqpName[i] = new QLabel(eqpNList[i], pgPl);
		eqplBox->addWidget(eqpName[i], i + 1, 0);
		eqpSlot[i] = new QPushButton("-", pgPl);
		eqplBox->addWidget(eqpSlot[i], i + 1, 1);
		eqpName[i] = new QLabel(eqpNList[8 + i], pgPl);
		eqplBox->addWidget(eqpName[i], i + 1, 2);
		eqpSlot[i] = new QPushButton("-", pgPl);
		eqplBox->addWidget(eqpSlot[i], i + 1, 3);
	}

	QScrollArea *itmBoxArea = new QScrollArea(pgPl);	// item area
	QWidget *itmBox = new QWidget();
	QGridLayout *itmlBox = new QGridLayout(itmBox);

	QSpacerItem *itemSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

	itmBoxArea->setWidget(itmBox);

	invlBox->addLayout(eqplBox);
	invlBox->addWidget(itmBoxArea);

	////////////////////////////////////////////////////////////////////////// pgPl credits

	pglPl->addLayout(sRow1, 0, 0, 1, 3);
	pglPl->addLayout(sRow2, 1, 0, 1, 3);
	pglPl->addLayout(sRow3, 2, 0, 1, 3);
	pglPl->addWidget(skillStk, 4, 0);
	pglPl->addLayout(miscBox, 4, 1);
	pglPl->addLayout(coreBox, 4, 2);
	pglPl->addWidget(skillHeader, 3, 0);
	pglPl->addLayout(invlBox, 0, 3, 5, 1);

	this->setCentralWidget(pgPl);
}

void setEqp(QPushButton *button)
{
	if (button->text() == "-")																				// change "Empty" to enum?
	{
		// new window with applicable eqp?
		// open slot for next inventory click?

		// emit "open slot", turn button blue
		// inventory button click function checks open slot, sets text of eqp if open, gives information otherwise
	}
	else
	{
		// idk
	}
}

void PLWindow::pexpUp()
{
	bool ok;
	QString expgain = QInputDialog::getText(this, tr("QInputDialog::getText()"),
		"Gain:", QLineEdit::Normal, QDir::home().dirName(), &ok);

	if (ok && !expgain.isEmpty())
	{
		player0->xp += expgain.toInt();
	}
}

void PLWindow::plvlUp()
{
	if (player0->xp < player0->xpcap)
		return;

	player0->xp -= player0->xpcap;
	++player0->lvl;
	player0->hp[0] = player0->lvl;

	// class stuff

	if (!(player0->lvl % 4))
	{
		// add core stat
	}
}

void PLWindow::secondarySkillPage(int index, QString str)
{
	////////////////////////////////////////////////////////////////////////// header

	QSignalMapper *skillMap = new QSignalMapper(this);

	QPushButton *backBtn = new QPushButton("Back", skillPg[index]);
	skilllPg[index]->addWidget(backBtn);
	connect(backBtn, SIGNAL(clicked()), skillMap, SLOT(map()));
	skillMap->setMapping(backBtn, 0);

	connect(skillMap, SIGNAL(mapped(int)), skillStk, SLOT(setCurrentIndex(int)));

	QFrame *divider1 = new QFrame(skillPg[index]);
	skilllPg[index]->addWidget(divider1);

	////////////////////////////////////////////////////////////////////////// skill check buttons

	QSignalMapper *sskillMap = new QSignalMapper(this);
	QStringList names = str.split(";");
	for (int i = 0; i < names.length(); ++i)
	{
		QPushButton *templbl = new QPushButton(names.value(i), skillPg[index]);
		skilllPg[index]->addWidget(templbl);
		connect(templbl, SIGNAL(clicked()), sskillMap, SLOT(map()));
		sskillMap->setMapping(templbl, i + 1);

		QWidget *tskillPg = new QWidget();
		QGridLayout *tskilllPg = new QGridLayout(tskillPg);

		tertiarySkillPage(tskillPg, tskilllPg, index);
	}
	connect(sskillMap, SIGNAL(mapped(int)), sskillStk[index], SLOT(setCurrentIndex(int)));

	////////////////////////////////////////////////////////////////////////// footer

	QSpacerItem *tempSkillSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	skilllPg[index]->addItem(tempSkillSpacer);
}

void PLWindow::tertiarySkillPage(QWidget *page, QGridLayout *layout, int index) // need to work on layout
{
	////////////////////////////////////////////////////////////////////////// header

	QSignalMapper *skillMap = new QSignalMapper(this);

	QPushButton *backBtn = new QPushButton("Back", page);
	layout->addWidget(backBtn);
	connect(backBtn, SIGNAL(clicked()), skillMap, SLOT(map()));
	skillMap->setMapping(backBtn, 0);

	connect(skillMap, SIGNAL(mapped(int)), skillStk, SLOT(setCurrentIndex(int)));

	QFrame *divider1 = new QFrame(page);
	layout->addWidget(divider1);

	////////////////////////////////////////////////////////////////////////// skill check buttons

	//QSignalMapper *map_1 = new QSignalMapper(this);
	//QString str;	// temp
	//int x;			// temp
	//QStringList names = str.split(";");
	//for (int i = 0; i < names.length(); ++i)
	//{
	//	switch (x)
	//	{
	//	case 'l':
	//		QLabel *newLabel = new QLabel(names.value(i), page);
	//		layout->addWidget(newLabel);
	//		break;

	//	case 'b':
	//		QPushButton *newButton = new QPushButton(names.value(i), page);
	//		layout->addWidget(newButton);
	//		connect(newButton, SIGNAL(clicked()), map_1, SLOT(map()));
	//		map_1->setMapping(newButton, i + 1);
	//		break;

	//	case 'e':
	//		QLineEdit *newEdit = new QLineEdit(names.value(i), page);
	//		layout->addWidget(newEdit);
	//		connect(newEdit, SIGNAL(clicked()), map_1, SLOT(map()));
	//		map_1->setMapping(newEdit, i + 1);
	//		break;
	//	}
	//}
	//connect(map_1, SIGNAL(mapped(int)), sskillStk[index], SLOT(setCurrentIndex(int)));

	////////////////////////////////////////////////////////////////////////// footer

	QFrame *divider2 = new QFrame(page);
	layout->addWidget(divider2);

	QPushButton *checkBtn = new QPushButton("Check", page); // only for next pages lul
	layout->addWidget(checkBtn);

	QSpacerItem *tempSkillSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	//layout->addItem(tempSkillSpacer);
}
