#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <fstream>
using namespace std;
void reverseString(string& str) {
	stack<char> chars;
	for (int i = 0; i < str.size(); i++) {
		chars.push(str[i]);
	}
	str = "";
	while (!chars.empty()) {
		str = str + chars.top();
		chars.pop();
	}
}
void tokenizeStr(string str) {
	string currentToken;
	stringstream streamedLine(str);
	int count = 0;

	while (streamedLine >> currentToken) {

		count++;

		if ((count) % 2 == 1) {
			reverseString(currentToken);
		}
		cout << currentToken << " ";
	}
}
