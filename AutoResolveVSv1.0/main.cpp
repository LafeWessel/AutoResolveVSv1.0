/*
* main.cpp
*
* Created on: Oct 8, 2016
*   Author: Lafe Wessel
*/


#include <string>
#include <algorithm>
#include <cmath>

#include <array>
#include <vector>

#include <fstream>
#include <iostream>
#include <sstream>

#include <chrono>
#include <random>
#include <time.h>

#include <stdlib.h>
#include <stdio.h>

using namespace std;

typedef std::chrono::high_resolution_clock myclock;
unsigned myseed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(myseed);


/*General Notes
*
* -In almost all constructors, the variables passed in have an 'I' following their name. This indicates that they are 'Input' variables.
*
* -Most, if not all, <<ostream operators for the enum classes use hard-coded output values.
*
Order of variables in Equipment file:
1. Type: A(Armor), W(Weapon), T(Trinket), B(Banner), F(Follower) (string/char)
2. Name (string)
3. Effect(s) (string)
4. Coin Value (int)
5. Index Value (int)
6. Autoresolve Bonus (int)
7. Range (int)

The 'Corpse Thief' Follower equipment has 1 as it's autoresolve bonus to help calculate bonuses when finding treasure at the end of battles.


Order of Variables in Units file:
1. Faction: 1,2,3 or 4, follows the enum class defined below (int)
2. Name (string)
3. Type: Melee(1), Cavalry(2) or Ranged(3) (int)
4. Autoresolve Bonus (int)
5. Soldiers in each unit(int)
All variables are comma-separated, so there must be no extraneous commas.
*
*
*
*/





/*
TODO Section:

TODO-There might be a memory leak or some other error that causes the program to exit after having calculated only some of the battles

TODO-COMMENT EVERYTHING

TODO-Find new way to output at the end of a battle that captures more data

TODO-Remove initialization within loops

TODO-Refactor, especially the classes

TODO-implement playerType enum class

TODO-Write test functions

TODO-Add way for the autoresolve bonuses of the units to be changed when soldiers are lost from a unit

TODO-Refactor parts of the battleTest functions into separate functions

TODO-Find error related to when a follower is looked for from treasureResults(), probably finds something null

*/

//This class is setup to read a line from a CSV file, split
//the line by commas, and put each string into a vector of strings
class CSVRow
{
private:
	vector<string> m_data;
public:
	string const& operator[](size_t index) const
	{
		return m_data[index];
	}
	size_t size() const
	{
		return m_data.size();
	}
	void readNextRow(istream& str)
	{
		string line;
		getline(str, line);
		stringstream lineStream(line);
		string cell;
		m_data.clear();
		while (getline(lineStream, cell, ','))
		{
			m_data.push_back(cell);
		}
		if (!lineStream && cell.empty())
		{
			m_data.push_back("");
		}
	}
};

//This function allows you to just do "file >> row" to read a
//row from a file and uses the CSVRow class to split it into a
//vector of strings
istream& operator>>(istream& str, CSVRow& data)
{
	data.readNextRow(str);
	return str;
}

int randomNumber(int range) //Returns a random number between 1 and the given range
{
	int random = 0;
	if (range == 0)
	{
		return 0;
	}
	uniform_int_distribution<int> dRange(1, abs(range));
	random = dRange(generator);
	return random;
}

//Same as randomNumber, but includes 0 in the range. Specifically meant for casualty calculation and arrays
int randomNumberCas(int range)
{

	if (range == 0)
	{
		return 0;
	}
	uniform_int_distribution<int> dRange(0, abs(range));
	return dRange(generator);
}

int inputCheck(int toCheck, int highestPoint, int lowestPoint) //Checks integer input between 2 given bounds and clamps them
{

	if (toCheck < lowestPoint)//Check against lowest possible value
	{
		toCheck = lowestPoint;
		cout << "Too small, set to: " << lowestPoint << endl;
	}
	else if (toCheck > highestPoint) //Check against highest possible value
	{
		toCheck = highestPoint;
		cout << "Too large, set to: " << highestPoint << endl;
	}
	return toCheck;
}

enum class faction //Will be used to determine the units that are available, currently does nothing more than denote the faction of a given Player
{
	rebel = 1, beladimir, lerastir, menoriad
};

enum class outcome //Is used to determine the number of casualties that a player takes after a battle
{
	Decisive_Victory = 1, Heroic_Victory, Close_Victory, Draw,
	Close_Defeat, Valiant_Defeat, Crushing_Defeat
};

enum class defenses //Lists the kinds of defenses that any given settlement may have
{
	None = 1, Wooden_Wall, Wooden_Wall_W_Moat, Stone_Wall, Stone_Wall_W_Moat
};

enum class monsterType //Lists the kinds of monsters fought; also uses hard-coded values to determine treasure received from beating them
{
	Minotaur = 1, Hobgoblin, Troll, Giant, Demon, Dragon, Empty
};

enum class unitType
{
	Melee = 1, Cavalry, Ranged
};

enum class playerType
{
	attacker = 1, defender
};

//Gives the given state of a general at the end of a battle, range 0-2 for each state
string outputGenState(int state)
{
	switch (state)
	{
	case(0):
		return "Unharmed";
		break;
	case(1):
		return "Wounded for 3 turns";
		break;
	case(2):
		return "Slain";
		break;
	default:
		return " Invalid int passed";
	}
}

//Used when reading in from the units document
faction intToFaction(int input)
{
	switch (input)
	{
	case 1:
		return faction::rebel;
		break;
	case 2:
		return faction::beladimir;
		break;
	case 3:
		return faction::lerastir;
		break;
	case 4:
		return faction::menoriad;
		break;
	default:
		cerr << "invalid integer input." << endl;
	}
	return faction::rebel;
}

//Used when reading in from the units document
unitType intToUnitType(int input)
{
	switch (input)
	{
	case 1:
		return unitType::Melee;
		break;
	case 2:
		return unitType::Cavalry;
		break;
	case 3:
		return unitType::Ranged;
		break;
	default:
		cerr << "invalid integer input." << endl;
	}
	return unitType::Melee;
}

//usually 10 times between 1 and 10 (10,10) for battles
int calculateBattleRandoms(int randomRolls, int randomRange) //Is used to calculate X number of times between 1 and Y
{
	int totalRand = 0;
	for (int i = 0; i < randomRolls; i++)
	{
		totalRand += randomNumber(randomRange);
	}
	return totalRand;
}

outcome determineOutcome(float endingTotal) //This determines the kind of outcome that occurs when a given battle result is passed in
{
	//All results are in relation to the attacker.
	//Victory
	if (endingTotal > 2)
	{
		if (endingTotal >= 20)
		{
			return outcome::Decisive_Victory;
		}
		else if (endingTotal >= 10)
		{
			return outcome::Heroic_Victory;
		}
		else
		{
			return outcome::Close_Victory;
		}
	}
	//Defeat
	else if (endingTotal < -2)
	{
		if (endingTotal <= -20)
		{
			return outcome::Crushing_Defeat;
		}
		else if (endingTotal <= -10)
		{
			return outcome::Valiant_Defeat;
		}
		else
		{
			return outcome::Close_Defeat;
		}
	}
	//Draw
	else
	{
		return outcome::Draw;
	}
}

ostream& operator<<(ostream& os, outcome& end) //Output formation for outcome class
{
	switch (end)
	{
	case(outcome::Decisive_Victory):
		return os << "Decisive Victory";
		break;
	case(outcome::Heroic_Victory):
		return os << "Heroic Victory";
		break;
	case(outcome::Close_Victory):
		return os << "Close Victory";
		break;
	case(outcome::Draw):
		return os << "Draw";
		break;
	case(outcome::Close_Defeat):
		return os << "Close Defeat";
		break;
	case(outcome::Valiant_Defeat):
		return os << "Valiant Defeat";
		break;
	case(outcome::Crushing_Defeat):
		return os << "Crushing Defeat";
		break;
	default:
		return os << " No valid outcome chosen " << endl;
	}

}

ostream& operator<<(ostream& os, unitType& type) //Output formation for outcome class
{
	switch (type)
	{
	case(unitType::Melee):
		return os << "Melee";
		break;
	case(unitType::Cavalry):
		return os << "Cavalry";
		break;
	case(unitType::Ranged):
		return os << "Ranged";
		break;

	default:
		return os << " No valid unitType chosen " << endl;
	}

}

void outputIntAsOutcome(int choice) //This outputs an integer as its corresponding outcome enum class name.
{
	switch (choice)
	{
	case(1):
		cout << "Decisive Victory";
		break;
	case(2):
		cout << "Heroic Victory";
		break;
	case(3):
		cout << "Close Victory";
		break;
	case(4):
		cout << "Draw";
		break;
	case(5):
		cout << "Close Defeat";
		break;
	case(6):
		cout << "Valiant Defeat";
		break;
	case(7):
		cout << "Crushing Defeat";
		break;
	default:
		cerr << " No valid outcome chosen " << endl;
	}
}

ostream& operator<<(ostream& os, faction& fact) //This outputs an integer as its corresponding faction name.
{
	switch (fact)
	{
	case(faction::rebel):
		return os << "Rebel";
		break;
	case(faction::beladimir):
		return os << "Beladimir";
		break;
	case(faction::lerastir):
		return os << "Lerastir";
		break;
	case(faction::menoriad):
		return os << "Menoriad";
		break;
	default:
		return os << " No valid faction chosen " << endl;
	}
}

ostream& operator<<(ostream& os, defenses& def) //This outputs an integer as its corresponding defenses name.
{
	switch (def)
	{
	case(defenses::None):
		return os << "None";
		break;
	case(defenses::Wooden_Wall):
		return os << "Wooden Walls";
		break;
	case(defenses::Wooden_Wall_W_Moat):
		return os << "Wooden Walls and Moat";
		break;
	case(defenses::Stone_Wall):
		return os << "Stone Walls";
		break;
	case(defenses::Stone_Wall_W_Moat):
		return os << "Stone Walls and Moat";
		break;
	default:
		return os << " No valid defenses chosen " << endl;
	}
}

