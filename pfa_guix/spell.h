#ifndef SPELL_H
#define SPELL_H

#include "frame.h"

class Spell
{
private:
    int slvl;
	vector<string> range; // distance (calc), type
    string cast; // target, cast time, duration
    string resist; // saving throw, effect, sr
	vector<string> dmg; // touch, amount, type
    string desc;
public:

};

#endif // SPELL_H
