#pragma once
#include "Battle.h"
#include "General.h"
#include "Treasure.h"
#include "faction.h"
#include "Roster.h"
#include "Unit.h"
#include "Player.h"

#include <algorithm>
#include <cmath>

#include <array>
#include <vector>
#include <string>
#include <chrono>
#include <random>

//#include <fstream>
#include <iostream>
//#include <sstream>
//#include <stdexcept>



class Prediction
{
protected:
	bool debug;

public:
	~Prediction();
	Prediction();
	Prediction(bool debugI);

	void calculatePrediction();

};
