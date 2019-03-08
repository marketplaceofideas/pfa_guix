#include "npc.h"
#include <cstdlib> // atoi
#include <iostream>
#include <fstream>

#include "frame.h"
using namespace std;

Npc::Npc(string temp) : Character(temp, "bestiary.txt")
{

}

void Npc::addIndex()
{
    string temp;
    cout << "name: ";
    getline(cin, temp);

    vector<string> fvec;
    int x = Frame::checkFile("bestiary.txt", fvec, temp);
    if (x == -1)
    {
        cout << "repeat" << endl;
        return;
    }
    ofstream indexfile("bestiary.txt");

    fvec.insert(fvec.begin() + x, temp); // name
    x++;

    for (int j = 0; j < fvec.size(); j++)
    {
        indexfile << fvec[j] << endl;
    }

    indexfile.close();
}