ostream& operator<<(ostream& os, monsterType& mon) //Thsi outputs an integer as its corresponding monsterType name
{
	switch (mon)
	{
	case(monsterType::Minotaur):
		return os << "Minotaur";
		break;
	case(monsterType::Hobgoblin):
		return os << "Hobgoblin";
		break;
	case(monsterType::Troll):
		return os << "Troll";
		break;
	case(monsterType::Giant):
		return os << "Giant";
		break;
	case(monsterType::Demon):
		return os << "Demon";
		break;
	case(monsterType::Dragon):
		return os << "Dragon";
		break;
	default:
		return os << " No valid monster chosen " << endl;
	}
}

class townStats //Is used in raid and siege battles to keep data on the town
{
private:
	int level;
	int supplies; //These are used more in Raid battles and can be sold during campaigns
	defenses townDefense;
	bool debug;

public:
	townStats();
	townStats(int levelI);

	int getSupplies() { return supplies; };
	defenses getDefenses() { return townDefense; };
	int getLevel() { return level; };
	bool getDebug() { return debug; }

	void setSupplies(int suppliesI) { supplies = suppliesI; };
	void setLevel(int levelI) { level = levelI; };
	void setDefenses(defenses defenseI) { townDefense = defenseI; };
	void setDebugBool(bool debugI) { debug = debugI; }

};

townStats::townStats() //void initializer
{
	level = 0;
	supplies = 0;
	townDefense = defenses::None;
	debug = false;
}

townStats::townStats(int levelI) //initializer
{
	level = levelI;
	supplies = 4 + (levelI * 4); //this takes the town level and determines the number of supplies it has
	switch (level) //this takes the town level and determines the defenses
	{
	case(1):
		townDefense = defenses::None;
		break;
	case(2):
		townDefense = defenses::Wooden_Wall;
		break;
	case(3):
		townDefense = defenses::Wooden_Wall_W_Moat;
		break;
	case(4):
		townDefense = defenses::Stone_Wall;
		break;
	case(5):
		townDefense = defenses::Stone_Wall_W_Moat;
		break;
	default:
		townDefense = defenses::None;
	}
	debug = false;
}

//This is used for all the equipment that is read in when the a Treasure class has initializeTreasure() is called.
//Used by generals and at the end of battles
class Equipment
{
private:
	string name;
	int autoBonus;
	int number;
	int range;
	string EquipType;
	string effect;
	int coinValue;
	bool debug;

public:
	Equipment(string nameI, int autoBonusI, int numberI, int rangeI, string EquipTypeI, string effectI, int coinValueI);
	Equipment();

	string getName() { return name; };
	int getABonus() { return autoBonus; };
	int getIndex() { return number; };
	int getRange() { return range; };
	string getEqType() { return EquipType; };
	string getEffect() { return effect; };
	int getCValue() { return coinValue; };
	bool getDebug() { return debug; }

	void setName(string nameI) { name = nameI; };
	void setABonus(int autoBonusI) { autoBonus = autoBonusI; };
	void setIndex(int indexI) { number = indexI; };
	void setRange(int rangeI) { range = rangeI; };
	void setEqType(string equipTypeI) { EquipType = equipTypeI; };
	void setEffect(string effectI) { effect = effectI; };
	void setCValue(int CValI) { coinValue = CValI; };
	void setDebugBool(bool debugI) { debug = debugI; }
};

Equipment::Equipment() //void initializer
{
	name = "";
	autoBonus = 0;
	number = 0;
	range = 0;
	EquipType = "";
	effect = "";
	coinValue = 0;
	debug = false;
}

Equipment::Equipment(string nameI, int autoBonusI, int numberI, int rangeI, string EquipTypeI, string effectI, int coinValueI) //initializer
{
	name = nameI;
	autoBonus = autoBonusI;
	number = numberI;
	range = rangeI;
	EquipType = EquipTypeI;
	effect = effectI;
	coinValue = coinValueI;
	debug = false;
}

ostream& operator<<(ostream& os, Equipment& eqpt) //output operator for Equipment class

{
	return os << eqpt.getName() << endl
		<< "Effect: " << eqpt.getEffect() << endl
		<< "Range: " << eqpt.getRange() << endl
		<< "EquipType: " << eqpt.getEqType() << endl
		<< "Coin Value: " << eqpt.getCValue() << endl;
}


class Unit
{
private:
	string name;
	int autoResBonus;
	int soldiersPerUnit;
	faction fact;
	unitType type;


public:
	Unit();
	Unit(string nameI, int autoResBonusI, int soldiersPerUnitI, faction factI, unitType typeI);

	string getName() { return name; };
	int getARBonus() { return autoResBonus; };
	int getSoldiersPerUnit() { return soldiersPerUnit; };
	faction& getFaction() { return fact; };
	unitType& getUnitType() { return type; };

	void setName(string nameI) { name = nameI; };
	void setARBonus(int ARBonusI) { autoResBonus = ARBonusI; };
	void setSoldiersPerUnit(int soldiersPerUI) { soldiersPerUnit = soldiersPerUI; };
	void setFaction(faction factI) { fact = factI; };
	void setUnitType(unitType typeI) { type = typeI; };

};

Unit::Unit()
{
	name = "No Name";
	autoResBonus = 1;
	soldiersPerUnit = 1;
	fact = faction::rebel;
	type = unitType::Melee;
}

Unit::Unit(string nameI, int autoResBonusI, int soldiersPerUnitI, faction factI, unitType typeI)
{
	name = nameI;
	autoResBonus = autoResBonusI;
	soldiersPerUnit = soldiersPerUnitI;
	fact = factI;
	type = typeI;
}

class Roster
{
private:
	vector<Unit> factionUnits;
	faction fact;
	bool debug;

public:
	Roster();
	Roster(vector<Unit> unitsI, faction factI);

	vector<Unit>& getUnits() { return factionUnits; };
	faction& getFaction() { return fact; };
	bool getDebugBool() { return debug; };
	int getNumberOfUnits() { return factionUnits.size(); };

	void setUnits(vector<Unit> unitsI) { factionUnits = unitsI; };
	void setFaction(faction factI) { fact = factI; };
	void setDebugBool(bool debugI) { debug = debugI; };
	vector<Unit> getUnitsOfType(unitType& type);
	Unit getUnitAtIndex(int index) { return factionUnits[index]; };

	void buildRoster();

};

Roster::Roster() //void initializer
{
	factionUnits = {};
	fact = faction::rebel;
	debug = false;
}

Roster::Roster(vector<Unit> unitsI, faction factI) //initializer
{
	factionUnits = unitsI;
	fact = factI;
	debug = false;
}

vector<Unit> Roster::getUnitsOfType(unitType& type) //gets all of the units of a specific type
{
	if (debug) { cout << "Roster::getUnitsOfType called for unitType: " << type << endl; }
	vector<Unit> unitsI = {};
	for (int i = 0; i < factionUnits.size(); i++)
	{
		if (factionUnits[i].getUnitType() == type)
		{
			unitsI.push_back(factionUnits[i]);
			if (debug) { cout << "unitsI pushed back: " << factionUnits[i].getName() << endl; }
		}
	}
	if (debug) { cout << "Roster::getUnitsOfType finished" << endl; }
	return unitsI;
}

void Roster::buildRoster() //Reads units in from the 'units' file and adds them to the roster if they match the roster's faction
{
	//Makes sure that the faction is acceptable before continuing
	if (fact != faction::beladimir && fact != faction::lerastir && fact != faction::menoriad && fact != faction::rebel)
	{
		cout << "No faction selected for roster building." << endl;
		return;
	}
	if (debug) { cout << "Faction selected: " << fact << endl; }
	ifstream file("units");
	CSVRow row;
	factionUnits = {};

	string Name;
	string ARBonus;
	string SoldiersPerU;
	faction Faction;
	unitType UnitType;

	//Reads the equipment file and puts equipment in the correct vectors then initializes the treasure
	while (file >> row)
	{

		Faction = intToFaction(stoi(row[0]));
		if (debug) { cout << "intToFaction(stoi(row[0])) : " << Faction << endl; }
		UnitType = intToUnitType(stoi(row[2]));
		if (debug) { cout << "intToUnitType(stoi(row[2])) : " << UnitType << endl; }

		Unit unitRead{};
		unitRead.setName(row[1]);
		if (debug) { cout << "unitRead Name set to : " << row[1] << endl; }
		unitRead.setARBonus(stoi(row[3]));
		if (debug) { cout << "unitRead ARBonus set to : " << stoi(row[3]) << endl; }
		unitRead.setSoldiersPerUnit(stoi(row[4]));
		if (debug) { cout << "unitRead soldiersPerUnit set to : " << stoi(row[4]) << endl; }
		unitRead.setFaction(Faction);
		if (debug) { cout << "unitRead Faction set to : " << Faction << endl; }
		unitRead.setUnitType(UnitType);
		if (debug) { cout << "unitRead UnitType set to : " << UnitType << endl; }


		if (unitRead.getFaction() == fact)
		{
			factionUnits.push_back(unitRead);
			if (debug) { cout << "factionUnits pushed: " << unitRead.getName() << endl; }
		}
		else
		{
			if (debug) { cout << unitRead.getName() << " was not pushed." << endl; }
		}
	}
	return;
}

class General //This is used by the Player class
{
private:
	int rank;
	int AutoResEqBonus; //Auto resolve bonus from Equipment
	Equipment armor;
	Equipment weapon;
	Equipment trinket;
	Equipment banner;
	Equipment follower;
	bool debug;

public:
	General();
	General(int rankI, Equipment armorI, Equipment weaponI, Equipment trinketI, Equipment bannerI, Equipment followerI);
	int getRank() { return rank; };

	int getARBonus() { return AutoResEqBonus; };
	Equipment& getArmor() { return armor; };
	Equipment& getWeapon() { return weapon; };
	Equipment& getTrinket() { return trinket; };
	Equipment& getBanner() { return banner; };
	Equipment& getFollower() { return follower; };
	bool getDebug() { return debug; }

	void setRank(int rankI) { rank = rankI; };
	void setAutoBonus(int autoBonusI) { AutoResEqBonus = autoBonusI; };
	void setArmor(Equipment equipI) { armor = equipI; };
	void setWeapon(Equipment equipI) { weapon = equipI; };
	void setTrinket(Equipment equipI) { trinket = equipI; };
	void setBanner(Equipment equipI) { banner = equipI; };
	void setFollower(Equipment equipI) { follower = equipI; };
	void setDebugBool(bool debugI) { debug = debugI; }

};

