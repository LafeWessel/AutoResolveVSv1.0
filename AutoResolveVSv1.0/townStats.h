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
	int level; //TODO-see if this even needs to be used or is just redundant with int cast of townDefense
	int supplies; //These are used more in Raid battles and can be used during campaigns
	defenses townDefense;
	bool debug;

public:
	~townStats();
	townStats();
	townStats(int levelI);
	void updateStats();

	int getSupplies() { 
		if (debug) { cout << "town stats supplies gotten" << endl; }
		return supplies; 
	};
	defenses getDefenses() { 
		if (debug) { cout << "town stats defenses gotten" << endl; }
		return townDefense; 
	};
	int getLevel() { 
		if (debug) { cout << "town stats level gotten" << endl; }
		return level; };

	void setSupplies(int suppliesI) { 
		if (debug) { cout << "town stats supplies set to: " << suppliesI << endl; }
		supplies = suppliesI;
	};
	void setLevel(int levelI) { 
		if (debug) { cout << "town stats level set to: " << levelI << endl; }
		level = levelI; 
		updateStats();
	};
	/*
	void setDefenses(defenses defenseI) { 
		if (debug) { cout << "town stats defenses set to: " << (int)defenseI << endl; }
		townDefense = defenseI; 
	};
	*/
	bool getDebug() { return debug; }
	void setDebug(bool debugI) { debug = debugI; }
};