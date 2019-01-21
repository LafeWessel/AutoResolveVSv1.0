/*
* main.cpp
*
* Created on: Oct 8, 2016
*   Author: Lafe Wessel
*/



#include <algorithm>
#include <cmath>

#include <array>
#include <vector>
#include <string>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Battle.h"
#include "CSVRow.h"
#include "defenses.h"
#include "Equipment.h"
#include "faction.h"
#include "General.h"
#include "Monster.h"
#include "MonsterBattle.h"
#include "monsterType.h"
#include "NavalBattle.h"
#include "NormalBattle.h"
#include "outcome.h"
#include "Player.h"
#include "playerType.h"
#include "RaidBattle.h"
#include "Roster.h"
#include "SiegeBattle.h"
#include "townStats.h"
#include "Treasure.h"
#include "Unit.h"
#include "unitType.h"
#include "randomCalculation.h"

using namespace std;




/*General Notes
*
* -In almost all constructors, the variables passed in have an 'I' following their name. This indicates that they are 'Input' variables.
*
* -Most, if not all, <<ostream operators for the enum classes use hard-coded output values.
*
Order of variables in Equipment file:
1. Type: A(Armor), W(Weapon), T(Trinket), B(Banner), F(Follower) (string/char)
2. Name (string)
3. Effect(s) (string)
4. Coin Value (int)
5. Index Value (int)
6. Autoresolve Bonus (int)
7. Range (int)

The 'Corpse Thief' Follower equipment has 1 as it's autoresolve bonus to help calculate bonuses when finding treasure at the end of battles.


Order of Variables in Units file:
1. Faction: 1,2,3 or 4, follows the enum class defined below (int)
2. Name (string)
3. Type: Melee(1), Cavalry(2) or Ranged(3) (int)
4. Autoresolve Bonus (int)
5. Soldiers in each unit(int)
All variables are comma-separated, so there must be no extraneous commas.
*
*
*Equipment and Units files must be put in the same directory as the .exe that is generated when the project is built.
*This seems to a bit temperamental, so I have them copied into 5 separate areas of the program to ensure it works
*/





/*
TODO Section:

TODO-COMMENT EVERYTHING

TODO-Find new way to output at the end of a battle that captures more data

TODO-Refactor, especially the classes

TODO-implement playerType enum class

TODO-Write test functions

TODO-Add way for the autoresolve bonuses of the units to be changed when soldiers are lost from a unit

TODO-Refactor parts of the battleTest functions into separate functions

TODO-Find error related to when a follower is looked for from treasureResults(), probably finds something null

TODO-Add enum class for equipment type

TODO-Remove unnecessary includes from class header files.

*/



int inputCheck(int toCheck, int highestPoint, int lowestPoint) //Checks integer input between 2 given bounds and clamps them
{

	if (toCheck < lowestPoint)//Check against lowest possible value
	{
		toCheck = lowestPoint;
		cout << "Too small, set to: " << lowestPoint << endl;
	}
	else if (toCheck > highestPoint) //Check against highest possible value
	{
		toCheck = highestPoint;
		cout << "Too large, set to: " << highestPoint << endl;
	}
	return toCheck;
}

//This outputs the results from a vector of battle results and also some statistics about them
void predictionOutput(vector<int> rawResults)
{
	//This makes a vector and fills it with the number of times an outcome is found in the vector that is passed in
	vector<int> processedResults{ 0,0,0,0,0,0,0 };
	int i = 0;
	while (i < rawResults.size())
	{
		processedResults[rawResults[i] - 1]++;
		i++;
	}

	//Outputs results
	i = 0;
	while (i < processedResults.size())
	{
		cout << "Results Processed at " << i << ": " << processedResults[i] << " : ";
		outputIntAsOutcome(i + 1);
		cout << endl;
		i++;
	}

	//Makes some floats that are used in statistics output below
	float success = (processedResults[0] + processedResults[1] + processedResults[2]);
	float total = (processedResults[0] + processedResults[1] + processedResults[2] + processedResults[3] + processedResults[4] + processedResults[5] + processedResults[6]);
	float victory = success / total;
	float draw = processedResults[3] / total;
	float loss = (1 - (draw + victory));

	cout << "Percent Victory: " << victory * 100 << endl;
	cout << "Percent Draw: " << draw * 100 << endl;
	cout << "Percent Loss: " << loss * 100 << endl;
	if (loss == 0)
	{
		cout << "Win - loss ratio: " << victory / .01 << endl;
	}
	else
	{
		cout << "Win - loss ratio: " << (victory / loss) << endl;
	}
	return;
}

