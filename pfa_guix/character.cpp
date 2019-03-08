#include "character.h"
//#include "weapon.h"
#include <cstdlib> // atoi
#include <fstream> // files
#include <sstream> // stringstream
#include "frame.h"
using namespace std; //                                              to sort by type, cr, etc: loop declare all IDs and then sort

Character::Character(string temp, string fname)
{
	QVector<QString> vec = Frame::findVec(temp, fname);
	QStringList nameVec = Frame::getQString("charFile"); // vector for file layout

	// add saveMod, maybe others

	Frame::setStat(cr, vec[nameVec.indexOf("CR")]);
	Frame::setStat(type, vec[nameVec.indexOf("Type")]);
	Frame::setStat(subtype, vec[nameVec.indexOf("Subtypes")]);
	Frame::setStat(environment, vec[nameVec.indexOf("Environment")]);
	Frame::setStat(organization, vec[nameVec.indexOf("Organization")]);
	Frame::setStat(name, vec[nameVec.indexOf("Name")]);
	Frame::setStat(id, vec[nameVec.indexOf("ID")]);
	Frame::setStat(sex, vec[nameVec.indexOf("Sex")]);
	Frame::setStat(age, vec[nameVec.indexOf("Age")]);
	Frame::setStat(height, vec[nameVec.indexOf("Height")]);
	Frame::setStat(weight, vec[nameVec.indexOf("Weight")]);
	Frame::setStat(race, vec[nameVec.indexOf("Race")]);
	Frame::setStat(class1, vec[nameVec.indexOf("Class")]);
	//Frame::setStat(classInfo, vec[nameVec.indexOf("classInfo")]));
	Frame::setStat(align, vec[nameVec.indexOf("Alignment")]);
	Frame::setStat(size1, vec[nameVec.indexOf("Size")]);
	Frame::setStat(lvl, vec[nameVec.indexOf("Level")]);
	Frame::setStat(xp, vec[nameVec.indexOf("XP")]);
	Frame::setStat(ac, vec[nameVec.indexOf("AC")]);
	Frame::setStat(deflect, vec[nameVec.indexOf("Deflect")]);
	Frame::setStat(hp, vec[nameVec.indexOf("HP")]);
	Frame::setStat(spd, vec[nameVec.indexOf("Speed")]);
	Frame::setStat(space, vec[nameVec.indexOf("Space")]);
	Frame::setStat(reach, vec[nameVec.indexOf("Reach")]);
	Frame::setStat(init, vec[nameVec.indexOf("Initiative")]);

	Frame::setStat(str, vec[nameVec.indexOf("STR")]);
	Frame::setStat(dex, vec[nameVec.indexOf("DEX")]);
	Frame::setStat(con, vec[nameVec.indexOf("CON")]);
	Frame::setStat(int1, vec[nameVec.indexOf("INT")]);
	Frame::setStat(wis, vec[nameVec.indexOf("WIS")]);
	Frame::setStat(cha, vec[nameVec.indexOf("CHA")]);
	Frame::setStat(bab, vec[nameVec.indexOf("BAB")]);
	Frame::setStat(cmb, vec[nameVec.indexOf("CMB")]);
	Frame::setStat(cmd, vec[nameVec.indexOf("CMD")]);
	Frame::setStat(fsav, vec[nameVec.indexOf("Fortitude Save")]);
	Frame::setStat(rsav, vec[nameVec.indexOf("Reflex Save")]);
	Frame::setStat(wsav, vec[nameVec.indexOf("Will Save")]);
	Frame::setStat(saveMod, vec[nameVec.indexOf("Save Mod")]);

	skill.resize(35);
	int skval = nameVec.indexOf("Acrobatics");
	for (int i = 0; i < 35; ++i)
		skillSetup(skill[i], vec[skval + i]);

	Frame::setStat(rank, vec[nameVec.indexOf("Rank")]);
	Frame::setStat(condition, vec[nameVec.indexOf("Condition")]);
	Frame::setStat(status, vec[nameVec.indexOf("Status")]);
	Frame::setStat(feat, vec[nameVec.indexOf("Feats")]);
	Frame::setStat(sability, vec[nameVec.indexOf("Special Abilities")]);
	Frame::setStat(spell, vec[nameVec.indexOf("Spells")]);
	Frame::setStat(proficiency, vec[nameVec.indexOf("Proficiency")]);
	Frame::setStat(trait, vec[nameVec.indexOf("Traits")]);
	Frame::setStat(aura, vec[nameVec.indexOf("Auras")]);
	Frame::setStat(dr, vec[nameVec.indexOf("DR")]);
	Frame::setStat(er, vec[nameVec.indexOf("ER")]);
	Frame::setStat(im, vec[nameVec.indexOf("IM")]);
	Frame::setStat(sr, vec[nameVec.indexOf("SR")]);
	Frame::setStat(lang, vec[nameVec.indexOf("Languages")]);
	Frame::setStat(favoredClass, vec[nameVec.indexOf("FavoredClass")]);
	Frame::setStat(extra, vec[nameVec.indexOf("Extra")]);

	Frame::setStat(legs, vec[nameVec.indexOf("Legs")]); // legs

	Frame::setStat(desc, vec[nameVec.indexOf("Description")]);
	Frame::setStat(gp, vec[nameVec.indexOf("gp")]);
	encumb.push_back(0);
	encumb.push_back(Frame::getTable("weight")[str[1]]); // setSize
	
	QStringList qsl = vec[nameVec.indexOf("Items")].split(';');
	for (int i = 0; i < qsl.size(); ++i)
		inv.push_back(Item(qsl[i].toStdString()));

	// update all 'total' vals

	if (id == "player")
	{
		// automate sub/types, xp[3], CR, class skills
	}
}

