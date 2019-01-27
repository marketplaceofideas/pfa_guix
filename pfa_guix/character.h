#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include "item.h"
#include "weapon.h"
#include "equipment.h"
using namespace std;

enum skillnums {acro, appr, bluf, clim, craf, dipl, disa, disg, esca, fly, hand, heal, inti, karc, kdun, keng, kgeo, khis,
           kloc, knat, knob, kpla, krel, ling, perc, perf, prof, ride, sens, slei, spel, stea, surv, swim, usem};

class Character
{
public:
    static string skillName[35];

    // variables

    string name;
    int xp; // all vectors?????????????????
    string race;
    string class1;
    string align;
    vector<string> size1; // change to string?
    int init;
    vector<string> trait;
    vector<string> aura;

    vector<int> ac; // total, armor, dex
    vector<int> hp; // lvl, hit dice, bonus..? FIX

    int fsav;
    int rsav;
    int wsav;

    // resistances
    vector<string> dr;
    vector<string> er;
    vector<string> im;
    int sr;

    vector<int> spd;

    vector<string> weapon;
    vector<string> ability;
    vector<string> spell;

    int str;
    int dex;
    int con;
    int int1;
    int wis;
    int cha;

    int bab;
    int cmb;
    int cmd;

    vector<string> feat;
    vector<vector<int>> skill; // total, rank, class, race, misc

    vector<string> lang;
    vector<string> sq;
    vector<string> inv; //////////////////////////////////////// customize
    vector<string> extra;

    vector<Weapon> wvec;

//public:
    static void randShop();
    void addInv();


    Character();
    int statMod(int);

    //descriptions
    static void checkDesc(string, string);
    static void addDesc(string, string);
    static void showDesc(string);

    //skills
    int chooseSkill();
    int rollSkill(int choice = -1);

    string useSkill(int sskill, int tskill, string pack);

    friend class Frame;
};

#endif
