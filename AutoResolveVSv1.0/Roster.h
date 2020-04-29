#pragma once
#include "CSVRow.h"
#include "faction.h"
#include "Unit.h"
#include "unitType.h"
#include "CSVDataReader.h"
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
class Roster
{
private:
	vector<Unit> factionUnits;
	faction fact;
	bool debug;

public:
	~Roster();
	Roster();
	Roster(bool debugI);
	Roster(vector<Unit> unitsI, faction factI);

	vector<Unit> getUnitsOfType(unitType type);
	vector<Unit> getUnits() { 
		if (debug) { cout << "roster unit vector gotten, size: " << factionUnits.size() << endl; }
		return factionUnits; };
	faction getFaction() { 
		if (debug) { cout << "roster faction gotten: " << (int)fact << endl; }
		return fact; };
	int getNumberOfUnits() { 
		if (debug) { cout << "roster number of units gotten: " << factionUnits.size() << endl; }
		return factionUnits.size(); };
	Unit getUnitAtIndex(int index) { 
		if (debug) { cout << "roster unit at index gotten, name: " << factionUnits[index].getName() << endl; }
		return factionUnits[index]; };

	void setUnits(vector<Unit> unitsI) { 
		if (debug) { cout << "roster unit vector set, size: " << unitsI.size() << endl; }
		factionUnits = unitsI; };
	void setFaction(faction factI) { 
		if (debug) { cout << "roster faction set to: " << (int)factI << endl; }
		fact = factI; };

	bool getDebug() { return debug; };
	void setDebug(bool debugI) { 
		debug = debugI; 
		for (int i = 0; i < factionUnits.size(); i++) {
			factionUnits[i].setDebug(debug);
		}
	};
	void printData();

	void buildRoster();
};

