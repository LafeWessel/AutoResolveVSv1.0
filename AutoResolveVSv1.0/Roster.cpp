#include "Roster.h"

Roster::~Roster()
{
}
Roster::Roster() //void initializer
{
	factionUnits = {};
	fact = faction::rebel;
	debug = false;
}

Roster::Roster(vector<Unit> unitsI, faction factI) //initializer
{
	factionUnits = unitsI;
	fact = factI;
	debug = false;
}

vector<Unit> Roster::getUnitsOfType(unitType& type) //gets all of the units of a specific type
{
	if (debug) { cout << "Roster::getUnitsOfType called for unitType: " << (int)type << endl; }
	vector<Unit> unitsI = {};
	for (int i = 0; i < factionUnits.size(); i++)
	{
		if (factionUnits[i].getUnitType() == type)
		{
			unitsI.push_back(factionUnits[i]);
			if (debug) { cout << "unitsI pushed back: " << factionUnits[i].getName() << endl; }
		}
	}
	if (debug) { cout << "Roster::getUnitsOfType finished" << endl; }
	return unitsI;
}

void Roster::buildRoster() //Reads units in from the 'units' file and adds them to the roster if they match the roster's faction
{
	CSVDataReader reader;
	factionUnits = reader.readUnits(fact);
	if (factionUnits.size() < 1) { throw invalid_argument("factionUnits not initialized with any elements"); }
	return;
}

