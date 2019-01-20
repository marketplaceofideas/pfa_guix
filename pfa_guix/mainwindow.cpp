#include "mainwindow.h"
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
		if (pfile.open(QIODevice::ReadOnly | QIODevice::Text)) // make this point to the correct directory
		{
			player0 = new Player(pfilename.toStdString(), "load");
			pflag = true;
			hide();
			plWin = new PLWindow(player0, this);
			plWin->show();
		}
		else
		{
			// create/input new character, save, then load:
		}
	}
}
