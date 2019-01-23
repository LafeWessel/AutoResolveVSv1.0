#pragma once
#include <iostream>
using namespace std;
enum class monsterType
{
Minotaur = 1, Hobgoblin, Troll, Giant, Demon, Dragon, Empty
};


ostream& operator<<(ostream& os, monsterType& mon) //Thsi outputs an integer as its corresponding monsterType name
{
	switch (mon)
	{
	case(monsterType::Minotaur):
		return os << "Minotaur";
		break;
	case(monsterType::Hobgoblin):
		return os << "Hobgoblin";
		break;
	case(monsterType::Troll):
		return os << "Troll";
		break;
	case(monsterType::Giant):
		return os << "Giant";
		break;
	case(monsterType::Demon):
		return os << "Demon";
		break;
	case(monsterType::Dragon):
		return os << "Dragon";
		break;
	default:
		return os << " No valid monster chosen " << endl;
	}
}