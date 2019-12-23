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
		if (debug) { cout << "siege rams gotten: " << rams << endl; }
		return rams; };
	int getCatapults() {
		if (debug) { cout << "siege catapults gotten: " << catapults << endl; }
		return catapults;};
	int getSiegeTowers() {
		if (debug) { cout << "siege towers gotten: " << siegeTowers << endl; }
		return siegeTowers; };
	townStats getTownLevel() {
		if (debug) { cout << "siege town stats gotten: " << townLevel.getLevel() << endl; }
		return townLevel; };


	void setRams(int ramsI) {
		if (debug) { cout << "siege rams set to: " << ramsI << endl; }
		rams = ramsI; };
	void setCatapults(int catapultsI) {
		if (debug) { cout << "siege catapults set to: " << catapultsI << endl; }
		catapults = catapultsI; };
	void setSiegeTowers(int siegeTowersI) { 
		if (debug) { cout << "siege towers set to: " << siegeTowersI << endl; }
		siegeTowers = siegeTowersI; };
	void setTownLevel(int townLevelI) {
		if (debug) { cout << "siege town level set to: " << townLevelI << endl; }
		townLevel.setLevel(townLevelI);
		townLevel.setDebug(debug);};

	void setDebug(bool debugI) { 
		debug = debugI;
		townLevel.setDebug(debug);
		treasure->setDebug(debug);
		attacker.setDebug(debug);
		defender.setDebug(debug);
	}
	void printDataSiege();
};

