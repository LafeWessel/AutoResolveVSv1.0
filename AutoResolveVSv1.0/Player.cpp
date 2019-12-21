#include "Player.h"

Player::~Player()
{
}

Player::Player() //void initializer
{
	Melee = 0;
	Cavalry = 0;
	Ranged = 0;
	general = General();
	AdvCombatDeck = false;
	fact = faction::rebel;
	debug = false;
	Reinforcements = 0;
	player = playerType::attacker;
}

//initializer
Player::Player(vector<Unit> unitsI, General generalI, int ReinforceI, bool AdvCombatDeckI, faction FactI, playerType type)
{
	setupUnitAutoresolveBonuses();
	//automatically adds reinforcements onto the total melee, cavalry and ranged soldiers the class has
	Melee += (ReinforceI * 4);
	Cavalry += (ReinforceI * 4);
	Ranged += (ReinforceI * 4);
	general = generalI;
	AdvCombatDeck = AdvCombatDeckI;
	fact = FactI;
	debug = false;
	Reinforcements = ReinforceI;
	player = type;
}

void Player::setPlayerUnits(vector<Unit> unitsI)
{
	
	playerUnits = unitsI;
	if (debug) { cout << "player player unit vector set, size: " << playerUnits.size() << endl; }
	if (debug) { cout << "player calling setupUnitAutoresolveBonuses" << endl; }
	setupUnitAutoresolveBonuses();
	return;
}

void Player::setReinforcements(int ReinforceI)
{
	if (debug) { cout << "player set reinforcements called" << endl; }
	//Removes any current reinforcements from autoresolve totals before adding the input bonuses
	Melee -= (Reinforcements * 4);
	Cavalry -= (Reinforcements * 4);
	Ranged -= (Reinforcements * 4);

	Melee += (4 * ReinforceI);
	Cavalry += (4 * ReinforceI);
	Ranged += (4 * ReinforceI);
	Reinforcements = ReinforceI;
}

void Player::setupUnitAutoresolveBonuses()
{
	if (debug) { cout << "player setupUnitAutoresolveBonuses called" << endl; }
	Melee = 0;
	Cavalry = 0;
	Ranged = 0;

	//Loops over the vector of player units, adding the autoresolve values.
	for (int i = 0; i < playerUnits.size(); i++)
	{
		switch (playerUnits[i].getUnitType())
		{
		case unitType::Melee:
			Melee += playerUnits[i].getARBonus();
			if (debug) { cout << playerUnits[i].getARBonus() << " added to Melee = " << Melee << endl; }
			break;
		case unitType::Cavalry:
			Cavalry += playerUnits[i].getARBonus();
			if (debug) { cout << playerUnits[i].getARBonus() << " added to Cavalry = " << Cavalry << endl; }
			break;
		case unitType::Ranged:
			Ranged += playerUnits[i].getARBonus();
			if (debug) { cout << playerUnits[i].getARBonus() << " added to Ranged = " << Ranged << endl; }
			break;
		default:
			cerr << "selected unit has no unitType." << endl;
		}
	}
	if (debug) { cout << "Melee total: " << Melee << endl; }
	if (debug) { cout << "Cavalry total: " << Cavalry << endl; }
	if (debug) { cout << "Ranged total: " << Ranged << endl; }

	Melee += (4 * Reinforcements);
	if (debug) { cout << "Melee with reinforcements " << Melee << endl; }
	Cavalry += (4 * Reinforcements);
	if (debug) { cout << "Cavalry with reinforcements " << Cavalry << endl; }
	Ranged += (4 * Reinforcements);
	if (debug) { cout << "Ranged with reinforcements " << Ranged << endl; }
	return;
}
