#include "item.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "frame.h"
using namespace std;

Item::Item(int i)
{

}

Item::Item(string temp)
{
    int id;
    if (temp == "")
    {
        cout << "search: ";
        getline(cin, temp);
        id = Frame::searchID("items.txt", temp); // -1 loop
    }
    else
    {
        id = Frame::searchID("items.txt", temp);
    }

    fstream indexfile("items.txt");
    string trash;

    for (int i = 0; i < id * Frame::setIndexLength("items.txt"); i++)
    {
        getline(indexfile, trash); // ignore to newline????????????????
    }

    getline(indexfile, name);
    getline(indexfile, type);

    getline(indexfile, temp);
    cost = atoi(temp.c_str());

    getline(indexfile, temp);
    weight = atoi(temp.c_str());

    getline(indexfile, desc);
}

void Item::addIndex()
{
    string temp;
    cout << "name: ";
    getline(cin, temp);

    vector<string> fvec;
    int x = Frame::checkFile("items.txt", fvec, temp);
    if (x == -1)
    {
        cout << "repeat" << endl;
        return;
    }
    ofstream indexfile("items.txt");

    fvec.insert(fvec.begin() + x, temp); // name
    x++;

    cout << "type" << endl
         << "1. gear" << endl
         << "2. special" << endl
         << "3. tools" << endl
         << "4. clothes" << endl
         << "5. living" << endl
         << "6. mounts" << endl
         << "7. transport" << endl
         << "8. services" << endl;
    cout << "choose: ";
    getline(cin, temp);

    switch(atoi(temp.c_str()))
    {
    case 1:
        temp = "gear";
        break;
    case 2:
        temp = "special";
        break;
    case 3:
        temp = "tools";
        break;
    case 4:
        temp = "clothes";
        break;
    case 5:
        temp = "living";
        break;
    case 6:
        temp = "mounts";
        break;
    case 7:
        temp = "transport";
        break;
    case 8:
        temp = "services";
        break;
    }
    fvec.insert(fvec.begin() + x, temp);
    x++;

    Frame::getStats("cost", x, fvec);
    Frame::getStats("weight", x, fvec);
    Frame::getStats("description", x, fvec);

    for (int j = 0; j < fvec.size(); j++)
    {
        cout << fvec[j] << endl;
        indexfile << fvec[j] << endl;
    }

    cout << endl;
    indexfile.close();
}

