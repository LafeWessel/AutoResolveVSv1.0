#include "RaidBattle.h"

RaidBattle::~RaidBattle()
{
}

RaidBattle::RaidBattle() //void initializer
{
	attacker = Player();
	defender = Player();
	townLevel = townStats();
	result = outcome::Draw;
}

RaidBattle::RaidBattle(Player attackerI, Player defenderI, townStats townLevelI) // initializer
{
	attacker = attackerI;
	defender = defenderI;
	townLevel = townLevelI;
	result = outcome::Draw;
}

void RaidBattle::calculateRaid() //combines base Battle calculation with the extras needed for Raid Battles, then calls output
{
	float overallTot = battleCalculate();
	if (debug) { cout << "Overall total returned from battleCalculate RaidBattle::calculateRaid" << endl; }
	overallTot -= ((townLevel.getLevel() * 10) - 10);
	if (debug) { cout << "Overall total - (townLevel(" << townLevel.getLevel() << ") * 10) -10 RaidBattle::calculateRaid" << endl; }

	//Finds outcome and gets casualties
	result = determineOutcome(overallTot);
	if (debug) { cout << "Outcome returned from determineOutcome:" << result << " RaidBattle::calculateRaid" << endl; }
	vector<vector<int>> totalCasualties = {};
	CalculateCas(totalCasualties);
	if (debug) { cout << "CalculateCas called RaidBattle::calculateRaid" << endl; }

	//determines number of supplies gained
	int suppliesGained = townLevel.getSupplies() / (int)result;
	if (debug) { cout << "Supplies gained: " << suppliesGained << "RaidBattle::calculateRaid" << endl; }

	//Outputs results from battle
	raidOutput(totalCasualties, suppliesGained);
	if (debug) { cout << "RaidBattle::calculateRaid finished" << endl; }
	return;
}

void RaidBattle::raidOutput(vector<vector<int>> totalCasualties, int suppGained) //uses base Battle output and adds Raid outputs
{
	if (debug) { cout << "Calling battleOutput, RaidBattle::raidOutput" << endl; }
	battleOutput(totalCasualties);
	if (output)
	{
		cout << "Attacker supplies gained: " << suppGained << endl;
	}
	if (debug) { cout << "RaidBattle::raidOutput finished" << endl; }
	return;
}
