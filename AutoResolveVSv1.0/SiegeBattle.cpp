#include "SiegeBattle.h"
outcome determineOutcomeSiege(float endingTotal) //This determines the kind of outcome that occurs when a given battle result is passed in
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

SiegeBattle::~SiegeBattle()
{
}

SiegeBattle::SiegeBattle() : Battle()//void initializer
{
	rams = 0;
	catapults = 0;
	siegeTowers = 0;
	townLevel = townStats();
}

SiegeBattle::SiegeBattle(bool debugI) : Battle(debugI)
{
	rams = 0;
	catapults = 0;
	siegeTowers = 0;
	townLevel = townStats();
}

SiegeBattle::SiegeBattle(Player attackerI, Player defenderI, int ramsI, int catapultsI, int siegeTowersI, townStats townLevelI) : 
	Battle(attackerI, defenderI)// initializer
{
	rams = ramsI;
	catapults = catapultsI;
	siegeTowers = siegeTowersI;
	townLevel = townLevelI;
}

SiegeBattle::SiegeBattle(Player attackerI, Player defenderI, int ramsI, int catapultsI, int siegeTowersI, townStats townLevelI, bool fileOutI, string fileNameI) : 
	Battle(attackerI, defenderI, fileOutI, fileNameI)
{
	rams = ramsI;
	catapults = catapultsI;
	siegeTowers = siegeTowersI;
	townLevel = townLevelI;
}

void SiegeBattle::calculateSiege() //combines base Battle calculation with the extras needed for Siege Battles, then calls output
{
	float overallTot = battleCalculate();
	if (debug) { cout << "Overall total returned from battleCalculate SiegeBattle::calculateSiege" << endl; }

	//Siege Battle-specific calculations
	overallTot -= (townLevel.getLevel() * 10) - 10;
	if (debug) { cout << "Overall total - (townLevel(" << townLevel.getLevel() << ") * 10) -10 SiegeBattle::calculateSiege" << endl; }
	overallTot += rams * 2;
	if (debug) { cout << "Overall total + rams(" << rams << ")*2 SiegeBattle::calculateSiege" << endl; }
	overallTot += catapults * 3;
	if (debug) { cout << "Overall total + catapults(" << catapults << ") * 3 SiegeBattle::calculateSiege" << endl; }
	overallTot += siegeTowers * 4;
	if (debug) { cout << "Overall total + siegeTowers(" << siegeTowers << ") * 4 SiegeBattle::calculateSiege" << endl; }

	//Determines the outcome and calculates the casualties
	result = determineOutcomeSiege(overallTot);
	if (debug) { cout << "Outcome returned from determineOutcome:" << (int)result << " SiegeBattle::calculateSiege" << endl; }
	vector<vector<int>> totalCasualties = {};
	CalculateCas(totalCasualties);
	if (debug) { cout << "CalculateCas called SiegeBattle::calculateSiege" << endl; }

	SiegeOutput(totalCasualties);
	if (debug) { cout << "SiegeBattle::calculateSiege finished" << endl; }
}

void SiegeBattle::SiegeOutput(vector<vector<int>> totalCasualties) //uses base Battle output and adds Siege outputs
{
	if (debug) { cout << "Calling battleOutput, SiegeBattle::SiegeOutput" << endl; }
	battleOutput(totalCasualties);

	if (output)
	{
		if ((int)result < 4)
		{
			cout << "The settlement was taken by the attackers." << endl;
			cout << "The defending army/garrison has been completely destroyed." << endl;
		}
		else
		{
			cout << "The settlement was successfully held by the defenders" << endl;
		}
	}
	if (debug) { cout << "SiegeBattle::SiegeOutput finished" << endl; }
	return;
}

void SiegeBattle::printDataSiege()
{
	cout << "SiegeBattle printData called" << endl
		<< "SiegeBattle rams: " << rams << endl
		<< "SiegeBattle catapults: " << catapults << endl
		<< "SeigeBattle siege towers: " << siegeTowers << endl
		<< "SiegeBattle townLevel(townStats): " << endl;
	townLevel.printData();
	printData();
}