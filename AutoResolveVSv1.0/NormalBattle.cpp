#include "NormalBattle.h"

NormalBattle::~NormalBattle()
{
}

NormalBattle::NormalBattle() //void initializer
{
	attacker = Player();
	defender = Player();
	result = outcome::Draw;
}

NormalBattle::NormalBattle(Player attackerI, Player defenderI) //initializer
{
	attacker = attackerI;
	defender = defenderI;
	result = outcome::Draw;
}

void NormalBattle::calculateNormal() //Uses base battle calculations and output
{
	if (debug) { cout << "Calling battleCalculate, NormalBattle::calculateNormal" << endl; }
	float overallTot = battleCalculate();
	if (debug) { cout << "Overall total returned from battleCalculate NormalBattle::calculateNormal" << endl; }

	//Finds result and determines casualties
	result = determineOutcome(overallTot);
	if (debug) { cout << "Outcome returned from determineOutcome:" << result << " NormalBattle::calculateNormal" << endl; }
	vector<vector<int>> totalCasualties = {};
	CalculateCas(totalCasualties);
	if (debug) { cout << "CalculateCas called NormalBattle::calculateNormal" << endl; }

	if (debug) { cout << "calling NormalOutput NormalBattle::calculateNormal" << endl; }
	normalOutput(totalCasualties);
	if (debug) { cout << "NormalBattle::calculateNormal finished" << endl; }
	return;
}

void NormalBattle::normalOutput(vector<vector<int>> totalCasualties) //Uses base battle output
{
	if (debug) { cout << "Calling battleOutput, NormalBattle::normalOutput" << endl; }
	battleOutput(totalCasualties);
	if (debug) { cout << "NormalBattle::normalOutput finished" << endl; }
	return;
}