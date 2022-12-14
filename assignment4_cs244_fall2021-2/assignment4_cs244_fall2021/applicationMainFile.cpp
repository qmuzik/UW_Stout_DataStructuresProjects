/*
-use this project as a base to solve the assignment.
-means, you update this code instead of starting from scratch.
-Most of the work will be in the bank_H.h file.
-mainly, the work involves enhancing the code with exceptions when approperiate and recursion
-CopyRights: Dr. Alnaeli, UW-Stout, 2021
*/

#include "doublyLinkedList_H.h" /*DoublyLinkedList class definition*/
#include "bank_H.h"  /*Bank classes definition and including other utility libraries*/
string menu();
int main()
{
	try {
		Bank bank1;
		/*improve this with exceptions (file not found)*/

		if (!bank1.fillBankListFromFile("database_names_balances.txt")) {
			throw string("Cannot open the file. Make sure that the file is located in the project folder.\n");
			exit(1);
		}
		bank1.printAllAccounts();

		int userEntry = 0;
		/*Note for my CS244 students:system("cls") is used for clearing the console screen.
		cls is a Dos command*/

		while (userEntry != 4) {
			cout << "**********************************\n";
			cout << menu();
			/*Can you improve this with exceptions?*/
			if (!(cin >> userEntry))
			{
				throw 1;
				/*cout << "Error: Selection must be integer\n";
				exit(1);*/
			}

			switch (userEntry) {
			case 0: system("cls"); break;
			case 1: system("cls"); {
				bank1.printAllAccounts();
			}
				  break;
			case 2: system("cls"); {
				double amount;
				cout << "enter amount -> ";
				/*Can you improve this with exceptions?*/
				if (!(cin >> amount))
				{
					throw 2;
					/*cout << "Error: amount must be a number!\n";
					exit(2);*/
				}

				cout << "Customers with account balance less tha " << amount << ":\n";
				bank1.printAccountsBelowAmount(amount);

			}
				  break;
			case 3:system("cls"); {
				BankAccount maxAccount0 = bank1.getMaxAccount();
				cout << maxAccount0 << endl;
			}
				  break;
			case 4:system("cls");
				break;
			default:
				throw 3;/*cout << "Invalid Entry\n";*/
				break;
			}
		}/*end while*/

	}

	catch (string e) {
		cout << "Exception: " << e << endl;
	}

	catch (int e) {
		if (e == 1) {
			cout << "Exception: Selection must be integer!\n" << "Code: " << e << endl;
			exit(1);
		}
		else if (e == 2) {
			cout << "Exception: Amount must be a number!\n" << "Code: " << e << endl;;
			exit(2);
		}

		else if (e == 3) {
			cout << "Exception: Selection must be from 1 - 4 !\n" << "Code: " << e << endl;
			exit(3);
		}
	}

	return 0;
}

string menu() {

	string message;
	message = "0. Clear Screen..\n1. Print All accounts.\n2. Print names of the customer who have balances below a given amount.";
	message = message + "\n3.The customer with the highest balance.\n4: Exit.\nYour Selection --> ";
	return message;
}