General::General() //void initializer
{
	rank = 1;
	AutoResEqBonus = 0;
	armor = Equipment{};
	weapon = Equipment{};
	trinket = Equipment{};
	banner = Equipment{};
	follower = Equipment{};
	debug = false;
}

General::General(int rankI, Equipment armorI, Equipment weaponI, Equipment trinketI, Equipment bannerI, Equipment followerI) //initializer
{
	rank = rankI;
	armor = armorI;
	weapon = weaponI;
	trinket = trinketI;
	banner = bannerI;
	follower = followerI;
	AutoResEqBonus = armorI.getABonus() + weaponI.getABonus() + trinketI.getABonus() + bannerI.getABonus();
	debug = false;
}

class Treasure //This keeps all the equipment to allow for finding of specific equipment and battle loot calculation
{

private:
	vector<Equipment> armor;
	vector<Equipment> weapon;
	vector<Equipment> trinket;
	vector<Equipment> banner;
	vector<Equipment> follower;
	vector<Equipment> dragon;
	bool debug;

public:
	Treasure();
	Treasure(vector<Equipment> armorI, vector<Equipment> weaponI, vector<Equipment> trinketI, vector<Equipment> bannerI, vector<Equipment> followerI, vector<Equipment> dragonI);
	//the last item in the follower array is the empty/null equipment
	Equipment noTreasure()
	{
		Equipment empty{ "No Treasure", 0,0,0,"","",0 };
		return empty;
	};

	//Subtracts 1 from the array so that it doesn't run off the end of the array of equipment
	Equipment findArmor() { return armor[randomNumber(armor.size()) - 1]; };
	Equipment findWeapon() { return weapon[randomNumber(weapon.size()) - 1]; };
	Equipment findTrinket() { return trinket[randomNumber(trinket.size()) - 1]; };
	Equipment findBanner() { return banner[randomNumber(banner.size()) - 1]; };
	Equipment findDragonEq() { return dragon[randomNumber(dragon.size()) - 1]; };
	//This subtracts 2 from the length of the array because the last item is the empty/null equipment
	Equipment findFollower() { return follower[randomNumber(follower.size()) - 1]; };

	Equipment findTreasure(int bonus); //Used at the end of battles to determine loot results

	Equipment getArmorAtIndex(int index) { return armor[index - 1]; };
	Equipment getWeaponAtIndex(int index) { return weapon[index - 1]; };
	Equipment getTrinketAtIndex(int index) { return trinket[index - 1]; };
	Equipment getBannerAtIndex(int index) { return banner[index - 1]; };
	Equipment getFollowerAtIndex(int index) { return follower[index - 2]; }; // -2 because the last element in array is null equipment
	Equipment getDragonAtIndex(int index) { return dragon[index - 1]; };

	vector<Equipment>& getArmorVector() { return armor; };
	vector<Equipment>& getWeaponVector() { return weapon; };
	vector<Equipment>& getTrinketVector() { return trinket; };
	vector<Equipment>& getBannerVector() { return banner; };
	vector<Equipment>& getFollowerVector() { return follower; };
	vector<Equipment>& getDragonVector() { return dragon; };

	void setArmorVector(vector<Equipment> equipVectorI) { armor = equipVectorI; };
	void setWeaponVector(vector<Equipment> equipVectorI) { weapon = equipVectorI; };
	void setTrinketVector(vector<Equipment> equipVectorI) { trinket = equipVectorI; };
	void setBannerVector(vector<Equipment> equipVectorI) { banner = equipVectorI; };
	void setFollowerVector(vector<Equipment> equipVectorI) { follower = equipVectorI; };
	void setDragonVector(vector<Equipment> equipVectorI) { dragon = equipVectorI; };

	bool getDebug() { return debug; }
	void setDebugBool(bool debugI) { debug = debugI; }

	void initializeTreasure(); //This grabs all the data from the file containing the equipment
};

Treasure::Treasure() //void initializer
{
	armor = {};
	weapon = {};
	trinket = {};
	banner = {};
	follower = {};
	dragon = {};
	debug = false;
}

//initializer
Treasure::Treasure(vector<Equipment> armorI, vector<Equipment> weaponI, vector<Equipment> trinketI, vector<Equipment> bannerI, vector<Equipment> followerI, vector<Equipment> dragonI)
{
	armor = armorI;
	weapon = weaponI;
	trinket = trinketI;
	banner = bannerI;
	follower = followerI;
	dragon = dragonI;
	debug = false;
}

void Treasure::initializeTreasure()
{
	if (debug) { cout << "initializeTreasure() called." << endl; }
	ifstream file("equipment");
	CSVRow row;
	string theEquipType;
	string theName;
	string theEffect;
	string theCoinValue;
	string theIndexNumber;
	string theAutoBonus;
	string theRange;
	vector<Equipment> armorI = {};
	vector<Equipment> weaponsI = {};
	vector<Equipment> trinketsI = {};
	vector<Equipment> bannersI = {};
	vector<Equipment> followersI = {};
	vector<Equipment> dragonsI = {};

	//Reads the equipment file and puts equipment in the correct vectors then initializes the treasure
	while (file >> row)
	{

		theEquipType = row[0];
		if (debug) { cout << "Equipment Type set to: " << row[0] << endl; }
		theName = row[1];
		if (debug) { cout << "Name set to: " << row[1] << endl; }
		theEffect = row[2];
		if (debug) { cout << "Effect set to: " << row[2] << endl; }
		theCoinValue = row[3];
		if (debug) { cout << "Coin Value set to: " << row[3] << endl; }
		theIndexNumber = row[4];
		if (debug) { cout << "Index Number set to: " << row[4] << endl; }
		theAutoBonus = row[5];
		if (debug) { cout << "AutoRBonus set to: " << row[5] << endl; }
		theRange = row[6];
		if (debug) { cout << "Range set to: " << row[6] << endl; }

		Equipment inputEquip(theName, stoi(theAutoBonus), stoi(theIndexNumber), stoi(theRange), theEquipType, theEffect, stoi(theCoinValue));

		if (theEquipType == "Armor")
		{
			armorI.push_back(inputEquip);
			if (debug) { cout << "armor vector pushed: " << inputEquip.getName() << endl; }
		}
		else if (theEquipType == "Weapon")
		{
			weaponsI.push_back(inputEquip);
			if (debug) { cout << "weapons vector pushed: " << inputEquip.getName() << endl; }
		}
		else if (theEquipType == "Trinket")
		{
			trinketsI.push_back(inputEquip);
			if (debug) { cout << "trinkets vector pushed: " << inputEquip.getName() << endl; }
		}
		else if (theEquipType == "Banner")
		{
			bannersI.push_back(inputEquip);
			if (debug) { cout << "banners vector pushed: " << inputEquip.getName() << endl; }
		}
		else if (theEquipType == "Follower")
		{
			followersI.push_back(inputEquip);
			if (debug) { cout << "followers vector pushed: " << inputEquip.getName() << endl; }
		}
		else if (theEquipType == "Dragon")
		{
			dragonsI.push_back(inputEquip);
			if (debug) { cout << "dragon vector pushed: " << inputEquip.getName() << endl; }
		}
		else
		{
			cerr << "Invalid equipment type given: " << theEquipType << endl;
		}
	}
	armor = armorI;
	weapon = weaponsI;
	trinket = trinketsI;
	banner = bannersI;
	follower = followersI;
	dragon = dragonsI;
	if (debug) { cout << " intitializeTreasure() finished" << endl; }
	return;
}

Equipment Treasure::findTreasure(int bonus) //Used to determine battle loot results
{
	if (debug) { cout << " findTreasure() called" << endl; }
	if ((randomNumber(8) + bonus) >= 5)
	{
		switch (randomNumber(5))
		{
		case(1):
			if (debug) { cout << " findArmor() returned" << endl; }
			return findArmor();
			break;
		case(2):
			if (debug) { cout << " findWeapon() returned" << endl; }
			return findWeapon();
			break;
		case(3):
			if (debug) { cout << " findTrinket() returned" << endl; }
			return findTrinket();
			break;
		case(4):
			if (debug) { cout << " findBanner() returned" << endl; }
			return findBanner();
			break;
		case(5):
			if (debug) { cout << " findFollower() returned" << endl; }
			return findFollower();
			break;
		default:
			cerr << "No type selected" << endl;
			return noTreasure();
		}
	}
	else
	{
		if (debug) { cout << " noTreasure() returned" << endl; }
		return noTreasure();
	}
	if (debug) { cout << " findTreasure() finished" << endl; }
}

class Monster //is used in monster battles
{
private:
	monsterType type;
	int coinReward;
	int autoResValue; //*10 + 10
	bool debug;

public:
	Monster();
	Monster(monsterType typeI);

	int getCoinReward() { return coinReward; };
	int getARValue() { return autoResValue; };
	monsterType& getMonsterType() { return type; };
	bool getDebug() { return debug; }

	void setCoinReward(int coinRewardI) { coinReward = coinRewardI; };
	void setAutoResValue(int autoResValI) { autoResValue = autoResValI; };
	void setMonsterType(monsterType monTypeI) { type = monTypeI; };
	void setDebugBool(bool debugI) { debug = debugI; }

	vector<Equipment> getEquipRewards(); //This gets the rewards associated with the type of Monster
};

Monster::Monster() //void initializer
{
	type = monsterType::Empty;
	coinReward = 0;
	autoResValue = 0;
	debug = false;
}

Monster::Monster(monsterType typeI) //initializer
{
	type = typeI;

	//These set the coin rewards; they are based on values I made elsewhere
	if ((int)typeI < 5)
	{
		coinReward = ((int)typeI + 1) * 100;
	}
	else if ((int)typeI < 6)
	{
		coinReward = ((int)typeI + 2) * 100;
	}
	else
	{
		coinReward = ((int)typeI + 1) * 200;
	}

	autoResValue = ((int)typeI * 10) + 10;
	debug = false;
}

