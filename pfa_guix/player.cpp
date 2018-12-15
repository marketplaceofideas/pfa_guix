#include "player.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "frame.h"
using namespace std;

//void Player::giveWeapon()
//{
//    wvec.push_back(Weapon());
//    wvec.push_back(Weapon());
//}

// create
Player::Player() : Character()
{
    string temp;
    cout << "1. Create character (not implemented)" << endl
         << "2. Input character" << endl
         << "3. Load character" << endl;
    cout << "Enter choice or 0 to exit: ";
    getline(cin, temp);
    cout << endl;

    switch(atoi(temp.c_str()))
    {
    case 0:
        return; // destruct
        break;
    case 1:
        create();
        break;
    case 2:
        input();
        break;
    case 3:
        load();
        break;
    }
}

void Player::create()
{

}

void Player::input()
{
    string temp;

    cout << "name: ";
    getline(cin, name);

    cout << "1. male" << endl
         << "2. female" << endl;
    cout << "choice: ";
    getline(cin, temp);
    cout << endl;

    switch(atoi(temp.c_str()))
    {
    case 1:
        sex = 'm';
        break;
    case 2:
        sex = 'f';
        break;
    }
    cout << "age: ";
    getline(cin, temp);
    age = atoi(temp.c_str());
    cout << "height (inches): ";
    getline(cin, temp);
    height = atoi(temp.c_str());
    cout << "weight: ";
    getline(cin, temp);
    weight = atoi(temp.c_str());

    cout << "alignment" << endl;
    cout << "1. ce" << endl
         << "2. cn" << endl
         << "3. cg" << endl
         << "4. ne" << endl
         << "5. nn" << endl
         << "6. ng" << endl
         << "7. le" << endl
         << "8. ln" << endl
         << "9. lg" << endl;
    cout << "choose: ";
    getline(cin, temp);

    switch(atoi(temp.c_str()))
    {
    case 1:
        align = "ce";
        break;
    case 2:
        align = "cn";
        break;
    case 3:
        align = "cg";
        break;
    case 4:
        align = "ne";
        break;
    case 5:
        align = "nn";
        break;
    case 6:
        align = "ng";
        break;
    case 7:
        align = "le";
        break;
    case 8:
        align = "ln";
        break;
    case 9:
        align = "lg";
        break;
    }

    cout << "lvl: ";
    getline(cin, temp);
    lvl = atoi(temp.c_str());
    cout << "xp: ";
    getline(cin, temp);
    xp = atoi(temp.c_str());

    cout << "str: ";
    getline(cin, temp);
    str = atoi(temp.c_str());
    cout << "dex: ";
    getline(cin, temp);
    dex = atoi(temp.c_str());
    cout << "con: ";
    getline(cin, temp);
    con = atoi(temp.c_str());
    cout << "int: ";
    getline(cin, temp);
    int1 = atoi(temp.c_str());
    cout << "wis: ";
    getline(cin, temp);
    wis = atoi(temp.c_str());
    cout << "cha: ";
    getline(cin, temp);
    cha = atoi(temp.c_str());

    cout << "favored class: ";
    getline(cin, temp);
    favoredClass.push_back(temp);

    cout << "class: ";
    getline(cin, class1); // change to menu maybe
    hp.push_back(lvl);
    setClass(0);
    hp.push_back(0);
    cmb = 0;
    cmd = 10;
    setxpcap();

    capacity = str*10;
    setRace();

    init = statMod(dex);
    inputStat(trait, "trait", "traits.txt");
    ac.push_back(10);
    ac.push_back(statMod(dex));
    ac.push_back(0);
    cout << "hp: ";
    getline(cin, temp);
    hp.push_back(atoi(temp.c_str()));

    inputStat(ability, "ability", "abilities.txt");
    inputStat(spell, "spell", "spells.txt");
    inputStat(feat, "feat", "feats.txt");


    int choice = -1;
    skill.resize(35,0);
    for(int i = 0; i < skill.size(); i++)
    {
        cout << i+1 << ". " << skillName[i] << endl;
    }
    while (choice != 0)
    {
        if (choice > 0)
        {
            cout << "value: ";
            getline(cin, temp);
            skill[choice-1] = atoi(temp.c_str());
        }
        cout << "Enter choice or 0 when done: ";
        getline(cin, temp);
        choice = atoi(temp.c_str());
    }

    inputStat(lang, "language");
    inputStat(extra, "extra");
    sr = 0;

    gp = 0;
    encumb = 0;

    cout << endl;
}

