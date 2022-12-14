#ifndef INVENTORY_H
#define INVENTORY_H
#include "doublyLinkedList.h"
#include "vehicle.h"
#include <fstream>
#include <iostream>
#include <string>

// Inventory Class 
class Inventory {
public:
	// Constructors
	Inventory();
	Inventory(DLinkedList<Vehicle> _inventoryList_, int numberOfcars_);

	// Setters
	void setInventoryList(DLinkedList<Vehicle> _inventoryList_);

	// Functions
	bool fillFromFile(string);
	void printAllRegisteredVehicles();
	void printAllAvailibleVehicles();
	void listOfReservedVehicles();
	void checkAvailibility(int seats);
	void reserveAVehicile(string);
	void returnAVehicle(string);
	void printAllVehiclesToFile();

	// Head and Tail of DLL
	DNode<Vehicle>* getHeadOfInventoryList() {
		return inventoryList.getHead();
	}

	DNode<Vehicle>* getTailOfInventoryList() {
		return inventoryList.getTail();
	}

private:
	DLinkedList<Vehicle> inventoryList;
	int numberOfcars;
};

// Methods for Inventory
Inventory::Inventory() {
	numberOfcars = 0;
}

Inventory::Inventory(DLinkedList<Vehicle> _inventoryList_, int numberOfcars_) {
	inventoryList = _inventoryList_;
	numberOfcars = numberOfcars_;
}

void Inventory::setInventoryList(DLinkedList<Vehicle> _inventoryList_) {
	inventoryList = _inventoryList_;
}

bool Inventory::fillFromFile(string fileName) {
	ifstream inFile;
	inFile.open(fileName.c_str());

	if (inFile.fail()) {
		return false;
	}

	int numOfRecords, numOfSeats;
	string vehicleID, vehicleMake, vehicleModel;

	string dummyRead = "";
	bool availible;
	int numberOfFeatures;

	inFile >> numOfRecords;
	getline(inFile, dummyRead);

	for (int i = 0; i < numOfRecords; ++i) {
		DLinkedList<string> featuresList;
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
			featuresList.addBack(currentFeature);
		}
		Vehicle currentVehicle(vehicleID, vehicleMake, vehicleModel, numOfSeats, availible, numberOfFeatures, featuresList);
		inventoryList.addFront(currentVehicle);
	}
	inFile.close();
	return true;
}

void Inventory::printAllRegisteredVehicles() {
	for (DNode<Vehicle>* curr = inventoryList.getHead()->getNext(); curr != inventoryList.getTail(); curr = curr->getNext())
	{
		cout << curr->getElem() << endl;
	}//end for
}

void Inventory::printAllAvailibleVehicles() {
	for (DNode<Vehicle>* curr = inventoryList.getHead()->getNext(); curr != inventoryList.getTail(); curr = curr->getNext())
	{
		Vehicle vehicle = (Vehicle)curr->getElem();
		if (vehicle.getAvailible() == true) {
			cout << curr->getElem() << endl;
		}
	}
}

void Inventory::listOfReservedVehicles() {
	for (DNode<Vehicle>* curr = inventoryList.getHead()->getNext(); curr != inventoryList.getTail(); curr = curr->getNext()) {
		Vehicle vehicle = (Vehicle)curr->getElem();
		if (vehicle.getAvailible() == false) {
			cout << curr->getElem() << endl;
		}
	}
}

void Inventory::checkAvailibility(int seats) {
	for (DNode<Vehicle>* curr = inventoryList.getHead()->getNext(); curr != inventoryList.getTail(); curr = curr->getNext()) {
		Vehicle vehicle = (Vehicle)curr->getElem();
		if (vehicle.getNumSeats() >= seats) {
			cout << curr->getElem() << endl;
		}
	}
}

void Inventory::reserveAVehicile(string vehicleID) {
	for (DNode<Vehicle>* curr = inventoryList.getHead()->getNext(); curr != inventoryList.getTail(); curr = curr->getNext()) {
		Vehicle vehicle = (Vehicle)curr->getElem();
		if (vehicle.getVehicleID() == vehicleID && vehicle.getAvailible() == true) {
			curr->elem.setAvailible(false);
			cout << "Thank you for reserving a vehicle!" << endl;
			break;
		}
		/*else if ((vehicle.getVehicleID() == vehicleID && vehicle.getAvailible() == false) || (vehicle.getVehicleID() != vehicleID)) {
			cout << "Vehicle is not available" << endl;
			break;
		}*/
	}
}

void Inventory::returnAVehicle(string vehicleID) {
	for (DNode<Vehicle>* curr = inventoryList.getHead()->getNext(); curr != inventoryList.getTail(); curr = curr->getNext()) {
		Vehicle vehicle = (Vehicle)curr->getElem();
		if (vehicle.getVehicleID() == vehicleID && vehicle.getAvailible() == false) {
			curr->elem.setAvailible(true);
			cout << "Thank you for returning the vehicle!" << endl;
			break;
		}
		/*else if ((vehicle.getVehicleID() == vehicleID && vehicle.getAvailible() == true) || (vehicle.getVehicleID() != vehicleID)) {
			cout << "Vehicle is not available" << endl;
			break;
		}*/
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
