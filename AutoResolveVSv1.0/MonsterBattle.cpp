#include "MonsterBattle.h"

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
		cout << result << endl
			<< "Attacker Soldier Cas: " << totalCasualties[0] << endl
			<< "Attacker Unit Cas: " << totalCasualties[1] << endl
			<< "Attacker General is " << outputGenState(totalCasualties[2]) << endl;
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
	attSoldierCasualties = calculateBattleRandoms(((int)result + 1), attSoldierTotal / 10);
	if (debug) { cout << "Attacking soldier casualties:" << attSoldierCasualties << " MonsterBattle::monsterCasualties" << endl; }
	int attUnitCasualties = attSoldierCasualties / 7 - 1;
	if (attSoldierCasualties < 0)
	{
		attSoldierCasualties = 0;
	}
	if (debug) { cout << "Attacking unit casualties:" << attUnitCasualties << " MonsterBattle::monsterCasualties" << endl; }

	//Determines if the general is wounded or killed
	if (debug) { cout << "Attacking soldier total:" << attSoldierTotal << " MonsterBattle::monsterCasualties" << endl; }
	if (randomNumber(10) < 2)
	{
		attGenWound = 1;
		if (debug) { cout << "General State set to 1(Wounded) MonsterBattle::monsterCasualties" << endl; }
		if (randomNumber(10) < 2)
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
	attTotal += calculateBattleRandoms(10, 10);
	if (debug) { cout << "attacker sum with randoms:" << attTotal << " MonsterBattle::calculateMonster" << endl; }
	monTotal += calculateBattleRandoms(10, 10);
	if (debug) { cout << "monster sum with randoms:" << monTotal << " MonsterBattle::calculateMonster" << endl; }

	//Adds rank and autoresolve bonuses from general and monster
	attTotal += attacker.getGeneral().getRank();
	if (debug) { cout << "attacker sum with general: " << attTotal << " MonsterBattle::calculateMonster" << endl; }
	attTotal += attacker.getGeneral().getARBonus();
	if (debug) { cout << "attacker sum with general autobonus: " << attTotal << " MonsterBattle::calculateMonster" << endl; }
	monTotal += monster.getARValue();
	if (debug) { cout << "monster sum with monster autobonus: " << monTotal << " MonsterBattle::calculateMonster" << endl; }

	//Determines outcome and casualties then calls output function
	result = determineOutcome(attTotal - monTotal);
	if (debug) { cout << "Outcome returned from determineOutcome:" << result << " MonsterBattle::calculateMonster" << endl; }
	vector<int> casualty{};
	monsterCasualties(casualty);
	if (debug) { cout << "monsterCasualties called MonsterBattle::calculateMonster" << endl; }
	monsterOutput(casualty);
	if (debug) { cout << "MonsterBattle::calculateMonster finished" << endl; }
	return;
}
