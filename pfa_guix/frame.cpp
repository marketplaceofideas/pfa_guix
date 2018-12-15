#include "frame.h"
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include "character.h"
#include "npc.h"
#include "player.h"
using namespace std;

vector<string> Frame::names;

void Frame::encounter(string temp) // idk
{
    if (temp == "")
    {
        while (temp != 0)
        {
            // npc vec?
        }
    }
    else
    {
        // find encounter in file, search all names
    }
}

void Frame::combat(Character *chars) // roll inits, cycle through actions
{
    // find who's sneaking, maybe add a character bool
    // find highest perception and throw sneak rolls at them
    // flag out the bad stealths
    // run through preliminary rounds (up to 2: surprise round, removing flatfoot round) (keep a counter for clock anyways)

    // main body: cycle person by person, action by action
    // each char will be in a []
    int roundcount = 1;
    while () // idk, maybe user-requested flag-out
    {
        cout << "Starting round " << roundcount << endl;
        for (int i = 0; i < _; ++i) // each char
        {
            cout << "1. ";
        }
    }
}

// playing

int Frame::rollDie(int die, int num, int mod)
{
    int temp = mod;
    for (int i = 0; i < num; i++)
    {
        temp += rand() % die + 1;
    }

    cout << endl << die << "->" << temp << endl;
    return temp;
}

// add module encapsulating all of this maybe (iterate through initiatives, offer each action on each turn)
void Frame::action(Player &c1, vector<Npc> &e1) // probably split by character type
{
    // track actions ??
    // optional: add function for every action, add leading functions for action types???
    // for each action, determine whether condition nullifies ability

    // options:
    // combat maneuvers
    string temp;
    vector<string> act;
    act.push_back("hit");

    for (int i = 0; i < act.size(); i++)
    {
        cout << i+1 << ". " << act[i] << endl;
    }
    cout << "choice: ";
    getline(cin, temp);
    if (act[atoi(temp.c_str())-1] == "hit")
    {
        for (int i = 0; i < act.size(); i++)
        {
            cout << i+1 << ". " << e1[i].name << endl;
        }
        cout << "choice: ";
        getline(cin, temp);
        int j = atoi(temp.c_str())-1;

        for (int i = 0; i < c1.wvec.size(); i++)
        {
            cout << i+1 << ". " << c1.wvec[i].name << endl;
        }
        cout << "choice: ";
        getline(cin, temp);

        hit(c1, e1[j], c1.wvec[atoi(temp.c_str())-1]);
    }
}

void Frame::hit(Player &c1, Npc &c2, Weapon &w)
{
    int dc = c2.ac[0];
    string temp;
    cout << "ff? ";
    getline(cin, temp);
    if (temp[0] == 'y')
    {
        dc -= c2.ac[1];
    }
    cout << "touch? ";
    getline(cin, temp);
    if (temp[0] == 'y')
    {
        dc -= c2.ac[2];
    }

    int i = rollDie(20);
    if (i == 1)
    {
        cout << "nat fail" << endl;
        return;
    }
    else if (i >= w.crit[0])
    {
        cout << "crit!" << endl;
        //critical using crit[1]
    }

    if (w.type != "ranged")
    {
        // or dex for rogue..?
        i += c1.bab + c1.statMod(c1.str);
    }
    else
    {
        cout << "are you within any enemy's melee range? ";
        getline(cin, temp);
        if (temp[0] == 'y')
        {
            // call aoo
        }
        cout << "is an ally within your target's melee range? ";
        getline(cin, temp);
        if (temp[0] == 'y')
        {
            // -4, take risk to hit ally
        }

        cout << "range: ";
        getline(cin, temp);
        if (atoi(temp.c_str()) > 5 * w.range)
        {
            cout << "Cannot shoot at this range" << endl;
            return;
        }
        int j = atoi(temp.c_str())-1 / w.range;
        i -= 2*j;
        i += c1.bab + c1.statMod(c1.dex);
    }

    if (i >= dc)
    {
        int j = w.dmg[0] * rollDie(w.dmg[1]); //+ w.dmg[2];
        // ask for bonuses maybe
        cout << "dealt " << j << " dmg to " << c2.name << endl; // make fancy
        c2.hp[3] -= j;
        if (c2.hp[3] < 0)
        {
            cout << "killed " << c2.name << endl;
        }
    }
}

