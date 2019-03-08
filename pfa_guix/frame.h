#ifndef FRAME_H
#define FRAME_H

#include <QtWidgets>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Character;
class Npc;
class Player;

class Item;
class Weapon;
class Equipment;

class Frame
{
private:

public:
	//void encounter(string temp = "")

	// namelists
	static vector<string> names;

	// factory
	static QVector<QString> findVec(string, string = "");

	static int getNameLoc(string, string);
	static int getIndexSize(string);

	//playing
	static int rollDie(int die, int num = 1, int mod = 0);
	static void action(Player&, vector<Npc>&); ///////////////////////////////////fix
	static void hit(Player&, Npc&, Weapon&);

	//searching, sorting
	static void setNames(string);
	static int searchID(string, string name = "");
	static void sortBy(string fname, int line);
	//template <typename T>
	static void declareAll(string, vector<Item>&);
	static string alnumOnly(string);

	//indexes
	static void clearFile(string);
	static int checkFile(string, vector<string>&, string);
	static int getInsertLoc(string, string);
	static void removeIndex(string);

	template <typename T>
	static QString getStat(vector<T> &vec)
	{
		QString str = "";
		for (int i = 0; i < vec.size(); ++i)
		{
			//str += QVariant(vec[i]).toString() + ";";
		}
		return str;
	}

	/*template <typename T>
	static QString getStat(vector<int> &vec)
	{
		QString str = "";
		for (int i = 0; i < vec.size(); ++i)
		{
			str += QString::number(vec[i]) + ";";
		}
		return str;
	}*/

	template <typename T>
	static void setStat(vector<T> &vec, QString &temp)
	{
		QStringList list = temp.split(";");
		for (int i = 0; i < list.length(); ++i)
		{
			QVariant qv(temp);
			if (list[i] == "")
				vec.push_back(T());
			else
				vec.push_back(qv.value<T>());
		}
	}

	template <typename T>
	static void setStat(T &val, QString &temp)
	{
		QVariant qv(temp);
		if (temp == "")
			val = T();
		else
			val = qv.value<T>();
	}

	static vector<double> getTable(string key, int index = -1);
	static vector<string> getString(string key, int index = -1);
	static QStringList getQString(QString key, int index = -1);
};

Q_DECLARE_METATYPE(std::string)

#endif // FRAME_H
