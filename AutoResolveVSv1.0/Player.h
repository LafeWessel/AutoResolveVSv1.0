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

	vector<Unit> getPlayerUnits() { 
		if (debug) { cout << "player unit vector gotten" << endl; }
		return playerUnits; 
	};
	int getMelee() { 
		if (debug) { cout << "player melee autoresolve bonus gotten" << endl; }
		return Melee; 
	};
	int getCavalry() { 
		if (debug) { cout << "player cavalry autoresolve bonus gotten" << endl; }
		return Cavalry; 
	};
	int getRanged() { 
		if (debug) { cout << "player ranged autoresolve bonus gotten" << endl; }
		return Ranged; 
	};
	General getGeneral() { 
		if (debug) { cout << "player general gotten" << endl; }
		return general; 
	};
	bool getAdvComDeck() { 
		if (debug) { cout << "player advanced combat deck gotten" << endl; }
		return AdvCombatDeck; 
	};
	faction getFaction() {
		if (debug) { cout << "player faction gotten" << endl; }
		return Fact; 
	};
	Unit getUnitAtIndex(int index) { 
		if (debug) { cout << "player getting unit at index" << endl; }
		if (index >= 0 && index < playerUnits.size()){
			return playerUnits[index];
		}
		else{
			cerr << "player invalid unit vector index selected: " << index << endl;
			return Unit{};
		}
	};
	int getNumberOfUnits() { 
		if (debug) { cout << "player number of units gotten" << endl; }
		return playerUnits.size(); 
	};
	playerType getPlayerType() {
		if (debug) { cout << "player player type gotten" << endl; }
		return player; 
	};

	void setReinforcements(int ReinforceI);
	void setPlayerUnits(vector<Unit> unitsI);
	void setMelee(int meleeI) { 
		if (debug) { cout << "player melee autoresolve bonus set" << endl; }
		Melee = meleeI; 
	};
	void setCavalry(int cavalryI) { 
		if (debug) { cout << "player cavalry autoresolve bonus set" << endl; }
		Cavalry = cavalryI; 
	};
	void setRanged(int rangedI) { 
		if (debug) { cout << "player ranged autoresolve bonus set" << endl; }
		Ranged = rangedI; 
	};
	void setGeneral(General generalI) { 
		if (debug) { cout << "player general set" << endl; }
		general = generalI;
		general.setDebug(debug);
	};
	void setAdvCombatDeck(bool advComDeckI) { 
		if (debug) { cout << "player advanced combat deck set" << endl; }
		AdvCombatDeck = advComDeckI; 
	};
	void setFaction(faction factionI) { 
		if (debug) { cout << "player faction set" << endl; }
		Fact = factionI; 
	};
	void setUnitAtIndex(int index, Unit unitI) { 
		if (debug) { cout << "player unit at index set" << endl; }
		if (index >= 0 && index < playerUnits.size()) {
			unitI.setDebug(debug);
			playerUnits[index] = unitI;
		}
		else {
			cerr << "player invalid set unit vector index selected: " << index<< endl;
		}
		 };
	void setPlayerType(playerType playerI) { 
		if (debug) { cout << "player player type set" << endl; }
		player = playerI;
	};
	
	bool getDebug() { return debug; }
	void setDebug(bool debugI) { 
		debug = debugI;
		general.setDebug(debug);
		for (int i = 0; i < playerUnits.size(); i++) {
			playerUnits[i].setDebug(debug);
		}
	}
};
