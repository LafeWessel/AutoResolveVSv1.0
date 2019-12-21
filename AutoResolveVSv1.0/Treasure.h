#pragma once
#include "CSVRow.h"
#include "Equipment.h"
#include "CSVDataReader.h"
#include <algorithm>
#include <cmath>

#include <array>
#include <vector>
#include <string>
#include <chrono>
#include <random>

//#include <fstream>
//#include <iostream>
//#include <sstream>
//#include <stdexcept>
using namespace std;
class Treasure //This keeps all the equipment to allow for finding of specific equipment and battle loot calculation
{

private:
	vector<Equipment> armor;
	vector<Equipment> weapon;
	vector<Equipment> trinket;
	vector<Equipment> banner;
	vector<Equipment> follower;
	vector<Equipment> dragon;
	bool debug;

	void sortEquipment(vector<Equipment>& toSort);

public:
	~Treasure();
	Treasure();
	Treasure(vector<Equipment> armorI, vector<Equipment> weaponI, vector<Equipment> trinketI, 
		vector<Equipment> bannerI, vector<Equipment> followerI, vector<Equipment> dragonI, bool debugI);
	//The last item in the follower array is the empty/null equipment
	Equipment noTreasure(){
		Equipment empty{ "No Treasure",0,0,0,equipmentType::null,"",0 };
		return empty;
	};

	//Subtracts 1 from the array so that it doesn't run off the end of the array of equipment
	Equipment findArmor();
	Equipment findWeapon();
	Equipment findTrinket();
	Equipment findBanner();
	Equipment findDragonEq();
	Equipment findFollower();

	Equipment findTreasure(int bonus); //Used at the end of battles to determine loot results

	vector<Equipment> getArmorVector() {
		if (debug) { cout << "armor vector gotten" << endl; }
		return armor;
	};
	vector<Equipment> getWeaponVector() { 
		if (debug) { cout << "weapon vector gotten" << endl; }
		return weapon;
	};
	vector<Equipment> getTrinketVector() {
		if (debug) { cout << "trinket vector gotten" << endl; }
		return trinket; 
	};
	vector<Equipment> getBannerVector() {
		if (debug) { cout << "banner vector gotten" << endl; }
		return banner;
	};
	vector<Equipment> getFollowerVector() {
		if (debug) { cout << "follower vector gotten" << endl; }
		return follower;
	};
	vector<Equipment> getDragonVector() {
		if (debug) { cout << "dragon vector gotten" << endl; }
		return dragon;
	};

	void setArmorVector(vector<Equipment> equipVectorI) { 
		armor = equipVectorI; 
		if (debug) { cout << "armor vector set" << endl; }
		for (int i = 0; i < armor.size(); i++) {
			armor[i].setDebug(debug);
		}
	};
	void setWeaponVector(vector<Equipment> equipVectorI) {
		weapon = equipVectorI;
		if (debug) { cout << "weapon vector set" << endl; }
		for (int i = 0; i < weapon.size(); i++) {
			weapon[i].setDebug(debug);
		}
	};
	void setTrinketVector(vector<Equipment> equipVectorI) {
		trinket = equipVectorI;
		if (debug) { cout << "trinket vector set" << endl; }
		for (int i = 0; i < trinket.size(); i++) {
			trinket[i].setDebug(debug);
		}
	};
	void setBannerVector(vector<Equipment> equipVectorI) {
		banner = equipVectorI;
		if (debug) { cout << "banner vector set" << endl; }
		for (int i = 0; i < banner.size(); i++) {
			banner[i].setDebug(debug);
		}
	};
	void setFollowerVector(vector<Equipment> equipVectorI) {
		follower = equipVectorI;
		if (debug) { cout << "follower vector set" << endl; }
		for (int i = 0; i < follower.size(); i++) {
			follower[i].setDebug(debug);
		}
	};
	void setDragonVector(vector<Equipment> equipVectorI) {
		dragon = equipVectorI;
		if (debug) { cout << "dragon vector set" << endl; }
		for (int i = 0; i < dragon.size(); i++) {
			dragon[i].setDebug(debug);
		}
	};

	bool getDebug() { return debug; }
	void setDebug(bool debugI) { 
		debug = debugI; 
		for (int i = 0; i < armor.size(); i++) {
			armor[i].setDebug(debug);
		}
		for (int i = 0; i < weapon.size(); i++) {
			weapon[i].setDebug(debug);
		}
		for (int i = 0; i < banner.size(); i++) {
			banner[i].setDebug(debug);
		}
		for (int i = 0; i < follower.size(); i++) {
			follower[i].setDebug(debug);
		}
		for (int i = 0; i < trinket.size(); i++) {
			trinket[i].setDebug(debug);
		}		
		for (int i = 0; i < dragon.size(); i++) {
			dragon[i].setDebug(debug);
		}
	}

	void initializeTreasure(); //This grabs all the data from the file containing the equipment
};

