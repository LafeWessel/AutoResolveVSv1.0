#pragma once
#include "Equipment.h"
#include "monsterType.h"
#include "Treasure.h"
#include <algorithm>
#include <cmath>

#include <array>
#include <vector>
#include <string>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;
class Monster //is used in monster battles
{
private:
	Treasure *treasure;
	monsterType type;
	int coinReward;
	int autoResValue; //*10 + 10
	bool debug;

public:
	~Monster();
	Monster();
	Monster(bool debugI);
	Monster(monsterType typeI, Treasure& treasureI);

	int getCoinReward() { 
		if (debug) { cout << "monster coin reward gotten: " << coinReward << endl; }
		return coinReward; };
	int getARValue() { 
		if (debug) { cout << "monster autoresolve value gotten: " << autoResValue << endl; }
		return autoResValue; };
	monsterType getMonsterType() { 
		if (debug) { cout << "monster monster type gotten: " << (int)type << endl; }
		return type; };

	void setMonsterType(monsterType monTypeI) { 
		if (debug) { cout << "monster monster type set to: " << (int)monTypeI << endl; }
		type = monTypeI; 
		if (debug) { cout << "calling setValuesFromMonsterType" << endl; }
		setValuesFromMonsterType();}; 
	void setTreasure(Treasure& treasureI) {
		treasure = &treasureI;
		treasure->setDebug(treasureI.getDebug());};

	bool getDebug() { return debug; }
	void setDebug(bool debugI) {
		if (debugI) { cout << "monster setDebug called" << endl; }
		debug = debugI;
		treasure->setDebug(debug);
	};
	void printData();

	void setValuesFromMonsterType();
	vector<Equipment> getEquipRewards(); //This gets the rewards associated with the type of Monster
};