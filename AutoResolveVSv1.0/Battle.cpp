#include "Battle.h"

typedef std::chrono::high_resolution_clock myclock;
std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

//Gives the given state of a general at the end of a battle, range 0-2 for each state
string Battle::outputGenState(int state)
{
	if (debug) { cout << "battle outputGenState called" << endl; }
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

int Battle::randomNumberBattle(int range) //Returns a random number between 1 and the given range
{
	if (debug) { cout << "randomNumberBattle Called" << endl; }
	if (debug) { cout << "range passed in: " << range << endl; }
	int random = 0;
	if (range == 0)
	{
		return 0;
	}
	uniform_int_distribution<int> dRange(1, abs(range));
	random = dRange(generator);
	if (debug) { cout << "random returning: " << random << endl; }
	return random;
}

string equipmentTypeToString(equipmentType type)
{
	switch (type)
	{
	case(equipmentType::weapon):
		return "Weapon";
		break;
	case(equipmentType::armor):
		return "Armor";
		break;
	case(equipmentType::trinket):
		return "Trinket";
		break;
	case(equipmentType::banner):
		return "Banner";
		break;
	case(equipmentType::dragon):
		return "Dragon";
		break;
	case(equipmentType::follower):
		return "Follower";
		break;
	case(equipmentType::null):
		return "null";
		break;
	default:
		return " No valid equipmentType chosen ";
	}
}

ostream& operator<<(ostream& os, Equipment& eqpt) //output operator for Equipment class
{
	return os << eqpt.getName() << endl
		<< "Effect: " << eqpt.getEffect() << endl
		<< "Range: " << eqpt.getRange() << endl
		<< "EquipType: " << equipmentTypeToString(eqpt.getEqType()) << endl
		<< "Coin Value: " << eqpt.getCValue() << endl;
}

//usually 10 times between 1 and 10 (10,10) for battles
int Battle::calculateBattleRandoms(int randomRolls, int randomRange) //Is used to calculate X number of times between 1 and Y
{
	if (debug) { cout << "battle calculateBattleRandoms called" << endl; }
	int totalRand = 0;
	for (int i = 0; i < randomRolls; i++)
	{
		int newRand = randomNumberBattle(randomRange);
		if (debug) { cout << newRand << " added to total random = " << totalRand << endl; }
		totalRand += newRand;
	}
	if (debug) { cout << "battle calculateBattleRandoms returning: " << totalRand << endl; }
	return totalRand;
}

//Same as randomNumber, but includes 0 in the range. Specifically meant for casualty calculation and arrays
int Battle::randomNumberCas(int range)
{
	if (debug) { cout << "battle randomNumberCas called" << endl; }
	if (range == 0)
	{
		return 0;
	}
	uniform_int_distribution<int> dRange(0, abs(range));
	int random = dRange(generator);
	if (debug) { cout << "battle randomNumberCas returning: " << random << endl; }
	return random;
}

Battle::~Battle()
{
	
}

Battle::Battle() //void initializer
{
	attacker = Player();
	defender = Player();
	treasure = &Treasure();
	result = outcome::Draw;
	output = true;
	debug = false;
	fileOut = false;
	fileName = "";
	data = BattleData();
}

Battle::Battle(bool debugI)
{
	attacker = Player();
	defender = Player();
	treasure = &Treasure();
	result = outcome::Draw;
	output = true;
	this->setDebug(debugI);
	fileOut = false;
	fileName = "";
	data = BattleData();
}

Battle::Battle(Player attackerI, Player defenderI) // initializer
{
	attacker = attackerI;
	defender = defenderI;
	treasure = &Treasure();
	result = outcome::Draw;
	output = true;
	debug = false;
	fileOut = false;
	fileName = "";
	data = BattleData();
}

Battle::Battle(Player attackerI, Player defenderI, bool fileOutI, string fileNameI) // initializer
{
	attacker = attackerI;
	defender = defenderI;
	treasure = &Treasure();
	result = outcome::Draw;
	output = true;
	debug = false;
	fileOut = fileOutI;
	fileName = fileNameI;
	data = BattleData();
}


 void Battle::treasureResults()
{
	if (debug) { cout << "treasureResults called" << endl; }
	if (debug) { cout << "treasureResults for attacker" << endl; }
	//Goes to where any bonus for finding loot at the end of a battle should be and sets the bonus to it.
	int bonus = attacker.getGeneral().getFollower().getABonus();

	if (debug) { cout << "attacker bonus is: " << bonus << endl; }
	//Looks for equipment and outputs what is returned
	Equipment foundAtt = treasure->findTreasure(bonus);
	if (debug) { cout << foundAtt.getName() << " returned from findTreasure" << endl; }
	if (output)
	{
		cout << foundAtt.getName() << " was found by the attacking army." << endl;
		//This outputs the stats of the equipment if it isn't the empty equipment
		if (foundAtt.getName() != treasure->noTreasure().getName())
		{
			cout << foundAtt << endl;
		}
	}

	if (debug) { cout << "treasureResults for defender" << endl; }
	//Then does the same as above for the defending Player.
	bonus = defender.getGeneral().getFollower().getABonus();

	if (debug) { cout << "defender bonus is: " << bonus << endl; }
	Equipment foundDef = treasure->findTreasure(bonus);
	if (debug) { cout << foundDef.getName() << " returned from findTreasure" << endl; }
	if (output)
	{
		cout << foundDef.getName() << " was found by the defending army." << endl;
		//This outputs the stats of the equipment if it isn't the empty equipment
		if (foundDef.getName() != treasure->noTreasure().getName())
		{
			cout << foundDef << endl;
		}
	}
	if (debug) { cout << "Battle::treasureResults finished" << endl; }
	return;
}

//casulaties vector values
//[x][0] = # of soldiers that are casualties
//[x][1] = # of units completely destroyed
//[x][2] = # of Upgrades received
//[x][3] = state of general's health
 void Battle::assignCasualties(vector<int>& casualties, int playerType) {

	 Player player = {};
	 //Determines which player to work on
	 if (playerType == 0) {
		 player = attacker;
	 }
	 else if (playerType == 1) {
		 player = defender;
	 }
	 else {
		 throw invalid_argument("Invalid playerType passed");
	 }

	 //Assigns casualties
	 vector<Unit> playerUnits = {};
	 playerUnits = player.getPlayerUnits();
	 if (debug) { cout << "number of player units: " << playerUnits.size() << endl; }

	 int assignedSoldierCasualties = 0;
	 int assignedUnitCasualties = 0;
	 int i = 0;
	 int cas = 0;

	 if (debug) { cout << "Battle assigning casualties" << endl; }
	 while (assignedSoldierCasualties < casualties[0])
	 {
		 if (debug) { cout << "Casualties to assign: " << casualties[0] - assignedSoldierCasualties << endl; }
		 //This makes the iterator skip units that have already lost all their soldiers.
		 while ( i < playerUnits.size()-1 && playerUnits[i].getCurrentSoldiers() == 0 )
		 {
			 i++;
		 }

		 //Determines the amount of soldiers lost
		 //If the unit casualties is maxed out, it makes sure that the unit loses 1 less than it's total number of soldiers at max; 
		 //0 if there is 1 soldier only
		 if (assignedUnitCasualties >= casualties[1])
		 {
			 if (playerUnits[i].getCurrentSoldiers() == 1)
			 {
				 cas = 0;
			 }
			 else
			 {
				 cas = randomNumberCas(playerUnits[i].getCurrentSoldiers() - 1);
			 }
		 }
		 else
		 {
			 cas = randomNumberCas(playerUnits[i].getCurrentSoldiers());
		 }

		 //Subtracts the casualties from the amount of soldiers in the unit and declares if they have fully perished
		 playerUnits[i].setCurrentSoldiers(playerUnits[i].getCurrentSoldiers() - cas);

		 if (playerUnits[i].getCurrentSoldiers() == 0)
		 {
			 if (debug) { cout << assignedSoldierCasualties << " " << playerUnits[i].getName() << " completely destroyed." << endl; }
			 assignedUnitCasualties++;
		 }
		 else
		 {
			 if (debug) { cout << assignedSoldierCasualties + cas << " " << playerUnits[i].getName() << " lost " << cas << " soldiers." << endl; }
		 }
		 assignedSoldierCasualties += cas;
		 i++;

		 //Wraps the index so it doesn't go off the end 
		 if (i > playerUnits.size() - 1)
		 {
			 i = 0;
			 if (debug) { cout << "Wrapped attacker casualty assignment loop" << endl; }
			 bool soldiersAboveOne = false;

			 //Checks to make sure that at least one unit can still have casualties assigned to it
			 for (int j = 0; j < playerUnits.size(); j++) {

				 if (playerUnits[j].getCurrentSoldiers() > 1) {
					 soldiersAboveOne = true;
					 if (debug) { cout << "soldiersAboveOne set to true" << endl; }
				 }
			 }

			 if (!soldiersAboveOne) {
				 casualties[0] = assignedSoldierCasualties-1;
				 if (debug) { cout << "reassigned casualties[0] to assignedSoldierCasualties" << endl; }
			 }

		 }
	 }


	 //Reassigns attacker's unit vector
	 vector<Unit> attackerUnitsAfterCasualties = {};
	 for (int i = 0; i < playerUnits.size(); i++)
	 {
		 if (playerUnits[i].getCurrentSoldiers() > 0)
		 {
			 attackerUnitsAfterCasualties.push_back(playerUnits[i]);
		 }
	 }
	 player.setPlayerUnits(attackerUnitsAfterCasualties);

	 //Reassigns attacker or defender to player
	 if (playerType == 0) {
		 attacker = player;
	 }
	 else if (playerType == 1) {
		 defender = player;
	 }
 }

//totalCasualties vector values
//[0][x] = Attacker's values
//[1][x] = Defender's values
//[x][0] = # of soldiers that are casualties
//[x][1] = # of units completely destroyed
//[x][2] = # of Upgrades received
//[x][3] = state of general's health
void Battle::battleOutput(vector<vector<int>>& totalCasualties) //Base battle-end output
{
	if (debug) { cout << "battleOutput called, calling treasureResults" << endl; }
	treasureResults();
	if (output)
	{
		if (debug) { cout << "Made it into output" << endl; }
		cout << result << endl;
	}

	if (output)
	{
		cout << "Attacker Soldier Casualties: " << totalCasualties[0][0] << endl;
		cout << "Attacker Unit Casualties: " << totalCasualties[0][2] << endl;
		cout << "Attacker General is " << outputGenState(totalCasualties[0][3]) << endl;
		cout << "Defender Soldier Casualties: " << totalCasualties[0][0] << endl;
		cout << "Defender Upgrades: " << totalCasualties[0][2] << endl;
		cout << "Defender General is " << outputGenState(totalCasualties[1][3]) << endl;
	}

	if (debug) { cout << "Battle::battleOutput finished" << endl; }
	return;
}

float Battle::battleCalculate() //contains the base calculations needed for battles
{

	if (debug) { cout << "battleCalculate called" << endl; }
	//Comparing these at the end will determine victory/draw/defeat in relation to the attacker
	//The defTotal is subtracted from the attTotal, thus a positive result is a victory for the attacker,
	//and the opposite for a negative result
	float attTotal = 0;
	float defTotal = 0;
	//Adds units + portions of reinforcements
	attTotal = attacker.getCavalry() + attacker.getMelee() + attacker.getRanged();
	if (debug) { cout << "attacker unit sum:" << attTotal << " Battle::battleCalculate" << endl; }
	defTotal = defender.getCavalry() + defender.getMelee() + defender.getRanged();
	if (debug) { cout << "defender unit sum:" << defTotal << " Battle::battleCalculate" << endl; }

	//Adds random values to randomize the battle outcome more
	attTotal += calculateBattleRandoms(10, 10);
	attTotal /= 6;
	if (debug) { cout << "attacker sum with randoms:" << attTotal << " Battle::battleCalculate" << endl; }
	defTotal += calculateBattleRandoms(10, 10);
	defTotal /= 6;
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
	attTotal += ((double)attacker.getCavalry() - (double)defender.getRanged()) * 1.5;
	if (debug) { cout << "attacker sum with cav-ran RPS:" << attTotal << " Battle::battleCalculate" << endl; }
	attTotal += ((double)attacker.getMelee() - (double)defender.getCavalry()) * 1.5;
	if (debug) { cout << "attacker sum with mel-cav RPS:" << attTotal << " Battle::battleCalculate" << endl; }
	attTotal += ((double)attacker.getRanged() - (double)defender.getMelee()) * 1.5;
	if (debug) { cout << "attacker sum with ran-mel RPS:" << attTotal << " Battle::battleCalculate" << endl; }
	
	float finalTotal = attTotal - defTotal;

	if (debug) { cout << "Battle::battleCalculate finished, returned: " << finalTotal << endl; }
	return finalTotal;
}

//calculates the casualties from a battle and returns in a specific format
void Battle::CalculateCas(vector<vector<int>>& totalCasualties) 
{
	if (debug) { cout << "CalculateCas called" << endl; }
	int attSoldierCasualties = 0;
	int defSoldierCasualties = 0;

	int attGenWound = 0;
	int defGenWound = 0;
	int attSoldierTotal = 0;
	int defSoldierTotal = 0;
	//Totals the amount of soldiers in the armies
	attSoldierTotal = attacker.getTotalSoldiers();
	defSoldierTotal = defender.getTotalSoldiers();

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

	if (debug) { cout << "Moving on to casualty assignment Battle::CalculateCas" << endl; }
	assignCasualties(attackerCasVec, 0);
	assignCasualties(defenderCasVec, 1);

	totalCasualties = { attackerCasVec,defenderCasVec };
}

void Battle::printData()
{
	cout << "Battle printData called" << endl
		<< "Battle attacker: " << endl;
	attacker.printData();
	cout << "Battle defender: " << endl;
	defender.printData();
	cout << "Battle result: " << (int)result << endl;
	if (treasure) { cout << "Battle Treasure pointer != NULL" << endl; }
}



