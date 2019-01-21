#include "Unit.h"

Unit::~Unit()
{
}

Unit::Unit()
{
	name = "No Name";
	autoResBonus = 1;
	soldiersPerUnit = 1;
	fact = faction::rebel;
	type = unitType::Melee;
}

Unit::Unit(string nameI, int autoResBonusI, int soldiersPerUnitI, faction factI, unitType typeI)
{
	name = nameI;
	autoResBonus = autoResBonusI;
	soldiersPerUnit = soldiersPerUnitI;
	fact = factI;
	type = typeI;
}