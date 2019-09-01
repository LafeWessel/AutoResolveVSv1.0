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


public:
	~Unit();
	Unit();
	Unit(string nameI, int autoResBonusI, int soldiersPerUnitI, int currentSoldiersI, faction factI, unitType typeI);

	string getName() { return name; };
	int getARBonus() { return autoResBonus * (currentSoldiers/soldiersPerUnit); };
	int getSoldiersPerUnit() { return soldiersPerUnit; };
	int getCurrentSoldiers() { return currentSoldiers; };
	faction& getFaction() { return fact; };
	unitType& getUnitType() { return type; };

	void setName(string nameI) { name = nameI; };
	void setARBonus(int ARBonusI) { autoResBonus = ARBonusI; };
	void setCurrentSoldiers(int currentSoldiersI) { currentSoldiers = currentSoldiersI; };
	void setSoldiersPerUnit(int soldiersPerUI) { soldiersPerUnit = soldiersPerUI; };
	void setFaction(faction factI) { fact = factI; };
	void setUnitType(unitType typeI) { type = typeI; };

};