vector<Equipment> Monster::getEquipRewards() //This figures out the treasure gained for killing a monster, based on info elsewhere
{
	if (debug) { cout << "getEquipRewards called" << endl; }
	Treasure treasure{};
	if (debug) { cout << "treasure initialized" << endl; }
	treasure.setDebugBool(debug);
	treasure.initializeTreasure();
	vector<Equipment> rewards = {};
	switch ((int)type)
	{
	case(1):
		if (debug)
		{
			Equipment reward = treasure.findWeapon();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure.findWeapon());
		}
		break;
	case(2):
		if (debug)
		{
			Equipment reward = treasure.findWeapon();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
			reward = treasure.findArmor();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure.findWeapon());
			rewards.push_back(treasure.findArmor());
		}
		break;
	case(3):
		if (debug)
		{
			Equipment reward = treasure.findWeapon();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
			reward = treasure.findTrinket();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure.findWeapon());
			rewards.push_back(treasure.findTrinket());
		}
		break;
	case(4):
		if (debug)
		{
			Equipment reward = treasure.findWeapon();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
			reward = treasure.findTrinket();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
			reward = treasure.findArmor();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure.findWeapon());
			rewards.push_back(treasure.findTrinket());
			rewards.push_back(treasure.findArmor());
		}
		break;
	case(5):
		if (debug)
		{
			Equipment reward = treasure.findBanner();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
			reward = treasure.findArmor();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure.findArmor());
			rewards.push_back(treasure.findBanner());
		}
		break;
	case(6):
		if (debug)
		{
			Equipment reward = treasure.findDragonEq();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure.findDragonEq());
		}
		break;
	default:
		cerr << "Something went wrong" << endl;
	}
	return rewards;
}

class Player //This is used in every kind of battle.
{
private:

	vector<Unit> playerUnits; //vector of units that are in the player's army
	int Melee; //Melee autoresolve bonus total
	int Cavalry; //Cavalry autoresolve bonus total
	int Ranged; //Ranged autoresolve bonus total
	General general; //Lowercase because class name uses uppercase
	bool AdvCombatDeck;
	faction Fact;
	bool debug;
	int Reinforcements;

	void setupUnitAutoresolveBonuses();

public:
	Player();
	Player(vector<Unit> unitsI, General generalI, int ReinforceI, bool AdvCombatDeckI, faction FactI);

	vector<Unit>& getPlayerUnits() { return playerUnits; };
	int getMelee() { return Melee; };
	int getCavalry() { return Cavalry; };
	int getRanged() { return Ranged; };
	General& getGeneral() { return general; };
	bool getAdvComDeck() { return AdvCombatDeck; };
	faction& getFaction() { return Fact; };
	bool getDebug() { return debug; }
	Unit& getUnitAtIndex(int index) { return playerUnits[index]; };
	int getNumberOfUnits() { return playerUnits.size(); };

	void setPlayerUnits(vector<Unit> unitsI);
	void setMelee(int meleeI) { Melee = meleeI; };
	void setCavalry(int cavalryI) { Cavalry = cavalryI; };
	void setRanged(int rangedI) { Ranged = rangedI; };
	void setGeneralG(General generalI) { general = generalI; };
	void setAdvCombatDeck(bool advComDeckI) { AdvCombatDeck = advComDeckI; };
	void setFaction(faction factionI) { Fact = factionI; };
	void setDebugBool(bool debugI) { debug = debugI; }
	void setReinforcements(int ReinforceI);
	void setUnitAtIndex(int index, Unit unitI) { playerUnits[index] = unitI; };



};

Player::Player() //void initializer
{
	Melee = 0;
	Cavalry = 0;
	Ranged = 0;
	general = General{};
	AdvCombatDeck = false;
	Fact = faction::rebel;
	debug = false;
	Reinforcements = 0;
}

//initializer
Player::Player(vector<Unit> unitsI, General generalI, int ReinforceI, bool AdvCombatDeckI, faction FactI)
{
	setupUnitAutoresolveBonuses();
	//automatically adds reinforcements onto the total melee, cavalry and ranged soldiers the class has
	Melee += (ReinforceI * 4);
	Cavalry += (ReinforceI * 4);
	Ranged += (ReinforceI * 4);
	general = generalI;
	AdvCombatDeck = AdvCombatDeckI;
	Fact = FactI;
	debug = false;
	Reinforcements = ReinforceI;
}

void Player::setPlayerUnits(vector<Unit> unitsI)
{
	playerUnits = unitsI;
	setupUnitAutoresolveBonuses();
	return;
}

void Player::setReinforcements(int ReinforceI)
{
	//Removes any current reinforcements from autoresolve totals before adding the input bonuses
	Melee -= (Reinforcements * 4);
	Cavalry -= (Reinforcements * 4);
	Ranged -= (Reinforcements * 4);

	Melee += (4 * ReinforceI);
	Cavalry += (4 * ReinforceI);
	Ranged += (4 * ReinforceI);
	Reinforcements = ReinforceI;
}

void Player::setupUnitAutoresolveBonuses()
{
	Melee = 0;
	Cavalry = 0;
	Ranged = 0;

	//Loops over the vector of player units, adding the autoresolve values.
	for (int i = 0; i < playerUnits.size(); i++)
	{
		switch (playerUnits[i].getUnitType())
		{
		case unitType::Melee:
			Melee += playerUnits[i].getARBonus();
			if (debug) { cout << playerUnits[i].getARBonus() << " added to Melee = " << Melee << endl; }
			break;
		case unitType::Cavalry:
			Cavalry += playerUnits[i].getARBonus();
			if (debug) { cout << playerUnits[i].getARBonus() << " added to Cavalry = " << Cavalry << endl; }
			break;
		case unitType::Ranged:
			Ranged += playerUnits[i].getARBonus();
			if (debug) { cout << playerUnits[i].getARBonus() << " added to Ranged = " << Ranged << endl; }
			break;
		default:
			cerr << "selected unit has no unitType." << endl;
		}
	}
	Melee += (4 * Reinforcements);
	if (debug) { cout << "Melee with reinforecements " << Melee << endl; }
	Cavalry += (4 * Reinforcements);
	if (debug) { cout << "Cavalry with reinforecements " << Cavalry << endl; }
	Ranged += (4 * Reinforcements);
	if (debug) { cout << "Ranged with reinforecements " << Ranged << endl; }
	return;
}

class Battle // siege, raid, normal and naval battles inherit from this class
{

protected:
	Player attacker;
	Player defender;
	outcome result;
	bool output;
	bool debug;

public:
	Battle();
	Battle(Player attackerI, Player defenderI);

	Player& getAttacker() { return attacker; };
	Player& getDefender() { return defender; };
	outcome& getOutcome() { return result; };
	int getEnding() { return (int)result; };
	bool getOutputBool() { return output; }
	bool getDebugBool() { return debug; }

	void setAttacker(Player attackerI) { attacker = attackerI; };
	void setDefender(Player defenderI) { defender = defenderI; };
	void setOutcome(outcome resultI) { result = resultI; };
	void setOutput(bool outputI) { output = outputI; };
	void setDebug(bool debugI) { debug = debugI; };
	void assignCasualties();

	void treasureResults(); //Determines whether or not loot is found at the end of a battle.
	void CalculateCas(vector<vector<int>>& totalCasualties); //Determines the amount of casualties at the end of a battle
	void battleOutput(vector<vector<int>> totalCasualties); //Output at battle, normally supplemented by other output in inherited classes
	float battleCalculate(); //Calculates the battle, is almost always supplemented by other calculations in inherited classes
};

Battle::Battle() //void initializer
{
	attacker = Player{};
	defender = Player{};
	result = outcome::Draw;
	output = true;
	debug = false;
}

Battle::Battle(Player attackerI, Player defenderI) // initializer
{
	attacker = attackerI;
	defender = defenderI;
	result = outcome::Draw;
	output = true;
	debug = false;
}

void Battle::treasureResults()
{
	//Initializes and fills a treasure class
	Treasure loot{};
	loot.setDebugBool(debug);
	loot.initializeTreasure();
	if (debug) { cout << "Treasure initialized. Battle::treasureResults" << endl; }

	//Goes to where any bonus for finding loot at the end of a battle should be and sets the bonus to it.
	int bonus = attacker.getGeneral().getFollower().getABonus();

	//Looks for equipment and outputs what is returned
	Equipment foundAtt = loot.findTreasure(bonus);
	if (output)
	{
		cout << foundAtt.getName() << " was found by the attacking army." << endl;
		//This outputs the stats of the equipment if it isn't the empty equipment
		if (foundAtt.getName() != loot.noTreasure().getName())
		{
			cout << foundAtt << endl;
		}
	}

	//Then does the same as above for the defending Player.
	bonus = defender.getGeneral().getFollower().getABonus();

	Equipment foundDef = loot.findTreasure(bonus);
	if (output)
	{
		cout << foundDef.getName() << " was found by the defending army." << endl;
		//This outputs the stats of the equipment if it isn't the empty equipment
		if (foundDef.getName() != loot.noTreasure().getName())
		{
			cout << foundDef << endl;
		}
	}
	if (debug) { cout << "Battle::treasureResults finished" << endl; }
	return;
}

