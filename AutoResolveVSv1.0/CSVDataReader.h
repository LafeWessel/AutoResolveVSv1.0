#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include "Equipment.h"
#include "Unit.h"
#include "faction.h"
#include "CSVRow.h"

class CSVDataReader
{
private:
	bool debug;

public:
	CSVDataReader();
	CSVDataReader(bool debugI);
	~CSVDataReader();	
	
	vector<Equipment> readEquipment();
	vector<Unit> readUnits(faction& fact);

	unitType intToUnitType(int input);
	equipmentType stringToEquipType(string nameI);
	faction intToFaction(int input);

	void setDebug(bool debugI) { debug = debugI; };
};

