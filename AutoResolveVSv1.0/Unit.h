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
	Unit(bool debugI);
	Unit(string nameI, int autoResBonusI, int soldiersPerUnitI, int currentSoldiersI, faction factI, unitType typeI);

	string getName() { 
		if (debug) { cout << "unit name gotten: " << name << endl; }
		return name;};
	int getARBonus() { 
		if (debug) { cout << "unit autoresolve bonus gotten: " << autoResBonus << endl; }
		return autoResBonus * (currentSoldiers/soldiersPerUnit); };
	int getSoldiersPerUnit() { 
		if (debug) { cout << "unit number of soldiers per unit gotten: " << soldiersPerUnit << endl; }
		return soldiersPerUnit;};
	int getCurrentSoldiers() {
		if (debug) { cout << "unit current soldiers gotten: " << currentSoldiers << endl; }
		return currentSoldiers;};
	faction getFaction() {
		if (debug) { cout << "unit faction gotten: " << (int)fact << endl; }
		return fact; };
	unitType getUnitType() {
		if (debug) { cout << "unit type gotten: " << (int)type << endl; }
		return type;};

	void setName(string nameI) { 
		if (debug) { cout << "unit name set to: "<< nameI << endl; }
		name = nameI;};
	void setARBonus(int ARBonusI) { 
		if (debug) { cout << "unit autoresolve bonus set to: " << ARBonusI << endl; }
		autoResBonus = ARBonusI;};
	void setCurrentSoldiers(int currentSoldiersI) {
		if (debug) { cout << "unit current soldiers set to: " << currentSoldiersI << endl; }
		currentSoldiers = currentSoldiersI;};
	void setSoldiersPerUnit(int soldiersPerUI) { 
		if (debug) { cout << "unit soldiers per unit set to: " << soldiersPerUI << endl; }
		soldiersPerUnit = soldiersPerUI;};
	void setFaction(faction factI) { 
		if (debug) { cout << "unit faction set to: " << (int)factI << endl; }
		fact = factI;};
	void setUnitType(unitType typeI) {
		if (debug) { cout << "unit type set to: " << (int)typeI << endl; }
		type = typeI; };

	void setDebug(bool debugI) { debug = debugI; };
	bool getDebug() { return debug; };
	void printData();
};