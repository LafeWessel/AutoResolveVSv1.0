/*
* main.cpp
*
* Created on: Oct 8, 2016
*   Author: Lafe Wessel
*/

#include <algorithm>
#include <cmath>

#include <vector>
#include <string>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <random>

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
#include "RaidBattle.h"
#include "Roster.h"
#include "SiegeBattle.h"
#include "townStats.h"
#include "Treasure.h"
#include "Unit.h"
#include "unitType.h"

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
1. Faction: 1,2,3, or 4, follows the enum class defined below (int)
2. Name (string)
3. Type: Melee(1), Cavalry(2) or Ranged(3) (int)
4. Autoresolve Bonus (int)
5. Soldiers in each unit(int)
All variables are comma-separated, so there must be no extraneous commas.
*
*
*Equipment and Units files must be put in the same directory as the .exe that is generated when the project is built.
*This seems to be a bit temperamental, so I have them copied into 5 separate areas of the program to ensure it works
*/

/*
TODO Section:

High Priority:
	TODO-Make a way for the tests to use randomized values
	TODO-Make a way for all the data in a battle, including results, cas, etc. to be captured in an array/vector
	TODO-Make sure that casualties are actually assigned for MonsterBattle
Low Priority:

TODO-Create an auto-balancing feature to determine what is an equal distribution of power -> AI
	-Can use a model to determine what contributes most to success?
	-Can make a db of results from numerous battles then analyze it with R or python
TODO-Learn and implement Qt GUI

***Possibly Fixed***
-Find error related to when a follower is looked for from treasureResults(), probably finds something null

*/

//Same as randomNumber, but includes 0 in the range. Specifically meant for casualty calculation and arrays
int randomNumberInt(int range)
{
	typedef std::chrono::high_resolution_clock myclock;
	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	
	if (range == 0)
	{
		return 0;
	}
	uniform_int_distribution<int> dRange(0, abs(range));
	return dRange(generator);
}

//Overloads randomNumberInt and has passable bounds instead of 0 - arg bounds
int randomNumberInt(int min, int max) {
	typedef std::chrono::high_resolution_clock myclock;
	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

	if (max == 0)
	{
		return 0;
	}
	uniform_int_distribution<int> dRange(abs(min), abs(max));
	return dRange(generator);
}

//Returns the faction relevant to the integer passed
faction intToFac(int fac) {

	switch (fac) {
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
			cerr << "Invalid integer passed to intToFac" << endl;
	}
	return faction::rebel;
}

//Returns the monsterType relevant to the integer passed
monsterType intToMType(int type) {
	switch (type) {
		case 1:
			return monsterType::Minotaur;
			break;
		case 2:
			return monsterType::Hobgoblin;
			break;
		case 3:
			return monsterType::Troll;
			break;
		case 4:
			return monsterType::Giant;
			break;
		case 5:
			return monsterType::Demon;
			break;
		case 6:
			return monsterType::Dragon;
			break;
		default:
			cerr << "Invalid integer passed to intToMType" << endl;
	}
}

//This outputs an integer as its corresponding outcome enum class name.
void outputIntAsOutcome(int choice) 
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

//Checks integer input between 2 given bounds and clamps them
int inputCheck(int toCheck, int highestPoint, int lowestPoint) 
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
	float total = 0.0;
	for (int i = 0; i < 7; i++)
	{
		total += processedResults[i];
	}
	//float total = (processedResults[0] + processedResults[1] + processedResults[2] + processedResults[3] + processedResults[4] + processedResults[5] + processedResults[6]);
	float victory = success / total;
	float draw = processedResults[3] / total;
	float loss = (1 - (draw + victory));

	cout << "Percent Victory: " << victory * 100 << endl;
	cout << "Percent Draw: " << draw * 100 << endl;
	cout << "Percent Loss: " << loss * 100 << endl;
	if (loss == 0)
	{
		cout << "Win - loss ratio: " << victory * 100 << endl;
	}
	else
	{
		cout << "Win - loss ratio: " << abs(victory / loss) << endl;
	}
	return;
}

