#include "mainwindow.h"
#include <cassert>

#include <QDir>

//#include <iostream> // temp

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	pflag = false;
	//default layout formatting, maybe (inventory qvbox was only the first line)
	//pglMain->setSpacing(6);
	//pglMain->setContentsMargins(11, 11, 11, 11);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////// pre META

	// size policies
	QSizePolicy mainBtnSize(QSizePolicy::Minimum, QSizePolicy::Minimum);
	QSizePolicy btnSize(QSizePolicy::Fixed, QSizePolicy::Fixed);

	this->resize(1200, 800);
	mainStk = new QStackedWidget(this);

	// main stack pages...
	QWidget *pgMain = new QWidget();
	QWidget *pgGm = new QWidget();
	QWidget *pgPl = new QWidget();
	// ...and their layouts
	QHBoxLayout *pglMain = new QHBoxLayout(pgMain);
	QGridLayout *pglGm = new QGridLayout(pgGm);
	QGridLayout *pglPl = new QGridLayout(pgPl);

	mainStk->addWidget(pgMain);
	mainStk->addWidget(pgGm);
	mainStk->addWidget(pgPl);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////// Main Page

	QSignalMapper *mapper = new QSignalMapper(this);

	QPushButton *gmBtn = new QPushButton("GM Sim", pgMain);
	gmBtn->setSizePolicy(mainBtnSize);
	connect(gmBtn, SIGNAL(clicked()), mapper, SLOT(map()));
	mapper->setMapping(gmBtn, 1);

	QPushButton *plBtn = new QPushButton("Player Sim", pgMain);
	plBtn->setSizePolicy(mainBtnSize);
	connect(plBtn, SIGNAL(clicked()), this, SLOT(openPlayer()));
	//mapper->setMapping(plBtn, 2);
	//QInputDialog *pIn = new QInputDialog(pgMain);

	connect(mapper, SIGNAL(mapped(int)), mainStk, SLOT(setCurrentIndex(int)));

	pglMain->addWidget(gmBtn);
	pglMain->addWidget(plBtn);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////// gm page

	/////////////////////////////////////////////////////////////////////////////////////////////////////////// player page

	////////////////////////////////////////////////////////////////////////// info row 1

	QHBoxLayout *sRow1 = new QHBoxLayout;

	QLineEdit *pName = new QLineEdit(pgPl);
	QComboBox *pSex = new QComboBox(pgPl);
	pSex->addItem("N");
	pSex->addItem("M");
	pSex->addItem("F");
	QLabel *lvlL = new QLabel("lvl:", pgPl);
	QPushButton *lvl = new QPushButton("1", pgPl);
	QLabel *expL = new QLabel("exp:", pgPl);
	QPushButton *expCurr = new QPushButton("1000", pgPl);
	QLabel *expMax = new QLabel("/2000", pgPl);

	sRow1->addWidget(pName);
	sRow1->addWidget(pSex);
	sRow1->addWidget(lvlL);
	sRow1->addWidget(lvl);
	sRow1->addWidget(expL);
	sRow1->addWidget(expCurr);
	sRow1->addWidget(expMax);

	////////////////////////////////////////////////////////////////////////// info row 2

	QHBoxLayout *sRow2 = new QHBoxLayout;

	QLabel *hitDie = new QLabel("d6", pgPl);
	QComboBox *align = new QComboBox(pgPl);
	pSex->addItem("CG");
	pSex->addItem("NG");
	pSex->addItem("LG");
	QLineEdit *pAge = new QLineEdit("age", pgPl);
	QLineEdit *pWeight = new QLineEdit("weight", pgPl);
	QLineEdit *pHeight = new QLineEdit("height", pgPl);
	QLineEdit *pDiety = new QLineEdit("diety", pgPl);

	sRow2->addWidget(hitDie);
	sRow2->addWidget(align);
	sRow2->addWidget(pAge);
	sRow2->addWidget(pWeight);
	sRow2->addWidget(pHeight);
	sRow2->addWidget(pDiety);

	////////////////////////////////////////////////////////////////////////// info row 3

	QHBoxLayout *sRow3 = new QHBoxLayout;

	QLabel *pRace = new QLabel("race", pgPl);
	QLabel *pClass = new QLabel("class", pgPl);
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
	QSpinBox *miscSpb[16];
	QLabel *coreRank[16];

	// core grid
	QString coreNList[]{ "HP", "AC", "init", "spd", "STR", "DEX", "CON", "INT", "WIS", "CHA", "BAB", "CMB", "CMD", "fsav", "wsav", "rsav" };
	for (int i = 0; i < 16; ++i)
	{
		coreName[i] = new QLabel(coreNList[i], pgPl);
		coreBox->addWidget(coreName[i], i, 0);
		miscSpb[i] = new QSpinBox(pgPl);
		coreBox->addWidget(miscSpb[i], i, 1);
		coreRank[i] = new QLabel("crank", pgPl);
		coreBox->addWidget(coreRank[i], i, 2);
	}

	////////////////////////////////////////////////////////////////////////// skills

	QLabel *skillHeader = new QLabel("skills", pgPl); // header

	QScrollArea *skillBoxArea = new QScrollArea(pgPl);	// skill area
	QWidget *skillBox = new QWidget();					// skillbox
	QGridLayout *skilllBox = new QGridLayout(skillBox);	// skillbox layout

	QPushButton *skillName[35];
	QLabel *skillRank[35];
	//QSpacerItem *skillSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

	// skill grid
	QString skillNList[]{ "Acrobatics", "Appraise", "Bluff", "Climb", "Craft", "Diplomacy", "Disable Device", "Disguise", "Escape Artist", "Fly", 
		"Handle Animal", "Heal", "Intimidate", "K. Arcana", "K. Dungeoneering", "K. Engineering", "K. Geography", "K. History", "K. Local", "K. Nature",
		"K. Nobility", "K. Planes", "K. Religion", "Linguistics", "Perception", "Perform", "Profession", "Ride", "Sense Motive", "Sleight of Hand",
		"Spellcraft", "Stealth", "Survival", "Swim", "Use Magic Device" };
	for (int i = 0; i < 35; ++i)
	{
		skillName[i] = new QPushButton(skillNList[i], skillBox);
		//skillName[i]->setSizePolicy(btnSize);
		skilllBox->addWidget(skillName[i], i, 0);
		skillRank[i] = new QLabel("srank", skillBox);
		skilllBox->addWidget(skillRank[i], i, 1);
	}

	skillBoxArea->setWidget(skillBox);

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

	QLabel *eqpHeader[3]; // x, weight/max
	QLabel *eqpName[16];
	QPushButton *eqpSlot[16];

	eqpHeader[0] = new QLabel("x", pgPl);
	eqplBox->addWidget(eqpHeader[0], 0, 0);
	eqpHeader[1] = new QLabel("w", pgPl);
	eqplBox->addWidget(eqpHeader[1], 0, 2);
	eqpHeader[2] = new QLabel("mw", pgPl);
	eqplBox->addWidget(eqpHeader[2], 0, 3);

	// equipment grid
	QString eqpNList[]{ "R. Hand", "Armor", "Chest", "Feet", "Head", "Neck", "Shoulders", "R. Ring",
		"L. Hand", "Body", "Belt", "Hands", "Headband", "Eyes", "Wrist", "L. Ring" };
	for (int i = 0; i < 8; ++i)
	{
		eqpName[i] = new QLabel(eqpNList[i], pgPl);
		eqplBox->addWidget(eqpName[i], i + 1, 0);
		eqpSlot[i] = new QPushButton("eSlot", pgPl);
		eqplBox->addWidget(eqpSlot[i], i + 1, 1);
		eqpName[i] = new QLabel(eqpNList[8+i], pgPl);
		eqplBox->addWidget(eqpName[i], i + 1, 2);
		eqpSlot[i] = new QPushButton("eSlot", pgPl);
		eqplBox->addWidget(eqpSlot[i], i + 1, 3);
	}

	QScrollArea *itmBoxArea = new QScrollArea(pgPl);	// item area
	QWidget *itmBox = new QWidget();
	QGridLayout *itmlBox = new QGridLayout(itmBox);

	QVector<QPushButton*> itemNames;
	QVector<QLabel*> itemWeight;
	QVector<QPushButton*> itemPrice;

	QSpacerItem *itemSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

	itmBoxArea->setWidget(itmBox);

	invlBox->addLayout(eqplBox);
	invlBox->addWidget(itmBoxArea);

	////////////////////////////////////////////////////////////////////////// pgPl credits

	pglPl->addLayout(sRow1, 0, 0, 1, 3);
	pglPl->addLayout(sRow2, 1, 0, 1, 3);
	pglPl->addLayout(sRow3, 2, 0, 1, 3);
	pglPl->addWidget(skillBoxArea, 4, 0);
	pglPl->addLayout(miscBox, 4, 1);
	pglPl->addLayout(coreBox, 4, 2);
	pglPl->addWidget(skillHeader, 3, 0);
	pglPl->addLayout(invlBox, 0, 3, 5, 1);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////// credits aka post META

	this->setCentralWidget(mainStk);
	mainStk->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
	if (pflag)
	{
		delete player0;
	}
}

