#include "Battle.h"

typedef std::chrono::high_resolution_clock myclock;
std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

//Gives the given state of a general at the end of a battle, range 0-2 for each state
string outputGenState(int state)
{
	switch (state)
	{
	case(0):
		return "Unharmed";
		break;
	case(1):
		return "Wounded for 3 turns";
		break;
	case(2):
		return "Slain";
		break;
	default:
		return " Invalid int passed";
	}
}

ostream& operator<<(ostream& os, equipmentType& end) //Output formation for equipmentType class
{
	switch (end)
	{
	case(equipmentType::weapon):
		return os << "Weapon";
		break;
	case(equipmentType::armor):
		return os << "Armor";
		break;
	case(equipmentType::trinket):
		return os << "Trinket";
		break;
	case(equipmentType::banner):
		return os << "Banner";
		break;
	case(equipmentType::dragon):
		return os << "Dragon";
		break;
	case(equipmentType::follower):
		return os << "Follower";
		break;
	case(equipmentType::null):
		return os << "null";
		break;
	default:
		return os << " No valid equipmentType chosen " << endl;
	}
}

ostream& operator<<(ostream& os, outcome& end) //Output formation for outcome class
{
	switch (end)
	{
	case(outcome::Decisive_Victory):
		return os << "Decisive Victory";
		break;
	case(outcome::Heroic_Victory):
		return os << "Heroic Victory";
		break;
	case(outcome::Close_Victory):
		return os << "Close Victory";
		break;
	case(outcome::Draw):
		return os << "Draw";
		break;
	case(outcome::Close_Defeat):
		return os << "Close Defeat";
		break;
	case(outcome::Valiant_Defeat):
		return os << "Valiant Defeat";
		break;
	case(outcome::Crushing_Defeat):
		return os << "Crushing Defeat";
		break;
	default:
		return os << " No valid outcome chosen " << endl;
	}
}

int randomNumberBattle(int range) //Returns a random number between 1 and the given range
{
	int random = 0;
	if (range == 0)
	{
		return 0;
	}
	uniform_int_distribution<int> dRange(1, abs(range));
	random = dRange(generator);
	return random;
}

ostream& operator<<(ostream& os, Equipment& eqpt) //output operator for Equipment class
{
	return os << eqpt.getName() << endl
		<< "Effect: " << eqpt.getEffect() << endl
		<< "Range: " << eqpt.getRange() << endl
		<< "EquipType: " << eqpt.getEqType() << endl
		<< "Coin Value: " << eqpt.getCValue() << endl;
}

//usually 10 times between 1 and 10 (10,10) for battles
int calculateBattleRandoms(int randomRolls, int randomRange) //Is used to calculate X number of times between 1 and Y
{
	int totalRand = 0;
	for (int i = 0; i < randomRolls; i++)
	{
		totalRand += randomNumberBattle(randomRange);
	}
	return totalRand;
}

//Same as randomNumber, but includes 0 in the range. Specifically meant for casualty calculation and arrays
int randomNumberCas(int range)
{
	if (range == 0)
	{
		return 0;
	}
	uniform_int_distribution<int> dRange(0, abs(range));
	return dRange(generator);
}

Battle::~Battle()
{
}

Battle::Battle() //void initializer
{
	attacker = Player();
	defender = Player();
	defender.setPlayerType(playerType::defender);
	result = outcome::Draw;
	output = true;
	debug = false;
}

Battle::Battle(Player attackerI, Player defenderI) // initializer
{
	attacker = attackerI;
	defender = defenderI;
	defender.setPlayerType(playerType::defender);
	result = outcome::Draw;
	output = true;
	debug = false;
}

void Battle::treasureResults()
{
	//Initializes and fills a treasure class
	Treasure loot{};
	loot.setDebugBool(debug);
	loot.initializeTreasure();
	if (debug) { cout << "Treasure initialized. Battle::treasureResults" << endl; }

	//Goes to where any bonus for finding loot at the end of a battle should be and sets the bonus to it.
	int bonus = attacker.getGeneral().getFollower().getABonus();

	//Looks for equipment and outputs what is returned
	Equipment foundAtt = loot.findTreasure(bonus);
	if (output)
	{
		cout << foundAtt.getName() << " was found by the attacking army." << endl;
		//This outputs the stats of the equipment if it isn't the empty equipment
		if (foundAtt.getName() != loot.noTreasure().getName())
		{
			cout << foundAtt << endl;
		}
	}

	//Then does the same as above for the defending Player.
	bonus = defender.getGeneral().getFollower().getABonus();

	Equipment foundDef = loot.findTreasure(bonus);
	if (output)
	{
		cout << foundDef.getName() << " was found by the defending army." << endl;
		//This outputs the stats of the equipment if it isn't the empty equipment
		if (foundDef.getName() != loot.noTreasure().getName())
		{
			cout << foundDef << endl;
		}
	}
	if (debug) { cout << "Battle::treasureResults finished" << endl; }
	return;
}

