#pragma once
#include <algorithm>
#include <cmath>

#include <array>
#include <vector>
#include <string>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;
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
	~Equipment();
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

ostream& operator<<(ostream& os, Equipment& eqpt) //output operator for Equipment class
{
	return os << eqpt.getName() << endl
		<< "Effect: " << eqpt.getEffect() << endl
		<< "Range: " << eqpt.getRange() << endl
		<< "EquipType: " << eqpt.getEqType() << endl
		<< "Coin Value: " << eqpt.getCValue() << endl;
}