#pragma once
#include "equipmentType.h"
#include <algorithm>
#include <cmath>

#include <array>
#include <vector>
#include <string>

//#include <fstream>
#include <iostream>
//#include <sstream>
//#include <stdexcept>
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
	equipmentType EquipType;
	string effect;
	int coinValue;
	bool debug;

public:
	~Equipment();
	Equipment(string nameI, int autoBonusI, int numberI, int rangeI, equipmentType EquipTypeI, string effectI, int coinValueI);
	Equipment();

	string getName() { return name; };
	int getABonus() { return autoBonus; };
	int getIndex() { return number; };
	int getRange() { return range; };
	equipmentType& getEqType() { return EquipType; };
	string getEffect() { return effect; };
	int getCValue() { return coinValue; };
	bool getDebug() { return debug; }

	void setName(string nameI) { name = nameI; };
	void setABonus(int autoBonusI) { autoBonus = autoBonusI; };
	void setIndex(int indexI) { number = indexI; };
	void setRange(int rangeI) { range = rangeI; };
	void setEqType(equipmentType equipTypeI) { EquipType = equipTypeI; };
	void setEffect(string effectI) { effect = effectI; };
	void setCValue(int CValI) { coinValue = CValI; };
	void setDebugBool(bool debugI) { debug = debugI; }
};

