#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "battleType.h"
#include "townStats.h"
#include "outcome.h"
#include "Player.h"
#include "Roster.h"
#include "Unit.h"

using namespace std;


class BattleData
{

private:
	
	vector<int> data;
	bool debug;

	vector<string> getUnitNames();
	void setAttackerUnitTotals(vector<Unit> u);
	void setDefenderUnitTotals(vector<Unit> u);

public:
	BattleData();
	BattleData(bool debugI);

	void setBattleType(battleType type);
	void setAttacker(Player& p);
	void setDefender(Player& p);
	void setAttackerRandoms(int rand);
	void setDefenderRandoms(int rand);
	void setAttackerGeneralState(int state);
	void setDefenderGeneralState(int state);
	void setSupplies(int supp);
	void setOutcome(outcome o);
	void setAttackerWon(bool won);
	void setAttackerCasualties(vector<int> cas);
	void setDefenderCasualties(vector<int> cas);
	void setAttackerTreasureRec(bool t);
	void setDefenderTreasureRec(bool t);
	void setAttackerShips(int ships);
	void setDefenderShips(int ships);
	void setAttackerUpgrades(int up);
	void setDefenderUpgrades(int up);
	void setRams(int ram);
	void setSiegeTowers(int siege);
	void setCatapults(int cat);
	void setTownStats(townStats& ts);
	void setAttackerEnd(Player& p);
	void setDefenderEnd(Player& p);

	void printData();
	void writeToFile(string fileName);
};

