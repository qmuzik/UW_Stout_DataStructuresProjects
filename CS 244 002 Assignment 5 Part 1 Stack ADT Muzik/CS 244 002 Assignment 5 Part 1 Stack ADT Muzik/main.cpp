#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "stackADT.h"

using namespace std;

int main()
{
	// Varibles
	stack<string> lines;
	ifstream inFile;
	inFile.open("Encrypted Message.txt");

	while (inFile.fail()) {
		cout << "Cannot open the file!\n";
		inFile.open("Encrypted Message.txt");
	}
	string currentLine;
	while (getline(inFile, currentLine))
	{
		lines.push(currentLine);
		//cout << currentLine << endl; // testing 
	}
	inFile.close();

	while (!lines.empty()) {
		string currentTop = lines.top();
		tokenizeStr(currentTop);
		cout << endl;
		lines.pop();
	}


}