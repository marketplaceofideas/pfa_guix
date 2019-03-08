#include "weapon.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "frame.h"
using namespace std;

Weapon::Weapon(string temp) : Item(temp, "weapons.txt")
{
	QVector<QString> vec = Frame::findVec(temp, "weapons.txt");

	Frame::setStat(difficulty, vec[6]);
	Frame::setStat(dmg, vec[7]);
	Frame::setStat(crit, vec[8]);
	Frame::setStat(range, vec[9]);
	Frame::setStat(dmgtype, vec[10]);
	Frame::setStat(special, vec[11]);
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
