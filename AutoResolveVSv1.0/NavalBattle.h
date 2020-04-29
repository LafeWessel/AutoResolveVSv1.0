#pragma once
#include "Battle.h"
//using namespace std;
class NavalBattle : public Battle
{
private:
	int attackerShips;
	int defenderShips;
	battleType type = battleType::Naval;

public:
	~NavalBattle();
	NavalBattle();
	NavalBattle(bool debugI);
	NavalBattle(Player attackerI, Player defenderI, int attShipsI, int defShipsI);
	NavalBattle(Player attackerI, Player defenderI, int attShipsI, int defShipsI, bool fileOutI, string fileNameI);

	void navalOutput(vector<vector<int>> totalCasualties);
	void calculateNaval();

	int getAttackerShips() { 
		if (debug) { cout << "naval attacker ships gotten: " << attackerShips << endl; }
		return attackerShips; };
	int getDefenderShips() {
		if (debug) { cout << "naval defender ships gotten: " << defenderShips << endl; }
		return defenderShips; };

	void setAttackerShips(int attShipsI) { 
		if (debug) { cout << "naval attacker ships set to: " << attShipsI << endl; }
		attackerShips = attShipsI; };
	void setDefenderShips(int defShipsI) { 
		if (debug) { cout << "naval defender ships set to: " << defShipsI << endl; }
		defenderShips = defShipsI; };

	void printDataNaval();
};

