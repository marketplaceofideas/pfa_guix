#include "frame.h"
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

#include "miscwindows.h"
#include "character.h"
#include "npc.h"
#include "player.h"
using namespace std;

vector<string> Frame::names;

QVector<QString> Frame::findVec(string temp, string fname)
{
	bool pflag = (fname == "");
	if (pflag)
		fname = temp + "1.txt";

	fstream file(fname.c_str());
	if (file)
	{
		if (!pflag)
		{
			fstream file(fname.c_str());
			int fileLoc = getNameLoc(fname, temp) * getIndexSize(fname);

			for (int i = 0; i < fileLoc; ++i)
				file.ignore('\n');
		}

		QVector<QString> vec;
		vec.resize(getString("charFile").size()); // FIX

		for (int i = 0; i < vec.size(); ++i)
		{
			getline(file, temp);
			vec[i] = QString::fromStdString(temp);
		}
		return vec;
	}
	throw (string)"Empty File";
}

int Frame::getNameLoc(string fname, string name)
{
	setNames(fname);

	name = alnumOnly(name);
	for (int i = 0; i < names.size(); ++i) // return index
	{
		if (alnumOnly(names[i]) == name)
			return i;
	}
	throw (string)"Bad Name";
}

int Frame::getIndexSize(string fname) // called by checkFile, findindexLength, removeEntry, setNames
{
	if (fname == "bestiary.txt" || fname == "player")
		return getString("charFile").size();
	else if (fname == "items.txt")
		return getString("itemsFile").size();
	else if (fname == "weapons.txt")
		return getString("weaponsFile").size();
	else if (fname == "equipment.txt")
		return getString("equipmentFile").size();

	return 3;
}

// playing

