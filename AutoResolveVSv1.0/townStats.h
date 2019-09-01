#pragma once
#include "defenses.h"
#include <algorithm>
#include <cmath>

//#include <array>
//#include <vector>
//#include <string>

//#include <fstream>
//#include <iostream>
//#include <sstream>
//#include <stdexcept>
using namespace std;
class townStats //Is used in raid and siege battles to keep data on the town
{
private:
	int level;
	int supplies; //These are used more in Raid battles and can be used during campaigns
	defenses townDefense;
	bool debug;

public:
	~townStats();
	townStats();
	townStats(int levelI);

	int getSupplies() { return supplies; };
	defenses getDefenses() { return townDefense; };
	int getLevel() { return level; };
	bool getDebug() { return debug; }

	void setSupplies(int suppliesI) { supplies = suppliesI; };
	void setLevel(int levelI) { level = levelI; };
	void setDefenses(defenses defenseI) { townDefense = defenseI; };
	void setDebugBool(bool debugI) { debug = debugI; }

};