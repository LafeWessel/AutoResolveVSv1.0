#pragma once
#include <chrono>
#include <random>
#include <time.h>

using namespace std;

typedef std::chrono::high_resolution_clock myclock;
unsigned myseed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(myseed);

int randomNumber(int range) //Returns a random number between 1 and the given range
{
	int random = 0;
	if (range == 0)
	{
		return 0;
	}
	uniform_int_distribution<int> dRange(1, abs(range));
	random = dRange(generator);
	return random;
}

//Same as randomNumber, but includes 0 in the range. Specifically meant for casualty calculation and arrays
int randomNumberCas(int range)
{

	if (range == 0)
	{
		return 0;
	}
	uniform_int_distribution<int> dRange(0, abs(range));
	return dRange(generator);
}

int calculateBattleRandoms(int randomRolls, int randomRange) //Is used to calculate X number of times between 1 and Y
{
	int totalRand = 0;
	for (int i = 0; i < randomRolls; i++)
	{
		totalRand += randomNumber(randomRange);
	}
	return totalRand;
}