//Creates and fills all the classes needed for a battle. Is called by the battleTestStd functions
void testSetupStd(Battle& battle, bool debug, Treasure& treasure)
{
	if (debug) { cout << "test setup called" << endl; }

	General attackerGen{};
	attackerGen.setArmor(treasure.findArmor());
	attackerGen.setBanner(treasure.findBanner());
	attackerGen.setFollower(treasure.findFollower());
	attackerGen.setTrinket(treasure.findTrinket());
	attackerGen.setWeapon(treasure.findWeapon());
	attackerGen.setRank(10);
	attackerGen.setDebug(debug);
	if (debug) { cout << "General initialized" << endl; }

	faction attFac = faction::beladimir;
	if (debug) { cout << "faction set" << endl; }

	Roster beladimirRoster{};
	beladimirRoster.setDebug(debug);
	beladimirRoster.setFaction(attFac);
	beladimirRoster.buildRoster();
	if (debug) { cout << "Roster built" << endl; }

	int size = beladimirRoster.getNumberOfUnits()-1;
	if (debug) { cout << "size of beladimir roster: " << size << endl; }
	vector<Unit> units{};
	Unit read{};
	int randomIndex;
	for (int i = 0; i < 20; i++)
	{
		randomIndex = randomNumberInt(size);
		if (debug) { cout << "randomIndex generated: " << randomIndex << endl; }
		read = beladimirRoster.getUnitAtIndex(randomIndex);
		read.setDebug(debug);
		if (debug) { cout << "Unit grabbed: " << read.getName() << endl; }
		units.push_back(read);
	}
	if (debug) { cout << "unit vector size: " << units.size() << endl; }
	Player attacker{};
	attacker.setDebug(debug);
	attacker.setFaction(attFac);
	attacker.setGeneral(attackerGen);
	attacker.setAdvCombatDeck(false);
	attacker.setReinforcements(10);
	attacker.setPlayerUnits(units);

	battle.setAttacker(attacker);
	if (debug) { cout << "Battle attacker set to attacker " << endl; }
	battle.setDefender(attacker);
	if (debug) { cout << "Battle defender set to attacker " << endl; }
	return;
}

//These 5 functions create a vector of results from creating and calculating battles with basic information
//that is then sent to predictionOutput()
//They are used for standard, symmetrical battle testing
void battleTestStd(int tests, NormalBattle battle, bool debug, Treasure& treasure)
{
	if (debug) { cout << "battleTest - normal called; calling testSetup" << endl; }
	testSetupStd(battle, debug, treasure);
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		if (debug) { cout << "Testing once, calling calculate normal" << endl; }
		battle.calculateNormal();
		if (debug) { cout << "calculateNormal finished" << endl; }
		resultsRaw.push_back((int)battle.getOutcome());
		if (debug) { cout << "ResultsRaw pushed: " << (int)battle.getOutcome() << endl; }
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
			resultsRaw.push_back((int)norm.getOutcome());
			if (debug) { cout << "ResultsRaw pushed: " << (int)norm.getOutcome() << endl; }
			if (debug) { cout << endl << endl << endl << endl; }
		}
		cout << "Normal Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}

void battleTestStd(int tests, SiegeBattle battle, bool debug, Treasure& treasure)
{
	if (debug) { cout << "battleTest - siege called; calling testSetup" << endl; }
	testSetupStd(battle, debug, treasure);

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
		resultsRaw.push_back((int)battle.getOutcome());
		if (debug) { cout << "ResultsRaw pushed: " << (int)battle.getOutcome() << endl; }
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
			resultsRaw.push_back((int)norm.getOutcome());
			if (debug) { cout << "ResultsRaw pushed: " << (int)norm.getOutcome() << endl; }
			if (debug) { cout << endl << endl << endl << endl; }
		}
		cout << "Siege Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}

