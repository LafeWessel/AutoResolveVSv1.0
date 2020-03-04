[#pragma once
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
	int supplies; //These are used more in Raid battles and can be used during campaigns
	defenses townDefense;
	bool debug;

public:
	~townStats();
	townStats();
	townStats(int levelI);
	void updateStats(int level);

	int getSupplies() { 
		if (debug) { cout << "town stats supplies gotten: " << supplies << endl; }
		return supplies; };
	defenses getDefenses() { 
		if (debug) { cout << "town stats defenses gotten: " << (int)townDefense << endl; }
		return townDefense; };
	int getLevel() { 
		if (debug) { cout << "town stats level gotten: " << (int)townDefense << endl; }
		return (int)townDefense; };

	void setSupplies(int suppliesI) { 
		if (debug) { cout << "town stats supplies set to: " << suppliesI << endl; }
		supplies = suppliesI;};
	void setLevel(int levelI) { 
		if (debug) { cout << "town stats level set to: " << levelI << endl; }
		updateStats(levelI);};

	bool getDebug() { return debug; }
	void setDebug(bool debugI) { debug = debugI; }
	void printData();
};