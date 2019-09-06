#pragma once
#include "faction.h"
#include "General.h"
#include "Player.h"
#include "playerType.h"
#include "Roster.h"
#include "Unit.h"
#include <algorithm>
#include <cmath>

#include <array>
#include <vector>
#include <string>

//#include <fstream>
#include <iostream>
//#include <sstream>
//#include <stdexcept>
using namespace std;
class Player //This is used in every kind of battle.
{
private:

	vector<Unit> playerUnits; //vector of units that are in the player's army
	int Melee; //Melee autoresolve bonus total
	int Cavalry; //Cavalry autoresolve bonus total
	int Ranged; //Ranged autoresolve bonus total
	General general; //Lowercase because class name uses uppercase
	bool AdvCombatDeck;
	faction Fact;
	bool debug;
	int Reinforcements;
	playerType player;

	void setupUnitAutoresolveBonuses();

public:
	~Player();
	Player();
	Player(vector<Unit> unitsI, General generalI, int ReinforceI, bool AdvCombatDeckI, faction FactI, playerType type);

	vector<Unit>& getPlayerUnits() { return playerUnits; };
	int getMelee() { return Melee; };
	int getCavalry() { return Cavalry; };
	int getRanged() { return Ranged; };
	General& getGeneral() { return general; };
	bool getAdvComDeck() { return AdvCombatDeck; };
	faction& getFaction() { return Fact; };
	bool getDebug() { return debug; }
	Unit& getUnitAtIndex(int index) { return playerUnits[index]; };
	int getNumberOfUnits() { return playerUnits.size(); };
	playerType& getPlayerType() { return player; };

	void setPlayerUnits(vector<Unit> unitsI);
	void setMelee(int meleeI) { Melee = meleeI; };
	void setCavalry(int cavalryI) { Cavalry = cavalryI; };
	void setRanged(int rangedI) { Ranged = rangedI; };
	void setGeneralG(General generalI) { general = generalI; };
	void setAdvCombatDeck(bool advComDeckI) { AdvCombatDeck = advComDeckI; };
	void setFaction(faction factionI) { Fact = factionI; };
	void setDebugBool(bool debugI) { debug = debugI; }
	void setReinforcements(int ReinforceI);
	void setUnitAtIndex(int index, Unit unitI) { playerUnits[index] = unitI; };
	void setPlayerType(playerType playerI) { player = playerI; };



};
