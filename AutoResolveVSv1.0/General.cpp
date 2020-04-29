#include "General.h"

General::~General()
{
}

General::General() //void initializer
{
	rank = 1;
	AutoResEqBonus = 0;
	armor = Equipment();
	weapon = Equipment();
	trinket = Equipment();
	banner = Equipment();
	follower = Equipment();
	debug = false;
}

General::General(bool debugI)
{
	rank = 1;
	AutoResEqBonus = 0;
	armor = Equipment();
	weapon = Equipment();
	trinket = Equipment();
	banner = Equipment();
	follower = Equipment();
	this->setDebug(debugI);
}

General::General(int rankI, Equipment armorI, Equipment weaponI, Equipment trinketI, Equipment bannerI, Equipment followerI) //initializer
{
	rank = rankI;
	armor = armorI;
	weapon = weaponI;
	trinket = trinketI;
	banner = bannerI;
	follower = followerI;
	debug = false;
	updateARBonus();
}

void General::updateARBonus()
{
	if (debug) { cout << "general updateARBonus called" << endl; }
	AutoResEqBonus = armor.getABonus() + weapon.getABonus() + trinket.getABonus() + banner.getABonus();
}

void General::printData()
{
	cout << "General printData called" << endl
		<< "General rank: " << rank << endl
		<< "General autoresolve equipment bonus: " << AutoResEqBonus << endl;
	cout << "General armor: " << endl;
	armor.printData();
	cout << "General weapon: " << endl;
	weapon.printData();
	cout << "General trinket: " << endl;
	trinket.printData();
	cout << "General banner: " << endl;
	banner.printData();
	cout << "General follower: " << endl;
	follower.printData();
}