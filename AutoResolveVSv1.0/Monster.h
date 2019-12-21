#pragma once
#include "Equipment.h"
#include "monsterType.h"
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
class Monster //is used in monster battles
{
private:
	Treasure *treasure; //maybe make into a pointer?
	monsterType type;
	int coinReward;
	int autoResValue; //*10 + 10
	bool debug;

public:
	~Monster();
	Monster();
	Monster(monsterType typeI, Treasure& treasureI);

	int getCoinReward() { 
		if (debug) { cout << "monster coin reward gotten" << endl; }
		return coinReward; 
	};
	int getARValue() { 
		if (debug) { cout << "monster autoresolve value gotten" << endl; }
		return autoResValue; 
	};
	monsterType getMonsterType() { 
		if (debug) { cout << "monster monster type gotten" << endl; }
		return type; 
	};

	void setCoinReward(int coinRewardI) { 
		if (debug) { cout << "monster coin reward set" << endl; }
		coinReward = coinRewardI; 
	};
	void setAutoResValue(int autoResValI) { 
		if (debug) { cout << "monster autoresolve value set" << endl; }
		autoResValue = autoResValI; 
	};
	void setMonsterType(monsterType monTypeI) { 
		if (debug) { cout << "monster monster type set" << endl; }
		type = monTypeI; 
		if (debug) { cout << "calling setValuesFromMonsterType" << endl; }
		setValuesFromMonsterType();
	};

	bool getDebug() { return debug; }
	void setDebug(bool debugI) {
		debug = debugI;
		treasure->setDebug(debug);
	};

	void setValuesFromMonsterType();
	vector<Equipment> getEquipRewards(); //This gets the rewards associated with the type of Monster
};