#ifndef NPC_H
#define NPC_H

#include "character.h"

class Npc : public Character
{
private:

public:
    Npc(string name);
    static void addIndex();
};

#endif // NPC_H
