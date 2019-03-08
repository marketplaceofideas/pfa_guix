#include "item.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "frame.h"
using namespace std;

Item::Item(string temp, string fname)
{
	QVector<QString> vec = Frame::findVec(temp, fname);

	Frame::setStat(name, vec[0]);
	Frame::setStat(type, vec[1]);
	Frame::setStat(cost, vec[2]);
	Frame::setStat(weight, vec[3]);
	Frame::setStat(magic, vec[4]);
	Frame::setStat(desc, vec[5]);
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
    ofstream file("items.txt");

	QVector<QString> vec;
	QVector<QString> nameVec;
	vec.resize(nameVec.size());

	//vec[0] = QString::number(cost);
	//vec[0] = QString::number(weight);

    file.close();
}

