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
	if (debug) { cout << "Roster::getUnitsOfType called for unitType: " << type << endl; }
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
	//Makes sure that the faction is acceptable before continuing
	//if (fact != faction::beladimir && fact != faction::lerastir && fact != faction::menoriad && fact != faction::rebel)
	if((int)fact == NULL)
	{
		cout << "No faction selected for roster building." << endl;
		return;
	}
	if (debug) { cout << "Faction selected: " << fact << endl; }

	ifstream file ("units.txt");
	//file.open("units");
	if (debug) { cout << "units tried.txt" << endl; }
	if (!file)
	{
		//file.open("units.csv");
		ifstream file ("units.csv");
		if (debug) { cout << "units.csv tried" << endl; }
	}
	else if (!file)
	{
		//file.open("units.txt");
		ifstream file ("units");
		if (debug) { cout << "units tried" << endl; }
	}
	else if (!file)
	{
		cerr << "units file not found." << endl;
		throw invalid_argument("Units file not found.");
	}
	CSVRow row;
	factionUnits = {};

	string Name;
	string ARBonus;
	string SoldiersPerU;
	faction Faction;
	unitType UnitType;
	Unit unitRead{};
	if (debug) { cout << "Beginning to read from file." << endl; }

	//Reads the equipment file and puts equipment in the correct vectors then initializes the treasure
	while (file >> row)
	{

		Faction = intToFaction(stoi(row[0]));
		if (debug) { cout << "intToFaction(stoi(row[0])) : " << Faction << endl; }
		UnitType = intToUnitType(stoi(row[2]));
		if (debug) { cout << "intToUnitType(stoi(row[2])) : " << UnitType << endl; }

		unitRead.setName(row[1]);
		if (debug) { cout << "unitRead Name set to : " << row[1] << endl; }
		unitRead.setARBonus(stoi(row[3]));
		if (debug) { cout << "unitRead ARBonus set to : " << stoi(row[3]) << endl; }
		unitRead.setSoldiersPerUnit(stoi(row[4]));
		if (debug) { cout << "unitRead soldiersPerUnit set to : " << stoi(row[4]) << endl; }
		unitRead.setFaction(Faction);
		if (debug) { cout << "unitRead Faction set to : " << Faction << endl; }
		unitRead.setUnitType(UnitType);
		if (debug) { cout << "unitRead UnitType set to : " << UnitType << endl; }


		if (unitRead.getFaction() == fact)
		{
			factionUnits.push_back(unitRead);
			if (debug) { cout << "factionUnits pushed: " << unitRead.getName() << endl; }
		}
		else
		{
			if (debug) { cout << unitRead.getName() << " was not pushed." << endl; }
		}
	}
	if (factionUnits.size() < 1) { throw invalid_argument("factionUnits not initialized with any elements"); }
	return;
}