void battleTestStd(int tests, RaidBattle battle, bool debug, Treasure& treasure)
{
	if (debug) { cout << "battleTest - raid called; calling testSetup" << endl; }
	testSetupStd(battle, debug, treasure);
	battle.setTownLevel(5);
	if (debug) { cout << "town level set to 5 " << endl; }
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		if (debug) { cout << "Testing once, calling calculate raid" << endl; }
		battle.calculateRaid();
		if (debug) { cout << "calculateSiege finished" << endl; }
		resultsRaw.push_back((int)battle.getOutcome());
		if (debug) { cout << "ResultsRaw pushed: " << (int)battle.getOutcome() << endl; }
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
			resultsRaw.push_back((int)norm.getOutcome());
			if (debug) { cout << "ResultsRaw pushed: " << (int)norm.getOutcome() << endl; }
			if (debug) { cout << endl << endl << endl << endl; }
		}
		cout << "Raid Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;

}

void battleTestStd(int tests, NavalBattle battle, bool debug, Treasure& treasure)
{
	if (debug) { cout << "battleTest - naval called; calling testSetup" << endl; }
	testSetupStd(battle, debug, treasure);
	battle.setAttackerShips(10);
	battle.setDefenderShips(10);
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		if (debug) { cout << "Testing once, calling calculate naval" << endl; }
		battle.calculateNaval();
		if (debug) { cout << "calculateNaval finished" << endl; }
		resultsRaw.push_back((int)battle.getOutcome());
		if (debug) { cout << "ResultsRaw pushed: " << (int)battle.getOutcome() << endl; }
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
			resultsRaw.push_back((int)norm.getOutcome());
			if (debug) { cout << "ResultsRaw pushed: " << (int)norm.getOutcome() << endl; }
			if (debug) { cout << endl << endl << endl << endl; }
		}
		cout << "Naval Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}

void battleTestStd(int tests, MonsterBattle battle, bool debug, Treasure& treasure)
{
	if (debug) { cout << "battleTest - monster called" << endl; }
	Equipment equip{};
	equip.setDebug(debug);
	equip = treasure.findArmor();
	General attackerGen{ 10,equip,equip,equip,equip,equip };
	attackerGen.setDebug(debug);
	faction attFac = faction::beladimir;
	Roster beladimirRoster{};
	beladimirRoster.setDebug(debug);
	beladimirRoster.setFaction(attFac);
	beladimirRoster.buildRoster();

	int size = beladimirRoster.getNumberOfUnits();
	if (debug) { cout << "size of beladimir roster: " << size << endl; }
	vector<Unit> units{};
	Unit read{};
	int randomIndex;
	for (int i = 1; i < 20; i++)
	{
		randomIndex = randomNumberInt(size - 1);
		if (debug) { cout << "randomIndex generated: " << randomIndex << endl; }
		read = beladimirRoster.getUnitAtIndex(randomIndex);
		if (debug) { cout << "Unit grabbed: " << read.getName() << endl; }
		units.push_back(read);
	}
	Player attacker{};
	attacker.setDebug(debug);
	attacker.setFaction(attFac);
	attacker.setGeneral(attackerGen);
	attacker.setAdvCombatDeck(false);
	attacker.setReinforcements(10);
	attacker.setPlayerUnits(units);

	Monster monster = {};
	monster.setMonsterType(monsterType::Dragon);
	monster.setTreasure(treasure);

	battle.setPlayer(attacker);
	battle.setMonster(monster);
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		if (debug) { cout << "Testing once, calling calculate monster" << endl; }
		battle.calculateMonster();
		if (debug) { cout << "calculateMonster finished" << endl; }
		resultsRaw.push_back((int)battle.getOutcome());
		if (debug) { cout << "ResultsRaw pushed: " << (int)battle.getOutcome() << endl; }
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
			norm.setDebug(debug);
			norm.calculateMonster();
			resultsRaw.push_back((int)norm.getOutcome());
			if (debug) { cout << "ResultsRaw pushed: " << (int)norm.getOutcome() << endl; }
			if (debug) { cout << endl << endl << endl << endl; }
		}
		cout << "Monster Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}

