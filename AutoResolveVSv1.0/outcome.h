#pragma once
#include <iostream>
using namespace std;
enum class outcome
{
Decisive_Victory = 1, Heroic_Victory, Close_Victory, Draw, Close_Defeat, Valiant_Defeat, Crushing_Defeat
};

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

void outputIntAsOutcome(int choice) //This outputs an integer as its corresponding outcome enum class name.
{
	switch (choice)
	{
	case(1):
		cout << "Decisive Victory";
		break;
	case(2):
		cout << "Heroic Victory";
		break;
	case(3):
		cout << "Close Victory";
		break;
	case(4):
		cout << "Draw";
		break;
	case(5):
		cout << "Close Defeat";
		break;
	case(6):
		cout << "Valiant Defeat";
		break;
	case(7):
		cout << "Crushing Defeat";
		break;
	default:
		cerr << " No valid outcome chosen " << endl;
	}
}
outcome determineOutcome(float endingTotal) //This determines the kind of outcome that occurs when a given battle result is passed in
{
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