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
	data[7] = p.getGeneral().getRank();
	data[8] = p.getGeneral().getARBonus();
	data[9] = p.getGeneral().getArmor().getABonus();
	data[10] = p.getGeneral().getWeapon().getABonus();
	data[11] = p.getGeneral().getFollower().getABonus();
	data[12] = p.getGeneral().getBanner().getABonus();
	data[13] = p.getGeneral().getTrinket().getABonus();
	data[14] = p.getAdvComDeck();
	data[15] = p.getMelee() + p.getRanged() + p.getCavalry();
	data[16] = p.getMelee();
	data[17] = p.getRanged();
	data[18] = p.getCavalry();
	data[19] = p.getTotalSoldiers();
	data[63] = p.getNumberOfUnits();
	data[64] = p.getReinforcements();
	setAttackerUnitTotals(p.getPlayerUnits());
}

void BattleData::setDefender(Player& p) {
	data[75] = p.getGeneral().getRank();
	data[76] = p.getGeneral().getARBonus();
	data[77] = p.getGeneral().getArmor().getABonus();
	data[78] = p.getGeneral().getWeapon().getABonus();
	data[79] = p.getGeneral().getFollower().getABonus();
	data[80] = p.getGeneral().getBanner().getABonus();
	data[81] = p.getGeneral().getTrinket().getABonus();
	data[82] = p.getAdvComDeck();
	data[83] = p.getMelee() + p.getRanged() + p.getCavalry();
	data[84] = p.getMelee();
	data[85] = p.getRanged();
	data[86] = p.getCavalry();
	data[87] = p.getTotalSoldiers();
	data[131] = p.getNumberOfUnits();
	data[132] = p.getReinforcements();
	setDefenderUnitTotals(p.getPlayerUnits());
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

void BattleData::setAttackerEnd(Player& p) {
	data[20] = p.getMelee() + p.getRanged() + p.getCavalry();
	data[21] = p.getMelee();
	data[22] = p.getRanged();
	data[23] = p.getCavalry();
	data[24] = p.getTotalSoldiers();
}

void BattleData::setDefenderEnd(Player& p) {
	data[88] = p.getMelee() + p.getRanged() + p.getCavalry();
	data[89] = p.getMelee();
	data[90] = p.getRanged();
	data[91] = p.getCavalry();
	data[92] = p.getTotalSoldiers();
}


vector<string> BattleData::getUnitNames() { //Returns a vector of the names of all the units in units.txt
	//Create 4 rosters, one for each faction, then read in their units and add them to the data column
	Roster rebel = Roster();
	rebel.setFaction(faction::rebel);
	rebel.buildRoster();
	Roster beladimir = Roster();
	beladimir.setFaction(faction::beladimir);
	beladimir.buildRoster();
	Roster lerastir = Roster();
	lerastir.setFaction(faction::lerastir);
	lerastir.buildRoster();
	Roster menoriad = Roster();
	menoriad.setFaction(faction::menoriad);
	menoriad.buildRoster();

	vector<string> names = {}; //Will contain the names of all the units available
	for (int i = 0; i < rebel.getNumberOfUnits(); i++) {
		names.push_back(rebel.getUnitAtIndex(i).getName());
	}
	for (int i = 0; i < beladimir.getNumberOfUnits(); i++) {
		names.push_back(beladimir.getUnitAtIndex(i).getName());
	}
	for (int i = 0; i < lerastir.getNumberOfUnits(); i++) {
		names.push_back(lerastir.getUnitAtIndex(i).getName());
	}
	for (int i = 0; i < menoriad.getNumberOfUnits(); i++) {
		names.push_back(menoriad.getUnitAtIndex(i).getName());
	}

	return names;
}

void BattleData::setAttackerUnitTotals(vector<Unit> u) {
	vector<string> names = getUnitNames();
	vector<int> totalUnits(names.size());
	for (int i = 0; i < totalUnits.size(); i++) {
		totalUnits[i] = 0;
	}

	//Increments the correct column to count the number of units of a certain type in the vector
	for (int i = 0; i < u.size(); i++) {
		for (int j = 0; j < names.size(); i++) {
			if (u[i].getName() == names[j]) {
				totalUnits[j]++;
			}
		}
	}
	for (int i = 0; i < totalUnits.size(); i++) {
		data[i + 25] = totalUnits[i];
	}

}

void BattleData::setDefenderUnitTotals(vector<Unit> u) {
	vector<string> names = getUnitNames();
	vector<int> totalUnits(names.size());
	for (int i = 0; i < totalUnits.size(); i++) {
		totalUnits[i] = 0;
	}

	//Increments the correct column to count the number of units of a certain type in the vector
	for (int i = 0; i < u.size(); i++) {
		for (int j = 0; j < names.size(); i++) {
			if (u[i].getName() == names[j]) {
				totalUnits[j]++;
			}
		}
	}
	for (int i = 0; i < totalUnits.size(); i++) {
		data[i + 93] = totalUnits[i];
	}

}