//Runs n battle tests with standard, symmetrical values
void standardTests(int tests, bool debug) {

	Treasure treasure{};
	treasure.setDebug(debug);
	treasure.initializeTreasure();

	NormalBattle normal{};
	normal.setTreasure(treasure);
	normal.setDebug(debug);
	if (debug) { cout << "Normal battle initialized void" << endl; }
	battleTestStd(tests, normal, debug, treasure);
	if (debug) { cout << "Tested Normal battle" << endl; }
	if (debug) { cin.get(); }

	SiegeBattle siege{};
	siege.setTreasure(treasure);
	siege.setDebug(debug);
	if (debug) { cout << "Siege battle initialized void" << endl; }
	battleTestStd(tests, siege, debug, treasure);
	if (debug) { cout << "Tested Siege battle" << endl; }
	if (debug) { cin.get(); }

	RaidBattle raid{};
	raid.setTreasure(treasure);
	raid.setDebug(debug);
	if (debug) { cout << "Raid battle initialized void" << endl; }
	battleTestStd(tests, raid, debug, treasure);
	if (debug) { cout << "Tested Raid battle" << endl; }
	if (debug) { cin.get(); }

	NavalBattle naval{};
	naval.setTreasure(treasure);
	naval.setDebug(debug);
	if (debug) { cout << "Naval battle initialized void" << endl; }
	battleTestStd(tests, naval, debug, treasure);
	if (debug) { cout << "Tested Naval battle" << endl; }
	if (debug) { cin.get(); }

	MonsterBattle monster{};
	if (debug) { cout << "Monster battle initialized void" << endl; }
	monster.setDebug(debug);
	if (debug) { cout << "Monster battle treasure set" << endl; }
	battleTestStd(tests, monster, debug, treasure);
	if (debug) { cout << "Tested Monster battle" << endl; }
	if (debug) { cin.get(); }
}

//Creates and fills all the classes needed for a battle in a random, asymmetric way. Called by battleTestRand functions
void testSetupRand(Battle& battle, bool debug, Treasure& treasure) {
	if (debug) { cout << "testSetupRand called" << endl; }

	//Create generals
	General attGen = {};
	attGen.setDebug(debug);
	if (randomNumberInt(1,10) >= 5){attGen.setArmor(treasure.findArmor());}
	if (randomNumberInt(1, 10) >= 5) {attGen.setBanner(treasure.findBanner());}
	if (randomNumberInt(1, 10) >= 5) {attGen.setFollower(treasure.findFollower());}
	if (randomNumberInt(1, 10) >= 5) {attGen.setTrinket(treasure.findTrinket());}
	if (randomNumberInt(1, 10) >= 5) {attGen.setWeapon(treasure.findWeapon());}
	attGen.setRank(randomNumberInt(1,10));

	General defGen = {};
	defGen.setDebug(debug);
	if (randomNumberInt(1, 10) >= 5) {defGen.setArmor(treasure.findArmor());}
	if (randomNumberInt(1, 10) >= 5) {defGen.setBanner(treasure.findBanner());}
	if (randomNumberInt(1, 10) >= 5) {defGen.setFollower(treasure.findFollower());}
	if (randomNumberInt(1, 10) >= 5) {defGen.setTrinket(treasure.findTrinket());}
	if (randomNumberInt(1, 10) >= 5) {defGen.setWeapon(treasure.findWeapon());}
	defGen.setRank(randomNumberInt(1, 10));
	
	//Select factions
	faction attFac = intToFac(randomNumberInt(1, 4));
	faction defFac = intToFac(randomNumberInt(1, 4));

	//Create Rosters
	Roster attRos = {};
	attRos.setDebug(debug);
	attRos.setFaction(attFac);
	attRos.buildRoster();

	Roster defRos = {};
	defRos.setDebug(debug);
	defRos.setFaction(defFac);
	defRos.buildRoster();

	//Fill Rosters
	int attSize = attRos.getNumberOfUnits() - 1;
	int attNumU = randomNumberInt(1, 20);
	vector<Unit> attU = {};
	for (int i = 0; i < attNumU; i++) {
		attU.push_back(attRos.getUnitAtIndex(randomNumberInt(attSize)));
	}

	int defSize = defRos.getNumberOfUnits() - 1;
	int defNumU = randomNumberInt(1, 20);
	vector<Unit> defU = {};
	for (int i = 0; i < defNumU; i++) {
		defU.push_back(defRos.getUnitAtIndex(randomNumberInt(defSize)));
	}

	//Create Players
	Player attacker{};
	attacker.setDebug(debug);
	attacker.setFaction(attFac);
	attacker.setGeneral(attGen);
	attacker.setAdvCombatDeck(randomNumberInt(1));
	attacker.setReinforcements(randomNumberInt(10));
	attacker.setPlayerUnits(attU);

	Player defender{};
	defender.setDebug(debug);
	defender.setFaction(defFac);
	defender.setGeneral(defGen);
	defender.setAdvCombatDeck(randomNumberInt(1));
	defender.setReinforcements(randomNumberInt(10));
	defender.setPlayerUnits(defU);

	//Assign attacker and defender
	battle.setAttacker(attacker);
	battle.setDefender(defender);

}

