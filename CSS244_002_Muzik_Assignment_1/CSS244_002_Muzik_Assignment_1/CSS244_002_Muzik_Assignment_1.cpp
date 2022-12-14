// CSS244_002_Muzik_Assignment_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;
/*Dynamic Array Version*/

/* Prototypes */

struct Player {

	// Players information
	string fullName, currentTeam;
	double rating;
	int jerseyNumber;

};

void sortingList(Player* inputList, int listSize);
void printingList(Player* myList, int recordNumber);
void printToFile(Player* myList, string fileName, int);

int main()
{
	ifstream inFile;
	inFile.open("xboxfifa-2.txt");

	// If the file cannot be opened
	if (inFile.fail()) {
		cout << " Cannot open the file, please check the file.";
		exit(1);
	}

	int numberOfRecords = 0;

	inFile >> numberOfRecords;

	int count = 0;

	Player* list = new Player[numberOfRecords];
	string dummy;
	while (!inFile.eof()) {
		getline(inFile, dummy);
		getline(inFile, list[count].fullName);
		getline(inFile, list[count].currentTeam);
		inFile >> list[count].rating;
		inFile.ignore();
		inFile >> list[count].jerseyNumber;
		count++;
	}

	sortingList(list, numberOfRecords);
	cout << "After sorting the information.\n" << endl;
	printingList(list, numberOfRecords);

	printToFile(list, "report1.txt", 4);

	return 0;

}

void printToFile(Player* myList, string fileName, int size) {
	ofstream outFile;
	outFile.open(fileName);
	int average = 0;

	for (int i = 0; i < size; i++) {
		outFile << i + 1 << ") " << myList[i].fullName << setw(20) << "\t%" << myList[i].rating << endl;
		average = myList[i].rating + average;
	}

	outFile << "-------------------------------------------" << endl;
	outFile << "Average: " << setw(30) << "\t%" << average / size << endl;

	outFile.close();
	cout << "Data has been sent to file \n";
}


void sortingList(Player* inputList, int listSize) {
	/* Sorting the player array based on Player Rating*/
	for (int i = 0; i < listSize; i++) {
		for (int j = 0; j < listSize; j++) {
			if (inputList[j].rating < inputList[i].rating) {
				Player tmpRecord = inputList[i];
				inputList[i] = inputList[j];
				inputList[j] = tmpRecord;
			}
		}
	}
}

void printingList(Player* myList, int recordNumber) {
	for (int i = 0; i < recordNumber; i++) {
		cout << "Name: " << myList[i].fullName << endl;
		cout << "Team: " << myList[i].currentTeam << endl;
		cout << "Rating: " << myList[i].rating << endl;
		cout << "Number: " << myList[i].jerseyNumber << endl;
		cout << "-------------------------------------" << endl;
	}
}

/*Vector Version*/
const int FIELDS = 4;

struct Player {

	// Players information
	string fullName, currentTeam;
	double rating;
	int jerseyNumber;

	void printFields() {
		cout << "Name: " << fullName << endl;
		cout << "Team: " << currentTeam << endl;
		cout << "Rating: " << rating << endl;
		cout << "Number: " << jerseyNumber << endl;
		cout << "-------------------------------------" << endl;
	}
};

void sortList(vector <Player>&);
void printList(vector <Player>);

int main()
{
	ifstream inFile;
	string dummy;
	vector <Player> playerList;
	inFile.open("xboxfifa-2.txt");

	// If the file cannot be opened
	if (inFile.fail()) {
		cout << " Cannot open the file, please check the file.";
		exit(1);
	}

	string playerNameCurrent, teamCurrent;
	double rankingCurrent;
	int  jerseyCurrent;

	while (!inFile.eof()) {
		getline(inFile, dummy);
		getline(inFile, playerNameCurrent);
		getline(inFile, teamCurrent);
		inFile >> rankingCurrent;
		inFile >> jerseyCurrent;


		Player current = { playerNameCurrent,teamCurrent,rankingCurrent,jerseyCurrent };

		playerList.push_back(current);
	}

	cout << "After Sorting: " << endl;
	sortList(playerList);
	printList(playerList);

	return 0;

}

void sortList(vector <Player>& playerList) {
	for (int i = 0; i < playerList.size(); i++) {
		for (int j = i + 1; j < playerList.size(); j++) {
			if (playerList[j].jerseyNumber > playerList[i].jerseyNumber) {
				Player tmpPlayer = playerList[i];
				playerList[i] = playerList[j];
				playerList[j] = tmpPlayer;
			}
		}
	}
}

void printList(vector<Player> playerList) {
	for (int i = 0; i < playerList.size(); i++) {
		playerList[i].printFields();
	}
}