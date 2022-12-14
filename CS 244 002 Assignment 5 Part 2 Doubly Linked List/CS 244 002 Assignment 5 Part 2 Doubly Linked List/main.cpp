#include <iostream>
#include <fstream>
#include <string>
#include "doublyLinkedList.h"
#include "inventory.h";
#include "vehicle.h"

// Menu
string menu();
using namespace std;


int main() {
	try {
		int userSelection = 0;

		Inventory mainInventory;

		if (!mainInventory.fillFromFile("vehicles.txt")) {
			throw string("Cannot open the file. Make sure that the file is located in the projet folder.");
			exit(1);
		}

		while (userSelection != 8)
		{
			cout << "************************************\n";
			cout << menu();

			if (!(cin >> userSelection)) {
				throw 1;
			}

			switch (userSelection) {

			case 0: system("cls");
				break;
			case 1: system("cls"); {
				mainInventory.printAllRegisteredVehicles();
			}
				  break;
			case 2: system("cls"); {
				mainInventory.printAllAvailibleVehicles();
			}
				  break;
			case 3: system("cls"); {
				mainInventory.listOfReservedVehicles();
			}
				  break;
			case 4: system("cls"); {
				int numOfSeats;
				cout << "Enter the number of seats-> ";
				if (!(cin >> numOfSeats)) {
					throw 1;
				}
				cout << "Vehicles that are currently availible for rental: " << endl;
				mainInventory.checkAvailibility(numOfSeats);
			}
				  break;
			case 5:  system("cls"); {
				string vehicleID;
				cout << "Enter the ID of the vehicle that you wish to reserve: ";
				if (!(cin >> vehicleID)) {
					throw 2;
				}
				mainInventory.reserveAVehicile(vehicleID);
			}
				  break;
			case 6: system("cls"); {
				string vehicleID;
				cout << "Enter the ID of the vehicle that you are returning: ";
				if (!(cin >> vehicleID)) {
					throw 2;
				}
				mainInventory.returnAVehicle(vehicleID);
			}
				  break;
			case 7: system("cls"); {
				mainInventory.printAllVehiclesToFile();
			}
				  break;
			case 8: system("cls");
				cout << "Thank you for using the car rental system." << endl;
				break;

			default:
				throw 3;
				break;
			}
		} /*end while for user selction*/
	}

	catch (string e) {
		cout << "Exception" << e << endl;
	}

	catch (int e) {
		if (e == 1) {
			cout << "Exception: Selection must be an integer!\n" << "Code: " << e << endl;
			exit(1);
		}
		else if (e == 2) {
			cout << "Exception: Selection must be a six digit number!\n" << "Code: " << e << endl;
			exit(2);
		}
		else if (e == 3) {
			cout << "Exception: Selection must be from 0 - 8 !\n" << "Code: " << e << endl;
			exit(3);

		}
	}
	return 0;
}

string menu() {
	string message;
	message = "0. Clear Screen.. \n1. Print All of the registered vehicles. \n2. Print list of the availible vehicles. \n3. List of reserved vehicles.\n4. Check availability.\n5. Reserve a vehicle.";
	message = message + "\n6. Return a vehicle. \n7. Print All of the reigistered vehicles to a text file. \n8. Exit. \nYour Selection --> ";
	return message;
}

