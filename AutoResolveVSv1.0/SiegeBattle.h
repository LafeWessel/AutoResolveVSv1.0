#pragma once
#include "Battle.h"
#include "townStats.h"
#include "Player.h"
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
class SiegeBattle : public Battle
{
private:
	int rams;
	int catapults;
	int siegeTowers;
	townStats townLevel;

public:

	SiegeBattle();
	SiegeBattle(Player attackerI, Player defenderI, int ramsI, int catapultsI, int siegeTowersI, townStats townLevelI);
	~SiegeBattle();

	void SiegeOutput(vector<vector<int>> totalCasualties);
	void calculateSiege();

	int getRams() { return rams; };
	int getCatapults() { return catapults; };
	int getSiegeTowers() { return siegeTowers; };
	townStats& getTownStats() { return townLevel; };

	void setRams(int ramsI) { rams = ramsI; };
	void setCatapults(int catapultsI) { catapults = catapultsI; };
	void setSiegeTowers(int siegeTowersI) { siegeTowers = siegeTowersI; };
	void setTownLevel(int townLevelI) { townLevel = townLevelI; };
};