void Battle::battleOutput(vector<vector<int>> totalCasualties) //Base battle-end output
{
	treasureResults();
	if (output)
	{
		if (debug) { cout << "Made it into output" << endl; }
		cout << result << endl;
	}

	if (debug) { cout << "Moving on to casualty assignment Battle::battleOutput" << endl; }
	//Maybe move this part to calculateCas()?
	//Determines attacker casualty distribution
	vector<Unit> attackerUnits = {};

	for (int i = 0; i < attacker.getNumberOfUnits() - 1; i++)
	{
		attackerUnits.push_back(attacker.getUnitAtIndex(i));
	}

	int assignedSoldierCasualties = 0;
	int assignedUnitCasualties = 0;
	int i = 0;
	int cas = 0;
	while (assignedSoldierCasualties <= totalCasualties[0][0])
	{
		//This makes the iterator skip units that have already lost all their soldiers.
		while (attackerUnits[i].getCurrentSoldiers() == 0)
		{
			i++;
		}
		//Determines the amount of soldiers lost
		//If the unit casualties is maxed out, it makes sure that the unit loses 1 less than it's total number of soldiers at max; 
		//0 if there is 1 soldier only
		if (assignedUnitCasualties >= totalCasualties[0][1])
		{
			if (attackerUnits[i].getCurrentSoldiers() == 1)
			{
				cas = 0;
			}
			else
			{
				cas = randomNumberCas(attackerUnits[i].getCurrentSoldiers() - 1);
			}
		}
		else
		{
			cas = randomNumberCas(attackerUnits[i].getCurrentSoldiers());
		}

		//Subtracts the casualties from the amount of soldiers in the unit and declares if they have fully perished
		attackerUnits[i].setCurrentSoldiers(attackerUnits[i].getCurrentSoldiers() - cas);

		if (attackerUnits[i].getCurrentSoldiers() == 0)
		{
			if (debug) { cout << assignedSoldierCasualties << " " << attackerUnits[i].getName() << " completely destroyed." << endl; }
			assignedUnitCasualties++;
		}
		else
		{
			if (debug) { cout << assignedSoldierCasualties + cas << " " << attackerUnits[i].getName() << " lost " << cas << " soldiers." << endl; }
		}
		assignedSoldierCasualties += cas;


		//Wraps the index so it doesn't go off the end
		i++;
		if (i >= attackerUnits.size() - 1)
		{
			i = 0;
			if (debug) { cout << "Wrapped attacker casualty assignment loop" << endl; }
		}
	}
	if (output)
	{
		cout << "Attacker Soldier Casualties: " << assignedSoldierCasualties << endl;
		cout << "Attacker Upgrades: " << assignedUnitCasualties << endl;
		cout << "Attacker General is " << outputGenState(totalCasualties[0][3]) << endl;
	}

	vector<Unit> attackerUnitsWithCasualties = {};
	for (int i = 0; i < attackerUnits.size() - 1; i++)
	{
		if (attackerUnits[i].getCurrentSoldiers() > 0)
		{
			attackerUnitsWithCasualties.push_back(attackerUnits[i]);
		}
	}
	attacker.setPlayerUnits(attackerUnitsWithCasualties);


	//Determines defender casualty distribution
	vector<Unit> defenderUnits = {};
	i = 0;
	for (int i = 0; i < defender.getNumberOfUnits() - 1; i++)
	{
		defenderUnits.push_back(defender.getUnitAtIndex(i));
	}

	assignedSoldierCasualties = 0;
	assignedUnitCasualties = 0;
	i = 0;
	cas = 0;
	while (assignedSoldierCasualties <= totalCasualties[1][0])
	{
		//This makes the iterator skip units that have already lost all their soldiers.
		while (defenderUnits[i].getCurrentSoldiers() == 0)
		{
			i++;
		}
		//Determines the amount of soldiers lost
		//If the unit casualties is maxed out, it makes sure that the unit loses 1 less than it's total number of soldiers at max; 0 if there is 1 soldier only
		if (assignedUnitCasualties >= totalCasualties[1][1])
		{
			if (defenderUnits[i].getCurrentSoldiers() == 1)
			{
				cas = 0;
			}
			else
			{
				cas = randomNumberCas(defenderUnits[i].getCurrentSoldiers() - 1);
			}
		}
		else
		{
			cas = randomNumberCas(defenderUnits[i].getCurrentSoldiers());
		}

		//Subtracts the casualties from the amount of soldiers in the unit and declares if they have fully perished
		defenderUnits[i].setCurrentSoldiers(defenderUnits[i].getCurrentSoldiers() - cas);

		if (defenderUnits[i].getCurrentSoldiers() == 0)
		{
			if (debug) { cout << assignedSoldierCasualties << " " << defenderUnits[i].getName() << " completely destroyed." << endl; }
			assignedUnitCasualties++;
		}
		else
		{
			if (debug) { cout << assignedSoldierCasualties + cas << " " << defenderUnits[i].getName() << " lost " << cas << " soldiers." << endl; }
		}
		assignedSoldierCasualties += cas;


		//Wraps the index so it doesn't go off the end
		i++;
		if (i >= defenderUnits.size() - 1)
		{
			i = 0;
			if (debug) { cout << "Wrapped defender casualty assignment loop" << endl; }
		}
	}
	if (output)
	{
		cout << "Defender Soldier Casualties: " << assignedSoldierCasualties << endl;
		cout << "Defender Upgrades: " << assignedUnitCasualties << endl;
		cout << "Defender General is " << outputGenState(totalCasualties[1][3]) << endl;
	}

	vector<Unit> defenderUnitsWithCasualties = {};
	for (int i = 0; i < defenderUnits.size() - 1; i++)
	{
		if (defenderUnits[i].getCurrentSoldiers() > 0)
		{
			defenderUnitsWithCasualties.push_back(defenderUnits[i]);
		}
	}
	defender.setPlayerUnits(defenderUnitsWithCasualties);


	if (debug) { cout << "Battle::battleOutput finished" << endl; }
	return;
}

