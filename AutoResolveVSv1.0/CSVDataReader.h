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
	bool debug = false;

public:
	CSVDataReader();
	~CSVDataReader();	
	
	vector<Equipment> readEquipment();
	vector<Unit> readUnits(faction& fact);
};

