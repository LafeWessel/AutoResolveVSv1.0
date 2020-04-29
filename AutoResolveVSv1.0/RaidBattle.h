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
	battleType type = battleType::Raid;

public:
	~RaidBattle();
	RaidBattle();
	RaidBattle(bool debugI);
	RaidBattle(Player attackerI, Player defenderI, townStats townLevelI);

	void raidOutput(vector<vector<int>> totalCasualties, int suppGained);
	void calculateRaid();

	townStats getTownLevel() { 
		if (debug) { cout << "raid town stats gotten: " << townLevel.getLevel() << endl; }
		return townLevel; 	};

	void setTownLevel(int townLevelI) { 
		if (debug) { cout << "town level set to: " << townLevelI << endl; }
		townLevel.setLevel(townLevelI);
		townLevel.setDebug(debug);};

	void setDebug(bool debugI) {
		debug = debugI;
		townLevel.setDebug(debug);
		treasure->setDebug(debug);
		attacker.setDebug(debug);
		defender.setDebug(debug);
	}
	void printDataRaid();
};

