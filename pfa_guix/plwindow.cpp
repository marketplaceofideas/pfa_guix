#include "plwindow.h"

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

	/////////////////////////////////////////////////////////////////////////////////////////////////////////// player page

	////////////////////////////////////////////////////////////////////////// info row 1

	QHBoxLayout *sRow1 = new QHBoxLayout();

	pName = new QLineEdit(QString::fromStdString(p0->name), pgPl);
	pName->setPlaceholderText("Name");
	pSex = new QComboBox(pgPl);
	pSex->addItem("N");
	pSex->addItem("M");
	pSex->addItem("F");
	QLabel *lvlLbl = new QLabel("lvl:", pgPl);
	lvlBtn = new QPushButton(QString::number(p0->lvl), pgPl);
	QLabel *expLbl = new QLabel("exp:", pgPl);
	expCurr = new QPushButton(QString::number(p0->xp), pgPl);
	expMax = new QLabel("/" + QString::number(p0->xpcap), pgPl);

	// set combo box for sex
	int sexVal = pSex->findText(QString(p0->sex));
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

	QHBoxLayout *sRow2 = new QHBoxLayout();

	QLabel *hitDie = new QLabel("d" + QString::number(p0->hp[1]), pgPl);
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
	pAge = new QLineEdit(QString::number(p0->age), pgPl);
	pAge->setPlaceholderText("Age");
	pWeight = new QLineEdit(QString::number(p0->weight) + " lbs.", pgPl);
	pWeight->setPlaceholderText("Weight");
	pHeight = new QLineEdit(QString::number(p0->height / 12) + "'" + QString::number(p0->height % 12) + "\"", pgPl);
	pHeight->setPlaceholderText("Height");
	pDiety = new QLineEdit("diety", pgPl);
	pDiety->setPlaceholderText("Diety");

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

	QLabel *pRace = new QLabel(QString::fromStdString(p0->race), pgPl);
	QLabel *pClass = new QLabel(QString::fromStdString(p0->class1), pgPl);
	QPushButton *pFamiliar = new QPushButton("familiar", pgPl);
	QLabel *pLang = new QLabel("language", pgPl);

	sRow3->addWidget(pRace);
	sRow3->addWidget(pClass);
	sRow3->addWidget(pFamiliar);
	sRow3->addWidget(pLang);

	////////////////////////////////////////////////////////////////////////// misc

	QLabel *skillHeader = new QLabel("skills", pgPl); // header

	/*QVBoxLayout *miscBox = new QVBoxLayout();

	QPushButton *spells = new QPushButton("spells", pgPl);
	miscBox->addWidget(spells);
	QPushButton *profs = new QPushButton("proficiencies", pgPl);
	miscBox->addWidget(profs);
	QPushButton *classStuff = new QPushButton("class", pgPl);
	miscBox->addWidget(classStuff);*/

	////////////////////////////////////////////////////////////////////////// pgPl credits

	pglPl->addLayout(sRow1, 0, 0, 1, 4);
	pglPl->addLayout(sRow2, 1, 0, 1, 4);
	pglPl->addLayout(sRow3, 2, 0, 1, 4);
	pglPl->addWidget(createSkill(pgPl), 4, 0);
	pglPl->addLayout(createCore(pgPl), 4, 1);
	pglPl->addWidget(createSpell(pgPl), 4, 2);
	pglPl->addWidget(createFeat(pgPl), 4, 3);
	pglPl->addWidget(skillHeader, 3, 0);
	pglPl->addLayout(createInv(pgPl), 0, 4, 5, 1);

	this->setCentralWidget(pgPl);
}

