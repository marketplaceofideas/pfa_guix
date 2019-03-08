#include "player.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "frame.h"
using namespace std;

Player::Player(string temp) : Character(temp)
{

}	

void Player::save(string filename)
{
    string temp = filename;

    ofstream file(temp.c_str());

	vector<string> vec;



    // add temporary conditions and stuff
    file.close();
}

void Player::setRace()
{
    string temp;
	/*
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
	*/

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

        //cout << "favored class: ";
        //getline(cin, temp);
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
        /*fsav++;
        rsav++;
        wsav++;*/
        break;
    case 7:
        race = "human";
        size1.push_back("medium");
        spd.push_back(30);

        rank++;
        break;
    }

    for (int i = 0; i < 5; i++)
    {
        spd.push_back(0);
    }
    if (size1[0] == "small")
    {
        encumb[1] = encumb[1] * 3/4;
        ac[0]++;
        bab[0]++;
        cmb[0]--;
        cmd[0]--;
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

	string classSkill; // temporary
    if (class1 == "rogue")
    {
        if (i == 0)
        {
            classSkill = ",1,2,3,4,5,6,7,8,9,13,15,19,24,25,26,27,29,30,32,34,35,";
            hp.push_back(8);
            rank = 8;
            proficiency.push_back("light armor");
            proficiency.push_back("simple weapons");
            proficiency.push_back("hand crossbow");
            proficiency.push_back("rapier");
            proficiency.push_back("sap");
            proficiency.push_back("shortbow");
            proficiency.push_back("shortsword");


            int j = lvl;
            /*bab = j - ((j+3 - (j+3)%4)/4);
            fsav = (j - j%3)/3;
            rsav = 2 + (j - j%2)/2;
            wsav = (j - j%3)/3;*/
        }
        else
        {
            int j = lvl;
            /*bab += j - ((j+3 - (j+3)%4)/4);
            fsav += (j - j%3)/3;
            rsav += 2 + (j - j%2)/2;
            wsav += (j - j%3)/3;

            j = lvl-1;
            bab -= j - ((j+3 - (j+3)%4)/4);
            fsav -= (j - j%3)/3;
            rsav -= 2 + (j - j%2)/2;
            wsav -= (j - j%3)/3;*/

            // add bonuses for classes?????????????????????
        }
    }
    else if (class1 == "wizard")
    {
        if (i == 0)
        {
            classSkill = ",2,5,10,14,15,16,17,18,19,20,21,22,23,24,27,31,";
            hp.push_back(6);
            rank = 2;
            proficiency.push_back("club");
            proficiency.push_back("dagger");
            proficiency.push_back("light crossbow");
            proficiency.push_back("heavy crossbow");
            proficiency.push_back("quarterstaff");

            int j = lvl;
            /*bab = (j - j%2)/2;
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
            wsav -= 2 + (j - j%2)/2;*/
        }
    }
    else
    {
        //cout << "error" << endl;
    }
}

// develop
void Player::gainlvl()
{
    lvl++;
    setClass();
    hp[0] = lvl;
    string temp;

	/*

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

	*/
}

void Player::gainSkill(int r)
{
    //string temp;
    //int choice;
    //for(int i = 0; i < skill.size(); i++)
    //{
    //    //cout << i+1 << ". " << skillName[i] << endl;
    //}
    //for (int i = 0; i < r; i++)
    //{
    //    //cout << "choice (no repeats): ";
    //    //getline(cin, temp);
    //    choice = atoi(temp.c_str());
    //    int j = 1;
    //    string s = string(",") + temp + string(",");
    //    if (skill[choice-1][0] == 0 && classSkill.find(s) != -1)
    //    {
    //        j += 3;
    //    }
    //    skill[choice-1][0] += j;
    //}

    ////cout << endl;
}

void Player::gainProficiency(string str)
{
    proficiency.push_back(str);
}

void Player::gainxp(int i)
{
    xp[0] += i;
    if (xp[0] >= xp[1])
    {
        gainlvl();
    }
}

void Player::gaingp(double i)
{
    gp += i;
}

// display

void Player::setxpcap()
{
    double dlvl = lvl;
    int xpcaptemp = round((2000*(pow(2,floor((dlvl+1)/2))-1)+3000*(pow(2,floor(dlvl/2))-1))/pow(10,(floor(sqrt(dlvl))+1))*2)/2*pow(10,(floor(sqrt(dlvl))+1));
    xp[1] = xpcaptemp + xpcaptemp % 2;
}

// general
void Player::inputStat(vector<string> &vec, string str, string fname)
{
    while(true)
    {
        string temp;
        //cout << "enter new " << str << " or 0 to finish: ";
        //getline(cin, temp);
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

