#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "item.h"

class Equipment : public Item
{
public:
	vector<string> slot; // head, belt, etc.
	vector<int> armor;

	Equipment(string);
    static void addIndex();

    friend class Frame;
};

#endif // EQUIPMENT_H