QVector<QString> Character::makeVec()
{
	QVector<QString> vec;
	QVector<QString> nameVec;
	vec.resize(nameVec.size());

	vec[nameVec.indexOf("CR")] = QString::number(cr);
	vec[nameVec.indexOf("Type")] = Frame::getStat(type);
	vec[nameVec.indexOf("Legs")] = QString::number(legs);
	vec[nameVec.indexOf("Subtypes")] = Frame::getStat(subtype);
	vec[nameVec.indexOf("Environment")] = QString::fromStdString(environment);
	vec[nameVec.indexOf("Organization")] = Frame::getStat(organization);
	vec[nameVec.indexOf("Name")] = QString::fromStdString(name);
	vec[nameVec.indexOf("ID")] = QString::fromStdString(id);
	vec[nameVec.indexOf("Sex")] = sex;
	vec[nameVec.indexOf("Age")] = QString::number(age);
	vec[nameVec.indexOf("Height")] = QString::number(height);
	vec[nameVec.indexOf("Weight")] = QString::number(weight);
	vec[nameVec.indexOf("Race")] = QString::fromStdString(race);
	vec[nameVec.indexOf("Class")] = QString::fromStdString(class1);
	vec[nameVec.indexOf("FavoredClass")] = Frame::getStat(favoredClass);
	//vec[nameVec.indexOf("Class Info")] = Frame::getStat(classInfo);
	vec[nameVec.indexOf("Alignment")] = QString::fromStdString(align);
	vec[nameVec.indexOf("Size")] = Frame::getStat(size1);
	vec[nameVec.indexOf("Level")] = QString::number(lvl);
	vec[nameVec.indexOf("XP")] = Frame::getStat(xp);
	vec[nameVec.indexOf("AC")] = Frame::getStat(ac);
	vec[nameVec.indexOf("Deflect")] = Frame::getStat(deflect);
	vec[nameVec.indexOf("HP")] = Frame::getStat(hp);
	//vec[nameVec.indexOf("Regen")] = Frame::getStat(regen);
	vec[nameVec.indexOf("Speed")] = Frame::getStat(spd);
	vec[nameVec.indexOf("Space")] = Frame::getStat(space);
	vec[nameVec.indexOf("Reach")] = Frame::getStat(reach);
	vec[nameVec.indexOf("Initiative")] = Frame::getStat(init);
	vec[nameVec.indexOf("STR")] = Frame::getStat(str);
	vec[nameVec.indexOf("DEX")] = Frame::getStat(dex);
	vec[nameVec.indexOf("CON")] = Frame::getStat(con);
	vec[nameVec.indexOf("INT")] = Frame::getStat(int1);
	vec[nameVec.indexOf("WIS")] = Frame::getStat(wis);
	vec[nameVec.indexOf("CHA")] = Frame::getStat(cha);
	vec[nameVec.indexOf("BAB")] = Frame::getStat(bab);
	vec[nameVec.indexOf("CMB")] = Frame::getStat(cmb);
	vec[nameVec.indexOf("CMD")] = Frame::getStat(cmd);
	vec[nameVec.indexOf("Fortitude Save")] = Frame::getStat(fsav);
	vec[nameVec.indexOf("Reflex Save")] = Frame::getStat(rsav);
	vec[nameVec.indexOf("Will Save")] = Frame::getStat(wsav);
	vec[nameVec.indexOf("Save Mod")] = Frame::getStat(saveMod);
	vec[nameVec.indexOf("Rank")] = QString::number(rank);
	vec[nameVec.indexOf("Condition")] = Frame::getStat(condition);
	vec[nameVec.indexOf("Status")] = Frame::getStat(status);
	vec[nameVec.indexOf("Feats")] = Frame::getStat(feat);
	vec[nameVec.indexOf("Special Abilities")] = Frame::getStat(sability);
	vec[nameVec.indexOf("Spells")] = Frame::getStat(spell);
	vec[nameVec.indexOf("Proficiency")] = Frame::getStat(proficiency);
	vec[nameVec.indexOf("Traits")] = Frame::getStat(trait);
	vec[nameVec.indexOf("Auras")] = Frame::getStat(aura);
	vec[nameVec.indexOf("DR")] = Frame::getStat(dr);
	vec[nameVec.indexOf("ER")] = Frame::getStat(er);
	vec[nameVec.indexOf("IM")] = Frame::getStat(im);
	vec[nameVec.indexOf("SR")] = Frame::getStat(sr);
	vec[nameVec.indexOf("Languages")] = Frame::getStat(lang);
	vec[nameVec.indexOf("Extra")] = Frame::getStat(extra);
	vec[nameVec.indexOf("Description")] = QString::fromStdString(desc);
	vec[nameVec.indexOf("gp")] = QString::number(gp);
	//vec[nameVec.indexOf("Encumb")] = Frame::getStat(encumb);
	//vec[nameVec.indexOf("Items")] = Frame::getStat();
	//vec[nameVec.indexOf("Weapons")] = Frame::getStat();
	//vec[nameVec.indexOf("Equipment")] = Frame::getStat();

	return vec;
}

