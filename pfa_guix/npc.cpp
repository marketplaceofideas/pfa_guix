#include "npc.h"
#include <cstdlib> // atoi
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "frame.h"
using namespace std;

Npc::Npc(string temp) : Character()
{
    int id;
    id = Frame::searchID("bestiary.txt", temp);

    fstream indexfile("bestiary.txt");
    string trash;

    for (int i = 0; i < id * Frame::setIndexLength("bestiary.txt"); i++)
    {
        getline(indexfile, trash); // ignore to newline????????????????
    }

    getline(indexfile, name);

    getline(indexfile, temp);
    cr = atof(temp.c_str());

    getline(indexfile, temp);
    Frame::setStats(type, temp);

    getline(indexfile, temp);
    xp = atoi(temp.c_str());
    getline(indexfile, race);
    getline(indexfile, class1);
    getline(indexfile, align);

    getline(indexfile, temp);
    Frame::setStats(size1, temp);

    getline(indexfile, temp);
    Frame::setStats(subtype, temp);

    getline(indexfile, temp);
    init = atoi(temp.c_str());

    getline(indexfile, temp);
    Frame::setStats(trait, temp);

    getline(indexfile, temp);
    Frame::setStats(aura, temp);

    getline(indexfile, temp);
    Frame::setStats(ac, temp);

    getline(indexfile, temp);
    Frame::setStats(hp, temp);
    hp.push_back(Frame::rollDie(hp[1], hp[0], hp[2]));

    getline(indexfile, temp);
    fsav = atoi(temp.c_str());
    getline(indexfile, temp);
    rsav = atoi(temp.c_str());
    getline(indexfile, temp);
    wsav = atoi(temp.c_str());

    getline(indexfile, temp);
    Frame::setStats(dr, temp);

    getline(indexfile, temp);
    Frame::setStats(er, temp);

    getline(indexfile, temp);
    Frame::setStats(im, temp);

    getline(indexfile, temp);
    sr = atoi(temp.c_str());

    getline(indexfile, temp);
    Frame::setStats(spd, temp);

    getline(indexfile, temp);
    Frame::setStats(weapon, temp);

    getline(indexfile, temp);
    Frame::setStats(ability, temp);

    getline(indexfile, temp);
    Frame::setStats(spell, temp);

    getline(indexfile, temp);
    str = atoi(temp.c_str());
    getline(indexfile, temp);
    dex = atoi(temp.c_str());
    getline(indexfile, temp);
    con = atoi(temp.c_str());
    getline(indexfile, temp);
    int1 = atoi(temp.c_str());
    getline(indexfile, temp);
    wis = atoi(temp.c_str());
    getline(indexfile, temp);
    cha = atoi(temp.c_str());

    getline(indexfile, temp);
    bab = atoi(temp.c_str());

    getline(indexfile, temp);
    cmb = atoi(temp.c_str());

    getline(indexfile, temp);
    cmd = atoi(temp.c_str());

    getline(indexfile, temp);
    Frame::setStats(feat, temp);

    getline(indexfile, temp);
    Frame::setStats(skill[0], temp);

    getline(indexfile, temp);
    Frame::setStats(lang, temp);

    getline(indexfile, temp);
    Frame::setStats(sq, temp);

    getline(indexfile, environment);

    getline(indexfile, temp);
    Frame::setStats(organization, temp);

    getline(indexfile, temp);
    Frame::setStats(treasure, temp);

    getline(indexfile, temp);
    Frame::setStats(sability, temp);

    getline(indexfile, desc);
    getline(indexfile, temp);
    Frame::setStats(extra, temp);
}

