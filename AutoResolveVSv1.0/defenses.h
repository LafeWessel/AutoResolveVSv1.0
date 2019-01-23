#pragma once
#include <iostream>
using namespace std;
enum class defenses
{
None = 1, Wooden_Wall, Wooden_Wall_W_Moat, Stone_Wall, Stone_Wall_W_Moat
};

ostream& operator<<(ostream& os, defenses& def) //This outputs an integer as its corresponding defenses name.
{
	switch (def)
	{
	case(defenses::None):
		return os << "None";
		break;
	case(defenses::Wooden_Wall):
		return os << "Wooden Walls";
		break;
	case(defenses::Wooden_Wall_W_Moat):
		return os << "Wooden Walls and Moat";
		break;
	case(defenses::Stone_Wall):
		return os << "Stone Walls";
		break;
	case(defenses::Stone_Wall_W_Moat):
		return os << "Stone Walls and Moat";
		break;
	default:
		return os << " No valid defenses chosen " << endl;
	}
}