#include <iostream>
#include <string>
#include "Queue ADT.h"
#include "Stack ADT.h"

using namespace std;

int main() {

	// Test the Rule of three for stack
	Stack<int> st1;

	st1.push(1);
	st1.push(2);
	st1.push(3);

	cout << "Constructor: " << st1.atTop() << endl;
	{
		// Assignment Overloading 
		Stack<int> st2;
		st2 = st1;
		cout << "Assignment Overloading: " << st2.atTop() << endl;
	}

	// cout << st1.atTop() << endl;
	{
		// Copy Constructor
		Stack<int> st3(st1);;
		cout << "Copy Constructor: " << st3.atTop() << endl;
	}
	//cout << st1.atTop() << endl;

	// Seperation 
	cout << "---------------------------------------\n" << endl;

	// Testing Rule of Three for Queue 
	ArrayQueue<int> aq1;

	aq1.enqueue(1);
	aq1.enqueue(2);
	aq1.enqueue(3);

	cout << "Constructor: " << aq1.front() << endl;

	{
		// Assignment Overloading 
		ArrayQueue<int> aq2;
		ArrayQueue<int> aq4;
		aq2.enqueue(4);
		aq2.enqueue(7);
		aq4 = aq2;
		cout << "Assignment Overloading: " << aq2.front() << endl;
	}

	{
		// Copy Constructor 
		ArrayQueue<int> aq3(aq1);
		cout << "Copy Constructor: " << aq3.front() << endl;
	}

	return 0;
}