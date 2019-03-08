#ifndef ITEM_H
#define ITEM_H

#include "frame.h"

class Item
{
public:
	// hp
    string name;
    string type; // weapon: light, 1-h, 2-h; armor: light, med, tower; item: gear, tool, transport
    double cost;
    double weight;

	vector<string> magic; // various
	string desc; // unique affects

    Item(string temp, string fname = "items.txt");
    static void addIndex();

    friend class Frame;
};

#endif // ITEM_H
