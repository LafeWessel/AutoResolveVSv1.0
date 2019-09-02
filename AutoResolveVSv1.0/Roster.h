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

