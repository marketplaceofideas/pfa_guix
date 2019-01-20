#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"

using namespace std;

class Player : public Character
{
public:
    char sex;
    int age;
    int height;
    int weight;
    int lvl;
    int xpcap;
    vector<string> favoredClass;
    string classSkill;
    int rank1;
    vector<string> equipped;
    vector<string> proficiency;
    vector<string> companion;

    double gp;
    double encumb;
    double capacity;

//public:
    //void giveWeapon();

	Player(string filename, string mode);

    // initialize
    void save(string filename);
    void setxpcap();
    void setRace();
    void setClass(int i = 1);

    //develop
    void gainlvl();
    void gainSkill(int r = 1);
    void gainProficiency(string);
    void gainxp(int);
    void gaingp(double);

    //display
    void display();
    void inputStat(vector<string>&, string, string fname = "");
    string saveStat(vector<string>);
    string saveStat(vector<int>);
};

#endif // PLAYER_H
