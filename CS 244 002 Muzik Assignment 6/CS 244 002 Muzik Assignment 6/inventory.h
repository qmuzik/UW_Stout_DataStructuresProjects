#ifndef INVENTORY_H
#define INVENTORY_H
#include "NodeList.h"
#include "vehicle.h"
#include <fstream>
#include <iostream>
#include <string>

// Inventory Class 
class Inventory {
public:
	// Constructors
	Inventory();
	Inventory(NodeList<Vehicle> _inventoryList_, int numberOfcars_);

	// Setters
	void setInventoryList(NodeList<Vehicle> _inventoryList_);

	// Functions
	bool fillFromFile(string);

	void printAllRegisteredVehiclesRecursively(NodeList<Vehicle>::Iterator thisPosition);
	void printAllAvailibleVehiclesRecursively(NodeList<Vehicle>::Iterator thisPosition);
	void listOfReservedVehiclesRecursively(NodeList<Vehicle>::Iterator thisPosition);
	void checkAvailibilityRecursively(int numOfSeats, NodeList<Vehicle>::Iterator thisPosition);
	void reserveAVehicile(int);
	void returnAVehicle(int);
	void printAllVehiclesToFile();

	// Get the head and Tail of the Nodelist
	NodeList<Vehicle>::Iterator beginIter() { return inventoryList.begin(); };
	NodeList<Vehicle>::Iterator endIter() { return inventoryList.end(); };

private:
	NodeList<Vehicle> inventoryList;
	int numberOfcars;
};

// Methods for Inventory
Inventory::Inventory() {
	numberOfcars = 0;
}

Inventory::Inventory(NodeList<Vehicle> _inventoryList_, int numberOfcars_) {
	for (NodeList<Vehicle>::Iterator thisPosition = _inventoryList_.begin(); thisPosition != inventoryList.end(); ++thisPosition) {
		inventoryList.insertBack(*thisPosition);
	}
	numberOfcars = numberOfcars_;
}

void Inventory::setInventoryList(NodeList<Vehicle> _inventoryList_) {
	inventoryList = _inventoryList_;
}

bool Inventory::fillFromFile(string fileName) {
	ifstream inFile;
	inFile.open(fileName.c_str());

	if (inFile.fail()) {
		return false;
	}

	int numOfRecords, numOfSeats, vehicleID;
	string vehicleMake, vehicleModel;

	string dummyRead = "";
	bool availible;
	int numberOfFeatures;

	inFile >> numOfRecords;
	getline(inFile, dummyRead);

	for (int i = 0; i < numOfRecords; ++i) {
		NodeList<string> featuresList;
		inFile >> vehicleID;
		getline(inFile, dummyRead);
		getline(inFile, vehicleMake);
		getline(inFile, vehicleModel);
		inFile >> numOfSeats;
		inFile >> availible;
		inFile >> numberOfFeatures;
		getline(inFile, dummyRead);
		string currentFeature;
		for (int j = 0; j < numberOfFeatures; ++j) {
			getline(inFile, currentFeature);
			featuresList.insertBack(currentFeature);
		}
		Vehicle currentVehicle(vehicleID, vehicleMake, vehicleModel, numOfSeats, availible, numberOfFeatures, featuresList);
		inventoryList.insertFront(currentVehicle);
	}
	inFile.close();
	return true;
}

void Inventory::printAllRegisteredVehiclesRecursively(NodeList<Vehicle>::Iterator thisPosition) {
	if (thisPosition != inventoryList.end()) {
		cout << (*thisPosition) << endl;
		printAllRegisteredVehiclesRecursively(++thisPosition);
	}
}

void Inventory::printAllAvailibleVehiclesRecursively(NodeList<Vehicle>::Iterator thisPosition) {
	if (thisPosition != inventoryList.end()) {
		if ((*thisPosition).getAvailible() == true) {
			cout << (*thisPosition) << endl;
		}
		printAllAvailibleVehiclesRecursively(++thisPosition);
	}
}

void Inventory::listOfReservedVehiclesRecursively(NodeList<Vehicle>::Iterator thisPosition) {
	if (thisPosition != inventoryList.end()) {
		if ((*thisPosition).getAvailible() == false) {
			cout << (*thisPosition) << endl;
		}
		listOfReservedVehiclesRecursively(++thisPosition);
	}
}

void Inventory::checkAvailibilityRecursively(int numOfSeats, NodeList<Vehicle>::Iterator thisPosition) {
	if (thisPosition != inventoryList.end()) {
		if (numOfSeats <= (*thisPosition).getNumSeats()) {
			if ((*thisPosition).getAvailible() == true)
			cout << (*thisPosition) << endl;
		}
		checkAvailibilityRecursively(numOfSeats, ++thisPosition);
	}

}

void Inventory::reserveAVehicile(int vehicleID) {
	for (NodeList<Vehicle>::Iterator thisPosition = inventoryList.begin(); thisPosition != inventoryList.end(); ++thisPosition) {
		try {
			Vehicle vehicle = (Vehicle)*thisPosition;
			if (vehicle.getVehicleID() == vehicleID) {
				if (vehicle.getAvailible() == true) {
					(*thisPosition).setAvailible(false);
					cout << "Thank you for reserving a vehicle!" << endl;
					break;
				}
				else if (vehicle.getAvailible() == false) {
					throw 5;
					break;
				}
			}
		}
		catch (int e) {
			if (e == 5) {
				cout << "Exception: Vehicle has already been reserved\n" << "Code: " << e << endl;
				break;
			}
		}
	}
}

void Inventory::returnAVehicle(int vehicleID) {
	for (NodeList<Vehicle>::Iterator thisPosition = inventoryList.begin(); thisPosition != inventoryList.end(); ++thisPosition) {
		try {
			Vehicle vehicle = (Vehicle)*thisPosition;
			if (vehicle.getVehicleID() == vehicleID) {
				if (vehicle.getAvailible() == false) {
					(*thisPosition).setAvailible(true);
					cout << "Thank you for returning the vehicle!" << endl;
					break;
				}
				else if (vehicle.getAvailible() == true) {
					throw 6;
					break;
				}
			}
		}
		catch (int e) {
			if (e == 6) {
				cout << "Exception: Vehicle is still availible\n" << "Code: " << e << endl;
				break;
			}
		}
	}
}

void Inventory::printAllVehiclesToFile() {
	ofstream outputFile;
	outputFile.open("List_Of_Vehicles.txt");
	outputFile << inventoryList;
	outputFile.close();
	cout << "Inventory List has been printed to a file!" << endl;
}
#endif // !INVENTORY_H