float Battle::battleCalculate() //contains the base calculations needed for battles
{
	//Comparing these at the end will determine victory/draw/defeat in relation to the attacker
	//The defTotal is subtracted from the attTotal, thus a positive result is a victory for the attacker,
	//and the opposite for a negative result
	float attTotal = 0;
	float defTotal = 0;
	//Adds units + portions of reinforcements
	attTotal += attacker.getCavalry() + attacker.getMelee() + attacker.getRanged();
	if (debug) { cout << "attacker unit sum:" << attTotal << " Battle::battleCalculate" << endl; }
	defTotal += defender.getCavalry() + defender.getMelee() + defender.getRanged();
	if (debug) { cout << "defender unit sum:" << defTotal << " Battle::battleCalculate" << endl; }

	//Adds random values to randomize the battle outcome more
	attTotal += calculateBattleRandoms(10, 10) / 6;
	if (debug) { cout << "attacker sum with randoms:" << attTotal << " Battle::battleCalculate" << endl; }
	defTotal += calculateBattleRandoms(10, 10) / 6;
	if (debug) { cout << "defender sum with randoms:" << defTotal << " Battle::battleCalculate" << endl; }

	//Adds rank and autoresolve bonuses from generals
	attTotal += attacker.getGeneral().getRank();
	if (debug) { cout << "attacker sum with general:" << attTotal << " Battle::battleCalculate" << endl; }
	defTotal += defender.getGeneral().getRank();
	if (debug) { cout << "defender sum with general:" << defTotal << " Battle::battleCalculate" << endl; }
	attTotal += attacker.getGeneral().getARBonus();
	if (debug) { cout << "attacker sum with general autobonus: " << attTotal << " Battle::battleCalculate" << endl; }
	defTotal += defender.getGeneral().getARBonus();
	if (debug) { cout << "defender sum with general autobonus: " << defTotal << " Battle::battleCalculate" << endl; }

	//Adds R-P-S stuff to attacker, but not defender so the difference isn't added twice
	attTotal += (attacker.getCavalry() - defender.getRanged()) * 1.5;
	if (debug) { cout << "attacker sum with cav-ran RPS:" << attTotal << " Battle::battleCalculate" << endl; }
	attTotal += (attacker.getMelee() - defender.getCavalry()) * 1.5;
	if (debug) { cout << "attacker sum with mel-cav RPS:" << attTotal << " Battle::battleCalculate" << endl; }
	attTotal += (attacker.getRanged() - defender.getMelee()) * 1.5;
	if (debug) { cout << "attacker sum with ran-mel RPS:" << attTotal << " Battle::battleCalculate" << endl; }

	if (debug) { cout << "Battle::battleCalculate finished, returned: " << attTotal - defTotal << endl; }
	return (attTotal - defTotal);
}

