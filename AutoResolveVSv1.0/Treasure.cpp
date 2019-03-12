#include "Treasure.h"

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
	if ((randomNumber(8) + bonus) >= 5)
	{
		switch (randomNumber(5))
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