#include "townStats.h"

townStats::~townStats()
{
}
townStats::townStats() //void initializer
{
	level = 0;
	supplies = 0;
	townDefense = defenses::None;
	debug = false;
}

townStats::townStats(int levelI) //initializer
{
	level = levelI;
	supplies = 4 + (levelI * 4); //this takes the town level and determines the number of supplies it has
	switch (level) //this takes the town level and determines the defenses
	{
	case(1):
		townDefense = defenses::None;
		break;
	case(2):
		townDefense = defenses::Wooden_Wall;
		break;
	case(3):
		townDefense = defenses::Wooden_Wall_W_Moat;
		break;
	case(4):
		townDefense = defenses::Stone_Wall;
		break;
	case(5):
		townDefense = defenses::Stone_Wall_W_Moat;
		break;
	default:
		townDefense = defenses::None;
	}
	debug = false;
}