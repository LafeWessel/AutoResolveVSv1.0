#include "Monster.h"

Monster::~Monster()
{
}

Monster::Monster() //void initializer
{
	type = monsterType::Empty;
	coinReward = 0;
	autoResValue = 0;
	debug = false;
}

Monster::Monster(monsterType typeI) //initializer
{
	type = typeI;

	//These set the coin rewards; they are based on values I made elsewhere
	if ((int)typeI < 5)
	{
		coinReward = ((int)typeI + 1) * 100;
	}
	else if ((int)typeI < 6)
	{
		coinReward = ((int)typeI + 2) * 100;
	}
	else
	{
		coinReward = ((int)typeI + 1) * 200;
	}

	autoResValue = ((int)typeI * 10) + 10;
	debug = false;
}

vector<Equipment> Monster::getEquipRewards() //This figures out the treasure gained for killing a monster, based on info elsewhere
{
	if (debug) { cout << "getEquipRewards called" << endl; }
	Treasure treasure{};
	if (debug) { cout << "treasure initialized" << endl; }
	treasure.setDebugBool(debug);
	treasure.initializeTreasure();
	vector<Equipment> rewards = {};
	switch (type)
	{
	case(monsterType::Minotaur):
		if (debug)
		{
			Equipment reward = treasure.findWeapon();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure.findWeapon());
		}
		break;
	case(monsterType::Hobgoblin):
		if (debug)
		{
			Equipment reward = treasure.findWeapon();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
			reward = treasure.findArmor();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure.findWeapon());
			rewards.push_back(treasure.findArmor());
		}
		break;
	case(monsterType::Troll):
		if (debug)
		{
			Equipment reward = treasure.findWeapon();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
			reward = treasure.findTrinket();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure.findWeapon());
			rewards.push_back(treasure.findTrinket());
		}
		break;
	case(monsterType::Giant):
		if (debug)
		{
			Equipment reward = treasure.findWeapon();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
			reward = treasure.findTrinket();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
			reward = treasure.findArmor();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure.findWeapon());
			rewards.push_back(treasure.findTrinket());
			rewards.push_back(treasure.findArmor());
		}
		break;
	case(monsterType::Demon):
		if (debug)
		{
			Equipment reward = treasure.findBanner();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
			reward = treasure.findArmor();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure.findArmor());
			rewards.push_back(treasure.findBanner());
		}
		break;
	case(monsterType::Dragon):
		if (debug)
		{
			Equipment reward = treasure.findDragonEq();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure.findDragonEq());
		}
		break;
	default:
		cerr << "Something went wrong" << endl;
	}
	return rewards;
}
