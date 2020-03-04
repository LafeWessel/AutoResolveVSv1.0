#pragma once
#include "battleType.h"
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



	

};