// searching, sorting

void Frame::setNames(string fname, int line) // fix up with int
{
    int lines = setIndexLength(fname);

    ifstream namefile(fname.c_str());
    names.clear();

    string temp;
    while (namefile) // copies file to vector
    {
        getline(namefile, temp);
        if (temp == "")
        {
            break;
        }
        names.push_back(temp);
        for (int i = 1; i < lines; i++)
        {
            getline(namefile, temp); // trash
        }
    }
    namefile.close();
}

int Frame::searchID(string fname, string name) // auto choose ???????
{
    setNames(fname);
    bool automatic = 1;

    if (name == "")
    {
        cout << "search: ";
        getline(cin, name);
        automatic = 0;
    }

    vector<int> flag;
    string out = "not found";
    for (int i = 0; i < names.size(); i++) //nsize
    {
        if (names[i].find(name) != string::npos)
        {
            if (flag.empty())
            {
                out.clear();
            }
            ostringstream sstemp;
            sstemp << i; // string stream
            flag.push_back(i);
            out += sstemp.str();
            out += ". ";
            out += names[i];
            out += "\n";
        }
    }

    cout << out;
    if (flag.empty())
    {
        cout << endl;
        return -1;
    }
    else if (automatic == 1 && name == names[flag[0]]) // automatic, finds exact name
    {
        for (int i = i; i < flag.size(); i++)
        {
            if (name == names[flag[i]])
            {
                cout << endl;
                return flag[i];
            }
        }
    }
    else if (flag.size() == 1 && name == names[flag[0]]) // permission
    {
        cout << endl;
        return flag[0];
    }
    else
    {
        string choice;
        cout << "Choose: ";
        getline(cin, choice);
        cout << endl;
        return atoi(choice.c_str());
    } // add cancel
}

void Frame::sortBy(string fname, int line)
{
    setNames(fname); // generalize
    vector<string> lineVec;


}

string Frame::alnumOnly(string str)
{
    string temp;
    for (int i = 0; i < str.size(); i++)
    {
        if (isalnum(str[i]))
        {
            temp += tolower(str[i]);
        }
    }
    return temp;
}

int Frame::setIndexLength(string fname) // called by checkFile, findindexLength, removeEntry, setNames
{
    int lines = 3;

    if (fname == "bestiary.txt")
    {
        lines = 45;
    }
    else if (fname == "items.txt")
    {
        lines = 6;
    }
    else if (fname == "weapons.txt")
    {
        lines = 12;
    }
    else if (fname == "equipment.txt")
    {
        lines = 7;
    }

    return lines;
}

// index manipulation

//void Frame::clearFile(string fname)
//{
//    int id;
//    if (temp == "")
//    {
//        cout << "search: ";
//        getline(cin, temp);
//        id = Frame::searchID(fname, temp, 0); // -1 loop
//    }
//    else
//    {
//        id = Frame::searchID(fname, temp, 1);
//    }
//
//    fstream indexfile(fname.c_str());
//    string trash;
//
//    for (int i = 0; i < id*lines; i++)
//    {
//        getline(indexfile, trash); // ignore to newline????????????????
//    }
//}

int Frame::checkFile(string fname, vector<string> &fvec, string temp) // checks for file, returns entry point
{
    int x = 0;
    int lines = setIndexLength(fname);

    fstream testfile(fname.c_str());

    if (!testfile)
    {
        ofstream file(fname.c_str());
        file.close();
    }
    else
    {
        x = findEntry(fname, temp);
        //cout << testfile;
        while (testfile)
        {
            getline(testfile, temp);
            fvec.push_back(temp);
        }
    }

    testfile.close();
    return x;
}

