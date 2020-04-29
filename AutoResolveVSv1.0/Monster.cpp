#include "Monster.h"


Monster::~Monster()
{
}

Monster::Monster() //void initializer
{
	treasure = &Treasure();
	type = monsterType::Empty;
	coinReward = 0;
	autoResValue = 0;
	debug = false;
}

Monster::Monster(bool debugI)
{
	treasure = &Treasure();
	type = monsterType::Empty;
	coinReward = 0;
	autoResValue = 0;
	this->setDebug(debugI);
}

Monster::Monster(monsterType typeI, Treasure& treasureI) //initializer
{
	type = typeI;
	treasure = &treasureI;
	setValuesFromMonsterType();
	debug = false;
}
//TODO-refactor this function
vector<Equipment> Monster::getEquipRewards() //This figures out the treasure gained for killing a monster, based on info elsewhere
{
	if (debug) { cout << "getEquipRewards called" << endl; }
	vector<Equipment> rewards = {};
	switch (type)
	{
	case(monsterType::Minotaur):
		if (debug)
		{
			Equipment reward = treasure->findWeapon();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure->findWeapon());
		}
		break;
	case(monsterType::Hobgoblin):
		if (debug)
		{
			Equipment reward = treasure->findWeapon();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
			reward = treasure->findArmor();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure->findWeapon());
			rewards.push_back(treasure->findArmor());
		}
		break;
	case(monsterType::Troll):
		if (debug)
		{
			Equipment reward = treasure->findWeapon();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
			reward = treasure->findTrinket();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure->findWeapon());
			rewards.push_back(treasure->findTrinket());
		}
		break;
	case(monsterType::Giant):
		if (debug)
		{
			Equipment reward = treasure->findWeapon();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
			reward = treasure->findTrinket();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
			reward = treasure->findArmor();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure->findWeapon());
			rewards.push_back(treasure->findTrinket());
			rewards.push_back(treasure->findArmor());
		}
		break;
	case(monsterType::Demon):
		if (debug)
		{
			Equipment reward = treasure->findBanner();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
			reward = treasure->findArmor();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure->findArmor());
			rewards.push_back(treasure->findBanner());
		}
		break;
	case(monsterType::Dragon):
		if (debug)
		{
			Equipment reward = treasure->findDragonEq();
			rewards.push_back(reward);
			cout << "rewards pushed: " << reward.getName() << endl;
		}
		else
		{
			rewards.push_back(treasure->findDragonEq());
		}
		break;
	default:
		cerr << "Something went wrong" << endl;
	}
	return rewards;
}

void Monster::setValuesFromMonsterType()
{
	if (debug) { cout << "setValuesFromMonsterType called" << endl; }
	//These set the coin rewards; they are based on values I made elsewhere
	if ((int)type < 5)
	{
		coinReward = ((int)type + 1) * 100;
		
	}
	else if ((int)type < 6)
	{
		coinReward = ((int)type + 2) * 100;
	}
	else
	{
		coinReward = ((int)type + 1) * 200;
	}
	if (debug) { cout << "coinReward set to: " << coinReward << endl; }

	autoResValue = ((int)type * 10) + 10;
	if (debug) { cout << "autoResolve Value set to: " << autoResValue << endl; }
}

void Monster::printData()
{
	cout << "Monster printData called" << endl
		<< "Monster monsterType: " << (int)type << endl
		<< "Monster coin reward: " << coinReward << endl
		<< "Monster autoresolve value: " << autoResValue << endl;
	if (treasure) { cout << "Monster treasure pointer != null" << endl; }
}