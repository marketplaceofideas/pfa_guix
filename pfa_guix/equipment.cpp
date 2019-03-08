#include "equipment.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "frame.h"
using namespace std;

Equipment::Equipment(string temp) : Item(temp, "equipment.txt")
{
	QVector<QString> vec = Frame::findVec(temp, "weapons.txt");

	Frame::setStat(slot, vec[6]);
	Frame::setStat(armor, vec[7]);
}

void Equipment::addIndex()
{
    
}
