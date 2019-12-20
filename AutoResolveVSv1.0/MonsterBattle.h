#pragma once
#include "Monster.h"
#include "outcome.h"
#include "Player.h"
#include "Treasure.h"

#include <algorithm>
#include <cmath>

#include <array>
#include <vector>
#include <string>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;
class MonsterBattle //This is the only type of battle that does NOT inherit from the Battle class
{
private:
	Treasure treasure;
	Player attacker;
	Monster monster;
	outcome result;
	bool output;
	bool debug;

public:
	~MonsterBattle();
	MonsterBattle();
	MonsterBattle(Player attackerI, Monster monsterI);

	void monsterOutput(vector<int>& totalCasualties);
	void monsterCasualties(vector<int>& attackerCasVec); //Calculates the casualties, needs only a 1D vector since there is only 1 Player
	void calculateMonster(); //Calculates the outcome and calls Casualty and output functions

	int getEnding() { return (int)result; };
	Player getPlayer() { return attacker; };
	Monster getMonster() { return monster; };
	outcome getOutcome() { return result; };
	bool getOutputBool() { return output; };
	bool getDebug() { return debug; };

	void setPlayer(Player playerI) { attacker = playerI; };
	void setMonster(Monster monsterI) { monster = monsterI; };
	void setOutcome(outcome resultI) { result = resultI; };
	void setOutput(bool outputI) { output = outputI; };
	void setDebug(bool debugI) { debug = debugI; };
};

