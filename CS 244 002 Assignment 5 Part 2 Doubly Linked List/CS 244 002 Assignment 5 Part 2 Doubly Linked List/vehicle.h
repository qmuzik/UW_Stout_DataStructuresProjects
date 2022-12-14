#ifndef VEHICLE_H
#define VEHICLE_H
#include "doublyLinkedList.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Vehicle {
public:
	// Constructors;
	Vehicle(); // Default Constructor
	Vehicle(string vehicleID_, string vehicleMake_, string vehicleModel_, int numOfSeats_, bool availibilty_, int numOfFeatures_, DLinkedList<string> featuresList_);
	Vehicle(const Vehicle& org); // Copy Constructor

	// Destructor 
	~Vehicle() {
		/*delete featuresList;*/
	}

	// Getters
	string getVehicleID();
	string getVehicleMake();
	string getVehicleModel();
	int getNumSeats();
	bool getAvailible();
	int getNumberOfFeatures();

	// Setters 
	void setVehicleID(string );
	void setVehicleMake(string );
	void setVehicleModel(string );
	void setNumSeats(int );
	void setAvailible(bool );
	void setNumberOfFeatures(int );

	// Operator Overloading
	friend ostream& operator<<(ostream& out, const Vehicle& objV); // Regular Output
	friend ofstream& operator<<(ofstream& out, const Vehicle& objV); // File Output
	Vehicle& operator=(const Vehicle& rhs); // Assignment Overloading 

private:
	string vehicleID;
	string vehicleMake;
	string vehicleModel;
	int numOfSeats;
	bool availible;
	int numberOfFeatures;
	DLinkedList<string> featuresList;
};

// Methods for Vechicle Class 
// Default Constructor 
Vehicle::Vehicle() {
	vehicleID = "-";
	vehicleMake = "-";
	vehicleModel = "-";
	numOfSeats = 0;
	availible = true;
	numberOfFeatures = 0;
}

// Constructor 
Vehicle::Vehicle(string vehicleID_, string vehicleMake_, string vehicleModel_, int numOfSeats_, bool availibilty_, int numOfFeatures_, DLinkedList<string> featuresList_) {
	vehicleID = vehicleID_;
	vehicleMake = vehicleMake_;
	vehicleModel = vehicleModel_;
	numOfSeats = numOfSeats_;
	availible = availibilty_;
	numberOfFeatures = numOfFeatures_;
	featuresList = featuresList_;
}

// Copy Constructor
Vehicle::Vehicle(const Vehicle& org) {
	vehicleID = org.vehicleID;
	vehicleMake = org.vehicleMake;
	vehicleModel = org.vehicleModel;
	numOfSeats = org.numOfSeats;
	availible = org.availible;
	numberOfFeatures = org.numberOfFeatures;
	for (DNode<string>* current = org.featuresList.getHead()->getNext(); current != org.featuresList.getTail(); current = current->getNext())
		featuresList.addBack(current->getElem());
}

// Getters  
string Vehicle::getVehicleID() {
	return vehicleID;
}

string Vehicle::getVehicleMake() {
	return vehicleMake;
}

string Vehicle::getVehicleModel() {
	return vehicleModel;
}

int Vehicle::getNumSeats() {
	return numOfSeats;
}

bool Vehicle::getAvailible() {
	return availible;
}

int Vehicle::getNumberOfFeatures() {
	return numberOfFeatures;
}

// Setters 
void Vehicle::setVehicleID(string _vehicle_ID_) {
	vehicleID = _vehicle_ID_;
}

void Vehicle::setVehicleMake(string _vehicle_MAKE_) {
	vehicleMake = _vehicle_MAKE_;
}

void Vehicle::setVehicleModel(string _vehicle_MODEL_) {
	vehicleModel = _vehicle_MODEL_;
}

void Vehicle::setNumSeats(int _numSEATS_) {
	numOfSeats = _numSEATS_;
}

void Vehicle::setAvailible(bool _availible_) {
	availible = _availible_;
}

void Vehicle::setNumberOfFeatures(int _numbOFFEATURES_) {
	numberOfFeatures = _numbOFFEATURES_;
}

// Operator Overloading

// Assingment Overloading 
Vehicle& Vehicle::operator=(const Vehicle& rhs) {
	if (this != &rhs)
	{
		vehicleID = rhs.vehicleID;
		vehicleMake = rhs.vehicleMake;
		vehicleModel = rhs.vehicleModel;
		numOfSeats = rhs.numOfSeats;
		availible = rhs.availible;
		numberOfFeatures = rhs.numberOfFeatures;
		while (!featuresList.empty()) {
			featuresList.removeFront();
		}
		for (DNode<string>* current = rhs.featuresList.getHead()->getNext(); current != rhs.featuresList.getTail(); current = current->getNext())
			featuresList.addBack(current->getElem());
	}
	return *this;
}

ostream& operator<<(ostream& out, const Vehicle& objV)
// overleaoding the insertion operator << Terimal OutPut
{
	out << "------------------------------------------\n";
	out << "ID: " << objV.vehicleID << endl;
	out << "Make: " << objV.vehicleMake << endl;
	out << "Model: " << objV.vehicleModel << endl;
	out << "Number of seats: " << objV.numOfSeats << endl;
	if (objV.availible)
		out << "Availability: available" << endl;
	else
		out << "Availability: Not available" << endl;
	out << "Extra Features[" << objV.numberOfFeatures << "]: " << endl;
	if (objV.numberOfFeatures < 1)
		out << "Basic trim" << endl;
	else {
		out << objV.featuresList << endl;  /*printing is overloaded in the DLinkedList class*/
	}
	return out;
}

ofstream& operator<<(ofstream& out, const Vehicle& objV)
// overleaoding the insertion operator << for the output file stream
{
	out << objV.vehicleID << endl;
	out << objV.vehicleMake << endl;
	out << objV.vehicleModel << endl;
	out << objV.numOfSeats << endl;
	out << objV.availible << endl;
	out << objV.numberOfFeatures << endl;
	for (DNode<string>* current = objV.featuresList.getHead()->getNext(); current != objV.featuresList.getTail(); current = current->getNext())
		out << current->getElem() << endl;
	return out;
}

#endif // !VEHICLE_H
