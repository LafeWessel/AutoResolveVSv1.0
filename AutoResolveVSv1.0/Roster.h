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

	vector<Unit> getUnits() { 
		if (debug) { cout << "roster unit vector gotten" << endl; }
		return factionUnits; 
	};
	faction getFaction() { 
		if (debug) { cout << "roster faction gotten" << endl; }
		return fact; 
	};
	int getNumberOfUnits() { 
		if (debug) { cout << "roster number of units gotten" << endl; }
		return factionUnits.size(); 
	};

	void setUnits(vector<Unit> unitsI) { 
		if (debug) { cout << "roster unit vector set" << endl; }
		factionUnits = unitsI; 
	};
	void setFaction(faction factI) { 
		if (debug) { cout << "roster faction set" << endl; }
		fact = factI; 
	};
	Unit getUnitAtIndex(int index) { 
		if (debug) { cout << "roster unit at index returned" << endl; }
		return factionUnits[index]; 
	};

	vector<Unit> getUnitsOfType(unitType& type);

	bool getDebug() { return debug; };
	void setDebug(bool debugI) { 
		debug = debugI; 
		for (int i = 0; i < factionUnits.size(); i++) {
			factionUnits[i].setDebug(debug);
		}
	};

	void buildRoster();
};

