// CS244_002_Muzik_Assignment3Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>

#include <string>

using namespace std;

class Player {

public:

	Player(string _fullName, int _numberOfGoals, int _numberOfAssists, int _numberOfEffectiveTouches, int _runningDistanceKM) {

		fullName = _fullName;

		numberOfGoals = _numberOfGoals;

		numberOfAssists = _numberOfAssists;

		numberOfEffectiveTouches = _numberOfEffectiveTouches;

		runningDistanceKM = _runningDistanceKM;

	}

	void printInfo() {

		cout << endl << fullName << endl;

		cout << numberOfGoals << endl;

		cout << numberOfAssists << endl;

		cout << numberOfEffectiveTouches << endl;

		cout << runningDistanceKM << endl;

	}

	string fullName;

	//You code goes here 
	friend bool operator>(Player& player1, Player& player2) {
		return ((player1.numberOfGoals > player2.numberOfGoals) && (player1.numberOfAssists > player2.numberOfAssists) && (player1.numberOfEffectiveTouches > player2.numberOfEffectiveTouches) || (player1.runningDistanceKM > player2.runningDistanceKM));
	}

private:

	int numberOfGoals;

	int numberOfAssists;

	int numberOfEffectiveTouches;

	int runningDistanceKM;

};

int main()

{

	Player player1("Cristiano Ronaldo dos Santos", 4, 7, 32, 17);

	Player player2("Lionel Andrés Messi", 2, 9, 37, 13);

	Player player3("Gareth Frank Bale", 1, 14, 33, 17);

	//binary 'operator' : 'type' does not define this operator or a conversion to a type acceptable to the predefined operator

	if (player1 > player2 && player1 > player3)

		cout << "Player of The game is " << player1.fullName << endl;

	else if (player2 > player1 && player2 > player3)

		cout << "Player of The game is " << player2.fullName << endl;

	else

		cout << "Player of The game is " << player3.fullName << endl;

	return 0;

}