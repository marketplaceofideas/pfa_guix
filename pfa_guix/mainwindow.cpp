#include "mainwindow.h"
#include <fstream>
#include <cassert>

#include <QDir>
#include <qiodevice.h>

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
	// ...and their layouts
	QHBoxLayout *pglMain = new QHBoxLayout(pgMain);
	QGridLayout *pglGm = new QGridLayout(pgGm);

	mainStk->addWidget(pgMain);
	mainStk->addWidget(pgGm);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////// Main Page

	QPushButton *gmBtn = new QPushButton("GM Sim", pgMain);
	gmBtn->setSizePolicy(mainBtnSize);
	connect(gmBtn, &QPushButton::clicked, [&] { mainStk->setCurrentIndex(1); });

	QPushButton *plBtn = new QPushButton("Player Sim", pgMain);
	plBtn->setSizePolicy(mainBtnSize);
	connect(plBtn, &QPushButton::clicked, [&] {
		bool ok = inputPlayer();
		if (ok)
		{
			player0 = new Player(pfilename); // set up player
			pflag = true;
			hide();
			plWin = new PLWindow(player0, this); // open player window
			plWin->show();
		}
	});

	pglMain->addWidget(gmBtn);
	pglMain->addWidget(plBtn);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////// gm page

	pglGm->addLayout(charList(pgGm), 0, 0);
	pglGm->addLayout(tempMisc(pgGm), 0, 1);
	pglGm->addLayout(shop(pgGm), 0, 2);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////// credits

	this->setCentralWidget(mainStk);
	mainStk->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
	if (pflag)
		delete player0;
	for (int i = 0; i < plVec.size(); ++i)
		delete plVec[i];
	for (int i = 0; i < npcVec.size(); ++i)
		delete npcVec[i];
}

QVBoxLayout *MainWindow::charList(QWidget *parent)
{
	QVBoxLayout *layout = new QVBoxLayout(parent);
	QScrollArea *scroll = new QScrollArea(parent);
	scroll->setWidgetResizable(true);

	QWidget *page = new QWidget();
	QVBoxLayout *scrollLayout = new QVBoxLayout(page);

	//////////////////////////////////////////////////////////////////////////

	scrollLayout->addWidget(new QLabel("Players", page));
	QVBoxLayout *plLayout = new QVBoxLayout(page);
	scrollLayout->addLayout(plLayout);

	scrollLayout->addWidget(new QLabel("NPCs", page));
	QVBoxLayout *npcLayout = new QVBoxLayout(page);
	scrollLayout->addLayout(npcLayout);

	QSpacerItem *skillSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	scrollLayout->addItem(skillSpacer);

	//////////////////////////////////////////////////////////////////////////

	QHBoxLayout *buttons = new QHBoxLayout(parent);

	QPushButton *plBtn = new QPushButton("Add Player", parent);
	connect(plBtn, &QPushButton::clicked, [=] {
		bool ok = inputPlayer();
		if (ok)
		{
			Player *ptemp = new Player(pfilename);
			plVec.push_back(ptemp); // set up player

			QPushButton *newButton = new QPushButton(QString::fromStdString(ptemp->name), page);
			plLayout->insertWidget(plLayout->count(), newButton);
		}
	});
	buttons->addWidget(plBtn);

	QPushButton *npcBtn = new QPushButton("Add NPC", parent);
	connect(npcBtn, &QPushButton::clicked, [=] {
		bool inputok = false;
		QString input = QInputDialog::getText(this, tr("QInputDialog::getText()"),
			"Name:", QLineEdit::Normal, "", &inputok); // get name
		if (inputok || !input.isEmpty())
		{
			try
			{
				Npc *ntemp = new Npc(input.toStdString());
				npcVec.push_back(ntemp); // set up player

				QPushButton *newButton = new QPushButton(QString::fromStdString(ntemp->id), page);
				npcLayout->insertWidget(npcLayout->count(), newButton);
			}
			catch (string err)
			{
				QMessageBox::information(this, "My Application", QString::fromStdString(err));
			}
		}
	});
	buttons->addWidget(npcBtn);

	//////////////////////////////////////////////////////////////////////////

	scroll->setWidget(page);
	layout->addWidget(scroll);
	layout->addLayout(buttons);
	return layout;
}

