#include "BattleData.h"

BattleData::BattleData()
{
	int nItems = 141;
	for (int i = 0; i < nItems; i++) {
		data.push_back(0);
	}
}
