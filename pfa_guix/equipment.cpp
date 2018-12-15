#include "equipment.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "frame.h"
using namespace std;

void Equipment::addIndex()
{
    string temp;
    cout << "name: ";
    getline(cin, temp);

    vector<string> fvec;
    int x = Frame::checkFile("equipment.txt", fvec, temp);
    if (x == -1)
    {
        cout << "repeat" << endl;
        return;
    }
    ofstream indexfile("equipment.txt");

    fvec.insert(fvec.begin() + x, temp); // name
    x++;

    // if item???????????????????????????????????????????
    cout << "type" << endl
         << "1. light" << endl
         << "2. medium" << endl
         << "3. heavy" << endl
         << "4. shield" << endl;
    cout << "choose: ";
    getline(cin, temp);

    switch(atoi(temp.c_str()))
    {
    case 1:
        temp = "light";
        break;
    case 2:
        temp = "medium";
        break;
    case 3:
        temp = "heavy";
        break;
    case 4:
        temp = "shield";
        break;
    }
    fvec.insert(fvec.begin() + x, temp);
    x++;

    Frame::getStats("cost", x, fvec);
    Frame::getStats("armor bonus", x, fvec);
    Frame::getStats("weight", x, fvec);
    Frame::getStats("description", x, fvec);

    for (int j = 0; j < fvec.size(); j++)
    {
        indexfile << fvec[j] << endl;
    }

    cout << endl;
    indexfile.close();
}