void Player::load()
{
    string temp;
    cout << "save name: ";
    getline(cin, temp);
    temp += "1.txt";

    ifstream file(temp.c_str());

    getline(file, name);

    getline(file, temp);
    sex = temp[0];
    getline(file, temp);
    age = atoi(temp.c_str());
    getline(file, temp);
    height = atoi(temp.c_str());
    getline(file, temp);
    weight = atoi(temp.c_str());

    getline(file, align);

    getline(file, temp);
    lvl = atoi(temp.c_str());
    getline(file, temp);
    xp = atoi(temp.c_str());
    getline(file, temp);
    xpcap = atoi(temp.c_str());
    getline(file, temp);
    str = atoi(temp.c_str());
    getline(file, temp);
    dex = atoi(temp.c_str());
    getline(file, temp);
    con = atoi(temp.c_str());
    getline(file, temp);
    int1 = atoi(temp.c_str());
    getline(file, temp);
    wis = atoi(temp.c_str());
    getline(file, temp);
    cha = atoi(temp.c_str());

    getline(file, race);

    getline(file, temp);
    Frame::setStats(favoredClass, temp);

    getline(file, class1);
    getline(file, classSkill);

    getline(file, temp);
    Frame::setStats(proficiency, temp);

    getline(file, temp);
    rank1 = atoi(temp.c_str());

    getline(file, temp);
    Frame::setStats(size1, temp);

    getline(file, temp);
    init = atoi(temp.c_str());

    getline(file, temp);
    Frame::setStats(trait, temp);
    getline(file, temp);
    Frame::setStats(aura, temp);
    getline(file, temp);
    Frame::setStats(ac, temp);
    getline(file, temp);
    Frame::setStats(hp, temp);

    getline(file, temp);
    fsav = atoi(temp.c_str());
    getline(file, temp);
    rsav = atoi(temp.c_str());
    getline(file, temp);
    wsav = atoi(temp.c_str());

    getline(file, temp);
    Frame::setStats(dr, temp);
    getline(file, temp);
    Frame::setStats(er, temp);
    getline(file, temp);
    Frame::setStats(im, temp);

    getline(file, temp);
    sr = atoi(temp.c_str());

    getline(file, temp);
    Frame::setStats(spd, temp);
    getline(file, temp);
    Frame::setStats(weapon, temp);
    getline(file, temp);
    Frame::setStats(ability, temp);
    getline(file, temp);
    Frame::setStats(spell, temp);

    getline(file, temp);
    bab = atoi(temp.c_str());
    getline(file, temp);
    cmb = atoi(temp.c_str());
    getline(file, temp);
    cmd = atoi(temp.c_str());

    getline(file, temp);
    Frame::setStats(feat, temp);
    getline(file, temp);
    Frame::setStats(skill, temp);
    getline(file, temp);
    Frame::setStats(lang, temp);
    getline(file, temp);
    Frame::setStats(sq, temp);
    getline(file, temp);
    Frame::setStats(inv, temp);
    getline(file, temp);
    Frame::setStats(equipped, temp);
    getline(file, temp);
    Frame::setStats(companion, temp);

    getline(file, temp);
    gp = atof(temp.c_str());
    getline(file, temp);
    encumb = atof(temp.c_str());
    getline(file, temp);
    capacity = atof(temp.c_str());

    getline(file, temp);
    Frame::setStats(extra, temp);

    cout << endl;
    file.close();
}

