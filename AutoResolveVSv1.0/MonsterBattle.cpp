#include "MonsterBattle.h"



int MonsterBattle::randomNumberMonster(int range) //Returns a random number between 1 and the given range
{
	if (debug) { cout << "monsterBattle randomNumberMonster called" << endl; }
	typedef std::chrono::high_resolution_clock myclock;
	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	if (debug) { cout << "monsterBattle random ranged passed in: " << range << endl; }
	int random = 0;
	if (range == 0)
	{
		return 0;
	}
	uniform_int_distribution<int> dRange(1, abs(range));
	random = dRange(generator);
	if (debug) { cout << "monsterBattle randomNumber random returning: " << random << endl; }
	return random;
}

//usually 10 times between 1 and 10 (10,10) for battles
int MonsterBattle::calculateBattleRandomsMonster(int randomRolls, int randomRange) //Is used to calculate X number of times between 1 and Y
{
	if (debug) { cout << "monsterBattle battleRandoms called" << endl; }
	int totalRand = 0;
	for (int i = 0; i < randomRolls; i++)
	{
		int newRand = randomNumberMonster(randomRange);
		totalRand += newRand;
		if (debug) { cout << "monsterBattle newRand: " << newRand << " total: " << totalRand << endl; }
	}
	if (debug) { cout << "monsterBattle battleRandoms returning: " << totalRand << endl; }
	return totalRand;
}

outcome MonsterBattle::determineOutcomeMonster(float endingTotal) //This determines the kind of outcome that occurs when a given battle result is passed in
{
	if (debug) { cout << "monsterBattle determineOutcome called" << endl; }
	//All results are in relation to the attacker.
	//Victory
	if (endingTotal > 2)
	{
		if (endingTotal >= 20)
		{
			return outcome::Decisive_Victory;
		}
		else if (endingTotal >= 10)
		{
			return outcome::Heroic_Victory;
		}
		else
		{
			return outcome::Close_Victory;
		}
	}
	//Defeat
	else if (endingTotal < -2)
	{
		if (endingTotal <= -20)
		{
			return outcome::Crushing_Defeat;
		}
		else if (endingTotal <= -10)
		{
			return outcome::Valiant_Defeat;
		}
		else
		{
			return outcome::Close_Defeat;
		}
	}
	//Draw
	else
	{
		return outcome::Draw;
	}
}

