#include "Equipment.h"

Equipment::~Equipment()
{
}

Equipment::Equipment() //void initializer
{
	name = "";
	autoBonus = 0;
	index = 0;
	range = 0;
	EquipType = equipmentType::null;
	effect = "";
	coinValue = 0;
	debug = false;
}

Equipment::Equipment(string nameI, int autoBonusI, int numberI, int rangeI, equipmentType EquipTypeI, string effectI, int coinValueI) //initializer
{
	name = nameI;
	autoBonus = autoBonusI;
	index = numberI;
	range = rangeI;
	EquipType = EquipTypeI;
	effect = effectI;
	coinValue = coinValueI;
	debug = false;
}