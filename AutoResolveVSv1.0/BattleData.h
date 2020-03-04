#pragma once
#include "battleType.h"
#include "townStats.h"
#include "outcome.h"
#include "Battle.h"
#include "RaidBattle.h"
#include "NavalBattle.h"
#include "NormalBattle.h"
#include "SiegeBattle.h"
#include "MonsterBattle.h"


class BattleData
{

private:
	
	vector<int> data;

public:
	BattleData();

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

};

