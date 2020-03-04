#include "BattleData.h"

BattleData::BattleData()
{
	//Makes sure the data array is the correct size/length
	int nItems = 141;
	for (int i = 0; i < nItems; i++) {
		data.push_back(0);
	}
}

void BattleData::setBattleType(battleType type) {
	data[0] = (int)type;
}

void BattleData::setAttacker(Player& p) {

	data[9] = p.getGeneral().getArmor().getABonus();
	data[10] = p.getGeneral().getWeapon().getABonus();
	data[11] = p.getGeneral().getFollower().getABonus();
	data[12] = p.getGeneral().getBanner().getABonus();
	data[13] = p.getGeneral().getTrinket().getABonus();

}

void BattleData::setDefender(Player& p) {

}

void BattleData::setAttackerRandoms(int rand) {
	data[1] = rand;
}

void BattleData::setDefenderRandoms(int rand) {
	data[2] = rand;
}

void BattleData::setAttackerGeneralState(int state) {
	data[68] = state;
}

void BattleData::setDefenderGeneralState(int state) {
	data[136] = state;
}

void BattleData::setSupplies(int supp) {
	data[6] = supp;
}

void BattleData::setOutcome(outcome o) {
	data[4] = (int)o;
}

void BattleData::setAttackerWon(bool won) {
	if (won) {
		data[5] = 1;
	}
	else {
		data[5] = 0;
	}
}

void BattleData::setAttackerCasualties(vector<int> cas) {
	data[67] = cas[0];
	data[66] = cas[1];
}

void BattleData::setDefenderCasualties(vector<int> cas) {
	data[135] = cas[0];
	data[134] = cas[1];
}

void BattleData::setAttackerTreasureRec(bool t) {
	if (t) {
		data[69] = 1;
	}
	else {
		data[69] = 0;
	}
}

void BattleData::setDefenderTreasureRec(bool t) {
	if (t) {
		data[137] = 1;
	}
	else {
		data[137] = 0;
	}
}

void BattleData::setAttackerShips(int ships) {
	data[71] = ships;
}

void BattleData::setDefenderShips(int ships) {
	data[139] = ships;
}

void BattleData::setAttackerUpgrades(int up) {
	data[65] = up;
}

void BattleData::setDefenderUpgrades(int up) {
	data[133] = up;
}

void BattleData::setRams(int ram) {
	data[72] = ram;
}

void BattleData::setSiegeTowers(int siege) {
	data[73] = siege;
}

void BattleData::setCatapults(int cat) {
	data[74] = cat;
}

void BattleData::setTownStats(townStats& ts) {
	data[140] = ts.getLevel();
}