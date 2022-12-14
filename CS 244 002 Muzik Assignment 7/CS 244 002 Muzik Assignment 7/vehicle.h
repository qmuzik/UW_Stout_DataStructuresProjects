#ifndef VEHICLE_H
#define VEHICLE_H
#include "BinarySearchTreeTemplateIter.h"
#include <fstream>
#include <iostream>
#include <string>
#include <list>
using namespace std;

class Vehicle {
public:
	// Tree Variable 
	LinkedBinarySearchTree<string> featuresListTree;

	// Constructors;
	Vehicle(); // Default Constructor
	Vehicle(int vehicleID_, string vehicleMake_, string vehicleModel_, int numOfSeats_, bool availibilty_, int numOfFeatures_, LinkedBinarySearchTree<string> featuresListTree_);
	Vehicle(const Vehicle& org); // Copy Constructor

	// Destructor 
	~Vehicle() {
	}

	// Getters
	int getVehicleID();
	string getVehicleMake();
	string getVehicleModel();
	int getNumSeats();
	bool getAvailible();
	int getNumberOfFeatures();

	// Setters 
	void setVehicleID(int);
	void setVehicleMake(string);
	void setVehicleModel(string);
	void setNumSeats(int);
	void setAvailible(bool);
	void setNumberOfFeatures(int);

	// Operator Overloading
	friend ostream& operator<<(ostream& out, const Vehicle& objV); // Regular Output
	friend ofstream& operator<<(ofstream& out, const Vehicle& objV); // File Output
	friend bool operator<(const Vehicle& v1, const Vehicle& v2); // Comparison between vehicles 
	Vehicle& operator=(const Vehicle& rhs); // Assignment Overloading 

private:
	int vehicleID;
	string vehicleMake;
	string vehicleModel;
	int numOfSeats;
	bool availible;
	int numberOfFeatures;
};

// Methods for Vechicle Class 
// Default Constructor 
Vehicle::Vehicle() {
	vehicleID = 0;
	vehicleMake = "-";
	vehicleModel = "-";
	numOfSeats = 0;
	availible = true;
	numberOfFeatures = 0;
}

// Constructor 
Vehicle::Vehicle(int vehicleID_, string vehicleMake_, string vehicleModel_, int numOfSeats_, bool availibilty_, int numOfFeatures_, LinkedBinarySearchTree<string> featuresListTree_) {
	vehicleID = vehicleID_;
	vehicleMake = vehicleMake_;
	vehicleModel = vehicleModel_;
	numOfSeats = numOfSeats_;
	availible = availibilty_;
	numberOfFeatures = numOfFeatures_;
	list<LinkedBinarySearchTree<string>::Iterator> L(featuresListTree_.Iterators());
	list<LinkedBinarySearchTree<string>::Iterator>::iterator iter = L.begin();
	for (++iter; iter != L.end(); ++iter) {
		featuresListTree.insert((*(*iter)));
	}
}

// Copy Constructor
Vehicle::Vehicle(const Vehicle& org) {
	vehicleID = org.vehicleID;
	vehicleMake = org.vehicleMake;
	vehicleModel = org.vehicleModel;
	numOfSeats = org.numOfSeats;
	availible = org.availible;
	numberOfFeatures = org.numberOfFeatures;
	list<LinkedBinarySearchTree<string>::Iterator> L(org.featuresListTree.Iterators());
	list<LinkedBinarySearchTree<string>::Iterator>::iterator iter = L.begin();
	for (++iter; iter != L.end(); ++iter) {
		featuresListTree.insert((*(*iter)));
	}
}

// Getters  
int Vehicle::getVehicleID() {
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
void Vehicle::setVehicleID(int _vehicle_ID_) {
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

//// Assingment Overloading 
Vehicle& Vehicle::operator=(const Vehicle& rhs) {
	if (this != &rhs)
	{
		vehicleID = rhs.vehicleID;
		vehicleMake = rhs.vehicleMake;
		vehicleModel = rhs.vehicleModel;
		numOfSeats = rhs.numOfSeats;
		availible = rhs.availible;
		numberOfFeatures = rhs.numberOfFeatures;
		list<LinkedBinarySearchTree<string>::Iterator> L2(rhs.featuresListTree.Iterators());
		list<LinkedBinarySearchTree<string>::Iterator>::iterator iter2 = L2.begin();
		while (L2.empty()) {
			L2.erase(iter2);
		}
		list<LinkedBinarySearchTree<string>::Iterator> L(rhs.featuresListTree.Iterators());
		list<LinkedBinarySearchTree<string>::Iterator>::iterator iter = L.begin();
		for (++iter; iter != L.end(); ++iter) {
			featuresListTree.insert((*(*iter)));
		}
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
		out << "[Basic trim]" << endl;
	else {
		list<LinkedBinarySearchTree<string>::Iterator> L(objV.featuresListTree.Iterators());
		list<LinkedBinarySearchTree<string>::Iterator>::iterator iter = L.begin();
		++iter;
		out << "[" << (*(*iter));
		for (++iter; iter != L.end(); ++iter) {
			out << ", " << (*(*iter));
		}
		out << "]" << endl;
	}

	return out;
}

ofstream& operator<<(ofstream& out, const Vehicle& objV)
// overleaoding the insertion operator << for the output file stream
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
		out << "[Basic trim]" << endl;
	else {
		list<LinkedBinarySearchTree<string>::Iterator> L(objV.featuresListTree.Iterators());
		list<LinkedBinarySearchTree<string>::Iterator>::iterator iter = L.begin();
		++iter;
		out << "[" << (*(*iter));
		for (++iter; iter != L.end(); ++iter) {
			out << ", " << (*(*iter));
		}
		out << "]" << endl;
	}
	return out;
}

bool operator<(const Vehicle& v1, const Vehicle& v2) {
	return  ((v1.numOfSeats < v2.numOfSeats));
}
#endif // !VEHICLE_H
#pragma once