//Gives the given state of a general at the end of a battle, range 0-2 for each state
string MonsterBattle::outputGenStateMonster(int state)
{
	if (debug) { cout << "monsterBattle outputGenState called" << endl; }
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


MonsterBattle::~MonsterBattle()
{
}

MonsterBattle::MonsterBattle() //void initializer
{
	attacker = Player();
	monster = Monster();
	result = outcome::Draw;
	output = true;
	debug = false;
}

MonsterBattle::MonsterBattle(Player attackerI, Monster monsterI) //initializer
{
	attacker = attackerI;
	monster = monsterI;
	result = outcome::Draw;
	output = true;
	debug = false;
}

void MonsterBattle::monsterOutput(vector<int>& totalCasualties) //Outputs information at the end of the Monster battle
{
	if (debug) { cout << "Calling battleOutput, MonsterBattle::monsterOutput" << endl; }
	if (output)
	{
		cout << (int)result << endl
			<< "Attacker Soldier Cas: " << totalCasualties[0] << endl
			<< "Attacker Unit Cas: " << totalCasualties[1] << endl
			<< "Attacker General is " << outputGenStateMonster(totalCasualties[2]) << endl;
		if ((int)result < 4)
		{
			cout << "Coins gained: " << monster.getCoinReward() << endl;
		}
	}
	if (debug) { cout << "MonsterBattle::monsterOutput finished" << endl; }
	return;
}

void MonsterBattle::monsterCasualties(vector<int>& attackerCasVec) //Calculates the casualties
{

	int attSoldierCasualties = 0;
	int attGenWound = 0;
	int attSoldierTotal = attacker.getCavalry() + attacker.getMelee() + attacker.getRanged();
	if (debug) { cout << "Attacking soldier total:" << attSoldierTotal << " MonsterBattle::monsterCasualties" << endl; }
	//Calculates the soldier and unit casualties
	attSoldierCasualties = calculateBattleRandomsMonster(((int)result + 1), attSoldierTotal / 10);
	if (debug) { cout << "Attacking soldier casualties:" << attSoldierCasualties << " MonsterBattle::monsterCasualties" << endl; }
	int attUnitCasualties = attSoldierCasualties / 7 - 1;
	if (attSoldierCasualties < 0)
	{
		attSoldierCasualties = 0;
	}
	if (debug) { cout << "Attacking unit casualties:" << attUnitCasualties << " MonsterBattle::monsterCasualties" << endl; }

	//Determines if the general is wounded or killed
	if (debug) { cout << "Attacking soldier total:" << attSoldierTotal << " MonsterBattle::monsterCasualties" << endl; }
	if (randomNumberMonster(10) < 2)
	{
		attGenWound = 1;
		if (debug) { cout << "General State set to 1(Wounded) MonsterBattle::monsterCasualties" << endl; }
		if (randomNumberMonster(10) < 2)
		{
			attGenWound = 2;
			if (debug) { cout << "General State set to 2(Slain) MonsterBattle::monsterCasualties" << endl; }
		}
	}


	attackerCasVec = { attSoldierCasualties, attUnitCasualties, attGenWound };
	if (debug) { cout << "Attacker casualty vector initialized MonsterBattle::monsterCasualties" << endl; }
	if (debug) { cout << "MonsterBattle::monsterCasualties finished" << endl; }
	return;
}

void MonsterBattle::calculateMonster()
{
	//Comparing these at the end will determine victory/draw/defeat in relation to the attacker
	//The monTotal is subtracted from the attTotal, thus a positive result is a victory for the attacker,
	//and the opposite for a negative result
	float attTotal = 0;
	float monTotal = 0;

	//Adds units + portions of reinforcements
	attTotal += attacker.getCavalry() + attacker.getMelee() + attacker.getRanged();
	if (debug) { cout << "attacker unit sum:" << attTotal << " MonsterBattle::calculateMonster" << endl; }


	//Adds random values to randomize the battle outcome more
	attTotal += calculateBattleRandomsMonster(10, 10);
	if (debug) { cout << "attacker sum with randoms:" << attTotal << " MonsterBattle::calculateMonster" << endl; }
	monTotal += calculateBattleRandomsMonster(10, 10);
	if (debug) { cout << "monster sum with randoms:" << monTotal << " MonsterBattle::calculateMonster" << endl; }

	//Adds rank and autoresolve bonuses from general and monster
	attTotal += attacker.getGeneral().getRank();
	if (debug) { cout << "attacker sum with general: " << attTotal << " MonsterBattle::calculateMonster" << endl; }
	attTotal += attacker.getGeneral().getARBonus();
	if (debug) { cout << "attacker sum with general autobonus: " << attTotal << " MonsterBattle::calculateMonster" << endl; }
	monTotal += monster.getARValue();
	if (debug) { cout << "monster sum with monster autobonus: " << monTotal << " MonsterBattle::calculateMonster" << endl; }

	//Determines outcome and casualties then calls output function
	result = determineOutcomeMonster(attTotal - monTotal);
	if (debug) { cout << "Outcome returned from determineOutcome:" << (int)result << " MonsterBattle::calculateMonster" << endl; }
	vector<int> casualty{};
	monsterCasualties(casualty);
	if (debug) { cout << "monsterCasualties called MonsterBattle::calculateMonster" << endl; }
	monsterOutput(casualty);
	if (debug) { cout << "MonsterBattle::calculateMonster finished" << endl; }
	return;
}

void MonsterBattle::printData()
{
	cout << "MonsterBattle printData called" << endl
		<< "MonsterBattle attacker: " << endl;
	attacker.printData();
	cout << "MonsterBattle monster: " << endl;
	monster.printData();
	cout << "MonsterBattle result: " << (int)result << endl;
}