//Specific case of testSetupRand for MonsterBattle class
void testSetupRand(MonsterBattle& battle, bool debug, Treasure& treasure) {
	if (debug) { cout << "testSetupRand MonsterBattle called" << endl; }
	General attGen = {};
	attGen.setDebug(debug);
	if (randomNumberInt(1, 10) >= 5) { attGen.setArmor(treasure.findArmor()); }
	if (randomNumberInt(1, 10) >= 5) { attGen.setBanner(treasure.findBanner()); }
	if (randomNumberInt(1, 10) >= 5) { attGen.setFollower(treasure.findFollower()); }
	if (randomNumberInt(1, 10) >= 5) { attGen.setTrinket(treasure.findTrinket()); }
	if (randomNumberInt(1, 10) >= 5) { attGen.setWeapon(treasure.findWeapon()); }
	attGen.setRank(randomNumberInt(1, 10));

	faction attFac = intToFac(randomNumberInt(1, 4));

	Roster attRos = {};
	attRos.setDebug(debug);
	attRos.setFaction(attFac);
	attRos.buildRoster();

	int attSize = attRos.getNumberOfUnits() - 1;
	int attNumU = randomNumberInt(1, 20);
	vector<Unit> attU = {};
	for (int i = 0; i < attNumU; i++) {
		attU.push_back(attRos.getUnitAtIndex(randomNumberInt(attSize)));
	}

	Player attacker{};
	attacker.setDebug(debug);
	attacker.setFaction(attFac);
	attacker.setGeneral(attGen);
	attacker.setAdvCombatDeck(randomNumberInt(1));
	attacker.setReinforcements(randomNumberInt(1, 10));
	attacker.setPlayerUnits(attU);

	Monster monster = {};
	monster.setMonsterType(intToMType(randomNumberInt(1, 6)));
	monster.setTreasure(treasure);

	battle.setPlayer(attacker);
	battle.setMonster(monster);
}

