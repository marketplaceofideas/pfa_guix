#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>
using namespace std;

class Item
{
protected:
    // magic ??????????????????
    string name;
    string type;
    double cost;
    double weight;
    string desc;

public:
    Item(int);
    Item(string temp = "");

    static void addIndex();


    friend class Frame;
};

#endif // ITEM_H
