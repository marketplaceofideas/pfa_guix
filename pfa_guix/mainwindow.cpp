#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	for (int i = 0; i <= 34; ++i)
	{
		skillBtn[i] = new QPushButton("x", ui.centralWidget);
		skillBtn[i]->setMaximumSize(100, 100);
		ui.skillNames->layout()->addWidget(skillBtn[i]);
		skillBtn[i]->show();

		skillLbl[i] = new QLabel("1", ui.centralWidget);
		skillLbl[i]->setMaximumSize(100, 100);
		ui.skillRanks->layout()->addWidget(skillLbl[i]);
		skillLbl[i]->show();
	}
}

MainWindow::~MainWindow()
{
	for (int i = 0; i <= 34; ++i)
	{
		delete skillBtn[i];
	}
	//delete ui;
}

//void MainWindow::on_diplBtn_clicked()
//{
	// jk jk
	// it's actually:
	// connect(skllBtn[i], SIGNAL(clicked()), this, SLOT(mySlot()));
	// insert [i] outbound according to skill
	// in the MW

	// probably need a dynamic window for skill detail selection
	// ie

	// input:
	// [_bonus_]
	// [x]cond1
	// [x]cond2
	// [roll]btn

	// output:
	// dc: []   roll: []
	// normal/critical success/failure :
	// x happens

	// misc: conditionals passed as array of bools (ie ints obv)? idk
	// crafting, profession might need separate func

	// side note: int thing is joke, takes up 4x the space but actually probably use ints here for obvious reasons
//}
