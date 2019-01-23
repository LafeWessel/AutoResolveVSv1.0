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
	ifstream file("equipment.txt");
	//file.open("equipment");
	if (debug) { cout << "equipment.txt tried" << endl; }
	if (!file)
	{
		//file.open("equipment.csv");
		ifstream file("equipment.csv");
		if (debug) { cout << "equipment.csv tried" << endl; }
	}
	else if(!file)
	{
		//file.open("equipment.txt");
		ifstream file("equipment");
		if (debug) { cout << "equipment tried" << endl; }
	}
	else if (!file)
	{
		cerr << "equipment file not found" << endl;
		throw invalid_argument("Equipment file not found.");
	}
	CSVRow row;
	string theEquipType;
	string theName;
	string theEffect;
	string theCoinValue;
	string theIndexNumber;
	string theAutoBonus;
	string theRange;

	//Reads the equipment file and puts equipment in the correct vectors then initializes the treasure
	while (file >> row)
	{
		if (debug) { cout << "Starting to read." << endl; }

		theEquipType = row[0];
		if (debug) { cout << "Equipment Type set to: " << row[0] << endl; }
		theName = row[1];
		if (debug) { cout << "Name set to: " << row[1] << endl; }
		theEffect = row[2];
		if (debug) { cout << "Effect set to: " << row[2] << endl; }
		theCoinValue = row[3];
		if (debug) { cout << "Coin Value set to: " << row[3] << endl; }
		theIndexNumber = row[4];
		if (debug) { cout << "Index Number set to: " << row[4] << endl; }
		theAutoBonus = row[5];
		if (debug) { cout << "AutoRBonus set to: " << row[5] << endl; }
		theRange = row[6];
		if (debug) { cout << "Range set to: " << row[6] << endl; }

		Equipment inputEquip(theName, stoi(theAutoBonus), stoi(theIndexNumber), stoi(theRange), theEquipType, theEffect, stoi(theCoinValue));

		if (theEquipType == "Armor")
		{
			armor.push_back(inputEquip);
			if (debug) { cout << "armor vector pushed: " << inputEquip.getName() << endl; }
		}
		else if (theEquipType == "Weapon")
		{
			weapon.push_back(inputEquip);
			if (debug) { cout << "weapons vector pushed: " << inputEquip.getName() << endl; }
		}
		else if (theEquipType == "Trinket")
		{
			trinket.push_back(inputEquip);
			if (debug) { cout << "trinkets vector pushed: " << inputEquip.getName() << endl; }
		}
		else if (theEquipType == "Banner")
		{
			banner.push_back(inputEquip);
			if (debug) { cout << "banners vector pushed: " << inputEquip.getName() << endl; }
		}
		else if (theEquipType == "Follower")
		{
			follower.push_back(inputEquip);
			if (debug) { cout << "followers vector pushed: " << inputEquip.getName() << endl; }
		}
		else if (theEquipType == "Dragon")
		{
			dragon.push_back(inputEquip);
			if (debug) { cout << "dragon vector pushed: " << inputEquip.getName() << endl; }
		}
		else
		{
			cerr << "Invalid equipment type given: " << theEquipType << endl;
		}
	}

	//if (armor.size() <1) { throw invalid_argument("Armor vector has no elements"); }
	//if (weapon.size() <1) { throw invalid_argument("Weapon vector has no elements"); }
	//if (trinket.size() <1) { throw invalid_argument("Trinket vector has no elements"); }
	//if (banner.size() <1) { throw invalid_argument("Banner vector has no elements"); }
	//if (follower.size() <1) { throw invalid_argument("Follower vector has no elements"); }
	//if (dragon.size() <1) { throw invalid_argument("Dragon vector has no elements"); }


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

