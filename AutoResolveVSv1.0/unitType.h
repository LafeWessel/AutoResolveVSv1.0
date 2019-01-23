#pragma once
#include <iostream>
using namespace std;
enum class unitType
{
Melee = 1, Cavalry, Ranged
};

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

ostream& operator<<(ostream& os, unitType& type) //Output formation for outcome class
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