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

Roster::Roster(bool debugI)
{
	factionUnits = {};
	fact = faction::rebel;
	this->setDebug(debugI);
}

Roster::Roster(vector<Unit> unitsI, faction factI) //initializer
{
	factionUnits = unitsI;
	fact = factI;
	debug = false;
}

vector<Unit> Roster::getUnitsOfType(unitType type) //gets all of the units of a specific type
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
	if (debug) { cout << "roster build roster called" << endl; }
	CSVDataReader reader(debug);
	factionUnits = reader.readUnits(fact);
	if (debug) { cout << "units vector size: " << factionUnits.size() << endl; }
	if (factionUnits.size() < 1) { throw invalid_argument("factionUnits not initialized with any elements"); }
	return;
}

void Roster::printData()
{
	cout << "Roster printData called" << endl
		<< "Roster Faction: " << (int)fact << endl;
	for (int i = 0; i < factionUnits.size(); i++) 
	{
		cout << "Roster factionUnits vector at " << i << ":" << endl;
		factionUnits[i].printData();
	}
}