void Npc::addIndex()
{
    string temp;
    cout << "name: ";
    getline(cin, temp);

    vector<string> fvec;
    int x = Frame::checkFile("bestiary.txt", fvec, temp);
    if (x == -1)
    {
        cout << "repeat" << endl;
        return;
    }
    ofstream indexfile("bestiary.txt");

    fvec.insert(fvec.begin() + x, temp); // name
    x++;

    Frame::getStats("cr", x, fvec);

    string temptype[3];
    cout << "type" << endl;
    cout << "1. abberation" << endl
         << "2. animal" << endl
         << "3. construct" << endl
         << "4. dragon" << endl
         << "5. fey" << endl
         << "6. humanoid" << endl
         << "7. magical beast" << endl
         << "8. monstrous humanoid" << endl
         << "9. ooze" << endl
         << "10. outsider" << endl
         << "11. plant" << endl
         << "12. undead" << endl
         << "13. vermin" << endl;
    cout << "choose: ";
    getline(cin, temp);
    cout << endl;

    switch(atoi(temp.c_str()))
    {
    case 1:
        temptype[0] = "abberation";
        break;
    case 2:
        temptype[0] = "animal";
        break;
    case 3:
        temptype[0] = "construct";
        break;
    case 4:
        temptype[0] = "dragon";
        break;
    case 5:
        temptype[0] = "fey";
        break;
    case 6:
        temptype[0] = "humanoid";
        break;
    case 7:
        temptype[0] = "magical beast";
        break;
    case 8:
        temptype[0] = "monstrous humanoid";
        break;
    case 9:
        temptype[0] = "ooze";
        break;
    case 10:
        temptype[0] = "outsider";
        break;
    case 11:
        temptype[0] = "plant";
        break;
    case 12:
        temptype[0] = "undead";
        break;
    case 13:
        temptype[0] = "vermin";
        break;
    }
    cout << "1. desert" << endl
         << "2. forest/jungle" << endl
         << "3. hill" << endl
         << "4. mountain" << endl
         << "5. plain" << endl
         << "6. ruins/dungeon" << endl
         << "7. sky" << endl
         << "8. swamp" << endl
         << "9. underground" << endl
         << "10. urban" << endl
         << "11. water" << endl;
    cout << "choose: ";
    getline(cin, temp);
    cout << endl;

    switch(atoi(temp.c_str()))
    {
    case 1:
        temptype[1] = "desert";
        break;
    case 2:
        temptype[1] = "forest/jungle";
        break;
    case 3:
        temptype[1] = "hill";
        break;
    case 4:
        temptype[1] = "mountain";
        break;
    case 5:
        temptype[1] = "plain";
        break;
    case 6:
        temptype[1] = "ruins/dungeon";
        break;
    case 7:
        temptype[1] = "sky";
        break;
    case 8:
        temptype[1] = "swamp";
        break;
    case 9:
        temptype[1] = "underground";
        break;
    case 10:
        temptype[1] = "urban";
        break;
    case 11:
        temptype[1] = "water";
        break;
    }
    cout << "1. cold" << endl
         << "2. extraplanar" << endl
         << "3. temperate" << endl
         << "4. tropical" << endl;
    cout << "choose: ";
    getline(cin, temp); //                     adjust to fvec
    cout << endl;

    switch(atoi(temp.c_str()))
    {
    case 1:
        temptype[2] = "cold";
        break;
    case 2:
        temptype[2] = "extraplanar";
        break;
    case 3:
        temptype[2] = "temperate";
        break;
    case 4:
        temptype[2] = "tropical";
        break;
    }
    temp = temptype[0] + ";" + temptype[1] + ";" + temptype[2];
    fvec.insert(fvec.begin() + x, temp);
    x++;

    Frame::getStats("xp", x, fvec);
    Frame::getStats("race", x, fvec);
    Frame::getStats("class", x, fvec);

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
    cout << endl;

    switch(atoi(temp.c_str()))
    {
    case 1:
        temp = "ce";
        break;
    case 2:
        temp = "cn";
        break;
    case 3:
        temp = "cg";
        break;
    case 4:
        temp = "ne";
        break;
    case 5:
        temp = "nn";
        break;
    case 6:
        temp = "ng";
        break;
    case 7:
        temp = "le";
        break;
    case 8:
        temp = "ln";
        break;
    case 9:
        temp = "lg";
        break;
    }
    fvec.insert(fvec.begin() + x, temp);
    x++;

    cout << "size" << endl;
    cout << "1. fine" << endl
         << "2. diminutive" << endl
         << "3. tiny" << endl
         << "4. small" << endl
         << "5. medium" << endl
         << "6. large" << endl
         << "7. huge" << endl
         << "8. gargantuan" << endl
         << "9. colossal" << endl;
    cout << "choose: ";
    getline(cin, temp);
    cout << endl;

    switch(atoi(temp.c_str()))
    {
    case 1:
        temp = "fine";
        break;
    case 2:
        temp = "diminutive";
        break;
    case 3:
        temp = "tiny";
        break;
    case 4:
        temp = "small";
        break;
    case 5:
        temp = "medium";
        break;
    case 6:
        temp = "large";
        break;
    case 7:
        temp = "huge";
        break;
    case 8:
        temp = "gargantuan";
        break;
    case 9:
        temp = "colossal";
        break;
    }
    if (temp == "large" || temp == "huge" || temp == "gargantuan" || temp == "colossal")
    {
        string temptemp;
        cout << "long or tall? ";
        getline(cin, temptemp);
        temp += ";" + temptemp;
    }
    fvec.insert(fvec.begin() + x, temp);
    x++;

    Frame::getStats("subtypes", x, fvec);
    Frame::getStats("initiative", x, fvec);
    temp = Frame::getStats("trait names", x, fvec);
    checkDesc("traits.txt", temp);
    temp = Frame::getStats("aura names", x, fvec);
    checkDesc("auras.txt", temp);

    Frame::getStats("ac, touch, ff", x, fvec);
    Frame::getStats("hp (randomized formula, num only)", x, fvec);

    Frame::getStats("fsav", x, fvec);
    Frame::getStats("rsav", x, fvec);
    Frame::getStats("wsav", x, fvec);
    // add exceptions as functions..?

    Frame::getStats("damage reduction (#;n1,n2)", x, fvec);
    Frame::getStats("energy resistances (#,n;#,n)", x, fvec);
    Frame::getStats("immunities", x, fvec);
    Frame::getStats("spell resistance", x, fvec);

    Frame::getStats("speed (normal, armor, burrow, climb, fly, swim)", x, fvec);

    Frame::getStats("weapons", x, fvec); // ?????????????????????????????

    temp = Frame::getStats("abilities (#,n)(def,spec.at,s.like)", x, fvec);
    checkDesc("abilities.txt", temp);

    temp = Frame::getStats("spells (#,n)", x, fvec); //??????????????????????????
    checkDesc("spells.txt", temp);
    Frame::getStats("str", x, fvec);
    Frame::getStats("dex", x, fvec);
    Frame::getStats("con", x, fvec);
    Frame::getStats("int", x, fvec);
    Frame::getStats("wis", x, fvec);
    Frame::getStats("cha", x, fvec);

    Frame::getStats("bab", x, fvec);
    Frame::getStats("cmb", x, fvec);
    Frame::getStats("cmd", x, fvec); // add exception as extra
    temp = Frame::getStats("feats", x, fvec);
    checkDesc("feats.txt", temp);

    int choice = -1;
	string temparr[35] = {"0"};
    for(int i = 0; i < 35; i++)
    {
        cout << i+1 << ". " << skillName[i] << endl;
    }
    while (choice != 0)
    {
        if (choice > 0)
        {
            cout << "value: ";
            getline(cin, temp);
            temparr[choice-1] = temp;
        }
        cout << "Enter choice or 0 when done: ";
        getline(cin, temp);
        choice = atoi(temp.c_str());
    }
    temp = temparr[0];
    for (int i = 1; i < 35; i++)
    {
        temp += ";" + temparr[i];
    }
    fvec.insert(fvec.begin() + x, temp);
    x++;

    Frame::getStats("languages", x, fvec);
    temp = Frame::getStats("special qualities", x, fvec);
    checkDesc("special_qualities.txt", temp);
    Frame::getStats("environment", x, fvec);
    Frame::getStats("organization", x, fvec);
    Frame::getStats("treasure", x, fvec);
    temp = Frame::getStats("spec ability names", x, fvec);
    checkDesc("special_abilities.txt", temp);
    Frame::getStats("description", x, fvec);

    cout << "extra (output): ";
    getline(cin, temp);
    fvec.insert(fvec.begin() + x, temp);
    x++;

    for (int j = 0; j < fvec.size(); j++)
    {
        indexfile << fvec[j] << endl;
    }

    indexfile.close();
}
