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
	monsterType type;
	int coinReward;
	int autoResValue; //*10 + 10
	bool debug;

public:
	~Monster();
	Monster();
	Monster(monsterType typeI);

	int getCoinReward() { return coinReward; };
	int getARValue() { return autoResValue; };
	monsterType& getMonsterType() { return type; };
	bool getDebug() { return debug; }

	void setCoinReward(int coinRewardI) { coinReward = coinRewardI; };
	void setAutoResValue(int autoResValI) { autoResValue = autoResValI; };
	void setMonsterType(monsterType monTypeI) { type = monTypeI; };
	void setDebugBool(bool debugI) { debug = debugI; }

	vector<Equipment> getEquipRewards(); //This gets the rewards associated with the type of Monster
};