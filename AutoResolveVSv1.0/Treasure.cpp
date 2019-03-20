#include "Treasure.h"


int randomNumberTreasure(int range) //Returns a random number between 1 and the given range
{
	
	typedef std::chrono::high_resolution_clock myclock;
	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	int random = 0;
	if (range == 0)
	{
		return 0;
	}
	uniform_int_distribution<int> dRange(1, abs(range));
	random = dRange(generator);
	return random;
}

Treasure::~Treasure()
{
}

Treasure::Treasure() //void initializer
{
	armor = {};
	weapon = {};
	trinket = {};
	banner = {};
	follower = {};
	dragon = {};
	debug = false;
}

//initializer
Treasure::Treasure(vector<Equipment> armorI, vector<Equipment> weaponI, vector<Equipment> trinketI, vector<Equipment> bannerI, vector<Equipment> followerI, vector<Equipment> dragonI)
{
	armor = armorI;
	weapon = weaponI;
	trinket = trinketI;
	banner = bannerI;
	follower = followerI;
	dragon = dragonI;
	debug = false;
}

Equipment Treasure::findArmor()
{
	return armor[randomNumberTreasure(armor.size() - 1)];
}

Equipment Treasure::findBanner()
{
	return banner[randomNumberTreasure(banner.size() - 1)];
}

Equipment Treasure::findFollower()
{
	return follower[randomNumberTreasure(follower.size() - 1)];
}

Equipment Treasure::findDragonEq()
{
	return dragon[randomNumberTreasure(dragon.size() - 1)];
}

Equipment Treasure::findTrinket()
{
	return trinket[randomNumberTreasure(trinket.size() - 1)];
}

Equipment Treasure::findWeapon()
{
	return weapon[randomNumberTreasure(weapon.size() - 1)];
}

void Treasure::initializeTreasure()
{
	if (debug) { cout << "initializeTreasure() called." << endl; }

	CSVDataReader reader;
	vector<Equipment> allEquipment = reader.readEquipment();
	sortEquipment(allEquipment);
	if (debug) { cout << " intitializeTreasure() finished" << endl; }
	return;
}

Equipment Treasure::findTreasure(int bonus) //Used to determine battle loot results
{
	if (debug) { cout << " findTreasure() called" << endl; }
	if ((randomNumberTreasure(8) + bonus) >= 5)
	{
		switch (randomNumberTreasure(5))
		{
		case(1):
			if (debug) { cout << " findArmor() returned" << endl; }
			return findArmor();
			break;
		case(2):
			if (debug) { cout << " findWeapon() returned" << endl; }
			return findWeapon();
			break;
		case(3):
			if (debug) { cout << " findTrinket() returned" << endl; }
			return findTrinket();
			break;
		case(4):
			if (debug) { cout << " findBanner() returned" << endl; }
			return findBanner();
			break;
		case(5):
			if (debug) { cout << " findFollower() returned" << endl; }
			return findFollower();
			break;
		default:
			cerr << "No type selected" << endl;
			return noTreasure();
		}
	}
	else
	{
		if (debug) { cout << " noTreasure() returned" << endl; }
		return noTreasure();
	}
	if (debug) { cout << " findTreasure() finished" << endl; }
}

void Treasure::sortEquipment(vector<Equipment> toSort)
{
	for (int i = 0; i < toSort.size(); i++)
	{
		if (toSort[i].getEqType() == "Armor")
		{
			armor.push_back(toSort[i]);
		}
		else if (toSort[i].getEqType() == "Trinket")
		{
			trinket.push_back(toSort[i]);
		}
		else if (toSort[i].getEqType() == "Banner")
		{
			banner.push_back(toSort[i]);
		}
		else if (toSort[i].getEqType() == "Weapon")
		{
			weapon.push_back(toSort[i]);
		}
		else if (toSort[i].getEqType() == "Follower")
		{
			follower.push_back(toSort[i]);
		}
		else
		{
			cerr << "no armor type found" << endl;
		}
	}
}