void Character::addItem(string name)
{
	
}

/*
void Player::setEncumb()
{
	if (encumb[0] < encumb[1] / 3)
	{
		// light load
	}
	else if (encumb[0] < encumb[1] * 2 / 3)
	{
		// medium load (max dex: +3, armor check: -3, reduce speed [below], run x4)
	}
	else if (encumb[0] < encumb[1])
	{
		// heavy load (max dex: +1, armor check: -6, reduce speed [below], run x3)
	}
	else
	{
		// overencumbered
	}

	int newSpd = 5 * (ceil(spd * 2 / 3) / 5);
}

void shop(string temp = "")//////////////////////////////////consider type???
{
    int id;
    if (temp == "")
    {
        cout << "search: ";
        getline(cin, temp);
        id = Frame::searchID("shops.txt", temp); // -1 loop
    }
    else
    {
        id = Frame::searchID("shops.txt", temp);
    }

    fstream indexfile("shops.txt");
    string trash;

    for (int i = 0; i < id*3; i++)
    {
        getline(indexfile, trash); // ignore to newline????????????????
    }

    Frame::setStat(svec, temp);
}


void addShop()
{

}

void Character::randShop() // move somewhere..?
{
    vector<string> ivec;
    //vector<string>
    Frame::setNames("items.txt");
//    vector<Weapon> wvec;
//    Frame::declareAll("weapons.txt", wvec);
//    vector<Equipment> evec;
//    Frame::declareAll("equipment.txt", evec);
//
//    for (int i = 0; i < wvec.size(); i++)
//    {
//        ivec.insert(ivec.end(), static_cast<Item>(wvec[i]));
//    }
//    for (int i = 0; i < evec.size(); i++)
//    {
//        ivec.insert(ivec.end(), static_cast<Item>(evec[i]));
//    }

    for (int i = 0; i < 10; i++)
    {
        int j = rand() % Frame::names.size();
        ivec.push_back(Frame::names[j]);
        Frame::names.erase(Frame::names.begin() + j);
    }

    for (int i = 0; i < ivec.size(); i++)
    {
        cout << i << ". " << ivec[i] << endl;
    }
    cout << "choice: ";

}
*/

