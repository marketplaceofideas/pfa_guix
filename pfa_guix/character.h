#ifndef CHARACTER_H
#define CHARACTER_H

#include <QtWidgets>
#include <vector>
#include "frame.h"
#include "item.h"
#include "weapon.h"
#include "equipment.h"

enum skillnums {acro, appr, bluf, clim, craf, dipl, disa, disg, esca, fly, hand, heal, inti, karc, kdun, keng, kgeo, khis,
           kloc, knat, knob, kpla, krel, ling, perc, perf, prof, ride, sens, slei, spel, stea, surv, swim, usem};

class Character : public QObject
{
	Q_OBJECT
public:
    //static string skillName[35];

	void skillSetup(vector<vector<int>> &vec, QString &temp)
	{
		QStringList list = temp.split(";");
		vec.resize(list.size());
		for (int i = 0; i < list.length(); ++i)
		{
			QStringList listlist = list[i].split(",");
			vec[i].resize(listlist.size());
			for (int j = 0; j < listlist.size(); ++j)
			{
				if (listlist[j] == 0)
					vec[i][j] = 0;
				else
					vec[i][j] = listlist[j].toInt();
			}
		}
	}

	// if unspecified and not dynamic: total, core, temp

	// typing
	double cr;
	vector<string> type;		// type, terrain, climate
	vector<string> subtype;
	string environment;
	vector<string> organization;
	int legs;

	// personal
    string name;
	string id;
	char sex;
	int age;
	int height;
	int weight;
	string race;
	string class1;
	string align;
	string deity;

	vector<string> size1;
	vector<int> space;
	vector<int> reach;

	int lvl;
	vector<int> xp;				// current, max, rewarded

	// core
	vector<string> deflect;
    vector<int> ac;				// total, armor, dex
    vector<int> hp;				// hp, mult, hitdie, bonus;		racial bonus: x_d_x
	vector<int> spd;			// land, armor, burrow, climb, fly, swim

	vector<int> init;

	vector<int> str;
	vector<int> dex;
	vector<int> con;
	vector<int> int1;
	vector<int> wis;
	vector<int> cha;

	vector<int> bab;
	vector<int> cmb;
	vector<int> cmd;

	vector<int> fsav;
	vector<int> rsav;
	vector<int> wsav;
	vector<string> saveMod;

	// extra
	// 35 skills, special types (craft), ->
	vector<vector<vector<int>>> skill; // total, rank, class, race, misc
	int rank;

	vector<string> condition;
	vector<string> status;		// prone, sneaking, etc
	vector<string> feat;
	vector<string> sability;	// ex, sp, su : _ex_:_sense_:name
    vector<string> spell;		// name:_ability_

	vector<string> proficiency;
	vector<string> trait;
	vector<string> aura;

	// resistances
	vector<string> dr;			// hardness?
	vector<string> er;
	vector<string> im;
	vector<int> sr;

    vector<string> lang;
	vector<string> favoredClass;
	vector<vector<string>> classInfo; // cleric domains, etc
    vector<string> extra;

	string desc;

	double gp;
	vector<double> encumb;

	vector<Item> inv;
    vector<Weapon> eqpW;		// right, left
	vector<Equipment> eqpE;		// armor, belt, body, chest, eyes, feet, hands, head, headband, neck, rring, lring, shield, shoulders, wrist
	vector<Item> eqpI;

	///////////////////////////////

	Character(string temp, string fname = "");
	
	void addItem(string);
	QVector<QString> makeVec();

	friend bool operator<(const Character &left, const Character &right);

    int statMod(int);

    //descriptions
    static void checkDesc(string, string); // remove?
    static void addDesc(string, string);
    static void showDesc(string);

    //skills
    int rollSkill(int choice = -1);
    string useSkill(int sskill, int tskill, string pack);



    friend class Frame;

	// signal handling for display windows
	template<typename T>
	void setter(vector<T> vec, int i, T val)
	{ vec[i] = val, refresh(); }

	template<typename T>
	void setter(T var, T val)
	{ var = val, refresh(); }

signals:
	void refresh();
};

#endif
