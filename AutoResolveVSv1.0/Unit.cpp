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