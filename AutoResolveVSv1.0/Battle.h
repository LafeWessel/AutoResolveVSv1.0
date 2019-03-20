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

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;



class Battle // siege, raid, normal and naval battles inherit from this class
{

protected:
	Player attacker;
	Player defender;
	outcome result;
	bool output;
	bool debug;


public:
	~Battle();
	Battle();
	Battle(Player attackerI, Player defenderI);

	Player& getAttacker() { return attacker; };
	Player& getDefender() { return defender; };
	outcome& getOutcome() { return result; };
	int getEnding() { return (int)result; };
	bool getOutputBool() { return output; }
	bool getDebugBool() { return debug; }

	void setAttacker(Player attackerI) { attacker = attackerI; };
	void setDefender(Player defenderI) { defender = defenderI; };
	void setOutcome(outcome resultI) { result = resultI; };
	void setOutput(bool outputI) { output = outputI; };
	void setDebug(bool debugI) { debug = debugI; };

	void treasureResults(); //Determines whether or not loot is found at the end of a battle.
	void CalculateCas(vector<vector<int>>& totalCasualties); //Determines the amount of casualties at the end of a battle
	void battleOutput(vector<vector<int>> totalCasualties); //Output at battle, normally supplemented by other output in inherited classes
	float battleCalculate(); //Calculates the battle, is almost always supplemented by other calculations in inherited classes
};




