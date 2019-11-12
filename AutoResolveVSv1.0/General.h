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
	int getRank() { return rank; };

	int getARBonus() { return AutoResEqBonus; };
	Equipment getArmor() { return armor; };
	Equipment getWeapon() { return weapon; };
	Equipment getTrinket() { return trinket; };
	Equipment getBanner() { return banner; };
	Equipment getFollower() { return follower; };
	bool getDebug() { return debug; }

	void setRank(int rankI) { rank = rankI; };
	void setAutoBonus(int autoBonusI) { AutoResEqBonus = autoBonusI; };
	void setArmor(Equipment equipI) { armor = equipI; };
	void setWeapon(Equipment equipI) { weapon = equipI; };
	void setTrinket(Equipment equipI) { trinket = equipI; };
	void setBanner(Equipment equipI) { banner = equipI; };
	void setFollower(Equipment equipI) { follower = equipI; };
	void setDebugBool(bool debugI) { debug = debugI; }

};
