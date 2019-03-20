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
class NormalBattle : public Battle
{
private:

public:
	~NormalBattle();
	NormalBattle();
	NormalBattle(Player attackerI, Player defenderI);

	void normalOutput(vector<vector<int>> totalCasualties);
	void calculateNormal();
	//needs no specific getters and setters
};

