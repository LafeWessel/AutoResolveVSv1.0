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
	int index;
	int range;
	equipmentType EquipType;
	string effect;
	int coinValue;
	bool debug;

public:
	~Equipment();
	Equipment(string nameI, int autoBonusI, int numberI, int rangeI, equipmentType EquipTypeI, string effectI, int coinValueI);
	Equipment();

	string getName() { 
		if (debug) { cout << "equipment name gotten" << endl; }
		return name; 
	};
	int getABonus() { 
		if (debug) { cout << "equipment autoresolve bonus gotten" << endl; }
		return autoBonus; 
	};
	int getIndex() { 
		if (debug) { cout << "equipment index gotten" << endl; }
		return index; 
	};
	int getRange() { 
		if (debug) { cout << "equipment range gotten" << endl; }
		return range; 
	};
	equipmentType getEqType() { 
		if (debug) { cout << "equipment type gotten" << endl; }
		return EquipType; 
	};
	string getEffect() { 
		if (debug) { cout << "equipment effect gotten" << endl; }
		return effect; 
	};
	int getCValue() { 
		if (debug) { cout << "equipment coin value gotten" << endl; }
		return coinValue; 
	};


	void setName(string nameI) { 
		if (debug) { cout << "equipment name set" << endl; }
		name = nameI; 
	};
	void setABonus(int autoBonusI) { 
		if (debug) { cout << "equipment autoresolve bonus set" << endl; }
		autoBonus = autoBonusI; 
	};
	void setIndex(int indexI) { 
		if (debug) { cout << "equipment index set" << endl; }
		index = indexI; 
	};
	void setRange(int rangeI) { 
		if (debug) { cout << "equipment range set" << endl; }
		range = rangeI; 
	};
	void setEqType(equipmentType equipTypeI) { 
		if (debug) { cout << "equipment type set" << endl; }
		EquipType = equipTypeI; 
	};
	void setEffect(string effectI) { 
		if (debug) { cout << "equipment effect set" << endl; }
		effect = effectI; 
	};
	void setCValue(int CValI) { 
		if (debug) { cout << "equipment coin value set" << endl; }
		coinValue = CValI; 
	};

	bool getDebug() { return debug; }
	void setDebug(bool debugI) { debug = debugI; }
};

