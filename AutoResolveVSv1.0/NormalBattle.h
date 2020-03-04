#pragma once
#include "Battle.h"

using namespace std;
class NormalBattle : public Battle
{
private:
	battleType type = battleType::Normal;
public:
	~NormalBattle();
	NormalBattle();
	NormalBattle(Player attackerI, Player defenderI);

	void normalOutput(vector<vector<int>> totalCasualties);
	void calculateNormal();
	//needs no specific getters and setters,
	//everything needed inherited from Battle

	void printDataNormal();
};

