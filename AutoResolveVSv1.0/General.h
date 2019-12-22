#pragma once
#include "Equipment.h"
#include "faction.h"
#include <algorithm>
#include <cmath>

#include <array>
#include <vector>
#include <string>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;
class General //This is used by the Player class
{
private:
	int rank;
	int AutoResEqBonus; //Auto resolve bonus from Equipment
	Equipment armor;
	Equipment weapon;
	Equipment trinket;
	Equipment banner;
	Equipment follower;
	bool debug;

public:
	~General();
	General();
	General(int rankI, Equipment armorI, Equipment weaponI, Equipment trinketI, Equipment bannerI, Equipment followerI);
	void updateARBonus();

	int getRank() { 
		if (debug) { cout << "general rank gotten: " << rank << endl; }
		return rank;};
	int getARBonus() { 
		if (debug) { cout << "general autoResolveBonus gotten: " << AutoResEqBonus << endl; }
		return AutoResEqBonus; };
	Equipment getArmor() { 
		if (debug) { cout << "general armor gotten: " << armor.getName() << endl; }
		return armor; };
	Equipment getWeapon() { 
		if (debug) { cout << "general weapon gotten: " << weapon.getName() << endl; }
		return weapon; };
	Equipment getTrinket() { 
		if (debug) { cout << "general trinket gotten: " << trinket.getName() << endl; }
		return trinket; };
	Equipment getBanner() { 
		if (debug) { cout << "general banner gotten: " << banner.getName() << endl; }
		return banner; };
	Equipment getFollower() { 
		if (debug) { cout << "general follower gotten: " << follower.getName() << endl; }
		return follower; };

	void setRank(int rankI) { 
		if (debug) { cout << "general rank set to: " << rankI << endl; }
		rank = rankI; };
	/*
	void setAutoBonus(int autoBonusI) {
		if (debug) { cout << "general autoresolve bonus set to: " << autoBonusI << endl; }
		AutoResEqBonus = autoBonusI; 
	};
	*/
	void setArmor(Equipment equipI) { 
		if (debug) { cout << "general armor set to: " << equipI.getName() << endl; }
		armor = equipI;
		armor.setDebug(debug);
		updateARBonus();};
	void setWeapon(Equipment equipI) { 
		if (debug) { cout << "general weapon set to: " << equipI.getName() << endl; }
		weapon = equipI; 
		weapon.setDebug(debug);
		updateARBonus();};
	void setTrinket(Equipment equipI) { 
		if (debug) { cout << "general trinket set to: " << equipI.getName() << endl; }
		trinket = equipI;
		trinket.setDebug(debug);
		updateARBonus();};
	void setBanner(Equipment equipI) { 
		if (debug) { cout << "general banner set to: " << equipI.getName() << endl; }
		banner = equipI; 
		banner.setDebug(debug);
		updateARBonus();};
	void setFollower(Equipment equipI) { 
		if (debug) { cout << "general follower set to: " << equipI.getName() << endl; }
		follower = equipI;
		follower.setDebug(debug);
		updateARBonus();};

	bool getDebug() { return debug; };
	void setDebug(bool debugI) {
		if (debugI) { cout << "general setDebug called" << endl; }
		debug = debugI;
		armor.setDebug(debug);
		weapon.setDebug(debug);
		trinket.setDebug(debug);
		banner.setDebug(debug);
		follower.setDebug(debug);
	};
	void printData();
};
