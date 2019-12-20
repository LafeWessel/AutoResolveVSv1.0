#pragma once
#include "faction.h"
#include "unitType.h"
#include <algorithm>
#include <cmath>

//#include <array>
//#include <vector>
#include <string>

//#include <fstream>
//#include <iostream>
//#include <sstream>
//#include <stdexcept>
using namespace std;
class Unit
{
private:
	string name;
	int autoResBonus;
	int soldiersPerUnit;
	int currentSoldiers;
	faction fact;
	unitType type;
	bool debug;

public:
	~Unit();
	Unit();
	Unit(string nameI, int autoResBonusI, int soldiersPerUnitI, int currentSoldiersI, faction factI, unitType typeI);

	string& getName() { 
		if (debug) { cout << "unit name gotten" << endl; }
		return name;
	};
	int getARBonus() { 
		if (debug) { cout << "unit autoresolve bonus gotten" << endl; }
		return autoResBonus * (currentSoldiers/soldiersPerUnit); 
	};
	int getSoldiersPerUnit() { 
		if (debug) { cout << "unit number of soldiers per unit gotten" << endl; }
		return soldiersPerUnit;
	};
	int getCurrentSoldiers() {
		if (debug) { cout << "unit current soldiers gotten" << endl; }
		return currentSoldiers;
	};
	faction getFaction() {
		if (debug) { cout << "unit faction gotten" << endl; }
		return fact; 
	};
	unitType getUnitType() {
		if (debug) { cout << "unit type gotten" << endl; }
		return type;
	};

	void setName(string nameI) { 
		if (debug) { cout << "unit name set" << endl; }
		name = nameI;
	};
	void setARBonus(int ARBonusI) { 
		if (debug) { cout << "unit autoresolve bonus set" << endl; }
		autoResBonus = ARBonusI;
	};
	void setCurrentSoldiers(int currentSoldiersI) {
		if (debug) { cout << "unit current soldiers set" << endl; }
		currentSoldiers = currentSoldiersI;
	};
	void setSoldiersPerUnit(int soldiersPerUI) { 
		if (debug) { cout << "unit soldiers per unit set" << endl; }
		soldiersPerUnit = soldiersPerUI;
	};
	void setFaction(faction factI) { 
		if (debug) { cout << "unit faction set" << endl; }
		fact = factI;
	};
	void setUnitType(unitType typeI) {
		if (debug) { cout << "unit type set" << endl; }
		type = typeI; 
	};

	void setDebug(bool debugI) { debug = debugI; };
	bool getDebug() { return debug; };
};