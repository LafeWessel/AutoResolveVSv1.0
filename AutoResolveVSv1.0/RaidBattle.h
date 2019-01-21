#pragma once
#include "Battle.h"
#include "townStats.h"
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

class RaidBattle : public Battle
{
private:
	townStats townLevel;

public:
	~RaidBattle();
	RaidBattle();
	RaidBattle(Player attackerI, Player defenderI, townStats townLevelI);

	void raidOutput(vector<vector<int>> totalCasualties, int suppGained);
	void calculateRaid();

	townStats& getTownStats() { return townLevel; };

	void setTownLevel(int townLevelI) { townLevel = townLevelI; };
};