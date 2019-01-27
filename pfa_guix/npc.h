#ifndef NPC_H
#define NPC_H
#include "character.h"

using namespace std;

class Npc : public Character
{
private:
    float cr;
    vector<string> type; // type, terrain, climate
    vector<string> subtype;

    string environment;
    vector<string> organization;
    vector<string> treasure;

    vector<string> sability;
    string desc;
public:
    Npc(string str = "");
    static void addIndex();
};

#endif // NPC_H