void Battle::battleOutput(vector<vector<int>> totalCasualties) //Base battle-end output
{
	treasureResults();
	if (output)
	{
		if (debug) { cout << "Made it into output" << endl; }
		cout << result << endl;
	}

	if (debug) { cout << "Moving on to casualty assignment Battle::battleOutput" << endl; }
	//Maybe move this part to calculateCas()?
	//Determines attacker casualty distribution
	vector<Unit> attackerUnits = {};

	for (int i = 0; i < attacker.getNumberOfUnits() - 1; i++)
	{
		attackerUnits.push_back(attacker.getUnitAtIndex(i));
	}

	int assignedSoldierCasualties = 0;
	int assignedUnitCasualties = 0;
	int i = 0;
	int cas = 0;
	while (assignedSoldierCasualties <= totalCasualties[0][0])
	{
		//This makes the iterator skip units that have already lost all their soldiers.
		while (attackerUnits[i].getSoldiersPerUnit() == 0)
		{
			i++;
		}
		//Determines the amount of soldiers lost
		//If the unit casualties is maxed out, it makes sure that the unit loses 1 less than it's total number of soldiers at max; 0 if there is 1 soldier only
		if (assignedUnitCasualties >= totalCasualties[0][1])
		{
			if (attackerUnits[i].getSoldiersPerUnit() == 1)
			{
				cas = 0;
			}
			else
			{
				cas = randomNumberCas(attackerUnits[i].getSoldiersPerUnit() - 1);
			}
		}
		else
		{
			cas = randomNumberCas(attackerUnits[i].getSoldiersPerUnit());
		}

		//Subtracts the casualties from the amount of soldiers in the unit and declares if they have fully perished
		attackerUnits[i].setSoldiersPerUnit(attackerUnits[i].getSoldiersPerUnit() - cas);

		if (attackerUnits[i].getSoldiersPerUnit() == 0)
		{
			cout << assignedSoldierCasualties << " " << attackerUnits[i].getName() << " completely destroyed." << endl;
			assignedUnitCasualties++;
		}
		else
		{
			cout << assignedSoldierCasualties + cas << " " << attackerUnits[i].getName() << " lost " << cas << " soldiers." << endl;
		}
		assignedSoldierCasualties += cas;


		//Wraps the index so it doesn't go off the end
		i++;
		if (i >= attackerUnits.size() - 1)
		{
			i = 0;
			if (debug) { cout << "Wrapped attacker casualty assignment loop" << endl; }
		}
	}
	if (output)
	{
		cout << "Attacker Soldier Casualties: " << assignedSoldierCasualties << endl;
		cout << "Attacker Upgrades: " << assignedUnitCasualties << endl;
		cout << "Attacker General is " << outputGenState(totalCasualties[0][3]) << endl;
	}

	vector<Unit> attackerUnitsWithCasualties = {};
	for (int i = 0; i < attackerUnits.size() - 1; i++)
	{
		if (attackerUnits[i].getSoldiersPerUnit() > 0)
		{
			attackerUnitsWithCasualties.push_back(attackerUnits[i]);
		}
	}
	attacker.setPlayerUnits(attackerUnitsWithCasualties);


	//Determines defender casualty distribution
	vector<Unit> defenderUnits = {};
	i = 0;
	for (int i = 0; i < defender.getNumberOfUnits() - 1; i++)
	{
		defenderUnits.push_back(defender.getUnitAtIndex(i));
	}

	assignedSoldierCasualties = 0;
	assignedUnitCasualties = 0;
	i = 0;
	cas = 0;
	while (assignedSoldierCasualties <= totalCasualties[1][0])
	{
		//This makes the iterator skip units that have already lost all their soldiers.
		while (defenderUnits[i].getSoldiersPerUnit() == 0)
		{
			i++;
		}
		//Determines the amount of soldiers lost
		//If the unit casualties is maxed out, it makes sure that the unit loses 1 less than it's total number of soldiers at max; 0 if there is 1 soldier only
		if (assignedUnitCasualties >= totalCasualties[1][1])
		{
			if (defenderUnits[i].getSoldiersPerUnit() == 1)
			{
				cas = 0;
			}
			else
			{
				cas = randomNumberCas(defenderUnits[i].getSoldiersPerUnit() - 1);
			}
		}
		else
		{
			cas = randomNumberCas(defenderUnits[i].getSoldiersPerUnit());
		}

		//Subtracts the casualties from the amount of soldiers in the unit and declares if they have fully perished
		defenderUnits[i].setSoldiersPerUnit(defenderUnits[i].getSoldiersPerUnit() - cas);

		if (defenderUnits[i].getSoldiersPerUnit() == 0)
		{
			cout << assignedSoldierCasualties << " " << defenderUnits[i].getName() << " completely destroyed." << endl;
			assignedUnitCasualties++;
		}
		else
		{
			cout << assignedSoldierCasualties + cas << " " << defenderUnits[i].getName() << " lost " << cas << " soldiers." << endl;
		}
		assignedSoldierCasualties += cas;


		//Wraps the index so it doesn't go off the end
		i++;
		if (i >= defenderUnits.size() - 1)
		{
			i = 0;
			if (debug) { cout << "Wrapped defender casualty assignment loop" << endl; }
		}
	}
	if (output)
	{
		cout << "Defender Soldier Casualties: " << assignedSoldierCasualties << endl;
		cout << "Defender Upgrades: " << assignedUnitCasualties << endl;
		cout << "Defender General is " << outputGenState(totalCasualties[1][3]) << endl;
	}

	vector<Unit> defenderUnitsWithCasualties = {};
	for (int i = 0; i < defenderUnits.size() - 1; i++)
	{
		if (defenderUnits[i].getSoldiersPerUnit() > 0)
		{
			defenderUnitsWithCasualties.push_back(defenderUnits[i]);
		}
	}
	defender.setPlayerUnits(defenderUnitsWithCasualties);


	if (debug) { cout << "Battle::battleOutput finished" << endl; }
	return;
}

float Battle::battleCalculate() //contains the base calculations needed for battles
{
	//Comparing these at the end will determine victory/draw/defeat in relation to the attacker
	//The defTotal is subtracted from the attTotal, thus a positive result is a victory for the attacker,
	//and the opposite for a negative result
	float attTotal = 0;
	float defTotal = 0;
	//Adds units + portions of reinforcements
	attTotal += attacker.getCavalry() + attacker.getMelee() + attacker.getRanged();
	if (debug) { cout << "attacker unit sum:" << attTotal << " Battle::battleCalculate" << endl; }
	defTotal += defender.getCavalry() + defender.getMelee() + defender.getRanged();
	if (debug) { cout << "defender unit sum:" << defTotal << " Battle::battleCalculate" << endl; }

	//Adds random values to randomize the battle outcome more
	attTotal += calculateBattleRandoms(10, 10) / 6;
	if (debug) { cout << "attacker sum with randoms:" << attTotal << " Battle::battleCalculate" << endl; }
	defTotal += calculateBattleRandoms(10, 10) / 6;
	if (debug) { cout << "defender sum with randoms:" << defTotal << " Battle::battleCalculate" << endl; }

	//Adds rank and autoresolve bonuses from generals
	attTotal += attacker.getGeneral().getRank();
	if (debug) { cout << "attacker sum with general:" << attTotal << " Battle::battleCalculate" << endl; }
	defTotal += defender.getGeneral().getRank();
	if (debug) { cout << "defender sum with general:" << defTotal << " Battle::battleCalculate" << endl; }
	attTotal += attacker.getGeneral().getARBonus();
	if (debug) { cout << "attacker sum with general autobonus: " << attTotal << " Battle::battleCalculate" << endl; }
	defTotal += defender.getGeneral().getARBonus();
	if (debug) { cout << "defender sum with general autobonus: " << defTotal << " Battle::battleCalculate" << endl; }

	//Adds R-P-S stuff to attacker, but not defender so the difference isn't added twice
	attTotal += (attacker.getCavalry() - defender.getRanged()) * 1.5;
	if (debug) { cout << "attacker sum with cav-ran RPS:" << attTotal << " Battle::battleCalculate" << endl; }
	attTotal += (attacker.getMelee() - defender.getCavalry()) * 1.5;
	if (debug) { cout << "attacker sum with mel-cav RPS:" << attTotal << " Battle::battleCalculate" << endl; }
	attTotal += (attacker.getRanged() - defender.getMelee()) * 1.5;
	if (debug) { cout << "attacker sum with ran-mel RPS:" << attTotal << " Battle::battleCalculate" << endl; }

	if (debug) { cout << "Battle::battleCalculate finished, returned: " << attTotal - defTotal << endl; }
	return (attTotal - defTotal);
}

void Battle::CalculateCas(vector<vector<int>>& totalCasualties) //calculates the casualties from a battle and returns in a specific format
{
	int attSoldierCasualties = 0;
	int defSoldierCasualties = 0;

	int attGenWound = 0;
	int defGenWound = 0;
	int attSoldierTotal = 0;
	int defSoldierTotal = 0;
	//Totals the amount of soldiers in the armies
	for (int i = 0; i < attacker.getPlayerUnits().size(); i++) //TODO redo how this gets the total soldiers; make it be a class fn and not have to loop here
	{
		attSoldierTotal += attacker.getPlayerUnits()[i].getSoldiersPerUnit();
	}
	for (int i = 0; i < defender.getPlayerUnits().size(); i++)
	{
		defSoldierTotal += defender.getPlayerUnits()[i].getSoldiersPerUnit();
	}

	if (debug) { cout << "attacker soldier total: " << attSoldierTotal << " Battle::CalculateCas" << endl; }
	if (debug) { cout << "defender soldier total: " << defSoldierTotal << " Battle::CalculateCas" << endl; }

	//Uses the value of the outcome to determine the amount of casualties that will be taken
	attSoldierCasualties = calculateBattleRandoms(((int)result + 1), attSoldierTotal / 10);
	if (debug) { cout << "attacker soldier casualty total: " << attSoldierCasualties << " Battle::CalculateCas" << endl; }
	defSoldierCasualties = calculateBattleRandoms((9 - (int)result), defSoldierTotal / 10);
	if (debug) { cout << "defender soldier casualty total: " << defSoldierCasualties << " Battle::CalculateCas" << endl; }

	//Calculates the amounts of upgrades received; they are used in the campaign
	int attUpgr = defSoldierCasualties / 6;
	if (debug) { cout << "attacker upgrade total: " << attUpgr << " Battle::CalculateCas" << endl; }
	int defUpgr = attSoldierCasualties / 6;
	if (debug) { cout << "defender upgrade total: " << defUpgr << " Battle::CalculateCas" << endl; }

	//Calculates the amount of units that are destroyed
	int attUnitCasualties = (attSoldierCasualties / 7) - 1;
	if (debug) { cout << "attacker unit casualty total: " << attUnitCasualties << " Battle::CalculateCas" << endl; }
	int defUnitCasualties = (defSoldierCasualties / 7) - 1;
	if (debug) { cout << "defender unit casualty total: " << defUnitCasualties << " Battle::CalculateCas" << endl; }

	//Determines whether or not either of the generals are wounded/killed
	if (randomNumber(10) < 2)
	{
		attGenWound = 1;
		if (debug) { cout << "attacker General state set to 1(Wounded) Battle::CalculateCas" << endl; }
		if (randomNumber(10) < 2)
		{
			attGenWound = 2;
			if (debug) { cout << "attacker General state set to 2(Slain) Battle::CalculateCas" << endl; }
		}
	}
	else { if (debug) { cout << "attacker General unharmed" << endl; } }
	if (randomNumber(10) < 2)
	{
		defGenWound = 1;
		if (debug) { cout << "defender General state set to 1(Wounded) Battle::CalculateCas" << endl; }
		if (randomNumber(10) < 2)
		{
			defGenWound = 2;
			if (debug) { cout << "defender General state set to 2(Slain) Battle::CalculateCas" << endl; }
		}
	}
	else { if (debug) { cout << "defender General unharmed" << endl; } }
	//Creates the vectors that contain the casualty data
	vector<int> attackerCasVec{ attSoldierCasualties, attUnitCasualties, attUpgr, attGenWound };
	if (debug) { cout << "Attacker Casualty vector initialized Battle::CalculateCas" << endl; }
	vector<int> defenderCasVec{ defSoldierCasualties, defUnitCasualties, defUpgr, defGenWound };
	if (debug) { cout << "Defender Casualty vector initialized Battle::CalculateCas" << endl; }
	totalCasualties = { attackerCasVec, defenderCasVec };
	if (debug) { cout << "Overall Casualty vector initialized Battle::CalculateCas" << endl; }
	return;
}