int Frame::findEntry(string fname, string str) // checks for alphabetical position
{
    int x = 0;
    setNames(fname);
    names.push_back("");
    int lines = setIndexLength(fname);

    str = alnumOnly(str);
    while (x < names.size()) // entry by entry
    {
        string temp = alnumOnly(names[x]);
        for (int j = 0; true; j++) // letter by letter
        {
            if (temp[j] == 0 && str[j] == 0)
            {
                cout << "repeat" << endl;
                return -1;
            }
            else if (temp[j] < str[j] || temp[j] == 0) // alphabetically higher
            {
                break;
            }
            else if (temp[j] > str[j] || str[j] == 0 || temp[0] == 0) // alphabetically lower
            {
                return x * lines;
            }
        }
        x++;
    }
}

void Frame::removeIndex(string fname)
{
    int lines = setIndexLength(fname);
    string temp;
    Frame::setNames(fname);
    for (int i = 0; i < Frame::names.size(); i++)
    {
        cout << i+1 << ". " << Frame::names[i] << endl;
    }
    cout << "choose (or 0 to cancel): ";
    getline(cin, temp);
    cout << endl;
    if (temp == "0")
    {
        return;
    }
    int n = atoi(temp.c_str())-1;

    fstream file(fname.c_str());
    vector<string> fvec;
    while (file)
    {
        getline(file, temp);
        fvec.push_back(temp);
    }
    file.close();

    ofstream ofile(fname.c_str());
    for (int i = 0; i < n*lines; i++)
    {
        ofile << fvec[i] << endl;
    }
    for (int i = n*lines + lines; i < fvec.size(); i++)
    {
        ofile << fvec[i] << endl;
    }

    ofile.close();
}

// individual stats

string Frame::getStats(string str, int &x, vector<string> &vfile)
{
    cout << str << ": ";
    getline(cin, str);
    vfile.insert(vfile.begin() + x, str);
    x++;
    return str;
}

void Frame::setStats(vector<string> &vec, string temp) // sets multiple stats in a ';'-separated string
{
    int i = temp.find(";");
    while (i > -1)
    {
        string temptemp = temp.substr(0,i);
        vec.push_back(temptemp);
        temp = temp.substr(i+1);
        i = temp.find(";");
    }
    if (temp != "")
    {
        vec.push_back(temp);
    }
}

void Frame::setStats(vector<int> &vec, string temp)
{
    int i = temp.find(";");
    while (i > -1)
    {
        string temptemp = temp.substr(0,i);
        vec.push_back(atoi(temptemp.c_str()));
        temp = temp.substr(i+1);
        i = temp.find(";");
    }
    vec.push_back(atoi(temp.c_str()));
}

void Frame::condOut(string str, string name)
{
    if (str != "")
    {
        cout << name << ": " << str << endl;
    }
}

void Frame::condOut(int i, string name)
{
    if (i > 0)
    {
        cout << name << ": " << i << endl;
    }
}

void Frame::displayStat(vector<string> vec, string str, int desc) //template <typename T>, add desc
{
    if (str != "" && vec.size() > 0)
    {
        cout << str << ": ";
    }
    for (int i = 0; i < vec.size(); i++)
    {
        if (i > 0)
        {
            cout << ", ";
        }
        cout << vec[i];
    }
    if (vec.size() > 0)
    {
        cout << endl;
    }
}

void Frame::displayStat(vector<int> vec, string str, int desc) // add desc, auto Character::inspect?
{
    if (str != "" && vec.size() > 0)
    {
        cout << str << ": ";
    }
    for (int i = 0; i < vec.size(); i++)
    {
        if (i > 0)
        {
            cout << ", ";
        }
        cout << vec[i];
    }
    if (vec.size() > 0)
    {
        cout << endl;
    }
}

//template <typename T>
//void Frame::condOut(T i, string name)
//{
//    if (i > 0)
//    {
//        cout << name << ": " << i << endl;
//    }
//}

//void Frame::displayStat(vector<T> vec, string str, int desc) // add desc, auto Character::inspect?
//{
//    if (str != "" && vec.size() > 0)
//    {
//        cout << str << ": ";
//    }
//    for (int i = 0; i < vec.size(); i++)
//    {
//        if (i > 0)
//        {
//            cout << ", ";
//        }
//        cout << vec[i];
//    }
//    if (vec.size() > 0)
//    {
//        cout << endl;
//    }
//}
