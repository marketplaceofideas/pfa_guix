#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "item.h"

using namespace std;

class Equipment : public Item
{
private:
    int armor;
    // lots of bonus limits/etc for later
    // magic
public:
    static void addIndex();

    friend class Frame;
};

#endif // EQUIPMENT_H
