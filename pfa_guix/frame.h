#ifndef FRAME_H
#define FRAME_H

#include <string>
#include <vector>
using namespace std;

//#include "character.h"
//#include "weapon.h"
class Character;
class Npc;
class Player;
class Item;
class Weapon;
//class Equipment;

class Frame
{
private:

public:
//    void encounter(string temp = "")

    static vector<string> names;

    //playing
    static int rollDie(int die, int num = 1, int mod = 0);
    static void action(Player&, vector<Npc>&); ///////////////////////////////////fix
    static void hit(Player&, Npc&, Weapon&);

    //searching, sorting
    static void setNames(string, int line = 0);
    static int searchID(string, string name = "");
    static void sortBy(string fname, int line);
    //template <typename T>
    static void declareAll(string, vector<Item>&);
    static string alnumOnly(string);
    static int setIndexLength(string);

    //indexes
    static void clearFile(string);
    static int checkFile(string, vector<string>&, string);
    static int findEntry(string, string);
    static void removeIndex(string);

    //stats
    static string getStats(string, int&, vector<string>&);
    static void setStats(vector<string>&, string);
    static void setStats(vector<int>&, string);
//    template <typename T>
//    void Frame::condOut(T i, string name)
//    static void displayStat(vector<int> vec, string str = "", int desc = 0);
};

#endif // FRAME_H
