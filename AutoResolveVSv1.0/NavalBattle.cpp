#include "NavalBattle.h"

NavalBattle::~NavalBattle()
{
}


NavalBattle::NavalBattle() //void initializer
{
	attacker = Player();
	defender = Player();
	attackerShips = 0;
	defenderShips = 0;
	result = outcome::Draw;
}

NavalBattle::NavalBattle(Player attackerI, Player defenderI, int attShipsI, int defShipsI) //initializer
{
	attackerShips = attShipsI;
	defenderShips = defShipsI;
	attacker = attackerI;
	defender = defenderI;
	result = outcome::Draw;
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
	this->attackerShips = totalCasualties[0][1] - 1;
	this->defenderShips = totalCasualties[1][1] - 1;
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
	result = determineOutcome(overallTot);
	if (debug) { cout << "Outcome returned from determineOutcome:" << result << " NavalBattle::calculateNaval" << endl; }
	vector<vector<int>> totalCasualties = {};
	CalculateCas(totalCasualties);
	if (debug) { cout << "CalculateCas called NavalBattle::calculateNaval" << endl; }

	//Calls output function
	navalOutput(totalCasualties);
	if (debug) { cout << "NavalBattle::calculateNaval finished" << endl; }
	return;
}


