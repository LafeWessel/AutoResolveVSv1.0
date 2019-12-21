#pragma once
#include "Battle.h"
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
class NavalBattle : public Battle
{
private:
	int attackerShips;
	int defenderShips;

public:
	~NavalBattle();
	NavalBattle();
	NavalBattle(Player attackerI, Player defenderI, int attShipsI, int defShipsI);

	void navalOutput(vector<vector<int>> totalCasualties);
	void calculateNaval();

	int getAttackerShips() { 
		if (debug) { cout << "naval attacker ships gotten" << endl; }
		return attackerShips; 
	};
	int getDefenderShips() {
		if (debug) { cout << "naval defender ships gotten" << endl; }
		return defenderShips; 
	};

	void setAttackerShips(int attShipsI) { 
		if (debug) { cout << "naval attacker ships set to: " << attShipsI << endl; }
		attackerShips = attShipsI; 
	};
	void setDefenderShips(int defShipsI) { 
		if (debug) { cout << "naval defender ships set to: " << defShipsI << endl; }
		defenderShips = defShipsI; 
	};
};