//These 5 functions create a vector of results from creating and calculating battles with randomized information
//that is sent to PredictionOutput()
//They are used for asymmetrical, randomized battle testing
void battleTestRand(int tests, NormalBattle battle, bool debug, Treasure& treasure) {
	if (debug) { cout << "Normal battleTestRand called" << endl; }
	
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		testSetupRand(battle, debug, treasure);
		if (debug) { cout << "Testing once, calling calculate normal" << endl; }
		battle.calculateNormal();
		if (debug) { cout << "calculateNormal finished" << endl; }
		resultsRaw.push_back((int)battle.getOutcome());
		if (debug) { cout << "ResultsRaw pushed: " << (int)battle.getOutcome() << endl; }
		cout << "Normal Battle results:" << endl;
		if (debug) { cout << "Attacker units in vector: " << battle.getAttacker().getPlayerUnits().size() << endl; }
		if (debug) { cout << "Defender units in vector: " << battle.getDefender().getPlayerUnits().size() << endl; }
		predictionOutput(resultsRaw);
	}
	else
	{
		for (int i = 0; i < tests; i++)
		{
			testSetupRand(battle, debug, treasure);
			NormalBattle norm = battle;
			norm.setOutput(debug);
			norm.setDebug(debug);
			norm.calculateNormal();
			resultsRaw.push_back((int)norm.getOutcome());
			if (debug) { cout << "ResultsRaw pushed: " << (int)norm.getOutcome() << endl; }
			if (debug) { cout << endl << endl << endl << endl; }
		}
		cout << "Normal Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}

void battleTestRand(int tests, SiegeBattle battle, bool debug, Treasure& treasure) {
	if (debug) { cout << "Siege battleTestRand called" << endl; }
	testSetupRand(battle, debug, treasure);
	battle.setCatapults(randomNumberInt(5));
	battle.setRams(randomNumberInt(5));
	battle.setSiegeTowers(randomNumberInt(5));
	battle.setTownLevel(randomNumberInt(1,5));
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		testSetupRand(battle, debug, treasure);
		battle.setCatapults(randomNumberInt(5));
		battle.setRams(randomNumberInt(5));
		battle.setSiegeTowers(randomNumberInt(5));
		battle.setTownLevel(randomNumberInt(1, 5));
		if (debug) { cout << "Testing once, calling calculate siege" << endl; }
		battle.calculateSiege();
		if (debug) { cout << "calculateSiege finished" << endl; }
		resultsRaw.push_back((int)battle.getOutcome());
		if (debug) { cout << "ResultsRaw pushed: " << (int)battle.getOutcome() << endl; }
		cout << "Siege Battle results:" << endl;
		if (debug) { cout << "Attacker units in vector: " << battle.getAttacker().getPlayerUnits().size() << endl; }
		if (debug) { cout << "Defender units in vector: " << battle.getDefender().getPlayerUnits().size() << endl; }
		predictionOutput(resultsRaw);
	}
	else
	{
		for (int i = 0; i < tests; i++)
		{
			testSetupRand(battle, debug, treasure);
			battle.setCatapults(randomNumberInt(5));
			if (debug) { cout << "Catapults set to 5 " << endl; }
			battle.setRams(randomNumberInt(5));
			if (debug) { cout << "Rams attacker set to 5 " << endl; }
			battle.setSiegeTowers(randomNumberInt(5));
			if (debug) { cout << "Siege towers attacker set to 5 " << endl; }
			battle.setTownLevel(randomNumberInt(1, 5));
			if (debug) { cout << "town level set to 5 " << endl; }
			SiegeBattle norm = battle;
			norm.setOutput(debug);
			norm.setDebug(debug);
			norm.calculateSiege();
			resultsRaw.push_back((int)norm.getOutcome());
			if (debug) { cout << "ResultsRaw pushed: " << (int)norm.getOutcome() << endl; }
			if (debug) { cout << endl << endl << endl << endl; }
		}
		cout << "Siege Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}

void battleTestRand(int tests, RaidBattle battle, bool debug, Treasure& treasure) {
	if (debug) { cout << "Raid battleTestRand called" << endl; }
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		testSetupRand(battle, debug, treasure);
		battle.setTownLevel(randomNumberInt(1, 5));
		if (debug) { cout << "Testing once, calling calculate raid" << endl; }
		battle.calculateRaid();
		if (debug) { cout << "calculateSiege finished" << endl; }
		resultsRaw.push_back((int)battle.getOutcome());
		if (debug) { cout << "ResultsRaw pushed: " << (int)battle.getOutcome() << endl; }
		cout << "raid Battle results:" << endl;
		if (debug) { cout << "Attacker units in vector: " << battle.getAttacker().getPlayerUnits().size() << endl; }
		if (debug) { cout << "Defender units in vector: " << battle.getDefender().getPlayerUnits().size() << endl; }
		predictionOutput(resultsRaw);
	}
	else
	{

		for (int i = 0; i < tests; i++)
		{
			testSetupRand(battle, debug, treasure);
			battle.setTownLevel(randomNumberInt(1, 5));
			RaidBattle norm = battle;
			norm.setOutput(debug);
			norm.setDebug(debug);
			norm.calculateRaid();
			resultsRaw.push_back((int)norm.getOutcome());
			if (debug) { cout << "ResultsRaw pushed: " << (int)norm.getOutcome() << endl; }
			if (debug) { cout << endl << endl << endl << endl; }
		}
		cout << "Raid Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}

void battleTestRand(int tests, NavalBattle battle, bool debug, Treasure& treasure) {
	if (debug) { cout << "Naval battleTestRand called" << endl; }
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		testSetupRand(battle, debug, treasure);
		battle.setAttackerShips(randomNumberInt(1, 10));
		battle.setDefenderShips(randomNumberInt(1, 10));
		if (debug) { cout << "Testing once, calling calculate naval" << endl; }
		battle.calculateNaval();
		if (debug) { cout << "calculateNaval finished" << endl; }
		resultsRaw.push_back((int)battle.getOutcome());
		if (debug) { cout << "ResultsRaw pushed: " << (int)battle.getOutcome() << endl; }
		cout << "Naval Battle results:" << endl;
		if (debug) { cout << "Attacker units in vector: " << battle.getAttacker().getPlayerUnits().size() << endl; }
		if (debug) { cout << "Defender units in vector: " << battle.getDefender().getPlayerUnits().size() << endl; }
		predictionOutput(resultsRaw);
	}
	else
	{

		for (int i = 0; i < tests; i++)
		{
			testSetupRand(battle, debug, treasure);
			battle.setAttackerShips(randomNumberInt(1, 10));
			battle.setDefenderShips(randomNumberInt(1, 10));
			NavalBattle norm = battle;
			norm.setOutput(debug);
			norm.setDebug(debug);
			norm.calculateNaval();
			resultsRaw.push_back((int)norm.getOutcome());
			if (debug) { cout << "ResultsRaw pushed: " << (int)norm.getOutcome() << endl; }
			if (debug) { cout << endl << endl << endl << endl; }
		}
		cout << "Naval Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}

void battleTestRand(int tests, MonsterBattle battle, bool debug, Treasure& treasure) {
	if (debug) { cout << "Monster battleTestRand called" << endl; }
	vector<int> resultsRaw{};

	if (debug) { cout << "tests to do: " << tests << endl; }
	if (tests <= 1)
	{
		testSetupRand(battle, debug, treasure);
		if (debug) { cout << "Testing once, calling calculate monster" << endl; }
		battle.calculateMonster();
		if (debug) { cout << "calculateMonster finished" << endl; }
		resultsRaw.push_back((int)battle.getOutcome());
		if (debug) { cout << "ResultsRaw pushed: " << (int)battle.getOutcome() << endl; }
		cout << "Monster Battle results:" << endl;
		if (debug) { cout << "Attacker units in vector: " << battle.getPlayer().getPlayerUnits().size() << endl; }
		predictionOutput(resultsRaw);
	}
	else
	{

		for (int i = 0; i < tests; i++)
		{
			testSetupRand(battle, debug, treasure);
			MonsterBattle norm = battle;
			norm.setOutput(debug);
			norm.setDebug(debug);
			norm.calculateMonster();
			resultsRaw.push_back((int)norm.getOutcome());
			if (debug) { cout << "ResultsRaw pushed: " << (int)norm.getOutcome() << endl; }
			if (debug) { cout << endl << endl << endl << endl; }
		}
		cout << "Monster Battle results:" << endl;
		predictionOutput(resultsRaw);
	}
	return;
}

//Runs numerous battle tests with asymmetric, randomized values
void randomizedTests(int tests, bool debug) {

	Treasure treasure{};
	treasure.setDebug(debug);
	treasure.initializeTreasure();

	NormalBattle normal{};
	normal.setTreasure(treasure);
	normal.setDebug(debug);
	if (debug) { cout << "Normal battle initialized void" << endl; }
	battleTestRand(tests, normal, debug, treasure);
	if (debug) { cout << "Tested Normal battle" << endl; }
	if (debug) { cin.get(); }

	SiegeBattle siege{};
	siege.setTreasure(treasure);
	siege.setDebug(debug);
	if (debug) { cout << "Siege battle initialized void" << endl; }
	battleTestRand(tests, siege, debug, treasure);
	if (debug) { cout << "Tested Siege battle" << endl; }
	if (debug) { cin.get(); }

	RaidBattle raid{};
	raid.setTreasure(treasure);
	raid.setDebug(debug);
	if (debug) { cout << "Raid battle initialized void" << endl; }
	battleTestRand(tests, raid, debug, treasure);
	if (debug) { cout << "Tested Raid battle" << endl; }
	if (debug) { cin.get(); }

	NavalBattle naval{};
	naval.setTreasure(treasure);
	naval.setDebug(debug);
	if (debug) { cout << "Naval battle initialized void" << endl; }
	battleTestRand(tests, naval, debug, treasure);
	if (debug) { cout << "Tested Naval battle" << endl; }
	if (debug) { cin.get(); }

	MonsterBattle monster{};
	if (debug) { cout << "Monster battle initialized void" << endl; }
	monster.setDebug(debug);
	if (debug) { cout << "Monster battle treasure set" << endl; }
	battleTestRand(tests, monster, debug, treasure);
	if (debug) { cout << "Tested Monster battle" << endl; }
	if (debug) { cin.get(); }
}

//Called on program start
int main()
{
	bool cont = true;

	while(cont) {
		bool debug = false;
		char toDebug = 'a';//Placeholder character

		while (toDebug != 'y' && toDebug != 'n')
		{
			cout << "Would you like to debug? (y/n)" << endl;
			cin >> toDebug;
			cin.get();
		//	cout << toDebug <<  endl;
		}
		if (toDebug == 'y')
		{
			debug = true;
		}

		if (debug) { cout << "Program started" << endl; }

		int tests = 1;
		cout << "How many tests:" << endl;
		cin >> tests;
		cin.get();
		tests = abs(tests);
		if (debug) { cout << "Tests set to: " << tests << endl; }
	
		char randomTest = 'a';
		while (randomTest != 'y' && randomTest != 'n')
		{
			cout << "Would you like to test with randomized values? (y/n)" << endl;
			cin >> randomTest;
			cin.get();
			//	cout << toDebug <<  endl;
		}
	
		if (randomTest == 'y') {
			randomizedTests(tests, debug);
		}
		else {
			standardTests(tests, debug);
		}

		if (debug) { cout << "Program finished" << endl; }
		cin.get();//This keeps the console window open
		
		char toCont = 'a';
		while (toCont != 'y' && toCont != 'n')
		{
			cout << "Would you like to make more calculations? (y/n)" << endl;
			cin >> toCont;
			cin.get();
			//	cout << toDebug <<  endl;
		}
		if (toCont == 'y') {
			cont = true;
		}
		else {
			cont = false;
		}
	}
	

	return 0;
}
