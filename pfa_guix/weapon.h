#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

class Weapon : public Item //////////////// friend function for certain spells
{
public:
	string difficulty;
	vector<int> dmg; // x;dx;+x
	vector<int> crit; // dx;*x
    int range;
	vector<string> dmgtype; // B, P, S
	vector<string> special; // acid, etc.
	// material

    Weapon(string);
    static void addIndex();

    friend class Frame;
};

#endif // WEAPON_H