class SiegeBattle : public Battle
{
private:
	int rams;
	int catapults;
	int siegeTowers;
	townStats townLevel;

public:

	SiegeBattle();
	SiegeBattle(Player attackerI, Player defenderI, int ramsI, int catapultsI, int siegeTowersI, townStats townLevelI);

	void SiegeOutput(vector<vector<int>> totalCasualties);
	void calculateSiege();

	int getRams() { return rams; };
	int getCatapults() { return catapults; };
	int getSiegeTowers() { return siegeTowers; };
	townStats& getTownStats() { return townLevel; };

	void setRams(int ramsI) { rams = ramsI; };
	void setCatapults(int catapultsI) { catapults = catapultsI; };
	void setSiegeTowers(int siegeTowersI) { siegeTowers = siegeTowersI; };
	void setTownLevel(int townLevelI) { townLevel = townLevelI; };
};

SiegeBattle::SiegeBattle() //void initializer
{
	attacker = Player();
	defender = Player();
	rams = 0;
	catapults = 0;
	siegeTowers = 0;
	townLevel = townStats();
	result = outcome::Draw;
}

SiegeBattle::SiegeBattle(Player attackerI, Player defenderI, int ramsI, int catapultsI, int siegeTowersI, townStats townLevelI) // initializer
{
	rams = ramsI;
	catapults = catapultsI;
	siegeTowers = siegeTowersI;
	townLevel = townLevelI;
	attacker = attackerI;
	defender = defenderI;
	result = outcome::Draw;
}

void SiegeBattle::calculateSiege() //combines base Battle calculation with the extras needed for Siege Battles, then calls output
{
	float overallTot = battleCalculate();
	if (debug) { cout << "Overall total returned from battleCalculate SiegeBattle::calculateSiege" << endl; }

	//Siege Battle-specific calculations
	overallTot -= (townLevel.getLevel() * 10) - 10;
	if (debug) { cout << "Overall total - (townLevel(" << townLevel.getLevel() << ") * 10) -10 SiegeBattle::calculateSiege" << endl; }
	overallTot += rams * 2;
	if (debug) { cout << "Overall total + rams(" << rams << ")*2 SiegeBattle::calculateSiege" << endl; }
	overallTot += catapults * 3;
	if (debug) { cout << "Overall total + catapults(" << catapults << ") * 3 SiegeBattle::calculateSiege" << endl; }
	overallTot += siegeTowers * 4;
	if (debug) { cout << "Overall total + siegeTowers(" << siegeTowers << ") * 4 SiegeBattle::calculateSiege" << endl; }

	//Determines the outcome and calculates the casualties
	result = determineOutcome(overallTot);
	if (debug) { cout << "Outcome returned from determineOutcome:" << result << " SiegeBattle::calculateSiege" << endl; }
	vector<vector<int>> totalCasualties = {};
	CalculateCas(totalCasualties);
	if (debug) { cout << "CalculateCas called SiegeBattle::calculateSiege" << endl; }

	SiegeOutput(totalCasualties);
	if (debug) { cout << "SiegeBattle::calculateSiege finished" << endl; }
}

void SiegeBattle::SiegeOutput(vector<vector<int>> totalCasualties) //uses base Battle output and adds Siege outputs
{
	if (debug) { cout << "Calling battleOutput, SiegeBattle::SiegeOutput" << endl; }
	battleOutput(totalCasualties);

	if (output)
	{
		if ((int)result < 4)
		{
			cout << "The settlement was taken by the attackers." << endl;
			cout << "The defending army/garrison has been completely destroyed." << endl;
		}
		else
		{
			cout << "The settlement was successfully held by the defenders" << endl;
		}
	}
	if (debug) { cout << "SiegeBattle::SiegeOutput finished" << endl; }
	return;
}

class RaidBattle : public Battle
{
private:
	townStats townLevel;


public:

	RaidBattle();
	RaidBattle(Player attackerI, Player defenderI, townStats townLevelI);

	void raidOutput(vector<vector<int>> totalCasualties, int suppGained);
	void calculateRaid();

	townStats& getTownStats() { return townLevel; };

	void setTownLevel(int townLevelI) { townLevel = townLevelI; };
};

RaidBattle::RaidBattle() //void initializer
{
	attacker = Player();
	defender = Player();
	townLevel = townStats();
	result = outcome::Draw;
}

RaidBattle::RaidBattle(Player attackerI, Player defenderI, townStats townLevelI) // initializer
{
	attacker = attackerI;
	defender = defenderI;
	townLevel = townLevelI;
	result = outcome::Draw;
}

void RaidBattle::calculateRaid() //combines base Battle calculation with the extras needed for Raid Battles, then calls output
{
	float overallTot = battleCalculate();
	if (debug) { cout << "Overall total returned from battleCalculate RaidBattle::calculateRaid" << endl; }
	overallTot -= ((townLevel.getLevel() * 10) - 10);
	if (debug) { cout << "Overall total - (townLevel(" << townLevel.getLevel() << ") * 10) -10 RaidBattle::calculateRaid" << endl; }

	//Finds outcome and gets casualties
	result = determineOutcome(overallTot);
	if (debug) { cout << "Outcome returned from determineOutcome:" << result << " RaidBattle::calculateRaid" << endl; }
	vector<vector<int>> totalCasualties = {};
	CalculateCas(totalCasualties);
	if (debug) { cout << "CalculateCas called RaidBattle::calculateRaid" << endl; }

	//determines number of supplies gained
	int suppliesGained = townLevel.getSupplies() / (int)result;
	if (debug) { cout << "Supplies gained: " << suppliesGained << "RaidBattle::calculateRaid" << endl; }

	//Outputs results from battle
	raidOutput(totalCasualties, suppliesGained);
	if (debug) { cout << "RaidBattle::calculateRaid finished" << endl; }
	return;
}

void RaidBattle::raidOutput(vector<vector<int>> totalCasualties, int suppGained) //uses base Battle output and adds Raid outputs
{
	if (debug) { cout << "Calling battleOutput, RaidBattle::raidOutput" << endl; }
	battleOutput(totalCasualties);
	if (output)
	{
		cout << "Attacker supplies gained: " << suppGained << endl;
	}
	if (debug) { cout << "RaidBattle::raidOutput finished" << endl; }
	return;
}

class NavalBattle : public Battle
{
private:
	int attackerShips;
	int defenderShips;

public:

	NavalBattle();
	NavalBattle(Player attackerI, Player defenderI, int attShipsI, int defShipsI);

	void navalOutput(vector<vector<int>> totalCasualties);
	void calculateNaval();

	int getAttackerShips() { return attackerShips; };
	int getDefenderShips() { return defenderShips; };

	void setAttackerShips(int attShipsI) { attackerShips = attShipsI; };
	void setDefenderShips(int defShipsI) { defenderShips = defShipsI; };
};

NavalBattle::NavalBattle() //void initializer
{
	attacker = Player();
	defender = Player();
	attackerShips = 0;
	defenderShips = 0;
	result = outcome::Draw;
}

NavalBattle::NavalBattle(Player attackerI, Player defenderI, int attShipsI, int defShipsI) //initializer
{
	attackerShips = attShipsI;
	defenderShips = defShipsI;
	attacker = attackerI;
	defender = defenderI;
	result = outcome::Draw;
}

void NavalBattle::navalOutput(vector<vector<int>> totalCasualties) //uses base Battle output and adds naval outputs
{
	if (debug) { cout << "Calling battleOutput, NavalBattle::NavalOutput" << endl; }
	battleOutput(totalCasualties);
	if (output)
	{
		cout << "Attacker Ship Cas: " << totalCasualties[0][1] - 1 << endl;
		cout << "Defender Ship Cas " << totalCasualties[1][1] - 1 << endl;
	}
	this->attackerShips = totalCasualties[0][1] - 1;
	this->defenderShips = totalCasualties[1][1] - 1;
	if (debug) { cout << "NavalBattle::navalOutput finished" << endl; }
	return;
}

void NavalBattle::calculateNaval() //combines base Battle calculation with the extras needed for Naval Battles, then calls output
{
	if (debug) { cout << "Calling battleCalculate, NavalBattle::calculateNaval" << endl; }
	//Uses base calculations and adds Naval Battle calculations
	float overallTot = battleCalculate();
	if (debug) { cout << "Overall total returned from battleCalculate NavalBattle::calculateNaval" << endl; }
	overallTot += attackerShips * 3;
	if (debug) { cout << "Overall total + attacker ships(" << attackerShips << ")*3 NavalBattle::calculateNaval" << endl; }
	overallTot -= defenderShips * 3;
	if (debug) { cout << "Overall total defender ships(" << defenderShips << ")*3 NavalBattle::calculateNaval" << endl; }

	//Gets the outcome and calculates the casualties
	result = determineOutcome(overallTot);
	if (debug) { cout << "Outcome returned from determineOutcome:" << result << " NavalBattle::calculateNaval" << endl; }
	vector<vector<int>> totalCasualties = {};
	CalculateCas(totalCasualties);
	if (debug) { cout << "CalculateCas called NavalBattle::calculateNaval" << endl; }

	//Calls output function
	navalOutput(totalCasualties);
	if (debug) { cout << "NavalBattle::calculateNaval finished" << endl; }
	return;
}