QVBoxLayout *MainWindow::shop(QWidget *parent)
{
	QVBoxLayout *layout = new QVBoxLayout(parent);
	QScrollArea *scroll = new QScrollArea(parent);
	scroll->setWidgetResizable(true);

	QWidget *page = new QWidget();
	QVBoxLayout *scrollLayout = new QVBoxLayout(page);

	//////////////////////////////////////////////////////////////////////////

	scrollLayout->addWidget(new QLabel("Weapons", page));
	QVBoxLayout *wpnLayout = new QVBoxLayout(page);
	scrollLayout->addLayout(wpnLayout);

	scrollLayout->addWidget(new QLabel("Equipment", page));
	QVBoxLayout *eqpLayout = new QVBoxLayout(page);
	scrollLayout->addLayout(eqpLayout);

	scrollLayout->addWidget(new QLabel("Items", page));
	QVBoxLayout *itmLayout = new QVBoxLayout(page);
	scrollLayout->addLayout(itmLayout);

	QSpacerItem *skillSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	scrollLayout->addItem(skillSpacer);

	//////////////////////////////////////////////////////////////////////////

	QHBoxLayout *buttons = new QHBoxLayout(parent);

	// THIS IS ONLY THEORETICAL, LATER ON IT WILL BE "ADD SHOP", "GENERATE SHOP", ETC.
	QPushButton *wpnBtn = new QPushButton("Add Weapon", parent);
	connect(wpnBtn, &QPushButton::clicked, [=] {
		bool inputok = false;
		QString input = QInputDialog::getText(this, tr("QInputDialog::getText()"),
			"Name:", QLineEdit::Normal, "", &inputok); // get name
		if (inputok || !input.isEmpty())
		{
			try
			{
				Weapon *wtemp = new Weapon(input.toStdString());
				wpnVec.push_back(wtemp); // set up player

				QPushButton *newButton = new QPushButton(QString::fromStdString(wtemp->name), page);
				wpnLayout->insertWidget(wpnLayout->count(), newButton);

				QPushButton *dmgLbl = new QPushButton(QString::number(wtemp->dmg[0]), page);
				wpnLayout->insertWidget(wpnLayout->count(), dmgLbl);
			}
			catch (string err)
			{
				QMessageBox::information(this, "My Application", QString::fromStdString(err));
			}
		}
	});
	buttons->addWidget(wpnBtn);

	QPushButton *eqpBtn = new QPushButton("Add Equipment", parent);
	connect(eqpBtn, &QPushButton::clicked, [=] {
		bool inputok = false;
		QString input = QInputDialog::getText(this, tr("QInputDialog::getText()"),
			"Name:", QLineEdit::Normal, "", &inputok); // get name
		if (inputok || !input.isEmpty())
		{
			try
			{
				Equipment *etemp = new Equipment(input.toStdString());
				eqpVec.push_back(etemp); // set up player

				QPushButton *newButton = new QPushButton(QString::fromStdString(etemp->name), page);
				wpnLayout->insertWidget(eqpLayout->count(), newButton);
			}
			catch (string err)
			{
				QMessageBox::information(this, "My Application", QString::fromStdString(err));
			}
		}
	});
	buttons->addWidget(eqpBtn);

	QPushButton *itmBtn = new QPushButton("Add Item", parent);
	connect(itmBtn, &QPushButton::clicked, [=] {
		bool inputok = false;
		QString input = QInputDialog::getText(this, tr("QInputDialog::getText()"),
			"Name:", QLineEdit::Normal, "", &inputok); // get name
		if (inputok || !input.isEmpty())
		{
			try
			{
				Item *itemp = new Item(input.toStdString());
				itmVec.push_back(itemp); // set up player

				QHBoxLayout *newLayout = new QHBoxLayout();

				QPushButton *itmName = new QPushButton(QString::fromStdString(itemp->name), page);
				newLayout->addWidget(itmName);

				QLabel *itmWeight = new QLabel(QString::number(itemp->weight), page);
				newLayout->addWidget(itmWeight);

				QLabel *itmCost = new QLabel(QString::number(itemp->cost), page);
				newLayout->addWidget(itmCost);

				itmLayout->insertLayout(itmLayout->count(), newLayout);
			}
			catch (string err)
			{
				QMessageBox::information(this, "My Application", QString::fromStdString(err));
			}
		}
	});
	buttons->addWidget(itmBtn);

	//////////////////////////////////////////////////////////////////////////

	scroll->setWidget(page);
	layout->addWidget(scroll);
	layout->addLayout(buttons);
	return layout;
}

