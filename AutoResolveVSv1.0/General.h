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

	int getRank() { 
		if (debug) { cout << "general rank gotten" << endl; }
		return rank;
	};
	int getARBonus() { 
		if (debug) { cout << "general autoResolveBonus gotten" << endl; }
		return AutoResEqBonus; 
	};
	Equipment getArmor() { 
		if (debug) { cout << "general armor gotten" << endl; }
		return armor; 
	};
	Equipment getWeapon() { 
		if (debug) { cout << "general weapon gotten" << endl; }
		return weapon; 
	};
	Equipment getTrinket() { 
		if (debug) { cout << "general trinket gotten" << endl; }
		return trinket; 
	};
	Equipment getBanner() { 
		if (debug) { cout << "general banner gotten" << endl; }
		return banner; 
	};
	Equipment getFollower() { 
		if (debug) { cout << "general follower gotten" << endl; }
		return follower; 
	};

	void setRank(int rankI) { 
		if (debug) { cout << "general rank set" << endl; }
		rank = rankI; 
	};
	void setAutoBonus(int autoBonusI) {
		if (debug) { cout << "general autoresolve bonus set" << endl; }
		AutoResEqBonus = autoBonusI; 
	};
	void setArmor(Equipment equipI) { 
		if (debug) { cout << "general armor set" << endl; }
		armor = equipI;
		armor.setDebug(debug);
	};
	void setWeapon(Equipment equipI) { 
		if (debug) { cout << "general weapon set" << endl; }
		weapon = equipI; 
		weapon.setDebug(debug);
	};
	void setTrinket(Equipment equipI) { 
		if (debug) { cout << "general trinket set" << endl; }
		trinket = equipI;
		trinket.setDebug(debug);
	};
	void setBanner(Equipment equipI) { 
		if (debug) { cout << "general banner set" << endl; }
		banner = equipI; 
		banner.setDebug(debug);
	};
	void setFollower(Equipment equipI) { 
		if (debug) { cout << "general follower set" << endl; }
		follower = equipI;
		follower.setDebug(debug);
	};

	bool getDebug() { return debug; };
	void setDebug(bool debugI) {
		debug = debugI;
		armor.setDebug(debug);
		weapon.setDebug(debug);
		trinket.setDebug(debug);
		banner.setDebug(debug);
		follower.setDebug(debug);
	};
};
