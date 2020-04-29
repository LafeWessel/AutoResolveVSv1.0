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
	NormalBattle(bool debugI);
	NormalBattle(Player attackerI, Player defenderI);
	NormalBattle(Player attackerI, Player defenderI, bool fileOutI, string fileNameI);

	void normalOutput(vector<vector<int>> totalCasualties);
	void calculateNormal();
	//needs no specific getters and setters,
	//everything needed inherited from Battle

	void printDataNormal();
};