void Player::save()
{
    string temp;
    cout << "save name (remember this for loading): ";
    getline(cin, temp);
    temp += "1.txt";

    ofstream file(temp.c_str());

    file << name << endl;
    file << sex << endl;
    file << age << endl;
    file << height << endl;
    file << weight << endl;
    file << align << endl;
    file << lvl << endl;
    file << xp << endl;
    file << xpcap << endl;
    file << str << endl;
    file << dex << endl;
    file << con << endl;
    file << int1 << endl;
    file << wis << endl;
    file << cha << endl;
    file << race << endl;
    file << saveStat(favoredClass) << endl;
    file << class1 << endl;
    file << classSkill << endl;
    file << saveStat(proficiency) << endl;
    file << rank1 << endl;
    file << saveStat(size1) << endl;
    file << init << endl;
    file << saveStat(trait) << endl;
    file << saveStat(aura) << endl;
    file << saveStat(ac) << endl;
    file << saveStat(hp) << endl;
    file << fsav << endl;
    file << rsav << endl;
    file << wsav << endl;
    file << saveStat(dr) << endl;
    file << saveStat(er) << endl;
    file << saveStat(im) << endl;
    file << sr << endl;
    file << saveStat(spd) << endl;
    file << saveStat(weapon) << endl;
    file << saveStat(ability) << endl;
    file << saveStat(spell) << endl;
    file << bab << endl;
    file << cmb << endl;
    file << cmd << endl;
    file << saveStat(feat) << endl;
    file << saveStat(skill) << endl;
    file << saveStat(lang) << endl;
    file << saveStat(sq) << endl;
    file << saveStat(inv) << endl;
    file << saveStat(equipped) << endl;
    file << saveStat(companion) << endl;
    file << gp << endl;
    file << encumb << endl;
    file << capacity << endl;
    file << saveStat(extra) << endl;

    // add temporary conditions and stuff
    cout << endl;
    file.close();
}

void Player::setRace()
{
    string temp;
    cout << "1. dwarf" << endl
         << "2. elf" << endl
         << "3. gnome" << endl
         << "4. half-elf" << endl
         << "5. half-orc" << endl
         << "6. halfling" << endl
         << "7. human" << endl;
    cout << "choose: ";
    getline(cin, temp);
    cout << endl;

    switch(atoi(temp.c_str()))
    {
    case 1:
        race = "dwarf";
        size1.push_back("medium");
        spd.push_back(20);

        proficiency.insert(proficiency.begin(), "dwarven");
        break;
    case 2:
        race = "elf";
        size1.push_back("medium");
        spd.push_back(30);

        proficiency.insert(proficiency.begin(), "elven");
        break;
    case 3:
        race = "gnome";
        size1.push_back("small");
        spd.push_back(20);

        proficiency.insert(proficiency.begin(), "gnome");
        break;
    case 4:
        race = "half-elf";
        size1.push_back("medium");
        spd.push_back(30);

        cout << "favored class: ";
        getline(cin, temp);
        favoredClass.push_back(temp);
        break;
    case 5:
        race = "half-orc";
        size1.push_back("medium");
        spd.push_back(30);

        proficiency.insert(proficiency.begin(), "orc");
        break;
    case 6:
        race = "halfling";
        size1.push_back("small");
        spd.push_back(20);

        proficiency.insert(proficiency.begin(), "halfling");
        fsav++;
        rsav++;
        wsav++;
        break;
    case 7:
        race = "human";
        size1.push_back("medium");
        spd.push_back(30);

        rank1++;
        break;
    }

    for (int i = 0; i < 5; i++)
    {
        spd.push_back(0);
    }
    if (size1[0] == "small")
    {
        capacity = capacity*3/4;
        ac[0]++;
        bab++;
        cmb--;
        cmd--;
    }
}