void testSetup(Battle& battle, bool debug)
{
	if (debug) { cout << "test setup called" << endl; }
	Treasure stuff{};
	stuff.setDebugBool(debug);
	stuff.initializeTreasure();
	if (debug) { cout << "Treasure initialized" << endl; }

	General attackerGen{ 10,stuff.findArmor(),stuff.findWeapon(),stuff.findTrinket(),stuff.findFollower(),stuff.findFollower() };
	attackerGen.setDebugBool(debug);
	if (debug) { cout << "General initialized" << endl; }

	faction attFac = faction::beladimir;
	if (debug) { cout << "faction set" << endl; }

	Roster beladimirRoster{};
	beladimirRoster.setDebugBool(debug);
	beladimirRoster.setFaction(attFac);
	beladimirRoster.buildRoster();
	if (debug) { cout << "Roster built" << endl; }

	int size = beladimirRoster.getNumberOfUnits();
	if (debug) { cout << "size of beladimir roster: " << size << endl; }
	vector<Unit> units{};
	Unit read{};
	int randomIndex;
	for (int i = 1; i < 20; i++)
	{
		randomIndex = randomNumberCas(size - 1);
		if (debug) { cout << "randomIndex generated: " << randomIndex << endl; }
		read = beladimirRoster.getUnitAtIndex(randomIndex);
		if (debug) { cout << "Unit grabbed: " << read.getName() << endl; }
		units.push_back(read);
	}
	Player attacker{};
	attacker.setDebugBool(debug);
	attacker.setFaction(attFac);
	attacker.setGeneralG(attackerGen);
	attacker.setAdvCombatDeck(false);
	attacker.setReinforcements(10);
	attacker.setPlayerUnits(units);

	battle.setAttacker(attacker);
	if (debug) { cout << "Battle attacker set to attacker " << endl; }
	battle.setDefender(attacker);
	if (debug) { cout << "Battle defender set to attacker " << endl; }
	return;
}

