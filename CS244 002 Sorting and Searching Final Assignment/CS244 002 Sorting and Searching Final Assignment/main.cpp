#include <iostream>
using namespace std;
const int SETSIZE = 100;
char charList[SETSIZE];

// Swaps elements inside sorting methods 
void swapValues(char& left, char& right) {
	char tmp = left;
	left = right;
	right = tmp;
}

void swapValuesIndex(int& left,int& right) {
	int tmp = left;
	left = right;
	right = tmp;
}

void insertElement(int startIndex, int endIndex)
// Upon completion, values[0]..values[endIndex] are sorted.
{
	bool finished = false;
	int current = endIndex;
	bool moreToSearch = true;
	while (moreToSearch && !finished)
	{
		if (charList[current] < charList[current - 1])
		{
			swapValues(charList[current], charList[current - 1]);
			current--;
			moreToSearch = (current != startIndex);
		}
		else
			finished = true;
	}
}

static void insertionSort()
// Sorts the values array using the insertion sort algorithm.
{
	for (int count = 1; count < SETSIZE; count++)
		insertElement(0, count);
}

// Removes Duplicate values inside array and shifts them to the right once 
int removeDuplicateChars(char arr[]) {
	int uniqueChars = 0;
	for (int i = 0; i < SETSIZE; i++) {
		for (int j = 0; j < i; j++) {
			if (arr[i] == arr[j]) {
				char replacementValue = '$';
				arr[i] = replacementValue;
			}
		}
		if (arr[i] != '$') {
			uniqueChars++;
		}
		// TODO: Move elements with $ to the end of array
	}
	return uniqueChars;
}

// Prints out the elements of the array 
void printArray(char arr[], int size) {
	cout << "{ ";
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << "} " << endl;
}

// Main method
int main() {
	// Fills the array with random characters from A to Z
	srand(time(nullptr));
	for (int i = 0; i < SETSIZE; ++i) {
		charList[i] = (rand() % 26) + 'A';
	}

	// Prints the array with no sorting or duplicate checking 
	cout << "Array before its sorted and is checked for duplicates: " << endl;
	printArray(charList, SETSIZE);
	cout << endl;

	// Sorts the array, checks for duplicates, and then prints it 
	cout << "Array after its sorted and is checked for duplicates: " << endl;
	cout << "Number of unique characters: ";
	insertionSort();
	cout << removeDuplicateChars(charList) << endl;
	printArray(charList, SETSIZE);
	cout << endl;

	return 0;
}