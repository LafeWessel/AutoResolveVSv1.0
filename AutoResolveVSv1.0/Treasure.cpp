#include "Treasure.h"


int Treasure::randomNumberTreasure(int range) //Returns a random number between 0 and the given range-1
{
	if (debug) { cout << range << " passed into random" << endl; }
	typedef std::chrono::high_resolution_clock myclock;
	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	unsigned int random = 0;
	if (range == 0)
	{
		if (debug) { cout << "Random range = 0" << endl; }
		return 0;
	}

	uniform_int_distribution<int> dRange(0, (abs(range)-1));
	random = dRange(generator);
	if (debug) { cout << "Random returning: " << random << endl; }
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

Treasure::Treasure(bool debugI) {
	armor = {};
	weapon = {};
	trinket = {};
	banner = {};
	follower = {};
	dragon = {};
	this->setDebug(debugI);
}

//initializer
Treasure::Treasure(vector<Equipment> armorI, vector<Equipment> weaponI, vector<Equipment> trinketI,
	vector<Equipment> bannerI, vector<Equipment> followerI, vector<Equipment> dragonI, bool debugI)
{
	armor = armorI;
	weapon = weaponI;
	trinket = trinketI;
	banner = bannerI;
	follower = followerI;
	dragon = dragonI;
	debug = debugI;
}

Equipment Treasure::findArmor()
{
	if (debug) { cout << "armor size: " << banner.size() << endl; }
	int selection = randomNumberTreasure(armor.size());
	if (debug) { cout << "selection: " << selection << endl; }
	return armor[selection];
}

Equipment Treasure::findBanner()
{
	if (debug) { cout << "banner size: " << banner.size() << endl; }
	int selection = randomNumberTreasure(banner.size());
	if (debug) { cout << "selection: " << selection << endl; }
	return banner[selection];
}

Equipment Treasure::findFollower()
{
	if (debug) { cout << "follower size: " << follower.size() << endl; }
	int selection = randomNumberTreasure(follower.size());
	if (debug) { cout << "selection: " << selection << endl; }
	return follower[selection];
}

Equipment Treasure::findDragonEq()
{
	if (debug) { cout << "dragon size: " << dragon.size() << endl; }
	int selection = randomNumberTreasure(dragon.size());
	if (debug) { cout << "selection: " << selection << endl; }
	return dragon[selection];
}

Equipment Treasure::findTrinket()
{
	if (debug) { cout << "trinket size: " << trinket.size() << endl; }
	int selection = randomNumberTreasure(trinket.size());
	if (debug) { cout << "selection: " << selection << endl; }
	return trinket[selection];
}

Equipment Treasure::findWeapon()
{
	if (debug) { cout << "weapon size: " << weapon.size() << endl; }
	int selection = randomNumberTreasure(weapon.size());
	if (debug) { cout << "selection: " << selection << endl; }
	return weapon[selection];
}

void Treasure::initializeTreasure()
{
	if (debug) { cout << "initializeTreasure() called." << endl; }

	CSVDataReader reader(debug);
	if (debug) { cout << "CSVDataReader initialized" << endl; }

	vector<Equipment> allEquipment = reader.readEquipment();
	if (debug) { cout << "All equipment read" << endl; }

	sortEquipment(allEquipment);
	if (debug) { cout << " intitializeTreasure() finished" << endl; }
	return;
}

Equipment Treasure::findTreasure(int bonus) //Used to determine battle loot results
{
	if (debug) { cout << " findTreasure() called" << endl; }
	int total = randomNumberTreasure(8) + bonus+1;
	if (debug) { cout << "random + bonus = " << total << endl; }
	if ( total >= 5)
	{
		switch (randomNumberTreasure(5)+1)
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

void Treasure::sortEquipment(vector<Equipment>& toSort)
{
	if (debug) { cout << "sortEquipment called" << endl; }
	if (debug) { cout << "sorting " << toSort.size() << " elements" << endl; }
	for (int i = 0; i < toSort.size(); i++)
	{
		switch (toSort[i].getEqType())
		{
		case (equipmentType::armor):
			if (debug) { cout << toSort[i].getName() << " added to the armor vector" << endl; }
			armor.push_back(toSort[i]);
			break;
		case (equipmentType::weapon):
			if (debug) { cout << toSort[i].getName() << " added to the weapon vector" << endl; }
			weapon.push_back(toSort[i]);
			break;
		case (equipmentType::trinket):
			if (debug) { cout << toSort[i].getName() << " added to the trinket vector" << endl; }
			trinket.push_back(toSort[i]);
			break;
		case (equipmentType::banner):
			if (debug) { cout << toSort[i].getName() << " added to the banner vector" << endl; }
			banner.push_back(toSort[i]);
			break;
		case (equipmentType::follower):
			if (debug) { cout << toSort[i].getName() << " added to the follower vector" << endl; }
			follower.push_back(toSort[i]);
			break;
		case (equipmentType::dragon):
			if (debug) { cout << toSort[i].getName() << " added to the dragon vector" << endl; }
			dragon.push_back(toSort[i]);
			break;
		default:
			cerr << "no armor type found, " << endl;
			break;
		}
	}
	if(debug)
	{ 
		cout << "Armor size: " << armor.size() << endl
			<< "Weapon size: " << weapon.size() << endl
			<< "Trinket size: " << trinket.size() << endl
			<< "Banner size: " << banner.size() << endl
			<< "Follower size: " << follower.size() << endl
			<< "Dragon size: " << dragon.size() << endl;
	}
}

void Treasure::setDebug(bool debugI) {
	if (debugI) { cout << "treasure setDebug called" << endl; }
	debug = debugI;

	for (Equipment e : armor){
		e.setDebug(debug);
	}
	for (Equipment e : weapon) {
		e.setDebug(debug);
	}
	for (Equipment e : trinket) {
		e.setDebug(debug);
	}
	for (Equipment e : banner) {
		e.setDebug(debug);
	}
	for (Equipment e : follower) {
		e.setDebug(debug);
	}
	for (Equipment e : dragon) {
		e.setDebug(debug);
	}

	if (debug) { cout << "treasure setDebug finished, total" << endl; }
}

void Treasure::printEquipmentVector(vector<Equipment>& equipVector, string name)
{
	for (int i = 0; i < equipVector.size(); i++)
	{
		cout << "Treasure " << name << " vector at " << i << ":" << endl;
		equipVector[i].printData();
	}
}

void Treasure::printData()
{
	cout << "Treasure printData called" << endl;
	printEquipmentVector(armor, "armor");
	printEquipmentVector(weapon, "weapon");
	printEquipmentVector(banner, "banner");
	printEquipmentVector(trinket, "trinket");
	printEquipmentVector(follower, "follower");
	printEquipmentVector(dragon, "dragon");
}

