#include "character.h"
//#include "weapon.h"
#include <cstdlib> // atoi
#include <string>
#include <vector>
#include <fstream> // files
#include <sstream> // stringstream
#include "frame.h"
using namespace std; //                                              to sort by type, cr, etc: loop declare all IDs and then sort

/*
void Player::addInv(string fname, string temp)
{

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

    Frame::setStats(svec, temp);
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

Character::Character()
{

}

int Character::statMod(int i)
{
    return (i - (i%2) - 10)/2;
}

//descriptions
void Character::checkDesc(string fname, string temp)
{
    Frame::names.clear();
    Frame::setStats(Frame::names, temp);
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
    Frame::getStats(name, x, fvec); // desc

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

//skills
int Character::chooseSkill()
{
    string temp;
    //cout << "enter first 4 characters of skill (no spaces, just k for knowledge) or menu for menu: ";
    //getline(cin, temp);
    if (temp == "menu")
    {
        for (int i = 0; i < skill.size(); i++)
        {
            //cout << i+1 << ". " << skillName[i] << endl;
        }
        //cout << "choose: ";
        //getline(cin, temp);
        return atoi(temp.c_str());
    }
    else
    {
        for (int i = 0; i < skill.size(); i++)
        {
            string str = Frame::alnumOnly(skillName[i]);
            if (str.find(temp) != string::npos)
            {
                return i;
            }
        }
        return -1;
    }
}

int Character::rollSkill(int choice)
{
    if (choice == -1)
    {
        int choice = chooseSkill();
    }
    if (choice == -1)
    {
        //cout << "not found" << endl;
        return -1;
    }

    int i = Frame::rollDie(20);
    i += skill[choice][0];
    if (choice == acro)
    {
        return i + statMod(dex);
    }
    else if (choice == appr)
    {
        return i + statMod(int1);
    }
    else if (choice == bluf)
    {
        return i + statMod(cha);
    }
    else if (choice == clim)
    {
        return i + statMod(str);
    }
    else if (choice == craf)
    {
        return i + statMod(int1);
    }
    else if (choice == dipl)
    {
        return i + statMod(cha);
    }
    else if (choice == disa)
    {
        return i + statMod(dex);
    }
    else if (choice == disg)
    {
        return i + statMod(cha);
    }
    else if (choice == esca)
    {
        return i + statMod(dex);
    }
    else if (choice == fly)
    {
        return i + statMod(dex);
    }
    else if (choice == hand)
    {
        return i + statMod(cha);
    }
    else if (choice == heal)
    {
        return i + statMod(wis);
    }
    else if (choice == inti)
    {
        return i + statMod(cha);
    }
    else if (choice == karc)
    {
        return i + statMod(int1);
    }
    else if (choice == kdun)
    {
        return i + statMod(int1);
    }
    else if (choice == keng)
    {
        return i + statMod(int1);
    }
    else if (choice == kgeo)
    {
        return i + statMod(int1);
    }
    else if (choice == khis)
    {
        return i + statMod(int1);
    }
    else if (choice == kloc)
    {
        return i + statMod(int1);
    }
    else if (choice == knat)
    {
        return i + statMod(int1);
    }
    else if (choice == knob)
    {
        return i + statMod(int1);
    }
    else if (choice == kpla)
    {
        return i + statMod(int1);
    }
    else if (choice == krel)
    {
        return i + statMod(int1);
    }
    else if (choice == ling)
    {
        return i + statMod(int1);
    }
    else if (choice == perc)
    {
        return i + statMod(wis);
    }
    else if (choice == perf)
    {
        return i + statMod(cha);
    }
    else if (choice == prof)
    {
        return i + statMod(wis);
    }
    else if (choice == ride)
    {
        return i + statMod(dex);
    }
    else if (choice == sens)
    {
        return i + statMod(wis);
    }
    else if (choice == slei)
    {
        return i + statMod(dex);
    }
    else if (choice == spel)
    {
        return i + statMod(int1);
    }
    else if (choice == stea)
    {
        return i + statMod(dex);
    }
    else if (choice == surv)
    {
        return i + statMod(wis);
    }
    else if (choice == swim)
    {
        return i + statMod(str);
    }
    else if (choice == usem)
    {
        return i + statMod(cha);
    }
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
			bool softground;
			int lethal, water, dc;
			// evaluate:
			int check, nlethal6, nlethal3 = 0;
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
						check = skill[swim][0];
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
	int check = Frame::rollDie(20) + skill[sskill][0];

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

string Character::skillName[35] = {"acrobatics", "appraise", "bluff", "climb", "craft", "diplomacy", "disable device", "disguise", "escape artist",
                                   "fly", "handle animal", "heal", "intimidate", "k.arcana", "k.dungeoneering", "k.engineering", "k.geography", "k.history",
                                   "k.local", "k.nature", "k.nobility", "k.planes", "k.religion", "linguistics", "perception", "perform", "profession", "ride",
                                   "sense motive", "sleight of hand", "spellcraft", "stealth", "survival" "swim", "use magic device"};

