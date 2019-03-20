#include "CSVDataReader.h"

//Used when reading in from the units document
faction intToFaction(int input)
{
	switch (input)
	{
	case 1:
		return faction::rebel;
		break;
	case 2:
		return faction::beladimir;
		break;
	case 3:
		return faction::lerastir;
		break;
	case 4:
		return faction::menoriad;
		break;
	default:
		cerr << "invalid integer input." << endl;
	}
	return faction::rebel;
}

ostream& operator<<(ostream& os, faction& fact) //This outputs an integer as its corresponding faction name.
{
	switch (fact)
	{
	case(faction::rebel):
		return os << "Rebel";
		break;
	case(faction::beladimir):
		return os << "Beladimir";
		break;
	case(faction::lerastir):
		return os << "Lerastir";
		break;
	case(faction::menoriad):
		return os << "Menoriad";
		break;
	default:
		return os << " No valid faction chosen " << endl;
	}
}







//Used when reading in from the units document
unitType intToUnitType(int input)
{
	switch (input)
	{
	case 1:
		return unitType::Melee;
		break;
	case 2:
		return unitType::Cavalry;
		break;
	case 3:
		return unitType::Ranged;
		break;
	default:
		cerr << "invalid integer input." << endl;
	}
	return unitType::Melee;
}

ostream& operator<<(ostream& os, unitType& type) //output formation for outcome class
{
	switch (type)
	{
	case(unitType::Melee):
		return os << "Melee";
		break;
	case(unitType::Cavalry):
		return os << "Cavalry";
		break;
	case(unitType::Ranged):
		return os << "Ranged";
		break;

	default:
		return os << " No valid unitType chosen " << endl;
	}
}


CSVDataReader::CSVDataReader()
{
}


CSVDataReader::~CSVDataReader()
{
}

vector<Equipment> CSVDataReader::readEquipment()
{
	vector<Equipment> readEquip{};
	ifstream file("equipment.txt");
	//file.open("equipment");
	if (debug) { cout << "equipment.txt tried" << endl; }
	if (!file)
	{
		//file.open("equipment.csv");
		ifstream file("equipment.csv");
		if (debug) { cout << "equipment.csv tried" << endl; }
	}
	else if(!file)
	{
		//file.open("equipment.txt");
		ifstream file("equipment");
		if (debug) { cout << "equipment tried" << endl; }
	}
	else if (!file)
	{
		cerr << "equipment file not found" << endl;
		throw invalid_argument("Equipment file not found.");
	}
	CSVRow row;
	string theEquipType;
	string theName;
	string theEffect;
	string theCoinValue;
	string theIndexNumber;
	string theAutoBonus;
	string theRange;

	//Reads the equipment file and puts equipment in the correct vectors then initializes the treasure
	while (file >> row)
	{
		if (debug) { cout << "Starting to read." << endl; }

		theEquipType = row[0];
		if (debug) { cout << "Equipment Type set to: " << row[0] << endl; }
		theName = row[1];
		if (debug) { cout << "Name set to: " << row[1] << endl; }
		theEffect = row[2];
		if (debug) { cout << "Effect set to: " << row[2] << endl; }
		theCoinValue = row[3];
		if (debug) { cout << "Coin Value set to: " << row[3] << endl; }
		theIndexNumber = row[4];
		if (debug) { cout << "Index Number set to: " << row[4] << endl; }
		theAutoBonus = row[5];
		if (debug) { cout << "AutoRBonus set to: " << row[5] << endl; }
		theRange = row[6];
		if (debug) { cout << "Range set to: " << row[6] << endl; }

		Equipment inputEquip(theName, stoi(theAutoBonus), stoi(theIndexNumber), stoi(theRange), theEquipType, theEffect, stoi(theCoinValue));
		readEquip.push_back(inputEquip);
	}

	//if (armor.size() <1) { throw invalid_argument("Armor vector has no elements"); }
	//if (weapon.size() <1) { throw invalid_argument("Weapon vector has no elements"); }
	//if (trinket.size() <1) { throw invalid_argument("Trinket vector has no elements"); }
	//if (banner.size() <1) { throw invalid_argument("Banner vector has no elements"); }
	//if (follower.size() <1) { throw invalid_argument("Follower vector has no elements"); }
	//if (dragon.size() <1) { throw invalid_argument("Dragon vector has no elements"); }
	return readEquip;
}

vector<Unit> CSVDataReader::readUnits(faction& fact)
{
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
	vector<Unit> readUnits{};
	CSVRow row;
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
			readUnits.push_back(unitRead);
			if (debug) { cout << "factionUnits pushed: " << unitRead.getName() << endl; }
		}
		else
		{
			if (debug) { cout << unitRead.getName() << " was not pushed." << endl; }
		}
	}
	return readUnits;
}

