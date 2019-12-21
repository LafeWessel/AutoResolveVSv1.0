#pragma once
#include "outcome.h"
#include "Player.h"
#include "Treasure.h"
#include <algorithm>
#include <cmath>

#include <array>
#include <vector>
#include <string>
#include <chrono>
#include <random>

//#include <fstream>
#include <iostream>
//#include <sstream>
//#include <stdexcept>
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


public:
	~Battle();
	Battle();
	Battle(Player attackerI, Player defenderI);

	int randomNumberBattle(int range);
	int calculateBattleRandoms(int randomRolls, int randomRange);
	int randomNumberCas(int range);
	string outputGenState(int state);

	Player getAttacker() { 
		if (debug) { cout << "battle attacker gotten: " << (int)attacker.getPlayerType() << endl; }
		return attacker; 
	};
	Player getDefender() { 
		if (debug) { cout << "battle defender gotten: " << (int)defender.getPlayerType() << endl; }
		return defender; 
	};
	outcome getOutcome() { 
		if (debug) { cout << "battle outcome gotten: " << (int)result << endl; }
		return result; 
	};
	/*
	int getOutcome() { //returns outcome as an int
		//TODO-remove and just use getOutcome and cast to and int
		if (debug) { cout << "battle ending gotten" << endl; }
		return (int)result; 
	};
	*/
	void setAttacker(Player attackerI) { 
		if (debug) { cout << "battle attacker set to: " << (int)attackerI.getPlayerType() << endl; }
		attacker = attackerI;
		attacker.setDebug(debug);
	};
	void setDefender(Player defenderI) { 
		if (debug) { cout << "battle defender set to: " << (int)defenderI.getPlayerType() << endl; }
		defender = defenderI; 
		defender.setDebug(debug);
	};
	void setOutcome(outcome resultI) { 
		if (debug) { cout << "battle outcome set to: " << (int)resultI << endl; }
		result = resultI; 
	};

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

	void treasureResults(); //Determines whether or not loot is found at the end of a battle.
	void CalculateCas(vector<vector<int>>& totalCasualties); //Determines the amount of casualties at the end of a battle
	void battleOutput(vector<vector<int>>& totalCasualties); //Output at battle, normally supplemented by other output in inherited classes
	float battleCalculate(); //Calculates the battle, is almost always supplemented by other calculations in inherited classes
};




