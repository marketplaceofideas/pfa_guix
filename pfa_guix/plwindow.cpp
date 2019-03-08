#include "plwindow.h"

#include "frame.h"

PLWindow::PLWindow(Player *player0, QWidget *parent)
	: QMainWindow(parent)
{
	p0 = player0;
	// size policies
	QSizePolicy mainBtnSize(QSizePolicy::Minimum, QSizePolicy::Minimum);
	QSizePolicy btnSize(QSizePolicy::Fixed, QSizePolicy::Fixed);

	this->resize(1200, 800);
	QWidget *pgPl = new QWidget();
	QGridLayout *pglPl = new QGridLayout(pgPl);

	////////////////////////////////////////////////////////////////////////// pgPl credits

	QLabel *skillHeader = new QLabel("skills", pgPl); // skill header

	pglPl->addLayout(infoRows(pgPl), 0, 0, 1, 4);
	pglPl->addWidget(skills(pgPl), 2, 0);
	pglPl->addLayout(core(pgPl), 2, 1);
	pglPl->addWidget(spells(pgPl), 2, 2);
	pglPl->addWidget(feats(pgPl), 2, 3);
	pglPl->addWidget(skillHeader, 1, 0);
	pglPl->addLayout(inventory(pgPl), 0, 4, 3, 1);

	p0->refresh();

	this->setCentralWidget(pgPl);
}

QVBoxLayout *PLWindow::infoRows(QWidget *parent)
{
	QVBoxLayout *layout = new QVBoxLayout();

	QHBoxLayout *sRow1 = new QHBoxLayout();

	QLineEdit *pName = new QLineEdit(QString::fromStdString(p0->name), parent);
	pName->setPlaceholderText("Name");
	QComboBox *pSex = new QComboBox(parent);
	pSex->addItem("N");
	pSex->addItem("M");
	pSex->addItem("F");

	QPushButton *lvlBtn = new QPushButton(QString::number(p0->lvl), parent);
	connect(p0, &Character::refresh, [=] { lvlBtn->setText(QString::number(p0->lvl)); }); // update as needed
	QPushButton *expCurr = new QPushButton(QString::number(p0->xp[0]), parent);
	connect(p0, &Character::refresh, [=] { expCurr->setText(QString::number(p0->xp[0])); }); // update as needed
	QLabel *expMax = new QLabel("/ " + QString::number(p0->xp[1]), parent);
	connect(p0, &Character::refresh, [=] { expMax->setText(QString::number(p0->xp[1])); }); // update as needed

	// set combo box for sex
	int sexVal = pSex->findText(QString(p0->sex));
	if (sexVal != -1)
		pSex->setCurrentIndex(sexVal);

	connect(lvlBtn, SIGNAL(clicked()), this, SLOT(plvlUp()));

	sRow1->addWidget(pName);
	sRow1->addWidget(pSex);
	sRow1->addWidget(new QLabel("lvl:", parent));
	sRow1->addWidget(lvlBtn);
	sRow1->addWidget(new QLabel("exp:", parent));
	sRow1->addWidget(expCurr);
	sRow1->addWidget(expMax);

	////////////////////////////////////////////////////////////////////////// info row 2

	QHBoxLayout *sRow2 = new QHBoxLayout();

	QLabel *hitDie = new QLabel("d" + QString::number(p0->hp[1]), parent);
	QComboBox *align = new QComboBox(parent);
	align->addItems(Frame::getQString("alignment"));

	QLineEdit *pAge = new QLineEdit(QString::number(p0->age), parent);
	pAge->setPlaceholderText("Age");
	QLineEdit *pWeight = new QLineEdit(QString::number(p0->weight) + " lbs.", parent);
	pWeight->setPlaceholderText("Weight");
	QLineEdit *pHeight = new QLineEdit(QString::number(p0->height / 12) + "'" + QString::number(p0->height % 12) + "\"", parent);
	pHeight->setPlaceholderText("Height");
	QLineEdit *pDiety = new QLineEdit(QString::fromStdString(p0->deity), parent);
	pDiety->setPlaceholderText("Deity");

	// set combo box for alignment
	int alnVal = align->findText(QString::fromStdString(p0->align));
	if (alnVal != -1)
		align->setCurrentIndex(alnVal);

	sRow2->addWidget(hitDie);
	sRow2->addWidget(align);
	sRow2->addWidget(pAge);
	sRow2->addWidget(pWeight);
	sRow2->addWidget(pHeight);
	sRow2->addWidget(pDiety);

	////////////////////////////////////////////////////////////////////////// info row 3

	QHBoxLayout *sRow3 = new QHBoxLayout();

	QPushButton *pSize = new QPushButton(QString::fromStdString(p0->size1[0]), parent);
	QLabel *pRace = new QLabel(QString::fromStdString(p0->race), parent);
	QLabel *pClass = new QLabel(QString::fromStdString(p0->class1), parent);
	QPushButton *pFamiliar = new QPushButton("familiar", parent);
	QLabel *pLang = new QLabel("language", parent);

	sRow3->addWidget(pSize);
	sRow3->addWidget(pRace);
	sRow3->addWidget(pClass);
	sRow3->addWidget(pFamiliar);
	sRow3->addWidget(pLang);

	layout->addLayout(sRow1);
	layout->addLayout(sRow2);
	layout->addLayout(sRow3);

	return layout;
}

