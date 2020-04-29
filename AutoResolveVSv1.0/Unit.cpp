#include "Unit.h"

Unit::~Unit()
{
}

Unit::Unit()
{
	name = "No Name";
	autoResBonus = 1;
	soldiersPerUnit = 1;
	currentSoldiers = 1;
	fact = faction::rebel;
	type = unitType::Melee;
	debug = false;
}

Unit::Unit(bool debugI) {
	name = "No Name";
	autoResBonus = 1;
	soldiersPerUnit = 1;
	currentSoldiers = 1;
	fact = faction::rebel;
	type = unitType::Melee;
	this->setDebug(debugI);
}

Unit::Unit(string nameI, int autoResBonusI, int soldiersPerUnitI, int currentSoldiersI, faction factI, unitType typeI)
{
	name = nameI;
	autoResBonus = autoResBonusI;
	soldiersPerUnit = soldiersPerUnitI;
	currentSoldiers = currentSoldiersI;
	fact = factI;
	type = typeI;
	debug = false;
}

void Unit::printData()
{
	cout << "Unit printData called" << endl
		<< "Unit name: " << name << endl
		<< "Unit autoresolve bonus: " << autoResBonus << endl
		<< "Unit soldiersPerUnit: " << soldiersPerUnit << endl
		<< "Unit currentSoldiers: " << currentSoldiers << endl
		<< "Unit faction: " << (int)fact << endl
		<< "Unit unitType: " << (int)type << endl;
}