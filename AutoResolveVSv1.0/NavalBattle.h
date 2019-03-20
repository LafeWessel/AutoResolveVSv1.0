#pragma once
#include "Battle.h"
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

	int getAttackerShips() { return attackerShips; };
	int getDefenderShips() { return defenderShips; };

	void setAttackerShips(int attShipsI) { attackerShips = attShipsI; };
	void setDefenderShips(int defShipsI) { defenderShips = defShipsI; };
};