QScrollArea *PLWindow::skills(QWidget *parent) // double check correct inheritance after switching scroll area and stack
{
	QScrollArea *skillBoxArea = new QScrollArea(parent);	// skill area
	skillBoxArea->QAbstractScrollArea::setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	skillBoxArea->horizontalScrollBar()->setEnabled(false);
	QStackedWidget *skillStk = new QStackedWidget();

	QWidget *skillMain = new QWidget();					// skillbox
	QGridLayout *skilllMain = new QGridLayout(skillMain);	// skillbox layout

	//QSpacerItem *skillSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

	// skill grid
	QStringList nameList = Frame::getQString("skill");
	for (int i = 0; i < 35; ++i)
	{
		QPushButton *skillName = new QPushButton(nameList[i], skillMain);
		skilllMain->addWidget(skillName, i, 0);
		connect(skillName, &QPushButton::clicked, [=] { skillStk->setCurrentIndex(i + 1); });

		QLabel *skillRank = new QLabel(skillMain);
		skilllMain->addWidget(skillRank, i, 1);
		connect(p0, &Character::refresh, [=] { 
			skillRank->setText(QString::number(p0->skill[i][0][0]));
			skillRank->setToolTip("rank:\t" + QString::number(p0->skill[i][1][0]) + "\nclass:\t" + QString::number(p0->skill[i][2][0]) + "\nmisc:\t" + QString::number(p0->skill[i][3][0]));
		}); // update as needed
	}

	skillStk->addWidget(skillMain);

	//////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < 35; ++i)
		skillStk->addWidget(secondarySkillPage(i, skillStk)); // FIX WIDTH ON 3

	skillStk->setCurrentIndex(0);
	skillBoxArea->setWidget(skillStk);
	return skillBoxArea;
}

QStackedWidget *PLWindow::secondarySkillPage(int index, QStackedWidget *upperStk)
{
	QStackedWidget *sskillStk = new QStackedWidget();
	QWidget *page = new QWidget();
	QVBoxLayout *layout = new QVBoxLayout(page);

	sskillStk->addWidget(page);

	////////////////////////////////////////////////////////////////////////// header

	QPushButton *backBtn = new QPushButton("Back", page);
	connect(backBtn, &QPushButton::clicked, [=] { upperStk->setCurrentIndex(0); });
	layout->addWidget(backBtn);

	QFrame *divider1 = new QFrame(page);
	layout->addWidget(divider1);

	////////////////////////////////////////////////////////////////////////// skill check buttons

	QString temp = Frame::getQString("sskill")[index];
	if (temp[0] == '[')
	{
		temp = temp.mid(temp.indexOf(']') + 1);
	}
	QStringList names = temp.split("; ");
	for (int i = 0; i < names.length(); ++i)
	{
		QPushButton *templbl = new QPushButton(names[i], page);
		connect(templbl, &QPushButton::clicked, [=] { sskillStk->setCurrentIndex(i + 1); });
		layout->addWidget(templbl);

		sskillStk->addWidget(tertiarySkillPage(index, i, sskillStk));
	}

	////////////////////////////////////////////////////////////////////////// footer

	QSpacerItem *tempSkillSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	layout->addItem(tempSkillSpacer);

	sskillStk->setCurrentIndex(0);
	return sskillStk;
}