bool operator<(const Character &left, const Character &right)
{
	return left.name < right.name;
}

int Character::statMod(int i)
{
    return (i - (i%2) - 10)/2;
}

//descriptions
void Character::checkDesc(string fname, string temp)
{
    Frame::names.clear();
    //Frame::setStat(Frame::names, temp);
    for (int i = 0; i < Frame::names.size(); i++)
    {
        addDesc(fname, Frame::names[i]);
    }
}

void Character::addDesc(string fname, string name)
{
    vector<string> fvec;
    int x = Frame::checkFile(fname, fvec, name);
    if (x == -1)
    {
        return;
    }
    ofstream descfile(fname.c_str());

    fvec.insert(fvec.begin() + x, name); // name
    x++;

    //cout << "enter description for ";
    //Frame::getStat(name, x, fvec); // desc

    fvec.insert(fvec.begin() + x, "");
    x++;

    for (int j = 0; j < fvec.size(); j++)
    {
        descfile << fvec[j] << endl;
    }

    descfile.close();
}

void Character::showDesc(string fname)
{
    string temp;
    //cout << "search: ";
    //getline(cin, temp);
    int id = Frame::searchID(fname, temp);

    fstream file(fname.c_str());
    for (int i = 0; i < id*3; i++)
    {
        //getline(file, temp);
    }
    //getline(file, temp);
    //cout << temp << endl;
}

int Character::rollSkill(int choice)
{
    if (choice == -1)
    {
        //int choice = chooseSkill();
    }
    if (choice == -1)
    {
        //cout << "not found" << endl;
        return -1;
    }

    int i = Frame::rollDie(20);
    //i += stoi(skill[choice][0]);
	// if blank = blank ...
}