QVBoxLayout *MainWindow::tempMisc(QWidget *parent)
{
	QVBoxLayout *layout = new QVBoxLayout(parent);

	//////////////////////////////////////////////////////////////////////////

	QPushButton *npcIndex = new QPushButton("Add NPC Index", parent);
	connect(npcIndex, &QPushButton::clicked, [=] { createIndex("bestiary.txt"); });
	layout->addWidget(npcIndex);
	QPushButton *itmIndex = new QPushButton("Add Item Index", parent);
	connect(itmIndex, &QPushButton::clicked, [=] { createIndex("items.txt"); });
	layout->addWidget(itmIndex);
	QPushButton *wpnIndex = new QPushButton("Add Weapon Index", parent);
	connect(wpnIndex, &QPushButton::clicked, [=] { createIndex("weapons.txt"); });
	layout->addWidget(wpnIndex);
	QPushButton *eqpIndex = new QPushButton("Add Equipment Index", parent);
	connect(eqpIndex, &QPushButton::clicked, [=] { createIndex("equipment.txt"); });
	layout->addWidget(eqpIndex);

	QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	layout->addItem(spacer);

	//////////////////////////////////////////////////////////////////////////

	return layout;
}

void MainWindow::createIndex(QString fname)
{
	QVector<QString> indexVec;
	IndexWindow *newIn = new IndexWindow(fname, indexVec, this);
	newIn->setModal(true);
	bool ok = newIn->exec();

	if (ok)
	{
		//  for debugging  //
		QString qs = "";
		for (int i = 0; i < indexVec.size(); ++i)
			qs += indexVec[i] + "\n";

		QInputDialog::getText(this, "Title",
			qs, QLineEdit::Normal, "ignore this dumbass");
		//  /////////////  //

		string name = indexVec[0].toStdString();
		if (name == "") // no name provided
			return;

		vector<string> fvec;
		int loc = Frame::checkFile(fname.toStdString(), fvec, name); // get file info

		vector<string> tempVec;
		for (int i = 0; i < loc; i++)
			tempVec.push_back(fvec[i]);
		for (int i = 0; i < indexVec.size(); ++i) // add new index to middle
			tempVec.push_back(indexVec[i].toStdString());
		tempVec.push_back("\n\n");
		for (int i = loc; i < fvec.size(); ++i)
			tempVec.push_back(fvec[i]);

		std::ofstream file(fname.toStdString().c_str());
		for (int i = 0; i < tempVec.size(); i++) // update file
			file << tempVec[i] << "\n";

		file.close();
		Frame::names.insert(Frame::names.begin() + loc, name); // update names
	}
}

bool MainWindow::getIndex(string fname, string &name)
{
	bool inputok = false;
	QString input = QInputDialog::getText(this, tr("QInputDialog::getText()"),
		"Name:", QLineEdit::Normal, "", &inputok); // get a player filename

	name = input.toStdString();

	if (!inputok || input.isEmpty()) // file input bad
		return false;

	std::ifstream testfile(fname.c_str());
	if (!testfile) // no file found
		return false;

	else // file found
	{
		testfile.close();
		return true;
	}
}

bool MainWindow::inputPlayer()
{
	bool fileok = false;
	QString input = QInputDialog::getText(this, tr("QInputDialog::getText()"),
		"Name:", QLineEdit::Normal, "", &fileok); // get a player filename

	if (!fileok || input.isEmpty()) // file input bad
		return false;

	pfilename = input.toStdString();
	string fname = pfilename + "1.txt";

	std::ifstream testfile(fname.c_str());
	if (!testfile) // no file found, input object
	{
		QVector<QString> vec;
		IndexWindow *newIn = new IndexWindow("player", vec, this);
		newIn->setModal(true);
		bool ok = newIn->exec();

		if (!ok)
			return false; // player input rejected

		//  for debugging  //
		QString qs = "";
		for (int i = 0; i < vec.size(); ++i)
			qs += vec[i] + "\n";

		QInputDialog::getText(this, "Title",
			qs, QLineEdit::Normal, "ignore this dumbass");
		//  /////////////  //

		std::ofstream file(fname.c_str());
		for (int i = 0; i < vec.size(); i++) // update file
			file << vec[i].toStdString() << "\n"; // endl here fucks the file up for some reason

		file.close();
		return true;
	}
	else // file found
	{
		testfile.close();
		return true;
	}
}
