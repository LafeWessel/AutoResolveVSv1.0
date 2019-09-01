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

	void sortEquipment(vector<Equipment> toSort);

public:
	~Treasure();
	Treasure();
	Treasure(vector<Equipment> armorI, vector<Equipment> weaponI, vector<Equipment> trinketI, vector<Equipment> bannerI, vector<Equipment> followerI, vector<Equipment> dragonI);
	//The last item in the follower array is the empty/null equipment
	Equipment noTreasure(){
		Equipment empty{ "No Treasure",0,0,0,"","",0 };
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

	Equipment getArmorAtIndex(int index) { return armor[index - 1]; };
	Equipment getWeaponAtIndex(int index) { return weapon[index - 1]; };
	Equipment getTrinketAtIndex(int index) { return trinket[index - 1]; };
	Equipment getBannerAtIndex(int index) { return banner[index - 1]; };
	Equipment getFollowerAtIndex(int index) { return follower[index - 1]; };
	Equipment getDragonAtIndex(int index) { return dragon[index - 1]; };

	vector<Equipment> getArmorVector() { return armor; };
	vector<Equipment> getWeaponVector() { return weapon; };
	vector<Equipment> getTrinketVector() { return trinket; };
	vector<Equipment> getBannerVector() { return banner; };
	vector<Equipment> getFollowerVector() { return follower; };
	vector<Equipment> getDragonVector() { return dragon; };

	void setArmorVector(vector<Equipment> equipVectorI) { armor = equipVectorI; };
	void setWeaponVector(vector<Equipment> equipVectorI) { weapon = equipVectorI; };
	void setTrinketVector(vector<Equipment> equipVectorI) { trinket = equipVectorI; };
	void setBannerVector(vector<Equipment> equipVectorI) { banner = equipVectorI; };
	void setFollowerVector(vector<Equipment> equipVectorI) { follower = equipVectorI; };
	void setDragonVector(vector<Equipment> equipVectorI) { dragon = equipVectorI; };

	bool getDebug() { return debug; }
	void setDebugBool(bool debugI) { debug = debugI; }

	void initializeTreasure(); //This grabs all the data from the file containing the equipment
};

