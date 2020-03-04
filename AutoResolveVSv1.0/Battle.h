#pragma once
#include "outcome.h"
#include "Player.h"
#include "Treasure.h"
#include "battleType.h"
#include <algorithm>
#include <cmath>

#include <array>
#include <vector>
#include <string>
#include <chrono>
#include <random>

#include <iostream>

using namespace std;



class Battle // siege, raid, normal and naval battles inherit from this class
{

protected:
	Treasure *treasure;
	Player attacker;
	Player defender;
	outcome result;
	bool output;
	bool debug;
	battleType type;


public:
	~Battle();
	Battle();
	Battle(Player attackerI, Player defenderI);

	int randomNumberBattle(int range);
	int calculateBattleRandoms(int randomRolls, int randomRange);
	int randomNumberCas(int range);
	string outputGenState(int state);

	Player getAttacker() { 
		return attacker; };
	Player getDefender() { 
		return defender; };
	outcome getOutcome() { 
		if (debug) { cout << "battle outcome gotten: " << (int)result << endl; }
		return result; };
	battleType getType() {
		return type; };

	void setAttacker(Player attackerI) { 
		attacker = attackerI;
		attacker.setDebug(debug);};
	void setDefender(Player defenderI) { 
		defender = defenderI; 
		defender.setDebug(debug);};
	void setOutcome(outcome resultI) { 
		if (debug) { cout << "battle outcome set to: " << (int)resultI << endl; }
		result = resultI; };

	bool getOutputBool() { return output; };
	bool getDebugBool() { return debug; };
	void setOutput(bool outputI) { output = outputI; };
	void setDebug(bool debugI) { 
		if (debugI) { cout << "battle setDebug called" << endl; }
		debug = debugI; 
		treasure->setDebug(debug);
		attacker.setDebug(debug);
		defender.setDebug(debug);
	};
	void setTreasure(Treasure& treasureI) {
		treasure = &treasureI;
		treasure->setDebug(treasureI.getDebug());
	};
	void printData();

	void treasureResults(); //Determines whether or not loot is found at the end of a battle.
	void CalculateCas(vector<vector<int>>& totalCasualties); //Determines the amount of casualties at the end of a battle
	void assignCasualties(vector<int>& casualties, int playerType); //assigns casualties to a player
	void battleOutput(vector<vector<int>>& totalCasualties); //Output at battle, normally supplemented by other output in inherited classes
	float battleCalculate(); //Calculates the battle, is almost always supplemented by other calculations in inherited classes
};




