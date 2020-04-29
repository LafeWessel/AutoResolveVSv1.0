#include "NavalBattle.h"
outcome determineOutcomeNaval(float endingTotal) //This determines the kind of outcome that occurs when a given battle result is passed in
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
NavalBattle::~NavalBattle()
{
}


NavalBattle::NavalBattle() : Battle()//void initializer
{
	attackerShips = 0;
	defenderShips = 0;
}

NavalBattle::NavalBattle(bool debugI) : Battle(debugI)
{
	attackerShips = 0;
	defenderShips = 0;
}

NavalBattle::NavalBattle(Player attackerI, Player defenderI, int attShipsI, int defShipsI) : 
	Battle(attackerI, defenderI)//initializer
{
	attackerShips = attShipsI;
	defenderShips = defShipsI;
}

NavalBattle::NavalBattle(Player attackerI, Player defenderI, int attShipsI, int defShipsI, bool fileOutI, string fileNameI) : 
	Battle(attackerI, defenderI, fileOutI, fileNameI)
{
	attackerShips = attShipsI;
	defenderShips = defShipsI;
}

void NavalBattle::navalOutput(vector<vector<int>> totalCasualties) //uses base Battle output and adds naval outputs
{
	if (debug) { cout << "Calling battleOutput, NavalBattle::NavalOutput" << endl; }
	battleOutput(totalCasualties);
	if (output)
	{
		cout << "Attacker Ship Cas: " << totalCasualties[0][1] - 1 << endl;
		cout << "Defender Ship Cas " << totalCasualties[1][1] - 1 << endl;
	}
	//Subtracts one from the amount of ships sunk for balancing reasons
	this->attackerShips -= totalCasualties[0][1] - 1;
	this->defenderShips -= totalCasualties[1][1] - 1;
	if (debug) { cout << "NavalBattle::navalOutput finished" << endl; }
	return;
}

void NavalBattle::calculateNaval() //combines base Battle calculation with the extras needed for Naval Battles, then calls output
{
	if (debug) { cout << "Calling battleCalculate, NavalBattle::calculateNaval" << endl; }
	//Uses base calculations and adds Naval Battle calculations
	float overallTot = battleCalculate();
	if (debug) { cout << "Overall total returned from battleCalculate NavalBattle::calculateNaval" << endl; }
	overallTot += attackerShips * 3;
	if (debug) { cout << "Overall total + attacker ships(" << attackerShips << ")*3 NavalBattle::calculateNaval" << endl; }
	overallTot -= defenderShips * 3;
	if (debug) { cout << "Overall total defender ships(" << defenderShips << ")*3 NavalBattle::calculateNaval" << endl; }

	//Gets the outcome and calculates the casualties
	result = determineOutcomeNaval(overallTot);
	if (debug) { cout << "Outcome returned from determineOutcome:" << (int)result << " NavalBattle::calculateNaval" << endl; }
	vector<vector<int>> totalCasualties = {};
	CalculateCas(totalCasualties);
	if (debug) { cout << "CalculateCas called NavalBattle::calculateNaval" << endl; }

	//Calls output function
	navalOutput(totalCasualties);
	if (debug) { cout << "NavalBattle::calculateNaval finished" << endl; }
	return;
}

void NavalBattle::printDataNaval()
{
	cout << "NavalBattle printData called" << endl
		<< "NavalBattle attacker ships: " << attackerShips << endl
		<< "NavalBattle defender ships: " << defenderShips << endl;
	printData();
}