void Player::setClass(int i) // this function sets at i=0, otherwise it finds the differences in stats between levels for advancement
{
    // barbarian, bard, cleric, druid, fighter, monk, paladin, ranger, sorcerer
    // alchemist, cavalier, inquisitor, oracle, summoner, witch
    // arcanist, bloodrager, brawler, hunter, investigator, shaman, skald, slayer, swashbuckler, warpriest,
    // gunslinger, magus, ninja, samurai
    // battle herald, holy vindicator, horizon walker, master chymist, master spy, nature warden, rage prophet, stalwart defender
    // arcane archer, arcane trickster, assassin, dragon disciple, duelist, eldritch knight, loremaster, master theurge, pathfinder chronicle, shadowdancer
    if (class1 == "rogue")
    {
        if (i == 0)
        {
            classSkill = ",1,2,3,4,5,6,7,8,9,13,15,19,24,25,26,27,29,30,32,34,35,";
            hp.push_back(8);
            rank1 = 8;
            proficiency.push_back("light armor");
            proficiency.push_back("simple weapons");
            proficiency.push_back("hand crossbow");
            proficiency.push_back("rapier");
            proficiency.push_back("sap");
            proficiency.push_back("shortbow");
            proficiency.push_back("shortsword");


            int j = lvl;
            bab = j - ((j+3 - (j+3)%4)/4);
            fsav = (j - j%3)/3;
            rsav = 2 + (j - j%2)/2;
            wsav = (j - j%3)/3;
        }
        else
        {
            int j = lvl;
            bab += j - ((j+3 - (j+3)%4)/4);
            fsav += (j - j%3)/3;
            rsav += 2 + (j - j%2)/2;
            wsav += (j - j%3)/3;

            j = lvl-1;
            bab -= j - ((j+3 - (j+3)%4)/4);
            fsav -= (j - j%3)/3;
            rsav -= 2 + (j - j%2)/2;
            wsav -= (j - j%3)/3;

            // add bonuses for classes?????????????????????
        }
    }
    else if (class1 == "wizard")
    {
        if (i == 0)
        {
            classSkill = ",2,5,10,14,15,16,17,18,19,20,21,22,23,24,27,31,";
            hp.push_back(6);
            rank1 = 2;
            proficiency.push_back("club");
            proficiency.push_back("dagger");
            proficiency.push_back("light crossbow");
            proficiency.push_back("heavy crossbow");
            proficiency.push_back("quarterstaff");

            int j = lvl;
            bab = (j - j%2)/2;
            fsav = (j - j%3)/3;
            rsav = (j - j%3)/3;
            wsav = 2 + (j - j%2)/2;
        }
        else
        {
            int j = lvl;
            bab += (j - j%2)/2;
            fsav += (j - j%3)/3;
            rsav += (j - j%3)/3;
            wsav += 2 + (j - j%2)/2;

            j = lvl-1;
            bab -= (j - j%2)/2;
            fsav -= (j - j%3)/3;
            rsav -= (j - j%3)/3;
            wsav -= 2 + (j - j%2)/2;
        }
    }
    else
    {
        cout << "error" << endl;
    }
}

// develop
void Player::gainlvl()
{
    lvl++;
    setClass();
    hp[0] = lvl;
    string temp;

    if (!(lvl%4))
    {
        for (int i = 0; i < 2; i++)
        {
            cout << "add stat" << endl
                 << "1. str" << endl
                 << "2. dex" << endl
                 << "3. con" << endl
                 << "4. int" << endl
                 << "5. wis" << endl
                 << "6. cha" << endl;
            cout << "choice (no doubling up): ";
            getline(cin, temp);
            cout << endl;

            switch(atoi(temp.c_str()))
            {
            case 1: // add?????????????????????????????????
                str++;
                break;
            case 2:
                dex++;
                break;
            case 3:
                con++;
                break;
            case 4:
                int1++;
                break;
            case 5:
                wis++;
                break;
            case 6:
                cha++;
                break;
            }
        }
    }

    int rgain = rank1 + statMod(int1);
    int hpgain = Frame::rollDie(hp[1]) + statMod(con);

    if (class1 == favoredClass[0] || (race == "half-elf" && class1 == favoredClass[1]))
    {
        cout << "1. extra skill" << endl
             << "2. extra hp (lul)" << endl;
        cout << "choice: ";
        getline(cin, temp);
        cout << endl;

        switch(atoi(temp.c_str()))
        {
        case 1:
            rgain++;
            break;
        case 2:
            hpgain++;
            break;
        }
    }

    hp[3] += hpgain;
    gainSkill(rgain);

    if (lvl%2)
    {
        cout << "new feat: ";
        getline(cin, temp);
        feat.push_back(temp);
        Character::addDesc("feats.txt", temp); // function??????????????
    }

    setxpcap();
}

void Player::gainSkill(int r)
{
    string temp;
    int choice;
    for(int i = 0; i < skill.size(); i++)
    {
        cout << i+1 << ". " << skillName[i] << endl;
    }
    for (int i = 0; i < r; i++)
    {
        cout << "choice (no repeats): ";
        getline(cin, temp);
        choice = atoi(temp.c_str());
        int j = 1;
        string s = string(",") + temp + string(",");
        if (skill[choice-1] == 0 && classSkill.find(s) != -1)
        {
            j += 3;
        }
        skill[choice-1] += j;
    }

    cout << endl;
}

