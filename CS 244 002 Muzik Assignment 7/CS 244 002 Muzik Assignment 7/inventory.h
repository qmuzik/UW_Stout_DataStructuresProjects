#ifndef INVENTORY_H
#define INVENTORY_H
#include "BinarySearchTreeTemplateIter.h"
#include "vehicle.h"
#include <fstream>
#include <iostream>
#include <string>

// Inventory Class 
class Inventory {
public:
	// Tree Varible
	LinkedBinarySearchTree<Vehicle> inventoryListTree;

	// Constructors
	Inventory();
	Inventory(LinkedBinarySearchTree<Vehicle> _inventoryListTree_, int numberOfcars_);

	// Destructor 
	~Inventory() {
	}

	// Operator Overloading
	Inventory& operator=(const Inventory& rhs); // Assignment Overloading 
	friend ofstream& operator<<(ofstream& out, const Inventory& invO);

	// Functions
	bool fillFromFile(string);
	void printAllRegisteredVehicles();
	void printAllAvailibleVehicles();
	void listOfReservedVehicles();
	void checkAvailibility(int numOfSeats);
	void reserveAVehicile(int);
	void returnAVehicle(int);
	void printAllVehiclesToFile();

private:
	int numberOfcars;
};

// Methods for Inventory

// Default Constructor 
Inventory::Inventory() {
	numberOfcars = 0;
}

// Constructor 
Inventory::Inventory(LinkedBinarySearchTree<Vehicle> _inventoryListTree_, int numberOfcars_) {
	inventoryListTree = _inventoryListTree_;
	numberOfcars = numberOfcars_;
}

Inventory& Inventory::operator=(const Inventory& rhs) {
	if (this != &rhs) {
		list<LinkedBinarySearchTree<Vehicle>::Iterator> L2(rhs.inventoryListTree.Iterators());
		list<LinkedBinarySearchTree<Vehicle>::Iterator>::iterator iter2 = L2.begin();
		while (L2.empty()) {
			L2.erase(iter2);
		}
		list<LinkedBinarySearchTree<Vehicle>::Iterator> L(rhs.inventoryListTree.Iterators());
		list<LinkedBinarySearchTree<Vehicle>::Iterator>::iterator iter = L.begin();
		for (++iter; iter != L.end(); ++iter) {
			inventoryListTree.insert((*(*iter)));
		}
		numberOfcars = rhs.numberOfcars;
	}
	return *this;
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
		LinkedBinarySearchTree<string> featuresList;
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
			featuresList.insert(currentFeature);
		}
		Vehicle currentVehicle(vehicleID, vehicleMake, vehicleModel, numOfSeats, availible, numberOfFeatures, featuresList);
		inventoryListTree.insert(currentVehicle);
	}
	inFile.close();
	return true;
}

void Inventory::printAllRegisteredVehicles() {
	list<LinkedBinarySearchTree<Vehicle>::Iterator> L(inventoryListTree.Iterators());
	list<LinkedBinarySearchTree<Vehicle>::Iterator>::iterator iter = L.begin();
	for (++iter; iter != L.end(); ++iter) {
		cout << (*(*iter)) << endl;
	}
}

void Inventory::printAllAvailibleVehicles() {
	list<LinkedBinarySearchTree<Vehicle>::Iterator> L(inventoryListTree.Iterators());
	list<LinkedBinarySearchTree<Vehicle>::Iterator>::iterator iter = L.begin();
	for (++iter; iter != L.end(); ++iter) {
		if ((*(*iter)).getAvailible() == true)
			cout << (*(*iter)) << endl;
	}
}

void Inventory::listOfReservedVehicles() {
	list<LinkedBinarySearchTree<Vehicle>::Iterator> L(inventoryListTree.Iterators());
	list<LinkedBinarySearchTree<Vehicle>::Iterator>::iterator iter = L.begin();
	for (++iter; iter != L.end(); ++iter) {
		if ((*(*iter)).getAvailible() == false)
			cout << (*(*iter)) << endl;
	}
}

void Inventory::checkAvailibility(int numOfSeats) {
	list<LinkedBinarySearchTree<Vehicle>::Iterator> L(inventoryListTree.Iterators());
	list<LinkedBinarySearchTree<Vehicle>::Iterator>::iterator iter = L.begin();
	for (++iter; iter != L.end(); ++iter) {
		if (numOfSeats <= (*(*iter)).getNumSeats()) {
			if ((*(*iter)).getAvailible() == true)
				cout << (*(*iter)) << endl;
		}
	}
}

void Inventory::reserveAVehicile(int vehicleID) {
	list<LinkedBinarySearchTree<Vehicle>::Iterator> L(inventoryListTree.Iterators());
	list<LinkedBinarySearchTree<Vehicle>::Iterator>::iterator iter = L.begin();
	for (++iter; iter != L.end(); ++iter) {
		try {
			if ((*(*iter)).getVehicleID() == vehicleID) {
				if ((*(*iter)).getAvailible() == true) {
					(*(*iter)).setAvailible(false);
					cout << "Thank you for reserving a vehicle!" << endl;
					break;
				}
				else if ((*(*iter)).getAvailible() == false) {
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
	list<LinkedBinarySearchTree<Vehicle>::Iterator> L(inventoryListTree.Iterators());
	list<LinkedBinarySearchTree<Vehicle>::Iterator>::iterator iter = L.begin();
	for (++iter; iter != L.end(); ++iter) {
		try {
			if ((*(*iter)).getVehicleID() == vehicleID) {
				if ((*(*iter)).getAvailible() == false) {
					(*(*iter)).setAvailible(true);
					cout << "Thank you for returning the vehicle!" << endl;
					break;
				}
				else if ((*(*iter)).getAvailible() == true) {
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
	list<LinkedBinarySearchTree<Vehicle>::Iterator> L(inventoryListTree.Iterators());
	list<LinkedBinarySearchTree<Vehicle>::Iterator>::iterator iter = L.begin(); {
		for (++iter; iter != L.end(); ++iter) {
			outputFile << (*(*iter)) << endl;
		}
		outputFile.close();
	}
	cout << "Inventory List has been printed to a file!" << endl;
}

ofstream& operator<<(ofstream& out, const Inventory& invO) {
	list<LinkedBinarySearchTree<Vehicle>::Iterator> L(invO.inventoryListTree.Iterators());
	list<LinkedBinarySearchTree<Vehicle>::Iterator>::iterator iter = L.begin();
	for (++iter; iter != L.end(); ++iter) {
		out << (*(*iter)) << endl;
	}

	return out;
}
#endif // !INVENTORY_H

