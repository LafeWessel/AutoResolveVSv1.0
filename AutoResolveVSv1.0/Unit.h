#pragma once
#include "faction.h"
#include "unitType.h"
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
class Unit
{
private:
	string name;
	int autoResBonus;
	int soldiersPerUnit;
	faction fact;
	unitType type;


public:
	~Unit();
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