void Battle::CalculateCas(vector<vector<int>>& totalCasualties) //calculates the casualties from a battle and returns in a specific format
{
	int attSoldierCasualties = 0;
	int defSoldierCasualties = 0;

	int attGenWound = 0;
	int defGenWound = 0;
	int attSoldierTotal = 0;
	int defSoldierTotal = 0;
	//Totals the amount of soldiers in the armies
	for (int i = 0; i < attacker.getPlayerUnits().size(); i++) //TODO redo how this gets the total soldiers; make it be a class fn and not have to loop here
	{
		attSoldierTotal += attacker.getPlayerUnits()[i].getCurrentSoldiers();
	}
	for (int i = 0; i < defender.getPlayerUnits().size(); i++)
	{
		defSoldierTotal += defender.getPlayerUnits()[i].getCurrentSoldiers();
	}

	if (debug) { cout << "attacker soldier total: " << attSoldierTotal << " Battle::CalculateCas" << endl; }
	if (debug) { cout << "defender soldier total: " << defSoldierTotal << " Battle::CalculateCas" << endl; }

	//Uses the value of the outcome to determine the amount of casualties that will be taken
	attSoldierCasualties = calculateBattleRandoms(((int)result + 1), attSoldierTotal / 10);
	if (debug) { cout << "attacker soldier casualty total: " << attSoldierCasualties << " Battle::CalculateCas" << endl; }
	defSoldierCasualties = calculateBattleRandoms((9 - (int)result), defSoldierTotal / 10);
	if (debug) { cout << "defender soldier casualty total: " << defSoldierCasualties << " Battle::CalculateCas" << endl; }

	//Calculates the amounts of upgrades received; they are used in the campaign
	int attUpgr = defSoldierCasualties / 6;
	if (debug) { cout << "attacker upgrade total: " << attUpgr << " Battle::CalculateCas" << endl; }
	int defUpgr = attSoldierCasualties / 6;
	if (debug) { cout << "defender upgrade total: " << defUpgr << " Battle::CalculateCas" << endl; }

	//Calculates the amount of units that are destroyed
	int attUnitCasualties = (attSoldierCasualties / 7) - 1;
	if (attUnitCasualties < 0)
	{
		attUnitCasualties = 0;
	}
	if (debug) { cout << "attacker unit casualty total: " << attUnitCasualties << " Battle::CalculateCas" << endl; }
	int defUnitCasualties = (defSoldierCasualties / 7) - 1;
	if (defUnitCasualties < 0)
	{
		defUnitCasualties = 0;
	}
	if (debug) { cout << "defender unit casualty total: " << defUnitCasualties << " Battle::CalculateCas" << endl; }

	//Determines whether or not either of the generals are wounded/killed
	if (randomNumberBattle(10) < 2)
	{
		attGenWound = 1;
		if (debug) { cout << "attacker General state set to 1(Wounded) Battle::CalculateCas" << endl; }
		if (randomNumberBattle(10) < 2)
		{
			attGenWound = 2;
			if (debug) { cout << "attacker General state set to 2(Slain) Battle::CalculateCas" << endl; }
		}
	}
	else { if (debug) { cout << "attacker General unharmed" << endl; } }
	if (randomNumberBattle(10) < 2)
	{
		defGenWound = 1;
		if (debug) { cout << "defender General state set to 1(Wounded) Battle::CalculateCas" << endl; }
		if (randomNumberBattle(10) < 2)
		{
			defGenWound = 2;
			if (debug) { cout << "defender General state set to 2(Slain) Battle::CalculateCas" << endl; }
		}
	}
	else { if (debug) { cout << "defender General unharmed" << endl; } }
	//Creates the vectors that contain the casualty data
	vector<int> attackerCasVec{ attSoldierCasualties, attUnitCasualties, attUpgr, attGenWound };
	if (debug) { cout << "Attacker Casualty vector initialized Battle::CalculateCas" << endl; }
	vector<int> defenderCasVec{ defSoldierCasualties, defUnitCasualties, defUpgr, defGenWound };
	if (debug) { cout << "Defender Casualty vector initialized Battle::CalculateCas" << endl; }
	totalCasualties = { attackerCasVec, defenderCasVec };
	if (debug) { cout << "Overall Casualty vector initialized Battle::CalculateCas" << endl; }
	return;
}