QWidget *PLWindow::tertiarySkillPage(int upper, int lower, QStackedWidget *upperStk) // need to work on layout
{
	QWidget *page = new QWidget();
	QGridLayout *layout = new QGridLayout(page);

	////////////////////////////////////////////////////////////////////////// header

	QPushButton *backBtn = new QPushButton("Back", page);
	connect(backBtn, &QPushButton::clicked, [=] { upperStk->setCurrentIndex(0); });
	layout->addWidget(backBtn, 0, 0, 1, 2);

	QFrame *divider1 = new QFrame(page);
	layout->addWidget(divider1, 1, 0, 1, 2);

	////////////////////////////////////////////////////////////////////////// skill check buttons

	QString temp = Frame::getQString("tskill", upper)[lower];
	if (Frame::getQString("sskill")[upper][0] == '[')
	{
		QString miscs = Frame::getQString("sskill")[upper];
		temp = temp + "; f; " + miscs.mid(1, miscs.indexOf(']') - 1);
	}

	QStringList names = temp.split("; ");
	QStringList dc;
	for (int i = 0; i < names.length(); ++i)
		dc.append("");

	for (int i = 0; i < names.length(); ++i)
	{
		QString prefix = names[i].mid(2, names[i].indexOf(')') - 2);
		QString name = names[i].mid(names[i].indexOf(')')+1);

		switch (names[i].toStdString()[0]) // add 's' combobox
		{
			case 'l': // label
			{
				QLabel *newLabel = new QLabel(name, page);
				layout->addWidget(newLabel, i + 2, 0, 1, 2);
				break;
			}

			case 'c': // checkbox
			{
				QLabel *newLabel = new QLabel(name, page);
				newLabel->setAlignment(Qt::AlignRight);
				layout->addWidget(newLabel, i + 2, 0);
				
				QCheckBox *newCheck = new QCheckBox(page);
				connect(newCheck, &QCheckBox::clicked, [=, &dc] {
					skillDC(prefix, dc[i], newCheck->isChecked()); });
				layout->addWidget(newCheck, i + 2, 1);
				break;
			}

			case 'e': // edit (lineedit)
			{
				QLabel *newLabel = new QLabel(name, page);
				newLabel->setAlignment(Qt::AlignRight);
				layout->addWidget(newLabel, i + 2, 0);

				QLineEdit *newEdit = new QLineEdit(page);
				newEdit->setMaximumWidth(80);
				connect(newEdit, &QLineEdit::textChanged, [=, &dc] {
					skillDC(":" + newEdit->text() + prefix.mid(1), dc[i]); });
				layout->addWidget(newEdit, i + 2, 1);
				break;
			}

			case 's': // selector (combobox)
			{
				QComboBox *newCombo = new QComboBox(page);
				QStringList svals = prefix.mid(1).split(',');
				QStringList nvals = name.split('|');
				for (int i = 0; i < nvals.length(); ++i)
				{
					newCombo->addItem(nvals[i]);
				}
				connect(newCombo, &QComboBox::currentTextChanged, [this, prefix, &dc, i, newCombo, svals] {
					skillDC(prefix[0] + svals[newCombo->currentIndex()], dc[i]); });
				newCombo->setCurrentIndex(0);
				layout->addWidget(newCombo, i + 2, 0, 1, 2);
				break;
			}

			case 'f':
			{
				QFrame *newFrame = new QFrame(page);
				layout->addWidget(newFrame, i + 2, 0, 1, 2);
				break;
			}
		}
	}

	////////////////////////////////////////////////////////////////////////// footer

	QFrame *divider2 = new QFrame(page);
	layout->addWidget(divider2, names.length()+3, 0, 1, 2);

	QPushButton *checkBtn = new QPushButton("Check", page); // only for next pages lul
	connect(checkBtn, &QPushButton::clicked, [=] { // &?
		QString pack = "";
		for (int i = 0; i < dc.length(); ++i) // maybe pass all in as strings for repurposing purposes
		{
			pack = pack + dc[i] + ";";
		}

		QString msg = QString::fromStdString(p0->useSkill(upper, lower, pack.toStdString())); // check the skill and return message
		
		QMessageBox::information(this, "Skill Check", msg, QMessageBox::Ok);
	});
	layout->addWidget(checkBtn, names.length() + 4, 0, 1, 2);

	QSpacerItem *tempSkillSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	layout->addItem(tempSkillSpacer, names.length() + 5, 0, 1, 2);

	return page;
}

