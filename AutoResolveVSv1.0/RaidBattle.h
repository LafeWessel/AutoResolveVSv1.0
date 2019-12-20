#pragma once
#include "Battle.h"
#include "townStats.h"
//#include <algorithm>
//#include <cmath>

//#include <array>
//#include <vector>
//#include <string>

//#include <fstream>
//#include <iostream>
//#include <sstream>
//#include <stdexcept>
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

	townStats getTownLevel() { 
		if (debug) { cout << "raid town stats gotten" << endl; }
		return townLevel; 	
	};

	void setTownLevel(int townLevelI) { 
		if (debug) { cout << "town level set" << endl; }
		townLevel = townLevelI; };
};

