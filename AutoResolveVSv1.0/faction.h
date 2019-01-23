#pragma once
#include <iostream>
using namespace std;
enum class faction
{
rebel = 1, beladimir, lerastir, menoriad
};

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