string Character::useSkill(int sskill, int tskill, string pack)
{
	vector<string> tvec; // vector for each tskill element
	stringstream stream(pack);
	string temp;
	while (getline(stream, temp, ';')) // unpack element rules
	{
		tvec.push_back(temp);
	}

	vector<string> bvec;
	vector<string> mvec;
	vector<string> avec;
	int b = 0;
	int m = 1;
	int a = 0;
	for (int i = 0; i < tvec.size(); ++i) // create b, m, a
	{
		if (tvec[i][1] == 'b') // +_b_num
		{
			if (tvec[i][0] == '+')
				b += stoi(tvec[i].substr(2));
			bvec.push_back(tvec[i][0] + tvec[i].substr(2));
		}
		else if (tvec[i][1] == 'm') // +_m_num
		{
			if (tvec[i][0] == '*')
				m *= stoi(tvec[i].substr(2));
			mvec.push_back(tvec[i][0] + tvec[i].substr(2));
		}
		else // +(a)num
		{
			if (tvec[i][0] == '+')
				a += stoi(tvec[i].substr(1));
			avec.push_back(tvec[i]);
		}
	}

    string critfail = "critical failure: ";
    string fail = "failed";
    string succ = "success";
    string critsucc = "critical success: ";

	// (,You fall,,){10}Walk on ledge/uneven ground; Avoid a.o.o.; (5You jump &dc& ft and fall,&20rsav:You narrowly catch the ledge&You miss the ledge and fall,You succeed and jump up to &dc(/2c1)& ft,)Long jump; "
	// "(5You jump &dc/4& ft and fall prone,&20rsav:You narrowly catch the ledge&You miss the ledge and fall,You succeed and jump up to &dc/4(/2c1)& ft,)High jump; Avoid fall damage"
	// , (,You use 1 full round action and fail (you cannot try again),You use 1 full round action and succeed,)

	switch (sskill)
	{
	case acro:
		switch (tskill)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			// pass in:
			bool softground = false;
			int lethal = 0, water = 0, dc = 0;
			// evaluate:
			int check = 0, nlethal6 = 0, nlethal3 = 0;
			bool spellcasting = false;

			if (lethal > 500)
			{
				spellcasting = true;
			}

			if (water >= 10) // fall into water
			{
				if (dc == 15) // deliberate
				{
					dc += 5 * lethal / 50; // dc increases by 5 for every 50 ft of dive

					if (skill[swim][0] > skill[acro][0])
					{
						//check = stoi(skill[swim][0]);
						// "you used swim"
					}
					if (check >= dc)
					{
						lethal -= 3 * water;
					}
				}
				else
				{
					lethal -= 40;
					nlethal3 += 20;
				}
			}
			else
			{
				if (dc == 15)
				{
					lethal -= 10;
					nlethal6 += 10;

					if (softground)
					{
						lethal -= 10;
						nlethal6 += 10;
					}
					if (check >= dc)
					{
						lethal -= 10;
					}
				}
			}

			if (lethal + nlethal6 + nlethal3 > 200)
			{
				lethal = 200 - nlethal6 - nlethal3;
			}

			// dmg + ndmg3 + ndmg6, output string + swimcheck + spellcast

			break;
		}
		break;
	case appr:
		break;
	case bluf:
		switch (tskill)
		{
		case 0:
		case 1:
		case 2:
			// 15 base val
			// passively targeted, takes twice as long as normal msg
			break;
		}
		break;
	case clim:
		break;
	case craf:
		break;
	case dipl:
		break;
	case disa:
		break;
	case disg:
		break;
	case esca:
		break;
	case fly:
		break;
	case hand:
		break;
	case heal:
		break;
	case inti:
		break;
	case karc:
		break;
	case kdun:
		break;
	case keng:
		break;
	case kgeo:
		break;
	case khis:
		break;
	case kloc:
		break;
	case knat:
		break;
	case knob:
		break;
	case kpla:
		break;
	case krel:
		break;
	case ling:
		break;
	case perc:
		break;
	case perf:
		break;
	case prof:
		break;
	case ride:
		break;
	case sens:
		break;
	case slei:
		break;
	case spel:
		break;
	case stea:
		break;
	case surv:
		break;
	case swim:
		break;
	case usem:
		break;
	}

	// check method: d20, rank, ability, racial, +3
	//int check = Frame::rollDie(20) + stoi(skill[sskill][0]);

 //   if (check < dc - 5 && critfail != "critical failure: ")
	//	return critfail;
 //   else if (check >= dc + 10 && critsucc != "critical success: ")
	//	return critsucc;
	//if (check < dc)
	//	return fail;
 //   else
	//	return succ;
	return succ;
}
