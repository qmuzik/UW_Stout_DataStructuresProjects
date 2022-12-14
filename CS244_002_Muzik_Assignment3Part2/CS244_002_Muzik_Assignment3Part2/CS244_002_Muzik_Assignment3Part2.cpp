// CS244_002_Muzik_Assignment3Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

class Drone {

public:
	string droneName;

	// Default Constructor
	Drone() {
		droneName = "Unknown Drone";
		licensed = true;
		payload = 1.5;
	}

	Drone(string droneName_, bool licensed_, double payload_) {
		droneName = droneName_;
		licensed = licensed_;
		payload = payload_;
	}

	bool getDroneLiscense() {
		return licensed;
	}

	double getDronePayload() {
		return payload;
	}

	virtual void printPayload() = 0;
	/* {
		cout << "Payload: " << getDronePayload();
	}*/

private:
	bool licensed;
	double payload;

};

class ScientificDrone :public Drone {
public:
	double sensorsWeight;
	double batteryWeight;

	ScientificDrone() : Drone() {
		sensorsWeight = 0;
		batteryWeight = 0;
	}

	ScientificDrone(string _droneName_, bool _licensed_, double _payload_, double sensorsWeight_, double batteryWeight_) :
		Drone(_droneName_, _licensed_, _payload_), sensorsWeight(sensorsWeight_), batteryWeight(batteryWeight_)
	{

	}

	ScientificDrone(double sensorsWeight_, double batteryWeight_) {
		sensorsWeight = sensorsWeight_;
		batteryWeight = batteryWeight_;
	}


void printPayload()
{
	cout << "Payload: " << (sensorsWeight + batteryWeight);
}

};

int main()
{
	cout << "Drone 1" << endl;
	ScientificDrone Drone1("Drone#1", true, 2, 3, 5);
	Drone1.printPayload();
	cout << endl;

	cout << "Drone 2" << endl;
	ScientificDrone Drone2(2, 3);
	Drone2.printPayload();
	cout << endl;

	cout << "Drone 3" << endl;
	ScientificDrone Drone3;
	Drone3.printPayload();
	cout << endl;

}