void Player::gainProficiency(string str)
{
    proficiency.push_back(str);
}

void Player::gainxp(int i)
{
    xp += i;
    if (xp >= xpcap)
    {
        gainlvl();
    }
}

void Player::gaingp(double i)
{
    gp += i;
}

//display
void Player::display()
{
    cout << name << endl;
    cout << "sex: " << sex << endl;
    cout << "age: " << age << endl;
    cout << "height: " << height/12 << "\'" << height%12 << "\"" << endl;
    cout << "weight: " << weight << endl;
    cout << "align: " << align << endl;
    cout << "lvl: " << lvl << endl;
    cout << "xp: " << xp << "/" << xpcap << endl;
    cout << "race: " << race << endl;
    Frame::displayStat(lang, "language");

    Frame::displayStat(favoredClass, "favored class");
    cout << "class: " << class1 << endl;
    cout << "rank: " << rank1 << endl;

    Frame::displayStat(size1, "size");

    cout << "init: " << init << endl;

    cout << "str: " << str << "     ";
    cout << "dex: " << dex << "     ";
    cout << "con: " << con << endl;
    cout << "int: " << int1 << "     ";
    cout << "wis: " << wis << "     ";
    cout << "cha: " << cha << endl;

    cout << "bab: " << bab << "     ";
    cout << "cmb: " << cmb << "     ";
    cout << "cmd: " << cmd << endl;

    Frame::displayStat(trait, "trait", 1);
    Frame::displayStat(aura, "aura", 1);

    Frame::displayStat(ac, "ac");
    cout << "hp: " << hp[3] << ", d" << hp[1] << endl;;
    cout << "fsav: " << fsav << endl;
    cout << "rsav: " << rsav << endl;
    cout << "wsav: " << wsav << endl;

    Frame::displayStat(dr, "dr");
    Frame::displayStat(er, "er");
    Frame::displayStat(im, "im");
    Frame::condOut(sr, "sr");

    Frame::displayStat(spd, "speed");
    Frame::displayStat(weapon, "weapon", 2);
    Frame::displayStat(ability, "ability", 1);
    Frame::displayStat(spell, "spell", 1);

    Frame::displayStat(feat, "feat");
    Character::displaySkill();

    cout << "gp: " << gp << endl;
    cout << "encumbrance: " << encumb << endl;
    cout << "capacity: " << capacity << endl;
    Frame::displayStat(inv, "inventory");
    Frame::displayStat(equipped, "equipped");
    Frame::displayStat(proficiency, "proficiency");
    Frame::displayStat(companion, "companion");
    Frame::displayStat(sq, "sq");
    Frame::displayStat(extra, "extra");
    cout << endl;
}

void Player::setxpcap()
{
    double dlvl = lvl;
    int xpcaptemp = round((2000*(pow(2,floor((dlvl+1)/2))-1)+3000*(pow(2,floor(dlvl/2))-1))/pow(10,(floor(sqrt(dlvl))+1))*2)/2*pow(10,(floor(sqrt(dlvl))+1));
    xpcap = xpcaptemp + xpcaptemp % 2;
}

// general
void Player::inputStat(vector<string> &vec, string str, string fname)
{
    while(true)
    {
        string temp;
        cout << "enter new " << str << " or 0 to finish: ";
        getline(cin, temp);
        if (temp == "0")
        {
            break;
        }
        if (fname != "")
        {
            addDesc(fname, temp);
        }
        vec.push_back(temp);
    }
}

string Player::saveStat(vector<string> vec)
{
    string temp = "";
    if (vec.size() > 0)
    {
        temp = vec[0];
    }
    for (int i = 1; i < vec.size(); i++)
    {
        temp += ";";
        temp += vec[i];
    }
    return temp;
}

string Player::saveStat(vector<int> vec)
{
    stringstream sstemp;
    if (vec.size() > 0)
    {
        sstemp << vec[0];
    }
    for (int i = 1; i < vec.size(); i++)
    {
        sstemp << ";";
        sstemp << vec[i];
    }
    string temp = "";
    sstemp >> temp;
    return temp;
}