void MainWindow::openPlayer()
{
	bool ok;
	pfilename = QInputDialog::getText(this, tr("QInputDialog::getText()"),
		"Name:", QLineEdit::Normal, QDir::home().dirName(), &ok);

	if (ok && !pfilename.isEmpty())
	{
		pfilename += "1.txt";
		QFile pfile(pfilename);
		if (pfile.open(QIODevice::Text)) // make this point to the correct directory
		{
			player0 = new Player(pfilename.toStdString(), "load");
			pflag = true;
			mainStk->setCurrentIndex(2);
		}
		else
		{
			mainStk->setCurrentIndex(2); // for debug
			// create/input new character, save, then load:



			//string temp;

			//// lvl, exp

			//cout << "str: ";
			//getline(cin, temp);
			//str = atoi(temp.c_str());
			//cout << "dex: ";
			//getline(cin, temp);
			//dex = atoi(temp.c_str());
			//cout << "con: ";
			//getline(cin, temp);
			//con = atoi(temp.c_str());
			//cout << "int: ";
			//getline(cin, temp);
			//int1 = atoi(temp.c_str());
			//cout << "wis: ";
			//getline(cin, temp);
			//wis = atoi(temp.c_str());
			//cout << "cha: ";
			//getline(cin, temp);
			//cha = atoi(temp.c_str());

			//cout << "favored class: ";
			//getline(cin, temp);
			//favoredClass.push_back(temp);

			//cout << "class: ";
			//getline(cin, class1); // change to menu maybe
			//hp.push_back(lvl);
			//setClass(0);
			//hp.push_back(0);
			//cmb = 0;
			//cmd = 10;
			//setxpcap();

			//capacity = str * 10;
			//setRace();

			//init = statMod(dex);
			//inputStat(trait, "trait", "traits.txt");
			//ac.push_back(10);
			//ac.push_back(statMod(dex));
			//ac.push_back(0);
			//cout << "hp: ";
			//getline(cin, temp);
			//hp.push_back(atoi(temp.c_str()));

			//inputStat(ability, "ability", "abilities.txt");
			//inputStat(spell, "spell", "spells.txt");
			//inputStat(feat, "feat", "feats.txt");


			//int choice = -1;
			//skill.resize(35, 0);
			//for (int i = 0; i < skill.size(); i++)
			//{
			//	cout << i + 1 << ". " << skillName[i] << endl;
			//}
			//while (choice != 0)
			//{
			//	if (choice > 0)
			//	{
			//		cout << "value: ";
			//		getline(cin, temp);
			//		skill[choice - 1] = atoi(temp.c_str());
			//	}
			//	cout << "Enter choice or 0 when done: ";
			//	getline(cin, temp);
			//	choice = atoi(temp.c_str());
			//}

			//inputStat(lang, "language");
			//inputStat(extra, "extra");
			//sr = 0;

			//gp = 0;
			//encumb = 0;

			//cout << endl;
		}
	}
}
