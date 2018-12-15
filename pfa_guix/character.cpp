#include "character.h"
//#include "weapon.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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

    cout << "enter description for ";
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
    cout << "search: ";
    getline(cin, temp);
    int id = Frame::searchID(fname, temp);

    fstream file(fname.c_str());
    for (int i = 0; i < id*3; i++)
    {
        getline(file, temp);
    }
    getline(file, temp);
    cout << temp << endl;
}

//skills
int Character::chooseSkill()
{
    string temp;
    cout << "enter first 4 characters of skill (no spaces, just k for knowledge) or menu for menu: ";
    getline(cin, temp);
    if (temp == "menu")
    {
        for (int i = 0; i < skill.size(); i++)
        {
            cout << i+1 << ". " << skillName[i] << endl;
        }
        cout << "choose: ";
        getline(cin, temp);
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
        cout << "not found" << endl;
        return -1;
    }

    int i = Frame::rollDie(20);
    i += skill[choice];
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


void Character::useSkill(int choice)
{
    if (choice == -1)
    {
        choice = chooseSkill();
    }

    if (choice == -1)
    {
        cout << "not found" << endl;
        return;
    }

    int dc = 0;
    int check;
    string temp;

    string critfail = "critical failure: ";
    string fail = "failed";
    string succstr = "success";
    string critsucc = "critical success: ";
    if (choice == acro)
    {
        cout << "1. ledge-walk (half speed)" << endl
             << "2. move through threatened space" << endl /////////check ground conditions: 1-4, add jump distance = check
             << "3. long jump" << endl
             << "4. high jump" << endl
             << "5. brace fall (when deliberate)";
        cout << "choice or 0 to exit: ";
        getline(cin, temp);
        switch(atoi(temp.c_str()))
        {
        case 0:
            return;
        case 1:
            cout << "width (inches): ";
            getline(cin, temp);
            dc += 20;
            dc -= ((atoi(temp.c_str()) + 3) / 5) * 5;
            break;
        case 2:
            cout << "opponent cmd: ";
            getline(cin, temp);
            dc += atoi(temp.c_str());

            cout << "through enemy? ";
            getline(cin, temp);
            if (temp[0] == 'y')
            {
                dc += 5;
            }

            cout << "full speed? ";
            getline(cin, temp);
            if (temp[0] == 'y')
            {
                dc += 10;
            }
            break;
        case 3:
            critfail += "fall";
            fail += ": 20rsav to catch ledge";
            check += 4*((spd[0] - 30) / 10); // override for climb speed

            cout << "distance: ";
            getline(cin, temp);
            dc += atoi(temp.c_str());

            cout << "10ft running start? ";
            getline(cin, temp);
            if (temp[0] == 'n')
            {
                dc *= 2;
            }
            break;
        case 4:
            critfail += "fall prone";
            fail += ": 20rsav to catch ledge";
            check += 4*((spd[0] - 30) / 10); // see above

            cout << "height: ";
            getline(cin, temp);
            dc += 4 * atoi(temp.c_str());

            cout << "10ft running start? ";
            getline(cin, temp);
            if (temp[0] == 'n')
            {
                dc *= 2;
            }
            break;
        case 5:
            dc += 15;
            succstr += ": ignore first 10ft of falling"; //cont
        }
    }
    else if (choice == appr)
    {
        cout << "1. " << endl
             << "2. " << endl
             << "3. " << endl
             << "4. " << endl;
        cout << "choice or 0 to exit: ";
        getline(cin, temp);
        switch(atoi(temp.c_str()))
        {
        case 0:
            return;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        }
    }
    else if (choice == bluf)
    {
        cout << "1. lie" << endl
             << "2. feint" << endl
             << "3. speak code" << endl;
        cout << "choice or 0 to exit: ";
        getline(cin, temp);
        switch(atoi(temp.c_str()))
        {
        case 0:
            return;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        }
    }
    else if (choice == clim)
    {

    }
    else if (choice == craf)
    {
        // depends on what user is invested in
        // alchemy, armor, basket, book, bow, calligraphy, carpentry, cloth, clothing, glass, jewelry, leather, locks, paintings, pottery, sculptures, ships, shoes
        // stonemasonry, traps, weapons, (skills?)

        cout << "1. alchemy" << endl
             << "2. armor" << endl
             << "3. bow" << endl
             << "4. weapon" << endl
             << "5. other" << endl
             << "6. trap" << endl;
        cout << "choice or 0 to exit: ";
        getline(cin, temp);
        switch(atoi(temp.c_str()))
        {
        case 0:
            return;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        }
    }
    else if (choice == dipl)
    {

    }
    else if (choice == disa)
    {

    }
    else if (choice == disg)
    {

    }
    else if (choice == esca)
    {

    }
    else if (choice == fly)
    {

    }
    else if (choice == hand)
    {

    }
    else if (choice == heal)
    {

    }
    else if (choice == inti)
    {

    }
    else if (choice == karc)
    {

    }
    else if (choice == kdun)
    {

    }
    else if (choice == keng)
    {

    }
    else if (choice == kgeo)
    {

    }
    else if (choice == khis)
    {

    }
    else if (choice == kloc)
    {

    }
    else if (choice == knat)
    {

    }
    else if (choice == knob)
    {

    }
    else if (choice == kpla)
    {

    }
    else if (choice == krel)
    {

    }
    else if (choice == ling)
    {

    }
    else if (choice == perc)
    {

    }
    else if (choice == perf)
    {

    }
    else if (choice == prof)
    {

    }
    else if (choice == ride)
    {

    }
    else if (choice == sens)
    {

    }
    else if (choice == slei)
    {

    }
    else if (choice == spel)
    {

    }
    else if (choice == stea)
    {

    }
    else if (choice == surv)
    {

    }
    else if (choice == swim)
    {

    }
    else if (choice == usem)
    {

    }

    if (check < dc - 5 && critfail != "critical failure: ")
    {
        cout << critfail;
    }
    else if (check >= dc + 10 && critsucc != "critical success: ")
    {
        cout << critsucc;
    }
    else if (check < dc)
    {
        cout << fail;
    }
    else
    {
        cout << succstr;
    }
}


void Character::displaySkill()
{
    for (int i = 0; i < skill.size(); i++)
    {
        Frame::condOut(skill[i], skillName[i]);
    }
}

string Character::skillName[35] = {"acrobatics", "appraise", "bluff", "climb", "craft", "diplomacy", "disable device", "disguise", "escape artist",
                                   "fly", "handle animal", "heal", "intimidate", "k.arcana", "k.dungeoneering", "k.engineering", "k.geography", "k.history",
                                   "k.local", "k.nature", "k.nobility", "k.planes", "k.religion", "linguistics", "perception", "perform", "profession", "ride",
                                   "sense motive", "sleight of hand", "spellcraft", "stealth", "survival" "swim", "use magic device"};