class NormalBattle : public Battle
{
private:

public:

	NormalBattle();
	NormalBattle(Player attackerI, Player defenderI);

	void normalOutput(vector<vector<int>> totalCasualties);
	void calculateNormal();
	//Needs no specific getters and setters
};

NormalBattle::NormalBattle() //void initializer
{
	attacker = Player();
	defender = Player();
	result = outcome::Draw;
}

NormalBattle::NormalBattle(Player attackerI, Player defenderI) //initializer
{
	attacker = attackerI;
	defender = defenderI;
	result = outcome::Draw;
}

void NormalBattle::calculateNormal() //Uses base battle calculations and output
{
	if (debug) { cout << "Calling battleCalculate, NormalBattle::calculateNormal" << endl; }
	float overallTot = battleCalculate();
	if (debug) { cout << "Overall total returned from battleCalculate NormalBattle::calculateNormal" << endl; }

	//Finds result and determines casualties
	result = determineOutcome(overallTot);
	if (debug) { cout << "Outcome returned from determineOutcome:" << result << " NormalBattle::calculateNormal" << endl; }
	vector<vector<int>> totalCasualties = {};
	CalculateCas(totalCasualties);
	if (debug) { cout << "CalculateCas called NormalBattle::calculateNormal" << endl; }

	if (debug) { cout << "calling NormalOutput NormalBattle::calculateNormal" << endl; }
	normalOutput(totalCasualties);
	if (debug) { cout << "NormalBattle::calculateNormal finished" << endl; }
	return;
}

void NormalBattle::normalOutput(vector<vector<int>> totalCasualties) //Uses base battle output
{
	if (debug) { cout << "Calling battleOutput, NormalBattle::normalOutput" << endl; }
	battleOutput(totalCasualties);
	if (debug) { cout << "NormalBattle::normalOutput finished" << endl; }
	return;
}

class MonsterBattle //This is the only type of battle that does NOT inherit from the Battle class
{
private:
	Player attacker;
	Monster monster;
	outcome result;
	bool output;
	bool debug;

public:

	MonsterBattle();
	MonsterBattle(Player attackerI, Monster monsterI);

	void monsterOutput(vector<int>& totalCasualties);
	void monsterCasualties(vector<int>& attackerCasVec); //Calculates the casualties, needs only a 1D vector since there is only 1 Player
	void calculateMonster(); //Calculates the outcome and calls Casualty and output functions

	int getEnding() { return (int)result; };
	Player& getPlayer() { return attacker; };
	Monster& getMonster() { return monster; };
	outcome& getOutcome() { return result; };
	bool getOutputBool() { return output; };
	bool getDebugBool() { return debug; };

	void setPlayer(Player playerI) { attacker = playerI; };
	void setMonster(Monster monsterI) { monster = monsterI; };
	void setOutcome(outcome resultI) { result = resultI; };
	void setOutput(bool outputI) { output = outputI; };
	void setDebugBool(bool debugI) { debug = debugI; };
};

MonsterBattle::MonsterBattle() //void initializer
{
	attacker = Player();
	monster = Monster();
	result = outcome::Draw;
	output = true;
	debug = false;
}

MonsterBattle::MonsterBattle(Player attackerI, Monster monsterI) //initializer
{
	attacker = attackerI;
	monster = monsterI;
	result = outcome::Draw;
	output = true;
	debug = false;
}

void MonsterBattle::monsterOutput(vector<int>& totalCasualties) //Outputs information at the end of the Monster battle
{
	if (debug) { cout << "Calling battleOutput, MonsterBattle::monsterOutput" << endl; }
	if (output)
	{
		cout << result << endl
			<< "Attacker Soldier Cas: " << totalCasualties[0] << endl
			<< "Attacker Unit Cas: " << totalCasualties[1] << endl
			<< "Attacker General is " << outputGenState(totalCasualties[2]) << endl;
		if ((int)result < 4)
		{
			cout << "Coins gained: " << monster.getCoinReward() << endl;
		}
	}
	if (debug) { cout << "MonsterBattle::monsterOutput finished" << endl; }
	return;
}

void MonsterBattle::monsterCasualties(vector<int>& attackerCasVec) //Calculates the casualties
{

	int attSoldierCasualties = 0;
	int attGenWound = 0;
	int attSoldierTotal = attacker.getCavalry() + attacker.getMelee() + attacker.getRanged();
	if (debug) { cout << "Attacking soldier total:" << attSoldierTotal << " MonsterBattle::monsterCasualties" << endl; }
	//Calculates the soldier and unit casualties
	attSoldierCasualties = calculateBattleRandoms(((int)result + 1), attSoldierTotal / 10);
	if (debug) { cout << "Attacking soldier casualties:" << attSoldierCasualties << " MonsterBattle::monsterCasualties" << endl; }
	int attUnitCasualties = attSoldierCasualties / 7 - 1;
	if (debug) { cout << "Attacking unit casualties:" << attUnitCasualties << " MonsterBattle::monsterCasualties" << endl; }

	//Determines if the general is wounded or killed
	if (debug) { cout << "Attacking soldier total:" << attSoldierTotal << " MonsterBattle::monsterCasualties" << endl; }
	if (randomNumber(10) < 2)
	{
		attGenWound = 1;
		if (debug) { cout << "General State set to 1(Wounded) MonsterBattle::monsterCasualties" << endl; }
		if (randomNumber(10) < 2)
		{
			attGenWound = 2;
			if (debug) { cout << "General State set to 2(Slain) MonsterBattle::monsterCasualties" << endl; }
		}
	}


	attackerCasVec = { attSoldierCasualties, attUnitCasualties, attGenWound };
	if (debug) { cout << "Attacker casualty vector initialized MonsterBattle::monsterCasualties" << endl; }
	if (debug) { cout << "MonsterBattle::monsterCasualties finished" << endl; }
	return;
}

void MonsterBattle::calculateMonster()
{
	//Comparing these at the end will determine victory/draw/defeat in relation to the attacker
	//The monTotal is subtracted from the attTotal, thus a positive result is a victory for the attacker,
	//and the opposite for a negative result
	float attTotal = 0;
	float monTotal = 0;

	//Adds units + portions of reinforcements
	attTotal += attacker.getCavalry() + attacker.getMelee() + attacker.getRanged();
	if (debug) { cout << "attacker unit sum:" << attTotal << " MonsterBattle::calculateMonster" << endl; }


	//Adds random values to randomize the battle outcome more
	attTotal += calculateBattleRandoms(10, 10);
	if (debug) { cout << "attacker sum with randoms:" << attTotal << " MonsterBattle::calculateMonster" << endl; }
	monTotal += calculateBattleRandoms(10, 10);
	if (debug) { cout << "monster sum with randoms:" << monTotal << " MonsterBattle::calculateMonster" << endl; }

	//Adds rank and autoresolve bonuses from general and monster
	attTotal += attacker.getGeneral().getRank();
	if (debug) { cout << "attacker sum with general: " << attTotal << " MonsterBattle::calculateMonster" << endl; }
	attTotal += attacker.getGeneral().getARBonus();
	if (debug) { cout << "attacker sum with general autobonus: " << attTotal << " MonsterBattle::calculateMonster" << endl; }
	monTotal += monster.getARValue();
	if (debug) { cout << "monster sum with monster autobonus: " << monTotal << " MonsterBattle::calculateMonster" << endl; }

	//Determines outcome and casualties then calls output function
	result = determineOutcome(attTotal - monTotal);
	if (debug) { cout << "Outcome returned from determineOutcome:" << result << " MonsterBattle::calculateMonster" << endl; }
	vector<int> casualty{};
	monsterCasualties(casualty);
	if (debug) { cout << "monsterCasualties called MonsterBattle::calculateMonster" << endl; }
	monsterOutput(casualty);
	if (debug) { cout << "MonsterBattle::calculateMonster finished" << endl; }
	return;
}

//This outputs the results from a vector of battle results and also some statistics about them
void predictionOutput(vector<int> rawResults)
{
	//This makes a vector and fills it with the number of times an outcome is found in the vector that is passed in
	vector<int> processedResults{ 0,0,0,0,0,0,0 };
	int i = 0;
	while (i < rawResults.size())
	{
		processedResults[rawResults[i] - 1]++;
		i++;
	}

	//Outputs results
	i = 0;
	while (i < processedResults.size())
	{
		cout << "Results Processed at " << i << ": " << processedResults[i] << " : ";
		outputIntAsOutcome(i + 1);
		cout << endl;
		i++;
	}

	//Makes some floats that are used in statistics output below
	float success = (processedResults[0] + processedResults[1] + processedResults[2]);
	float total = (processedResults[0] + processedResults[1] + processedResults[2] + processedResults[3] + processedResults[4] + processedResults[5] + processedResults[6]);
	float victory = success / total;
	float draw = processedResults[3] / total;
	float loss = (1 - (draw + victory));

	cout << "Percent Victory: " << victory * 100 << endl;
	cout << "Percent Draw: " << draw * 100 << endl;
	cout << "Percent Loss: " << loss * 100 << endl;
	if (loss == 0)
	{
		cout << "Win - loss ratio: " << victory / .01 << endl;
	}
	else
	{
		cout << "Win - loss ratio: " << (victory / loss) << endl;
	}
	return;
}

