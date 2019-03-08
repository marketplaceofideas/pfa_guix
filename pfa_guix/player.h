#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

class Player : public Character
{
public:
    //string classSkill;
    //vector<string> companion;


//public:
    //void giveWeapon();

	Player(string name);
	//Player(const Player&) = delete;
    void save(string filename);

	// initialize
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
    void inputStat(vector<string>&, string, string fname = "");
    string saveStat(vector<string>);
    string saveStat(vector<int>);
};

#endif // PLAYER_H