// fix double / int business based on whether modifiers can apply to non *_ str's
void PLWindow::skillDC(QString str, QString &mod, bool check) // consider passing a QString[] where each value corresponds to a trigger for the check
{
	// +_b/m_val  /  *_b/m_val
	if (str.toStdString()[0] == '+' || str.toStdString()[0] == '*')
	{
		if (check)
			mod = str;
		else
			mod = "";

		return;
	}

	// =_b/m_val:mod		   --->  +_b/m_val
	// :_b/m_val,x1:y1,x2:y2   --->  +_b/m_val
	else if (str.toStdString()[0] == ':' || str.toStdString()[0] == '=')
	{
		// new prefix
		QString pre = "+";
		int start = 1;
		if (str.toStdString()[1] == 'b' || str.toStdString()[1] == 'm')
		{
			pre += str.toStdString()[1];
			++start;
		}

		// collect and verify value entered by user
		QString in = str.mid(start, str.indexOf(',') - start);
		bool ok;
		in.toInt(&ok);
		if (!ok)			// bad value
		{
			mod = "error";
			return;
		}
		else if (in == "")	// empty value
		{
			mod = "";
			return;
		}

		else if (str.toStdString()[0] == '=')
		{
			// multiply and set user value
			QStringList nums = str.mid(str.indexOf(',') + 1).split(':');
			int x = nums[0].toDouble() * nums[1].toDouble();
			mod = pre + QString::number(x);
			return;
		}

		else if (str.toStdString()[0] == ':')
		{
			// go through table and check user value against rules
			QStringList pairs = str.mid(str.indexOf(',') + 1).split(',');
			for (int i = 0; i < pairs.length(); ++i)
			{
				QStringList nums = pairs[i].split(':');
				if (in.toInt() >= nums[0].toInt())
				{
					mod = pre + QString::number(nums[1].toInt());
				}
			}
			return;
		}
	}
}

QVBoxLayout *PLWindow::inventory(QWidget *parent)
{
	QVBoxLayout *layout = new QVBoxLayout();			// box
	QGridLayout *eqpLayout = new QGridLayout();			// equipment box

	QLabel *eqpHeader[3];
	QLabel *eqpName[16];
	QPushButton *eqpSlot[16];

	eqpHeader[0] = new QLabel("x", parent);
	eqpLayout->addWidget(eqpHeader[0], 0, 0);
	eqpHeader[1] = new QLabel(QString::number(p0->encumb[0]), parent);
	eqpLayout->addWidget(eqpHeader[1], 0, 2);
	eqpHeader[2] = new QLabel("/" + QString::number(p0->encumb[1]), parent);
	eqpLayout->addWidget(eqpHeader[2], 0, 3);

	// equipment grid
	QStringList nameList = Frame::getQString("slots");
	for (int i = 0; i < 8; ++i)
	{
		eqpName[i] = new QLabel(nameList[i], parent);
		eqpLayout->addWidget(eqpName[i], i + 1, 0);
		eqpSlot[i] = new QPushButton("-", parent);
		eqpLayout->addWidget(eqpSlot[i], i + 1, 1);
		eqpName[i] = new QLabel(nameList[8 + i], parent);
		eqpLayout->addWidget(eqpName[i], i + 1, 2);
		eqpSlot[i] = new QPushButton("-", parent);
		eqpLayout->addWidget(eqpSlot[i], i + 1, 3);
	}

	QScrollArea *itmScroll = new QScrollArea(parent);	// item area
	itmScroll->setWidgetResizable(true);
	QWidget *itmPage = new QWidget();
	QVBoxLayout *itmLayout = new QVBoxLayout(itmPage);

	connect(p0, &Character::refresh, [=] {
		QLayoutItem *child;
		while ((child = itmLayout->takeAt(0)) != 0) // clear layout
				delete child;

		for (int i = 0; i < p0->inv.size(); ++i)
		{
			QFrame *newFrame = new QFrame(itmPage);
			QHBoxLayout *newLayout = new QHBoxLayout(newFrame);
			newLayout->setContentsMargins(0, 0, 0, 0);
			QPushButton *newButton = new QPushButton(QString::fromStdString(p0->inv[i].name), newFrame);
			newLayout->addWidget(newButton);
			newLayout->addWidget(new QLabel(QString::number(p0->inv[i].weight), newFrame));
			newLayout->addWidget(new QLabel(QString::number(p0->inv[i].cost), newFrame));
			itmLayout->addWidget(newFrame);
		}

		QSpacerItem *itmSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
		itmLayout->addItem(itmSpacer);
	});

	itmScroll->setWidget(itmPage);

	layout->addLayout(eqpLayout);
	layout->addWidget(itmScroll);

	return layout;
}