int Frame::rollDie(int die, int num, int mod)
{
    int temp = mod;
    for (int i = 0; i < num; i++)
    {
        temp += rand() % die + 1; // get better random?
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
}

void Frame::hit(Player &c1, Npc &c2, Weapon &w)
{
    
}

// searching, sorting

void Frame::setNames(string fname) // fix up with int
{
	names.clear();
    int lines = getIndexSize(fname);
	string temp = "";

    ifstream file(fname.c_str());
    while (file) // copies file to vector
    {
        getline(file, temp);
        if (temp == "") // eof
            break;

        names.push_back(temp);
        for (int i = 1; i < lines; i++) // go to next name
            file.ignore('\n');
    }
    file.close();
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
                out.clear();

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
        for (int i = 0; i < flag.size(); i++)
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
    int lines = getIndexSize(fname);

    ifstream testfile(fname.c_str());
    if (!testfile) // no file yet, create one
    {
        ofstream file(fname.c_str());
        file.close();
    }
    else
    {
        x = getInsertLoc(fname, temp);
        while (testfile)
        {
            getline(testfile, temp);
            fvec.push_back(temp);
        }
    }

    testfile.close();
    return x;
}

int Frame::getInsertLoc(string fname, string str) // checks for alphabetical position
{
    int x = 0;
	int lines = getIndexSize(fname);
    setNames(fname);

    str = alnumOnly(str);
    while (x < names.size()) // entry by entry
    {
        string temp = alnumOnly(names[x]);

        if (str.compare(temp) == 0) // equal
			throw "repeated index";
        else if (str.compare(temp) > 0) // alphabetically higher
            ++x;
        else if (str.compare(temp) < 0) // alphabetically lower
            return x * lines;
    }
	return x * lines;
}

void Frame::removeIndex(string fname)
{
    int lines = getIndexSize(fname);
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

vector<double> Frame::getTable(string key, int index)
{
	if (key == "weight")
	{
		return { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 115, 130, 150, 175, 200, 230, 260, 300, 350, 400, 460, 520, 600, 700, 800, 920, 1040, 1200, 1400 };
	}

	else if (key == "weight")
	{
		return { .125, .25, .5, .75, 1, 2, 4, 8, 16 };
	}

	else
	{
		int x = -1;
		assert(x != -1);
		return { 0 };
	}
}

// disable targeted skill checks for player (gm only), create window: [target][value] -> [t1][t2], [val]
vector<string> Frame::getString(string key, int index) // PASS WHAT VALUES TO THE PLAYER FUNCTION????????????
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (key == "type")
	{
		return { "Abberation", "Animal", "Construct", "Dragon", "Fey", "Humanoid", "Magical Beast", "Monstrous Humanoid", "Ooze", "Outsider", "Plant", "Undead", "Vermin" };
	}

	else if (key == "terrain")
	{
		return { "Desert", "Forest/Jungle", "Hill", "Mountain", "Plain", "Ruins/Dungeon", "Sky", "Swamp", "Underground", "Urban", "Water" };
	}

	else if (key == "climate")
	{
		return { "Cold", "Extraplanar", "Temperate", "Tropical" };
	}

	else if (key == "class")
	{
		return { "Alchemist", "Arcanist", "Barbarian", "Bard", "Bloodrager", "Brawler", "Cavalier", "Cleric", "Druid", "Fighter", "Gunslinger", "Hunter", "Inquisitor", "Investigator", "Magus", 
			"Monk", "Ninja", "Oracle", "Paladin", "Ranger", "Rogue", "Samurai", "Shaman", "Skald", "Slayer", "Sorcerer", "Summoner", "Swashbuckler", "Warpriest", "Witch", "Wizard" };
	}

	else if (key == "race")
	{
		return { "Dwarf", "Elf", "Gnome", "Half-Elf", "Half-Orc", "Halfling", "Human", "Aasimar", "Catfolk", "Dhampir", "Drow", "Fetchling", "Goblin", "Hobgoblin", "Ifrit", "Kobold", "Orc", 
			"Oread", "Ratfolk", "Sylph", "Tengu", "Tiefling", "Undine", "Changeling", "Duergar", "Gillman", "Grippli", "Kitsune", "Merfolk", "Nagaji", "Samsaran", "Strix", "Suli", "Svirfneblin", 
			"Vanara", "Vishkanya", "Wayang", "Boggard", "Bugbear", "Fire Giant", "Frost Giant", "Ghoul", "Gnoll", "Lizardfolk", "Ogre", "Orc", "Sahuagin", "Serpentfolk", "Troglodyte", "Troll", 
			"Vampire" };
	}

	else if (key == "alignment")
	{
		return { "LG", "NG", "CG", "LN", "NN", "CN", "LE", "NE", "CE" };
	}

	else if (key == "size")
	{
		return { "Fine", "Diminutive", "Tiny", "Small", "Medium", "Large", "Huge", "Gargantuan", "Colossal" };
	}

	else if (key == "languages")
	{
		return { "Aboleth", "Abyssal", "Aklo", "Aquan", "Auran", "Boggard", "Celestial", "Common", "Cyclops", "Dark Folk", "Draconic", "Drow Sign Language", "Druidic", "Dwarven",
			"D’ziriak", "Elven", "Giant", "Gnoll", "Gnome", "Goblin", "Grippli", "Halfling", "Ignan", "Infernal", "Necril", "Orc", "Protean", "Sphinx", "Sylvan", "Tengu", "Terran", "Treant",
			"Undercommon", "Vegepygmy" };
	}

	else if (key == "conditions")
	{
		return { "Antagonized", "Bleed", "Blinded", "Broken", "Confused", "Cowering", "Dazed", "Dazzled", "Dead", "Deafened", "Disabled", "Dying", "Energy Drained", "Entangled",
			"Exhausted", "Fascinated", "Fatigued", "Flat-Footed", "Frightened", "Grappled", "Helpless", "Incorporeal", "Invisible", "Nauseated", "Panicked", "Paralyzed", "Petrified", "Pinned", 
			"Prone", "Shaken", "Sickened", "Sinking", "Stable", "Staggered", "Stunned", "Unconscious" };
	}

	else if (key == "subtypes")
	{
		return { "Adlet", "Aeon", "Agathion", "Air", "Angel", "Aquatic", "Archon", "Asura", "Augmented", "Automaton", "Azata", "Behemoth", "Catfolk", "Chaotic", "Clockwork", "Cold",
			"Colossus", "Daemon", "Dark Folk", "Deep One", "Demodand", "Demon", "Devil", "Div", "Dwarf", "Earth", "Elemental", "Elf", "Evil", "Extraplanar", "Fire", "Giant", "Gnome", "Goblinoid",
			"Godspawn", "Good", "Great Old One", "Halfling", "Herald", "Hive", "Human", "Incorporeal", "Inevitable", "Kaiju", "Kami", "Kasatha", "Kitsune", "Kyton", "Lawful", "Leshy", "Mythic",
			"Native", "Nightshade", "Oni", "Orc", "Protean", "Psychopomp", "Qlippoth", "Rakshasa", "Ratfolk", "Reptilian", "Robot", "Samsaran", "Sasquatch", "Shapechanger", "Swarm", "Troop", 
			"Udaeus", "Unbreathing", "Vanara", "Vishkanya", "Water" };
	}

	else if (key == "dr")
	{
		return { "Admantine", "Bludgeoning", "Chaotic", "Cold Iron", "Epic", "Evasion", "Evil", "Good", "Magic", "Silver", "Slashing" };
	}

	else if (key == "im")
	{
		return { "Weapon Damage", "Piercing Damage", "Precision Damage", "Slashing Damage", "Enchantment Spells", "Energy Spells", "Illusion Spells", "Acid", "Charm", "Cold", "Compulsion", 
			"Critical Hits", "Curse Effects", "Deafness", "Death Effects", "Disease", "Electricity", "Fear", "Fire", "Flanking", "Gaze Effects", "Illusions", "Magic", "Mind-Altering Effects", 
			"Negative Energy", "Paralysis", "Phantasms", "Poinson", "Polymorph", "Sight Attacks", "Sleep", "Sneak Attacks", "Sonic", "Stun", "Visual Effects" };
	}

	else if (key == "er")
	{
		return { "Acid", "Cold", "Fire", "Sonic" };
	}

	else if (key == "deflect")
	{
		return { "Evil" };
	}

	else if (key == "regen")
	{
		return { "Acid", "Cold Iron", "Evil", "Fire", "Good" };
	}

	// spells, feats, items, weapons, equipment, 
	else if (key == "save mod" || key == "spells" || key == "feats" || key == "items" || key == "weapons" || key == "equipment")
	{
		return { "temp" };
	}

	else if (key == "slots")
	{
		return { "R. Hand", "Armor", "Chest", "Feet", "Head", "Neck", "Shoulders", "R. Ring", "L. Hand", "Body", "Belt", "Hands", "Headband", "Eyes", "Wrist", "L. Ring" };
	}

	else if (key == "craft")
	{
		return { "Alchemy", "Armor", "Baskets", "Blacksmithing", "Books", "Bows", "Calligraphy", "Carpentry", "Clocks", "Cloth", "Clothing", "Gemcutting", "Glass", "Jewelry", "Leather", "Locks", 
			"Paintings", "Pottery", "Rope", "Scrimshaw", "Sculptures", "Ships", "Shoes", "Siege Engine", "Stonemasonry", "Traps", "Weapons" };
	}

	else if (key == "perform")
	{
		return { "Act", "Comedy", "Dance", "Keyboard", "Oratory", "Percussion", "String", "Wind", "Sing" };
	}

	else if (key == "profession")
	{
		return { "Architect", "Baker", "Barrister", "Brewer", "Butcher", "Clerk", "Cook", "Courtesan", "Driver", "Engineer", "Farmer", "Fisherman", "Gambler", "Gardener", "Herbalist", "Innkeeper", 
			"Librarian", "Merchant", "Midwife", "Miller", "Miner", "Porter", "Sailor", "Scribe", "Shepherd", "Stable Master", "Soldier", "Soothsayer", "Tanner", "Trapper", "Woodcutter" };
	}

	else if (key == "skill")
	{
		return { "Acrobatics", "Appraise", "Bluff", "Climb", "Craft", "Diplomacy", "Disable Device", "Disguise", "Escape Artist", "Fly", "Handle Animal", "Heal", "Intimidate", "K. Arcana",
			"K. Dungeoneering", "K. Engineering", "K. Geography", "K. History", "K. Local", "K. Nature", "K. Nobility", "K. Planes", "K. Religion", "Linguistics", "Perception", "Perform", 
			"Profession", "Ride", "Sense Motive", "Sleight of Hand", "Spellcraft", "Stealth", "Survival", "Swim", "Use Magic Device" };
	}

	else if (key == "sskill")
	{
		// [misc traits]
		return {
			"[s(+0,2,5)Even ground|Slightly obstructed (gravel, sand)|Severely obstructed (cavern, rubble); s(+0,2,5)Dry ground|Slightly slippery (wet)|Severely slippery (icy); s(+0,2,5)"
				"Flat ground|Slightly sloped (<45)|Severely sloped(>45); (+0,2,5,10)Steady ground|Slightly unsteady (boat)|Moderately unstead(boat in storm)|Severely unstead (earthquake)]"
				"Walk on ledge/uneven ground; Avoid a.o.o.; Long jump; High jump; Avoid fall damage", // handle separately
			"Evaluate item (GM only); Evaluate hoard", // handle with inventory?
			"Lie; Feint in combat (GM only); Secret message",
			"[c(+-10)Opposite wall to brace against; c(-5)Corner wall to brace against; c(+5)Slippery surface]"
				"Climb; Catch yourself; Catch someone else; Haul with rope",
			"Alchemy; Armor; Bows; Traps; Weapons",
			"Diplomacy", // targeted, need to add affinity first
			"Disarm/sabotage device (GM only); Open lock",
			"Disguise yourself (GM only)",
			"Tied rope; Bindings; Grappler",
			"[s(+0,0,2,4,8,12,16)Light (0-10 mph)|Moderate (11-20 mph)|Strong (21-30 mph)|Severe (31-50 mph)|Windstorm (51-74 mph)|Hurricane (75-174 mph)|Tornado (175+ mph)]"
				"Maneuver; Recover from attack/collision; Avoid fall damage",
			"", // handle
			"", // heal
			"", // intimidate
			"", //Construct/dragon/magical beast; Aura using detect magic; Spell effect; Magic materials; Targeted spell" //; Spells cast with material (?)",	// k arc
			"", //Abberation/ooze; Underground hazard; Mineral/stone/metal; Slope; Depth underground",															// dun
			"", //Dangerous construction; Structure style/age; Structure weakness",																				// eng
			"", //Creature ethnicity/accent; Regional terrain features; Location of nearby community/site",														// geo
			"", //Significant events; Appr. date of event; Obscure/ancient event",																				// his
			"", //Humanoid; Local laws/rulers/locations; Common rumor/tradition; Hidden organizations/rulers/locations",										// loc
			"", //Animal/fey/monstrous humanoid/plant/vermin; Natural hazard; Common plant/animal; Unnatural weather" //; Artificial nature of feature (?)",	// nat
			"", //Current rulers/symbols; Proper etiquette; Line of succession",																				// nob
			"", //Outsider; Names of planes; Current plane; Creature's planar origin",																			// pla
			"", //Undead; Common diety's symbol/clergy; Common mythology/tenets; Obscure diety's symbol/clergy"													// rel
			"",
			"", // gm only (perc)
			"", // perf
			"", // prof
			"",
			"Hunch; Sense enchantment; Discern secret message",
			"Palm object; Hide small object on body; Pickpocket",
			"", // spellcraft (always passive?)
			"",
			"",
			"",
			""
		};
	}

	else if (key == "tskill")
	{
		assert(index != -1);

		// :,table +,add =,directmod
		// b,base m,end --- default:(b=0) * (m=1) + a(unspecified),addition
		vector<vector<string>> tskill = {{"e(:0:20,2:15,7:10,12:5,36:0)distance (in); c(+5)full speed", // 10 autopass, lost dex bonus, re-check on dmgd
			"e(=1:1)Enemy cmd; c(+5)Moving through; c(+10)Full speed; c(+5)Prone; e(=1:2)Repeated in round", // impossible if not in light armor with light weight
			"e(=b1:2)Distance (ft); c(*m.5)10 ft start", // fail by 4 or less, dc20 reflex save to catch, otherwise fall/prone
			"e(=b1:8)Distance (ft); c(*m.5)10 ft start", // ^base land spd: =(spd-30)/10:-4; cannot exceed max speed, but show max distance (1/2 for standing l.jump)
			"c()Deliberate; c()Water; c()Distance (ft)"},

			{"c()Common item",
			"s(+20,25,30)Normal hoard|Large hoard|Massive hoard"},

			{"e(=b1:1)Opponent sense motive check; s(+-5,0,-5,-10,-20)The target wants to believe you|The lie is believable|The lie is unlikely|The lie is far-fetched|The lie is impossible; "
				"c(+5)The target is impaired; e(=1:1)You have proof (max 10)",
			"", // feint, targeted
			"c(+5)Message is complex"},

			{"l()Pitons or handholds take 1min / piton, 1hold / 5ft; s(+0,5,10,15,20,25,30)Steep slope/knotted rope against wall|Rope against wall/knotted rope|Surface w/ ledges|"
				"Surface w/ hand/footholds (pitons/tree/rope)|Surface w/ narrow hand/footholds|Rough surface (brick wall)|Overhang/ceiling with handholds; c(+5)Half speed "
				"(rather than quarter)",
			"s(+0,5,10,15,20,25,30)Steep slope/knotted rope against wall|Rope against wall/knotted rope|Surface w/ ledges|Surface w/ hand/footholds "
				"(pitons/tree/rope)|Surface w/ narrow hand/footholds|Rough surface (brick wall)|Overhang/ceiling with handholds; s(+10,20)Slope (< 60 degrees)|Wall (>60 degrees)",
			"s(+0,5,10,15,20,25,30)Steep slope/knotted rope against wall|Rope against wall/knotted rope|Surface w/ ledges|Surface w/ hand/footholds (pitons/tree/rope)|"
				"Surface w/ narrow hand/footholds|Rough surface (brick wall)|Overhang/ceiling with handholds", // + melee touch attack, +10
			"e()Weight"},

			{"",
			"",
			"",
			"",
			""},

			{""},

			{"",
			"s(+30,35,40,50)Simple lock|Average lock|Good lock|Superior lock; c(+-10)Thieves tools"},

			{""},

			{"e(=1:1)Enemy cmb", // +20
			"s(+20,23,30,35,30)Net/plant/entangle|Snare spell|Manacles|Masterwork manacles|Tight space",
			"e(=1:1)Enemy cmd"}, // targeted

			{"s(+10,15,15,20,20)Fly at half speed|Hover|Turn using 5ft of movement|Turn around using 10ft of movement|Fly up at >45 degrees",
			"s(+10,25)Attacked|Collision",
			""}, // +10

			{""},

			{""},

			{""},
				// k
			{""}, // arc

			{""}, // dun

			{""}, // eng

			{""}, // geo

			{""}, // his

			{""}, // loc

			{""}, // nat

			{""}, // nob

			{""}, // pla

			{""}, // rel
			// k
			{""},

			{""},

			{""},

			{""},

			{""},

			{"",
			"",
			""},

			{"",
			"",
			""},

			{""},

			{""},

			{""},

			{""},

			{""}
		};
		return tskill[index];
	}

	else if (key == "playerKey") // add proficiency
	{
		vector<string> npcCreate{ "n;1;Legs", "m;1,2.3;XP", "s;1;Race", "s;1;Class", "n;1;Level", "s;1;Alignment", "s;1;Size", "m;1.2;Initiative", "e;0;Special Abilities", "m;3;AC", "d;1;Deflect",
			"m;1.4;HP", "m;1.2;Fortitude Save", "m;1.2;Reflex Save", "m;1.2;Will Save", "d;1;Save Mod", "d;0;DR", "s;0;IM", "d;0;ER", "m;1.2;SR", "m;6;Speed", "m;1.2;Space", "m;1.2;Reach", 
			"s;0;Spells", "m;1.2;STR", "m;1.2;DEX", "m;1.2;CON", "m;1.2;INT", "m;1.2;WIS", "m;1.2;CHA", "m;1.2;BAB", "m;1.2;CMB", "m;1.2;CMD", "s;0;Feats", "s;0;Languages", "s;0;Items", 
			"s;0;Weapons", "s;0;Equipment" };
		vector<string> temp = getString("skill");
		npcCreate.insert(npcCreate.end(), temp.begin(), temp.end());
		return npcCreate;
	}

	else if (key == "bestiaryKey")
	{
		vector<string> npcCreate{ "e;1;ID", "e;1;CR", "s;3;Type;Type,Terrain,Climate", "n;1;Legs", "m;1,2.3;XP", "s;1;Race", "s;1;Class", "n;1;Level", "s;1;Alignment", "s;1;Size", "s;0;Subtypes",
			"m;1.2;Initiative", "e;0;Special Abilities", "m;3;AC", "d;1;Deflect", "m;4;HP", "m;1.2;Fortitude Save", "m;1.2;Reflex Save", "m;1.2;Will Save", "d;1;Save Mod", "d;0;DR", "s;0;IM", 
			"d;0;ER", "m;1.2;SR", "m;6;Speed", "m;1.2;Space", "m;1.2;Reach", "s;0;Spells", "m;1.2;STR", "m;1.2;DEX", "m;1.2;CON", "m;1.2;INT", "m;1.2;WIS", "m;1.2;CHA", "m;1.2;BAB", "m;1.2;CMB", 
			"m;1.2;CMD", "s;0;Feats", "s;0;Languages", "e;1;Environment", "e;1;Organization", "s;0;Items", "s;0;Weapons", "s;0;Equipment", "e;1;Description" };
		vector<string> temp = getString("skill");
		npcCreate.insert(npcCreate.end(), temp.begin(), temp.end());
		return npcCreate;
	}

	else if (key == "charFile" || key == "playerFile" || key == "bestiaryFile")
	{
		vector<string> charFile = { "ID", "CR", "Type", "Legs", "Subtypes", "Environment", "Organization", "Name", "Sex", "Age", "Height", "Weight", "Race", "Class", "FavoredClass", "Class Info",
			"Alignment", "Deity", "Size", "Level", "XP", "AC", "Deflect", "HP", "Regen", "Speed", "Space", "Reach", "Initiative", "STR", "DEX", "CON", "INT", "WIS", "CHA", "BAB", "CMB", "CMD",
			"Fortitude Save", "Reflex Save", "Will Save", "Save Mod", "Rank", "Condition", "Status", "Feats", "Special Abilities", "Spells", "Proficiency", "Traits", "Auras", "DR", "ER", "IM", "SR",
			"Languages", "Extra", "Description", "gp", "Encumb", "Items", "Weapons", "Equipment", "eqpItems", "eqpWeapons", "eqpEquipment" };
		vector<string> temp = getString("skill");
		charFile.insert(charFile.end(), temp.begin(), temp.end());
		return charFile;
	}

	else if (key == "itemsKey")
	{
		return { "e;1;Name", "e;1;Type", "e;1;Cost", "e;1;Weight", "e;1;Magic", "e;1;Desc" };
	}

	else if (key == "weaponsKey")
	{
		vector<string> wpnKey = getString("itemsKey");
		vector<string> temp{ "e;1;Difficulty", "e;1;Damage", "e;1;Critical", "e;1;Range", "e;1;Damage Type", "e;1;Special" };
		wpnKey.insert(wpnKey.end(), temp.begin(), temp.end());
		return wpnKey;
	}

	else if (key == "equipmentKey")
	{
		vector<string> eqpKey = getString("itemsKey");
		vector<string> temp{ "e;1;Slot", "e;1;Armor" };
		eqpKey.insert(eqpKey.end(), temp.begin(), temp.end());
		return eqpKey;
	}

	else if (key == "itemsFile")
	{
		return { "Name", "Type", "Cost", "Weight", "Magic", "Desc" };
	}

	else if (key == "weaponsFile")
	{
		vector<string> wpnFile = getString("itemsFile");
		vector<string> temp{ "Difficulty", "Damage", "Critical", "Range", "Damage Type", "Special" };
		wpnFile.insert(wpnFile.end(), temp.begin(), temp.end());
		return wpnFile;
	}

	else if (key == "equipmentFile")
	{
		vector<string> eqpFile = getString("itemsFile");
		vector<string> temp{ "Slot", "Armor" };
		eqpFile.insert(eqpFile.end(), temp.begin(), temp.end());
		return eqpFile;
	}

	else
	{
		int x = -1;
		assert(x != -1);
		return { "c empty" };
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
}

QStringList Frame::getQString(QString key, int index)
{
	vector<string> temp = getString(key.toStdString(), index);
	QVector<QString> qtemp;
	for (int i = 0; i < temp.size(); ++i)
	{
		qtemp.append(QString::fromStdString(temp[i]));
	}
	return qtemp.toList();
}
