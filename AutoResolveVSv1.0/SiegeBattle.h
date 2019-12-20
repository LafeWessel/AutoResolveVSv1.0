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

	int getRams() { 
		if (debug) { cout << "siege rams gotten" << endl; }
		return rams; 
	};
	int getCatapults() {
		if (debug) { cout << "siege catapults gotten" << endl; }
		return catapults;
	};
	int getSiegeTowers() {
		if (debug) { cout << "siege towers gotten" << endl; }
		return siegeTowers; 
	};
	townStats getTownLevel() {
		if (debug) { cout << "siege town stats gotten" << endl; }
		return townLevel; 
	};


	void setRams(int ramsI) {
		if (debug) { cout << "siege rams set" << endl; }
		rams = ramsI; 
	};
	void setCatapults(int catapultsI) {
		if (debug) { cout << "siege catapults set" << endl; }
		catapults = catapultsI; 
	};
	void setSiegeTowers(int siegeTowersI) { 
		if (debug) { cout << "siege towers set" << endl; }
		siegeTowers = siegeTowersI; 
	};
	void setTownLevel(int townLevelI) {
		if (debug) { cout << "siege town level set" << endl; }
		townLevel = townLevelI; 
	};
};