QGridLayout *PLWindow::core(QWidget *parent)
{
	QGridLayout *layout = new QGridLayout();

	//QLabel *coreHeader[4];
	QLabel *coreName[16];
	QSpinBox *miscSpb[16];
	QLabel *coreRank[16];

	// core grid
	QString coreNList[]{ "HP", "AC", "spd", "init", "STR", "DEX", "CON", "INT", "WIS", "CHA", "BAB", "CMB", "CMD", "fsav", "wsav", "rsav" };
	vector<int> coreNList2[]{ p0->hp, p0->ac, p0->init, p0->spd, p0->str, p0->dex, p0->con, p0->int1, p0->wis, p0->cha, p0->bab, p0->cmb, p0->cmd, p0->fsav, p0->wsav, p0->rsav };
	for (int i = 0; i < 16; ++i)
	{
		coreName[i] = new QLabel(coreNList[i], parent);
		layout->addWidget(coreName[i], i, 0);
		miscSpb[i] = new QSpinBox(parent);
		layout->addWidget(miscSpb[i], i, 1);
		coreRank[i] = new QLabel(parent);
		connect(p0, &Character::refresh, [=] { 
			coreRank[i]->setText(QString::number(coreNList2[i][0]));
			//if (i > 2) coreRank[i]->setToolTip("core:\t" + QString::number(coreNList2[i][1]) + "\nmisc:\t" + QString::number(coreNList2[i][2]));
		}); // update as needed
		layout->addWidget(coreRank[i], i, 2);
	}

	return layout;
}

QScrollArea *PLWindow::spells(QWidget *parent)
{
	QScrollArea *scroll = new QScrollArea(parent);
	QWidget *page = new QWidget();
	QVBoxLayout *layout = new QVBoxLayout(page);

	QPushButton *temp = new QPushButton("spell1", page);
	layout->addWidget(temp);

	QSpacerItem *spellSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	layout->addItem(spellSpacer);

	scroll->setWidget(page);
	return scroll;
}

QScrollArea *PLWindow::feats(QWidget *parent)
{
	QScrollArea *scroll = new QScrollArea(parent);
	QWidget *page = new QWidget();
	QVBoxLayout *layout = new QVBoxLayout(page);

	QPushButton *temp = new QPushButton("feat1", page);
	layout->addWidget(temp);

	QSpacerItem *spellSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	layout->addItem(spellSpacer);

	scroll->setWidget(page);
	return scroll;
}

void PLWindow::setEqp(QPushButton *button)
{
	if (button->text() == "-")
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
		p0->xp[0] += expgain.toInt();
	}
}

void PLWindow::plvlUp()
{
	if (p0->xp[0] < p0->xp[1])
		return;

	p0->xp[0] -= p0->xp[1];
	++p0->lvl;
	p0->hp[0] = p0->lvl;

	// class stuff

	if (!(p0->lvl % 4))
	{
		// add core stat
	}
}

