#ifndef WEAPON_H
#define WEAPON_H
#include "item.h"

#include <string>
#include <vector>
using namespace std;

class Weapon : public Item //////////////// friend function for certain spells
{
private:
    string difficulty;
    vector<int> dmg;
    vector<int> crit;
    int range;
    vector<string> dmgtype;
    vector<string> special;
    // magic
public:
    Weapon(string temp = "");
    static void addIndex();

    friend class Frame;
};

#endif // WEAPON_H
