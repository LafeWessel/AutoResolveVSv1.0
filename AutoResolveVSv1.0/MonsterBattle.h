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

	int getEnding() { 
		if (debug) { cout << "monster battle ending gotten" << endl; }
			return (int)result;
	};
	Player getPlayer() { 
		if (debug) { cout << "monster battle player gotten" << endl; }
		return attacker; 
	};
	Monster getMonster() { 
		if (debug) { cout << "monster battle monster gotten" << endl; }
		return monster; 
	};
	outcome getOutcome() { 
		if (debug) { cout << "monster battle outcome gotten" << endl; }
		return result; 
	};

	void setPlayer(Player playerI) { 
		if (debug) { cout << "monster battle player set" << endl; }
		attacker = playerI;
		attacker.setDebug(debug);
	};
	void setMonster(Monster monsterI) { 
		if (debug) { cout << "monster battle monster set" << endl; }
		monster = monsterI;
		monster.setDebug(debug);
	};
	void setOutcome(outcome resultI) { 
		if (debug) { cout << "monster battle outcome set" << endl; }
		result = resultI;
	};

	bool getOutput() { return output; };
	bool getDebug() { return debug; };
	void setOutput(bool outputI) { output = outputI; };
	void setDebug(bool debugI) {	
		debug = debugI;
		attacker.setDebug(debug);
		monster.setDebug(debug);
	};
};

