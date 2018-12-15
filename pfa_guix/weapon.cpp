#include "weapon.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "frame.h"
using namespace std;

Weapon::Weapon(string temp) : Item(0)
{
    int id;
    if (temp == "")
    {
        cout << "search: ";
        getline(cin, temp);
        id = Frame::searchID("weapons.txt", temp); // -1 loop
    }
    else
    {
        id = Frame::searchID("weapons.txt", temp);
    }

    fstream indexfile("weapons.txt");
    string trash;

    for (int i = 0; i < id * Frame::setIndexLength("weapons.txt"); i++)
    {
        getline(indexfile, trash); // ignore to newline????????????????
    }

    getline(indexfile, name);
    getline(indexfile, difficulty);
    getline(indexfile, type);

    getline(indexfile, temp);
    cost = atoi(temp.c_str());

    getline(indexfile, temp);
    Frame::setStats(dmg, temp);

    getline(indexfile, temp);
    Frame::setStats(crit, temp);

    getline(indexfile, temp);
    range = atoi(temp.c_str());

    getline(indexfile, temp);
    weight = atoi(temp.c_str());

    getline(indexfile, temp);
    Frame::setStats(dmgtype, temp);

    getline(indexfile, temp);
    Frame::setStats(special, temp);

    getline(indexfile, desc);
}

//void Weapon::checkEntry()
//{
//    Frame::names.clear();
//    Frame::setStats(Frame::names, temp);
//    for (int i = 0; i < Frame::names.size(); i++)
//    {
//        addDesc(fname, Frame::names[i]);
//    }
//}

void Weapon::addIndex()
{
    string temp;
    cout << "name: ";
    getline(cin, temp);

    vector<string> fvec;
    int x = Frame::checkFile("weapons.txt", fvec, temp);
    if (x == -1)
    {
        cout << "repeat" << endl;
        return;
    }
    ofstream indexfile("weapons.txt");

    fvec.insert(fvec.begin() + x, temp); // name
    x++;

    cout << "difficulty" << endl /////////////////////////////////////edit
            << "1. simple" << endl
            << "2. martial" << endl
            << "3. exotic" << endl;
    cout << "choose: ";
    getline(cin, temp);

    switch(atoi(temp.c_str()))
    {
    case 1:
        temp = "simple";
        break;
    case 2:
        temp = "martial";
        break;
    case 3:
        temp = "exotic";
        break;
    }
    fvec.insert(fvec.begin() + x, temp);
    x++;

    cout << "type" << endl /////////////////////////////////////edit
         << "1. unarmed" << endl
         << "2. light" << endl
         << "3. one-handed" << endl
         << "4. two-handed" << endl
         << "5. ranged" << endl;
    cout << "choose: ";
    getline(cin, temp);

    switch(atoi(temp.c_str()))
    {
    case 1:
        temp = "unarmed";
        break;
    case 2:
        temp = "light";
        break;
    case 3:
        temp = "one-handed";
        break;
    case 4:
        temp = "two-handed";
        break;
    case 5:
        temp = "ranged";
        break;
    }
    fvec.insert(fvec.begin() + x, temp);
    x++;

    Frame::getStats("cost", x, fvec);
    Frame::getStats("dmg (num, die)", x, fvec);
    Frame::getStats("crit (low, mult)", x, fvec);
    Frame::getStats("range", x, fvec);
    Frame::getStats("weight", x, fvec);

    Frame::getStats("dmgtype (1,o/a,2)", x, fvec);
    Frame::getStats("special", x, fvec);
    Frame::getStats("description", x, fvec);

    for (int j = 0; j < fvec.size(); j++)
    {
        indexfile << fvec[j] << endl;
    }

    cout << endl;
    indexfile.close();
}

