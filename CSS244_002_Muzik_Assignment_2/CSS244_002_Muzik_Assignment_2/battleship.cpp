#include "battleship.h"
#include <iostream>
#include <ctime>
#include<string>
using namespace std;

//this is a friend function to Location class.
bool compare(const Location& loc1, const Location& loc2) {
	return (loc1 == loc2);
	/*nitoce that == operator is overloaded for the Location class*/

}

//overloding the << operator to teach the compiler how to print a ship info using cout
ostream& operator<<(ostream& os, const Ship& sh)
{
	string status;
	if (!sh.sunk)
		status = " up ";
	else
		status = " sunk ";
	sh.loc.print();

	os << "->" << status;
	return os;
}

//--------Location implementation-----------------------------------------------------------------------//
Location::Location()  // void constructor, dynamically allocates the coordinates array and assigns -1 to both of the coordinates
{
	coordinates = new int[2];
	coordinates[0] = -1;
	coordinates[1] = -1;
}

Location::Location(int x, int y)// overloaded constructor to be used to create a location object with given coordinates.
{
	coordinates = new int[2];
	coordinates[0] = x;
	coordinates[1] = y;
}

void Location::pick() // picks a random location. Means assigns 1 to 6 to the elements of the coordinates array
{
	coordinates[0] = (rand() % 6) + 1;
	coordinates[1] = (rand() % 6) + 1;
}

void Location::fire() // asks the user to input coordinates of the next shot
{
	int userDataEntryX, userDataEntryY;

	cout << "Enter the coordinates from 1 - 6 for X: ";
	while (true)
	{
		cin >> userDataEntryX;

		if (!cin) {
			cout << "Error. Only Numerical Values accepted. Please re-enter the coordinates from 1 - 6 for X:";
			cin.clear();
			cin.ignore(512, '\n');
			continue;
		}
		else {
			coordinates[0] = userDataEntryX;
			break;
		}
	}

	cout << "Enter the coordinates from 1 - 6 for Y: ";
	while (true) {
		cin >> userDataEntryY;

		if (!cin) {
			cout << "Error. Only Numerical Values accepted. Please re-enter the coordinates from 1 - 6 for Y:";
			cin.clear();
			cin.ignore(512, '\n');
			continue;
		}

		else {
			coordinates[0] = userDataEntryY;
			break;
		}

	}

}

void Location::print() const // prints location in format "[x,y]"  e.g., [2,4]
{
	cout << "[" << coordinates[0] << "," << coordinates[1] << "]";
}

Location::Location(const Location& org)// copycostructor
{
	coordinates = new int[2];
	for (int i = 0; i < 2; i++) {
		coordinates[i] = org.coordinates[i];
	}
}

Location& Location::operator=(const Location& rhs) //assignment overloading
{
	if (this != &rhs) {
		delete[] coordinates;
		coordinates = new int[2];
		for (int i = 0; i < 2; i++) {
			coordinates[i] = rhs.coordinates[i];
		}
	}
	return *this;
}

Location::~Location()//destructor
{
	delete[] coordinates;
}

//--------Ship implementation------------------------------------------------//
Ship::Ship() {
	sunk = false;
}

bool Ship::match(const Location& otherLocation) const {
	return compare(loc, otherLocation);
}

void Ship::sink() // sets "sunk" member variable of the ship to true
{
	sunk = true;
}

void Ship::setLocation(const Location& otherLocation) // deploys the ship at the specified location
{
	loc = otherLocation;
}

//--------Fleet implementation ------------------//

int Fleet::check(const Location& loc) const {
	for (int i = 0; i < FLEET_SIZE; i++) {
		if (ships[i].match(loc)) {
			return i;
		}
	}
	return -1;
}

void Fleet::deployFleet() {
	Location temp;
	for (int i = 0; i < FLEET_SIZE; i++) {
		temp.pick();
		int index = check(temp);
		if (index < 0) {
			ships[i].setLocation(temp);
		}
		else {
			--i;
		}
	}
}

bool Fleet::operational() const {
	for (int i = 0; i < FLEET_SIZE; i++) {
		if (ships[i].isSunk() == false) {
			return true;
		}
	}
	return false;
}

//int Fleet::isHitNSink(const Location& loc) {
//	for (int i = 0; i < FLEET_SIZE; i++) {
//		if () {
//
//		}
//	}
//}