QScrollArea *PLWindow::createSkill(QWidget *parent) // double check correct inheritance after switching scroll area and stack
{
	QScrollArea *skillBoxArea = new QScrollArea(parent);	// skill area
	QStackedWidget *skillStk = new QStackedWidget();

	QWidget *skillMain = new QWidget();					// skillbox
	QGridLayout *skilllMain = new QGridLayout(skillMain);	// skillbox layout

	QPushButton *skillName[35];
	//QSpacerItem *skillSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

	// skill grid
	for (int i = 0; i < 35; ++i)
	{
		skillName[i] = new QPushButton(getString("skill", i), skillMain);
		skilllMain->addWidget(skillName[i], i, 0);
		connect(skillName[i], &QPushButton::clicked, [=] { skillStk->setCurrentIndex(i + 1); });

		skillRank[i] = new QLabel(QString::number(p0->skill[i][0]), skillMain);
		skilllMain->addWidget(skillRank[i], i, 1);
	}

	skillStk->addWidget(skillMain);

	//////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < 2; ++i) // fix
	{
		skillStk->addWidget(secondarySkillPage(i, skillStk));
	}

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

	QString temp = getString("sskill", index);
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

	QString temp = getString("tskill" + QString::number(upper), lower);
	if (getString("sskill", upper)[0] == '[')
	{
		QString miscs = getString("sskill", upper);
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
				connect(newCheck, &QCheckBox::clicked, [=] { skillDC(prefix, dc.value(i), newCheck->isChecked()); });
				layout->addWidget(newCheck, i + 2, 1);
				break;
			}

			case 'e': // edit (lineedit)
			{
				QLabel *newLabel = new QLabel(name, page);
				newLabel->setAlignment(Qt::AlignRight);
				layout->addWidget(newLabel, i + 2, 0);

				QLineEdit *newEdit = new QLineEdit(page);
				connect(newEdit, &QLineEdit::textChanged, [=] { skillDC(":" + newEdit->text() + prefix.mid(1), dc.value(i)); });
				layout->addWidget(newEdit, i + 2, 1);
				break;
			}

			case 's': // selector (combobox)
			{
				QComboBox *newCombo = new QComboBox(page);
				QStringList svals = prefix.mid(1).split(',');
				for (int i = 0; i < svals.length(); ++i)
				{
					newCombo->addItem(svals[i]);
				}
				connect(newCombo, &QComboBox::currentTextChanged, [=] { skillDC(prefix[0] + svals[newCombo->currentIndex()], dc.value(i)); });
				newCombo->setCurrentIndex(0);
				layout->addWidget(newCombo, i + 2, 0, 1, 2);
				break;
			}

			case 'f':
				QFrame *newFrame = new QFrame(page);
				layout->addWidget(newFrame, i + 2, 0, 1, 2);
				break;
		}
	}

	////////////////////////////////////////////////////////////////////////// footer

	QFrame *divider2 = new QFrame(page);
	layout->addWidget(divider2, names.length()+3, 0, 1, 2);

	QPushButton *checkBtn = new QPushButton("Check", page); // only for next pages lul
	connect(checkBtn, &QPushButton::clicked, [=] {
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

QVBoxLayout *PLWindow::createInv(QWidget *parent)
{
	QVBoxLayout *layout = new QVBoxLayout();			// box
	QGridLayout *eqpLayout = new QGridLayout();			// equipment box

	QLabel *eqpName[16];

	eqpHeader[0] = new QLabel("x", parent);
	eqpLayout->addWidget(eqpHeader[0], 0, 0);
	eqpHeader[1] = new QLabel(QString::number(p0->encumb), parent);
	eqpLayout->addWidget(eqpHeader[1], 0, 2);
	eqpHeader[2] = new QLabel("/" + QString::number(p0->capacity), parent);
	eqpLayout->addWidget(eqpHeader[2], 0, 3);

	// equipment grid
	QString eqpNList[]{ "R. Hand", "Armor", "Chest", "Feet", "Head", "Neck", "Shoulders", "R. Ring",
		"L. Hand", "Body", "Belt", "Hands", "Headband", "Eyes", "Wrist", "L. Ring" };
	for (int i = 0; i < 8; ++i)
	{
		eqpName[i] = new QLabel(eqpNList[i], parent);
		eqpLayout->addWidget(eqpName[i], i + 1, 0);
		eqpSlot[i] = new QPushButton("-", parent);
		eqpLayout->addWidget(eqpSlot[i], i + 1, 1);
		eqpName[i] = new QLabel(eqpNList[8 + i], parent);
		eqpLayout->addWidget(eqpName[i], i + 1, 2);
		eqpSlot[i] = new QPushButton("-", parent);
		eqpLayout->addWidget(eqpSlot[i], i + 1, 3);
	}

	QScrollArea *itmScroll = new QScrollArea(parent);	// item area
	QWidget *itmPage = new QWidget();
	QGridLayout *itmLayout = new QGridLayout(itmPage);

	QSpacerItem *itemSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

	itmScroll->setWidget(itmPage);

	layout->addLayout(eqpLayout);
	layout->addWidget(itmScroll);

	return layout;
}

QGridLayout *PLWindow::createCore(QWidget *parent)
{
	QGridLayout *layout = new QGridLayout();

	//QLabel *coreHeader[4];
	QLabel *coreName[16];

	// core grid
	QString coreNList[]{ "HP", "AC", "init", "spd", "STR", "DEX", "CON", "INT", "WIS", "CHA", "BAB", "CMB", "CMD", "fsav", "wsav", "rsav" };
	int coreNList2[]{ p0->hp[3], p0->ac[0], p0->init, p0->spd[0], p0->str, p0->dex, p0->con, p0->int1, p0->wis, p0->cha, p0->bab, p0->cmb, p0->cmd, p0->fsav, p0->wsav, p0->rsav };
	for (int i = 0; i < 16; ++i)
	{
		coreName[i] = new QLabel(coreNList[i], parent);
		layout->addWidget(coreName[i], i, 0);
		miscSpb[i] = new QSpinBox(parent);
		layout->addWidget(miscSpb[i], i, 1);
		coreRank[i] = new QLabel(QString::number(coreNList2[i]), parent);
		layout->addWidget(coreRank[i], i, 2);
	}

	return layout;
}

QScrollArea *PLWindow::createSpell(QWidget *parent)
{
	QScrollArea *scroll = new QScrollArea(parent);
	QWidget *page = new QWidget();
	QVBoxLayout *layout = new QVBoxLayout(page);

	QPushButton *temp = new QPushButton("spell1", page);
	QSpacerItem *spellSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	layout->addWidget(temp);
	layout->addItem(spellSpacer);

	scroll->setWidget(page);
	return scroll;
}

QScrollArea *PLWindow::createFeat(QWidget *parent)
{
	QScrollArea *scroll = new QScrollArea(parent);
	QWidget *page = new QWidget();
	QVBoxLayout *layout = new QVBoxLayout(page);

	QPushButton *temp = new QPushButton("feat1", page);
	QSpacerItem *spellSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	layout->addWidget(temp);
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
		p0->xp += expgain.toInt();
	}
}

void PLWindow::plvlUp()
{
	if (p0->xp < p0->xpcap)
		return;

	p0->xp -= p0->xpcap;
	++p0->lvl;
	p0->hp[0] = p0->lvl;

	// class stuff

	if (!(p0->lvl % 4))
	{
		// add core stat
	}
}

// disable targeted skill checks for player (gm only), create window: [target][value] -> [t1][t2], [val]
QString PLWindow::getString(QString key, int index) // PASS WHAT VALUES TO THE PLAYER FUNCTION????????????????????????????????????????????????????????????????????????????????????????????
{
	QString skill[]{ "Acrobatics", "Appraise", "Bluff", "Climb", "Craft", "Diplomacy", "Disable Device", "Disguise", "Escape Artist", "Fly",
		"Handle Animal", "Heal", "Intimidate", "K. Arcana", "K. Dungeoneering", "K. Engineering", "K. Geography", "K. History", "K. Local", "K. Nature",
		"K. Nobility", "K. Planes", "K. Religion", "Linguistics", "Perception", "Perform", "Profession", "Ride", "Sense Motive", "Sleight of Hand",
		"Spellcraft", "Stealth", "Survival", "Swim", "Use Magic Device" };

	// [misc traits]
	QString sskill[]{
		"[s(+0,2,5)Even ground,Slightly obstructed (gravel, sand),Severely obstructed (cavern, rubble); s(+0,2,5)Dry ground,Slightly slippery (wet),Severely slippery (icy); s(+0,2,5)"
			"Flat ground,Slightly sloped (<45),Severely sloped(>45); (+0,2,5,10)Steady ground,Slightly unsteady (boat),Moderately unstead(boat in storm),Severely unstead (earthquake)]"
			"Walk on ledge/uneven ground; Avoid a.o.o.; Long jump; High jump; Avoid fall damage", // handle separately
		"Evaluate item (GM only); Evaluate hoard", // handle with inventory?
		"Lie; Feint in combat (GM only); Secret message",
		"[c(+-10)Opposite wall to brace against; c(-5)Corner wall to brace against; c(+5)Slippery surface]"
			"Climb; Catch yourself; Catch someone else; Haul with rope",
		"Alchemy; Armor; Bows; Traps; Weapons",
		"Diplomacy", // targeted, need to add affinity first
		"Disarm/sabotage device (GM only); Open lock",
		"Disguise yourself (GM only)",
		"Tied rope; Bindings; Grappler",
		"[s(+0,0,2,4,8,12,16)Light (0-10 mph),Moderate (11-20 mph),String (21-30 mph),Severe (31-50 mph),Windstorm (51-74 mph),Hurricane (75-174 mph),Tornado (175+ mph)]"
			"Maneuver; Recover from attack/collision; Avoid fall damage",
		"", // handle
		"", // heal
		"", // intimidate
		"", //Construct/dragon/magical beast; Aura using detect magic; Spell effect; Magic materials; Targeted spell" //; Spells cast with material (?)",	// k arc
		"", //Abberation/ooze; Underground hazard; Mineral/stone/metal; Slope; Depth underground",															// dun
		"", //Dangerous construction; Structure style/age; Structure weakness",																				// eng
		"", //Creature ethnicity/accent; Regional terrain features; Location of nearby community/site",														// geo
		"", //Significant events; Appr. date of event; Obscure/ancient event",																				// his
		"", //Humanoid; Local laws/rulers/locations; Common rumor/tradition; Hidden organizations/rulers/locations",										// loc
		"", //Animal/fey/monstrous humanoid/plant/vermin; Natural hazard; Common plant/animal; Unnatural weather" //; Artificial nature of feature (?)",	// nat
		"", //Current rulers/symbols; Proper etiquette; Line of succession",																				// nob
		"", //Outsider; Names of planes; Current plane; Creature's planar origin",																			// pla
		"", //Undead; Common diety's symbol/clergy; Common mythology/tenets; Obscure diety's symbol/clergy"													// rel
		"",
		"", // gm only (perc)
		"", // perf
		"", // prof
		"",
		"Hunch; Sense enchantment; Discern secret message",
		"Palm object; Hide small object on body; Pickpocket",
		"", // spellcraft (always passive?)
		"",
		"",
		"",
		""
	};

	// :,table +,add =,directmod
	// b,base m,end --- default:(b=0) * (m=1) + a(unspecified),addition
	QVector<QVector<QString>> tskill = {
		{"e(:0:20,2:15,7:10,12:5,36:0)distance (in); c(+5)full speed", // 10 autopass, lost dex bonus, re-check on dmgd
		"e(=1:1)Enemy cmd; c(+5)Moving through; c(+10)Full speed; c(+5)Prone; e(=1:2)Repeated in round", // impossible if not in light armor with light weight
		"e(=b1:2)Distance (ft); c(*m.5)10 ft start", // fail by 4 or less, dc20 reflex save to catch, otherwise fall/prone
		"e(=b1:8)Distance (ft); c(*m.5)10 ft start", // ^base land spd: =(spd-30)/10:-4; cannot exceed max speed, but show max distance (1/2 for standing l.jump)
		"c()Deliberate; c()Water; c()Distance (ft)"},

		{"c()Common item",
		"s(+20,25,30)Normal hoard,Large hoard,Massive hoard"},

		{"e(=b1:1)Opponent sense motive check; s(+-5,0,-5,-10,-20)The target wants to believe you,The lie is believable,The lie is unlikely,The lie is far-fetched,The lie is impossible; c(+5)The target is impaired;"
			"e(=1:1)You have proof (max 10)",
		"", // feint, targeted
		"c(+5)Message is complex"},

		{"l()Pitons or carved handholds take 1min/piton, 1piton/5ft; s(+0,5,10,15,20,25,30)Steep slope/knotted rope against wall,Rope against wall/knotted rope,Surface with ledges,Surface with hand/footholds (pitons/tree/unknotted rope),Surface with narrow hand/footholds,"
			"Rough surface (brick wall),Overhang/ceiling with handholds; c(+5)Half speed (rather than quarter)",
		"s(+0,5,10,15,20,25,30)Steep slope/knotted rope against wall,Rope against wall/knotted rope,Surface with ledges,Surface with hand/footholds (pitons/tree/unknotted rope),Surface with narrow hand/footholds,"
			"Rough surface (brick wall),Overhang/ceiling with handholds; s(+10,20)Slope (< 60 degrees),Wall (>60 degrees)",
		"s(+0,5,10,15,20,25,30)Steep slope/knotted rope against wall,Rope against wall/knotted rope,Surface with ledges,Surface with hand/footholds (pitons/tree/unknotted rope),Surface with narrow hand/footholds,"
			"Rough surface (brick wall),Overhang/ceiling with handholds", // + melee touch attack, +10
		"e()Weight"},

		{"",
		"",
		"",
		"",
		""},

		{"",
		"s(+30,35,40,50)Simple lock,Average lock,Good lock,Superior lock; c(+-10)Thieves tools"},

		{""},

		{"e(=1:1)Enemy cmb", // +20
		"s(+20,23,30,35,30)Net/plant/entangle,Snare spell,Manacles,Masterwork manacles,Tight space",
		"e(=1:1)Enemy cmd"}, // targeted

		{"s(+10,15,15,20,20)Fly at half speed,Hover,Turn using 5ft of movement,Turn around using 10ft of movement,Fly up at >45 degrees",
		"s(+10,25)Attacked,Collision",
		""}, // +10

		{""},

		{""},

		{""},
		// k
		{""}, // arc

		{""}, // dun

		{""}, // eng

		{""}, // geo

		{""}, // his

		{""}, // loc

		{""}, // nat

		{""}, // nob

		{""}, // pla

		{""}, // rel
		// k
		{""},

		{""},
		
		{""},

		{""},

		{""},

		{""},

		{""},

		{""},

		{""},

		{""},

		{""},

		{""}
	};

	if (key == "skill")
	{
		return skill[index];
	}
	else if (key == "sskill")
	{
		return sskill[index];
	}
	else if (key.left(6) == "tskill")
	{
		return tskill[key.mid(6).toInt()][index];
	}
	else
	{
		return "c empty";
	}
}
