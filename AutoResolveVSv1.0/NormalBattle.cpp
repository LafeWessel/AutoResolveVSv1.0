#include "NormalBattle.h"
outcome determineOutcomeNormal(float endingTotal) //This determines the kind of outcome that occurs when a given battle result is passed in
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
	result = determineOutcomeNormal(overallTot);
	if (debug) { cout << "Outcome returned from determineOutcome:" << (int)result << " NormalBattle::calculateNormal" << endl; }
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