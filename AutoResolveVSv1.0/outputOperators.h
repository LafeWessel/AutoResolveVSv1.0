#pragma once
#include "faction.h"
#include "unitType.h"
#include "monsterType.h"
#include "defenses.h"
#include "outcome.h"
#include "Equipment.h"
#include "CSVRow.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <istream>
using namespace std;

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

ostream& operator<<(ostream& os, monsterType& mon) //Thsi outputs an integer as its corresponding monsterType name
{
	switch (mon)
	{
	case(monsterType::Minotaur):
		return os << "Minotaur";
		break;
	case(monsterType::Hobgoblin):
		return os << "Hobgoblin";
		break;
	case(monsterType::Troll):
		return os << "Troll";
		break;
	case(monsterType::Giant):
		return os << "Giant";
		break;
	case(monsterType::Demon):
		return os << "Demon";
		break;
	case(monsterType::Dragon):
		return os << "Dragon";
		break;
	default:
		return os << " No valid monster chosen " << endl;
	}
}

ostream& operator<<(ostream& os, defenses& def) //This outputs an integer as its corresponding defenses name.
{
	switch (def)
	{
	case(defenses::None):
		return os << "None";
		break;
	case(defenses::Wooden_Wall):
		return os << "Wooden Walls";
		break;
	case(defenses::Wooden_Wall_W_Moat):
		return os << "Wooden Walls and Moat";
		break;
	case(defenses::Stone_Wall):
		return os << "Stone Walls";
		break;
	case(defenses::Stone_Wall_W_Moat):
		return os << "Stone Walls and Moat";
		break;
	default:
		return os << " No valid defenses chosen " << endl;
	}
}

ostream& operator<<(ostream& os, outcome& end) //Output formation for outcome class
{
	switch (end)
	{
	case(outcome::Decisive_Victory):
		return os << "Decisive Victory";
		break;
	case(outcome::Heroic_Victory):
		return os << "Heroic Victory";
		break;
	case(outcome::Close_Victory):
		return os << "Close Victory";
		break;
	case(outcome::Draw):
		return os << "Draw";
		break;
	case(outcome::Close_Defeat):
		return os << "Close Defeat";
		break;
	case(outcome::Valiant_Defeat):
		return os << "Valiant Defeat";
		break;
	case(outcome::Crushing_Defeat):
		return os << "Crushing Defeat";
		break;
	default:
		return os << " No valid outcome chosen " << endl;
	}

}

void outputIntAsOutcome(int choice) //This outputs an integer as its corresponding outcome enum class name.
{
	switch (choice)
	{
	case(1):
		cout << "Decisive Victory";
		break;
	case(2):
		cout << "Heroic Victory";
		break;
	case(3):
		cout << "Close Victory";
		break;
	case(4):
		cout << "Draw";
		break;
	case(5):
		cout << "Close Defeat";
		break;
	case(6):
		cout << "Valiant Defeat";
		break;
	case(7):
		cout << "Crushing Defeat";
		break;
	default:
		cerr << " No valid outcome chosen " << endl;
	}
}

ostream& operator<<(ostream& os, Equipment& eqpt) //output operator for Equipment class
{
	return os << eqpt.getName() << endl
		<< "Effect: " << eqpt.getEffect() << endl
		<< "Range: " << eqpt.getRange() << endl
		<< "EquipType: " << eqpt.getEqType() << endl
		<< "Coin Value: " << eqpt.getCValue() << endl;
}



outcome determineOutcome(float endingTotal) //This determines the kind of outcome that occurs when a given battle result is passed in
{
	//All results are in relation to the attacker.
	//Victory
	if (endingTotal > 2)
	{
		if (endingTotal >= 20)
		{
			return outcome::Decisive_Victory;
		}
		else if (endingTotal >= 10)
		{
			return outcome::Heroic_Victory;
		}
		else
		{
			return outcome::Close_Victory;
		}
	}
	//Defeat
	else if (endingTotal < -2)
	{
		if (endingTotal <= -20)
		{
			return outcome::Crushing_Defeat;
		}
		else if (endingTotal <= -10)
		{
			return outcome::Valiant_Defeat;
		}
		else
		{
			return outcome::Close_Defeat;
		}
	}
	//Draw
	else
	{
		return outcome::Draw;
	}
}