//These 5 functions below are overloaded. They create a vector of results from creating and calculating battles with basic information
//that is then sent to predictionOutput()
void battleTest(int tests, NormalBattle& battle, bool debug)
{
	testSetup(battle, debug);
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		if (debug) { cout << "Testing once, calling calculate normal" << endl; }
		battle.calculateNormal();
		if (debug) { cout << "calculateNormal finished" << endl; }
		resultsRaw.push_back((int)battle.getEnding());
		if (debug) { cout << "ResultsRaw pushed: " << battle.getEnding() << endl; }
		cout << "Normal Battle results:" << endl;
		if (debug) { cout << "Attacker units in vector: " << battle.getAttacker().getPlayerUnits().size() << endl; }
		if (debug) { cout << "Defender units in vector: " << battle.getDefender().getPlayerUnits().size() << endl; }
		predictionOutput(resultsRaw);
	}
	else
	{

		for (int i = 0; i < tests; i++)
		{
			NormalBattle norm = battle;
			norm.setOutput(debug);
			norm.setDebug(debug);
			norm.calculateNormal();
			resultsRaw.push_back((int)norm.getEnding());
			if (debug) { cout << "ResultsRaw pushed: " << norm.getEnding() << endl; }
		}
		cout << "Normal Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}

void battleTest(int tests, SiegeBattle& battle, bool debug)
{
	testSetup(battle, debug);

	battle.setCatapults(5);
	if (debug) { cout << "Catapults set to 5 " << endl; }
	battle.setRams(5);
	if (debug) { cout << "Rams attacker set to 5 " << endl; }
	battle.setSiegeTowers(5);
	if (debug) { cout << "Siege towers attacker set to 5 " << endl; }
	battle.setTownLevel(5);
	if (debug) { cout << "town level set to 5 " << endl; }
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		if (debug) { cout << "Testing once, calling calculate siege" << endl; }
		battle.calculateSiege();
		if (debug) { cout << "calculateSiege finished" << endl; }
		resultsRaw.push_back((int)battle.getEnding());
		if (debug) { cout << "ResultsRaw pushed: " << battle.getEnding() << endl; }
		cout << "Siege Battle results:" << endl;
		if (debug) { cout << "Attacker units in vector: " << battle.getAttacker().getPlayerUnits().size() << endl; }
		if (debug) { cout << "Defender units in vector: " << battle.getDefender().getPlayerUnits().size() << endl; }
		predictionOutput(resultsRaw);
	}
	else
	{

		for (int i = 0; i < tests; i++)
		{
			SiegeBattle norm = battle;
			norm.setOutput(debug);
			norm.setDebug(debug);
			norm.calculateSiege();
			resultsRaw.push_back((int)norm.getEnding());
			if (debug) { cout << "ResultsRaw pushed: " << norm.getEnding() << endl; }
		}
		cout << "Siege Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}

void battleTest(int tests, RaidBattle& battle, bool debug)
{
	testSetup(battle, debug);
	battle.setTownLevel(5);
	if (debug) { cout << "town level set to 5 " << endl; }
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		if (debug) { cout << "Testing once, calling calculate raid" << endl; }
		battle.calculateRaid();
		if (debug) { cout << "calculateSiege finished" << endl; }
		resultsRaw.push_back((int)battle.getEnding());
		if (debug) { cout << "ResultsRaw pushed: " << battle.getEnding() << endl; }
		cout << "raid Battle results:" << endl;
		if (debug) { cout << "Attacker units in vector: " << battle.getAttacker().getPlayerUnits().size() << endl; }
		if (debug) { cout << "Defender units in vector: " << battle.getDefender().getPlayerUnits().size() << endl; }
		predictionOutput(resultsRaw);
	}
	else
	{

		for (int i = 0; i < tests; i++)
		{
			RaidBattle norm = battle;
			norm.setOutput(debug);
			norm.setDebug(debug);
			norm.calculateRaid();
			resultsRaw.push_back((int)norm.getEnding());
			if (debug) { cout << "ResultsRaw pushed: " << norm.getEnding() << endl; }
		}
		cout << "Raid Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;

}

void battleTest(int tests, NavalBattle& battle, bool debug)
{
	testSetup(battle, debug);
	battle.setAttackerShips(10);
	battle.setDefenderShips(10);
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		if (debug) { cout << "Testing once, calling calculate naval" << endl; }
		battle.calculateNaval();
		if (debug) { cout << "calculateNaval finished" << endl; }
		resultsRaw.push_back((int)battle.getEnding());
		if (debug) { cout << "ResultsRaw pushed: " << battle.getEnding() << endl; }
		cout << "Naval Battle results:" << endl;
		if (debug) { cout << "Attacker units in vector: " << battle.getAttacker().getPlayerUnits().size() << endl; }
		if (debug) { cout << "Defender units in vector: " << battle.getDefender().getPlayerUnits().size() << endl; }
		predictionOutput(resultsRaw);
	}
	else
	{

		for (int i = 0; i < tests; i++)
		{
			NavalBattle norm = battle;
			norm.setOutput(debug);
			norm.setDebug(debug);
			norm.calculateNaval();
			resultsRaw.push_back((int)norm.getEnding());
			if (debug) { cout << "ResultsRaw pushed: " << norm.getEnding() << endl; }
		}
		cout << "Naval Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}

void battleTest(int tests, MonsterBattle& battle, bool debug)
{
	Treasure stuff{};
	stuff.setDebugBool(debug);
	stuff.initializeTreasure();

	Equipment equip{};
	equip.setDebugBool(debug);
	equip = stuff.findArmor();
	General attackerGen{ 10,equip,equip,equip,equip,equip };
	attackerGen.setDebugBool(debug);
	faction attFac = faction::beladimir;
	Roster beladimirRoster{};
	beladimirRoster.setDebugBool(debug);
	beladimirRoster.setFaction(attFac);
	beladimirRoster.buildRoster();

	int size = beladimirRoster.getNumberOfUnits();
	if (debug) { cout << "size of beladimir roster: " << size << endl; }
	vector<Unit> units{};
	Unit read{};
	int randomIndex;
	for (int i = 1; i < 20; i++)
	{
		randomIndex = randomNumberCas(size - 1);
		if (debug) { cout << "randomIndex generated: " << randomIndex << endl; }
		read = beladimirRoster.getUnitAtIndex(randomIndex);
		if (debug) { cout << "Unit grabbed: " << read.getName() << endl; }
		units.push_back(read);
	}
	Player attacker{};
	attacker.setDebugBool(debug);
	attacker.setFaction(attFac);
	attacker.setGeneralG(attackerGen);
	attacker.setAdvCombatDeck(false);
	attacker.setReinforcements(10);
	attacker.setPlayerUnits(units);

	battle.setPlayer(attacker);
	battle.setMonster(monsterType::Dragon);
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		if (debug) { cout << "Testing once, calling calculate monster" << endl; }
		battle.calculateMonster();
		if (debug) { cout << "calculateMonster finished" << endl; }
		resultsRaw.push_back((int)battle.getEnding());
		if (debug) { cout << "ResultsRaw pushed: " << battle.getEnding() << endl; }
		cout << "Monster Battle results:" << endl;
		if (debug) { cout << "Attacker units in vector: " << battle.getPlayer().getPlayerUnits().size() << endl; }
		predictionOutput(resultsRaw);
	}
	else
	{

		for (int i = 0; i < tests; i++)
		{
			MonsterBattle norm = battle;
			norm.setOutput(debug);
			norm.setDebugBool(debug);
			norm.calculateMonster();
			resultsRaw.push_back((int)norm.getEnding());
			if (debug) { cout << "ResultsRaw pushed: " << norm.getEnding() << endl; }
		}
		cout << "Monster Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}


//Called on program start. At the moment, it only predicts the results from each kind of battle.
int main()
{
	bool debug = false;
	if (debug) { cout << "Program started" << endl; }

	//initializes seed for random number generation
	myseed = myclock::now().time_since_epoch().count();
	generator.seed(myseed);
	if (debug) { cout << "Time-based seed for random numbers initialized" << endl; }

	NormalBattle normal{};
	if (debug) { cout << "Normal battle initialized void" << endl; }
	SiegeBattle siege{};
	if (debug) { cout << "Siege battle initialized void" << endl; }
	RaidBattle raid{};
	if (debug) { cout << "Raid battle initialized void" << endl; }
	NavalBattle naval{};
	if (debug) { cout << "Naval battle initialized void" << endl; }
	MonsterBattle monster{};
	if (debug) { cout << "Monster battle initialized void" << endl; }
	int tests = 10;
	if (debug) { cout << "Tests set to: " << tests << endl; }

	battleTest(tests, normal, debug);
	if (debug) { cout << "Tested Normal battle" << endl; }
	battleTest(tests,siege, debug);
	if (debug) { cout << "Tested Siege battle" << endl; }
	battleTest(tests,raid, debug);
	if (debug) { cout << "Tested Raid battle" << endl; }
	battleTest(tests, naval, debug);
	if (debug) { cout << "Tested Naval battle" << endl; }
	battleTest(tests, monster, debug);
	if (debug) { cout << "Tested Monster battle" << endl; }

	if (debug) { cout << "Program finished" << endl; }

	//This just keeps the console window open
	cin.get();
	return 0;
}