void testSetup(Battle& battle, bool debug)
{
	Treasure stuff{};
	stuff.setDebugBool(debug);
	stuff.initializeTreasure();

	Equipment equip{};
	equip.setDebugBool(debug);
	equip = stuff.findArmor();
	General attackerGen{ 10,equip,equip,equip,equip,equip };
	attackerGen.setDebugBool(debug);
	faction attFac = faction::beladimir;
	Roster beladimirRoster{};
	beladimirRoster.setDebugBool(debug);
	beladimirRoster.setFaction(attFac);
	beladimirRoster.buildRoster();

	int size = beladimirRoster.getNumberOfUnits();
	if (debug) { cout << "size of beladimir roster: " << size << endl; }
	vector<Unit> units{};
	Unit read{};
	int randomIndex;
	for (int i = 1; i < 20; i++)
	{
		randomIndex = randomNumberCas(size - 1);
		if (debug) { cout << "randomIndex generated: " << randomIndex << endl; }
		read = beladimirRoster.getUnitAtIndex(randomIndex);
		if (debug) { cout << "Unit grabbed: " << read.getName() << endl; }
		units.push_back(read);
	}
	Player attacker{};
	attacker.setDebugBool(debug);
	attacker.setFaction(attFac);
	attacker.setGeneralG(attackerGen);
	attacker.setAdvCombatDeck(false);
	attacker.setReinforcements(10);
	attacker.setPlayerUnits(units);

	battle.setAttacker(attacker);
	if (debug) { cout << "Battle attacker set to attacker " << endl; }
	battle.setDefender(attacker);
	if (debug) { cout << "Battle defender set to attacker " << endl; }
	return;
}

//These 5 functions below are overloaded. They create a vector of results from creating and calculating battles with basic information
//that is then sent to predictionOutput()
void battleTest(int tests, NormalBattle& battle, bool debug)
{
	testSetup(battle, debug);
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		if (debug) { cout << "Testing once, calling calculate normal" << endl; }
		battle.calculateNormal();
		if (debug) { cout << "calculateNormal finished" << endl; }
		resultsRaw.push_back((int)battle.getEnding());
		if (debug) { cout << "ResultsRaw pushed: " << battle.getEnding() << endl; }
		cout << "Normal Battle results:" << endl;
		if (debug) { cout << "Attacker units in vector: " << battle.getAttacker().getPlayerUnits().size() << endl; }
		if (debug) { cout << "Defender units in vector: " << battle.getDefender().getPlayerUnits().size() << endl; }
		predictionOutput(resultsRaw);
	}
	else
	{

		for (int i = 0; i < tests; i++)
		{
			NormalBattle norm = battle;
			norm.setOutput(debug);
			norm.setDebug(debug);
			norm.calculateNormal();
			resultsRaw.push_back((int)norm.getEnding());
			if (debug) { cout << "ResultsRaw pushed: " << norm.getEnding() << endl; }
		}
		cout << "Normal Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}

void battleTest(int tests, SiegeBattle& battle, bool debug)
{
	testSetup(battle, debug);

	battle.setCatapults(5);
	if (debug) { cout << "Catapults set to 5 " << endl; }
	battle.setRams(5);
	if (debug) { cout << "Rams attacker set to 5 " << endl; }
	battle.setSiegeTowers(5);
	if (debug) { cout << "Siege towers attacker set to 5 " << endl; }
	battle.setTownLevel(5);
	if (debug) { cout << "town level set to 5 " << endl; }
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		if (debug) { cout << "Testing once, calling calculate siege" << endl; }
		battle.calculateSiege();
		if (debug) { cout << "calculateSiege finished" << endl; }
		resultsRaw.push_back((int)battle.getEnding());
		if (debug) { cout << "ResultsRaw pushed: " << battle.getEnding() << endl; }
		cout << "Siege Battle results:" << endl;
		if (debug) { cout << "Attacker units in vector: " << battle.getAttacker().getPlayerUnits().size() << endl; }
		if (debug) { cout << "Defender units in vector: " << battle.getDefender().getPlayerUnits().size() << endl; }
		predictionOutput(resultsRaw);
	}
	else
	{

		for (int i = 0; i < tests; i++)
		{
			SiegeBattle norm = battle;
			norm.setOutput(debug);
			norm.setDebug(debug);
			norm.calculateSiege();
			resultsRaw.push_back((int)norm.getEnding());
			if (debug) { cout << "ResultsRaw pushed: " << norm.getEnding() << endl; }
		}
		cout << "Siege Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}

void battleTest(int tests, RaidBattle& battle, bool debug)
{
	testSetup(battle, debug);
	battle.setTownLevel(5);
	if (debug) { cout << "town level set to 5 " << endl; }
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		if (debug) { cout << "Testing once, calling calculate raid" << endl; }
		battle.calculateRaid();
		if (debug) { cout << "calculateSiege finished" << endl; }
		resultsRaw.push_back((int)battle.getEnding());
		if (debug) { cout << "ResultsRaw pushed: " << battle.getEnding() << endl; }
		cout << "raid Battle results:" << endl;
		if (debug) { cout << "Attacker units in vector: " << battle.getAttacker().getPlayerUnits().size() << endl; }
		if (debug) { cout << "Defender units in vector: " << battle.getDefender().getPlayerUnits().size() << endl; }
		predictionOutput(resultsRaw);
	}
	else
	{

		for (int i = 0; i < tests; i++)
		{
			RaidBattle norm = battle;
			norm.setOutput(debug);
			norm.setDebug(debug);
			norm.calculateRaid();
			resultsRaw.push_back((int)norm.getEnding());
			if (debug) { cout << "ResultsRaw pushed: " << norm.getEnding() << endl; }
		}
		cout << "Raid Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;

}

void battleTest(int tests, NavalBattle& battle, bool debug)
{
	testSetup(battle, debug);
	battle.setAttackerShips(10);
	battle.setDefenderShips(10);
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		if (debug) { cout << "Testing once, calling calculate naval" << endl; }
		battle.calculateNaval();
		if (debug) { cout << "calculateNaval finished" << endl; }
		resultsRaw.push_back((int)battle.getEnding());
		if (debug) { cout << "ResultsRaw pushed: " << battle.getEnding() << endl; }
		cout << "Naval Battle results:" << endl;
		if (debug) { cout << "Attacker units in vector: " << battle.getAttacker().getPlayerUnits().size() << endl; }
		if (debug) { cout << "Defender units in vector: " << battle.getDefender().getPlayerUnits().size() << endl; }
		predictionOutput(resultsRaw);
	}
	else
	{

		for (int i = 0; i < tests; i++)
		{
			NavalBattle norm = battle;
			norm.setOutput(debug);
			norm.setDebug(debug);
			norm.calculateNaval();
			resultsRaw.push_back((int)norm.getEnding());
			if (debug) { cout << "ResultsRaw pushed: " << norm.getEnding() << endl; }
		}
		cout << "Naval Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}

void battleTest(int tests, MonsterBattle& battle, bool debug)
{
	Treasure stuff{};
	stuff.setDebugBool(debug);
	stuff.initializeTreasure();

	Equipment equip{};
	equip.setDebugBool(debug);
	equip = stuff.findArmor();
	General attackerGen{ 10,equip,equip,equip,equip,equip };
	attackerGen.setDebugBool(debug);
	faction attFac = faction::beladimir;
	Roster beladimirRoster{};
	beladimirRoster.setDebugBool(debug);
	beladimirRoster.setFaction(attFac);
	beladimirRoster.buildRoster();

	int size = beladimirRoster.getNumberOfUnits();
	if (debug) { cout << "size of beladimir roster: " << size << endl; }
	vector<Unit> units{};
	Unit read{};
	int randomIndex;
	for (int i = 1; i < 20; i++)
	{
		randomIndex = randomNumberCas(size - 1);
		if (debug) { cout << "randomIndex generated: " << randomIndex << endl; }
		read = beladimirRoster.getUnitAtIndex(randomIndex);
		if (debug) { cout << "Unit grabbed: " << read.getName() << endl; }
		units.push_back(read);
	}
	Player attacker{};
	attacker.setDebugBool(debug);
	attacker.setFaction(attFac);
	attacker.setGeneralG(attackerGen);
	attacker.setAdvCombatDeck(false);
	attacker.setReinforcements(10);
	attacker.setPlayerUnits(units);

	battle.setPlayer(attacker);
	battle.setMonster(monsterType::Dragon);
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		if (debug) { cout << "Testing once, calling calculate monster" << endl; }
		battle.calculateMonster();
		if (debug) { cout << "calculateMonster finished" << endl; }
		resultsRaw.push_back((int)battle.getEnding());
		if (debug) { cout << "ResultsRaw pushed: " << battle.getEnding() << endl; }
		cout << "Monster Battle results:" << endl;
		if (debug) { cout << "Attacker units in vector: " << battle.getPlayer().getPlayerUnits().size() << endl; }
		predictionOutput(resultsRaw);
	}
	else
	{

		for (int i = 0; i < tests; i++)
		{
			MonsterBattle norm = battle;
			norm.setOutput(debug);
			norm.setDebugBool(debug);
			norm.calculateMonster();
			resultsRaw.push_back((int)norm.getEnding());
			if (debug) { cout << "ResultsRaw pushed: " << norm.getEnding() << endl; }
		}
		cout << "Monster Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}


//Called on program start. At the moment, it only predicts the results from each kind of battle.
int main()
{
	bool debug = true;
	if (debug) { cout << "Program started" << endl; }

	//initializes seed for random number generation
	myseed = myclock::now().time_since_epoch().count();
	generator.seed(myseed);
	if (debug) { cout << "Time-based seed for random numbers initialized" << endl; }

	NormalBattle normal{};
	if (debug) { cout << "Normal battle initialized void" << endl; }
	SiegeBattle siege{};
	if (debug) { cout << "Siege battle initialized void" << endl; }
	RaidBattle raid{};
	if (debug) { cout << "Raid battle initialized void" << endl; }
	NavalBattle naval{};
	if (debug) { cout << "Naval battle initialized void" << endl; }
	MonsterBattle monster{};
	if (debug) { cout << "Monster battle initialized void" << endl; }
	int tests = 100;
	if (debug) { cout << "Tests set to: " << tests << endl; }

	//battleTest(tests, normal, debug);
	if (debug) { cout << "Tested Normal battle" << endl; }
	//battleTest(tests,siege, debug);
	if (debug) { cout << "Tested Siege battle" << endl; }
	//battleTest(tests,raid, debug);
	if (debug) { cout << "Tested Raid battle" << endl; }
	//battleTest(tests, naval, debug);
	if (debug) { cout << "Tested Naval battle" << endl; }
	battleTest(tests, monster, debug);
	if (debug) { cout << "Tested Monster battle" << endl; }

	if (debug) { cout << "Program finished" << endl; }

	return 0;
}
