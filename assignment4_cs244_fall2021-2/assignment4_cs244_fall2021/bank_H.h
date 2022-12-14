#ifndef BankH_H
#define BankH_H
#include "doublyLinkedList_H.h"
#include <iostream>
#include<string>
#include <fstream>
using namespace std;

class BankAccount {
public:
	BankAccount() : ownerName("No Name"), balance(0) {}
	BankAccount(string _ownerName_, double _balance_) : ownerName(_ownerName_), balance(_balance_) {}
	friend ostream& operator<<(ostream& os, const BankAccount& account);
	friend BankAccount firstMax(BankAccount, BankAccount);
	string getownerName() { return ownerName; }
	double getbalance() { return balance; }

private:
	string ownerName;
	double balance;
};
ostream& operator<<(ostream& os, const BankAccount& account) {
	os << "[" << account.ownerName << ", " << account.balance << "]";
	return os;
}
BankAccount firstMax(BankAccount acc1, BankAccount acc2) {
	if (acc2.balance > acc1.balance)
		return acc2;
	else
		return acc1;
}

/*************************** Bank Class ******************************/
class Bank {
public:
	Bank() {}
	Bank(DLinkedList<BankAccount> _accountList_) : accountList(_accountList_) {}
	void setaccountList(DLinkedList<BankAccount> _accountList_) {
		/*Pre-conditions: _accountList_ is a valid Doubly Linked List Object*/
		accountList = _accountList_;
	}
	bool fillBankListFromFile(string);
	/*Refactoring the following method members:*/
	void printAllAccounts();
	void printAllAccountsRecursively(DNode<BankAccount>*);
	void printAccountsBelowAmount(double amount);
	void printAccountsBelowAmountRecursively(double amount, DNode<BankAccount>* current);
	BankAccount getMaxAccount();
	BankAccount getMaxAccountRecursively(DNode<BankAccount>* current, BankAccount maxAccount);

	/*the following methods will help you have access to the head and the tail of the doubly-Linked List member.*/
	DNode<BankAccount>* getHeadOfAccountList() { return accountList.getHead(); }
	DNode<BankAccount>* getTailOfAccountList() { return accountList.getTail(); }
private:
	DLinkedList<BankAccount> accountList;
};

bool Bank::fillBankListFromFile(string fileName) {
	/*Pre-conditions: fileName is a valid text file name with the right path*/
	ifstream inFile;
	inFile.open(fileName.c_str());
	if (inFile.fail()) {
		return false;
	}
	string currentOwnerName;
	double currentBalance;
	string dummy = "";

	while (getline(inFile, currentOwnerName)) {
		inFile >> currentBalance;
		// cout << currentOwnerName << "\n" << currentBalance << endl;
		BankAccount currentAccount(currentOwnerName, currentBalance);
		accountList.addFront(currentAccount);
		//  cout << currentAccount << endl;
		getline(inFile, dummy); /*  \n  */
	}
	inFile.close();
	return true;
}

/*The following methods need to be updated (refactoring) so that they are implemented recursively (using recursion).*/
void Bank::printAllAccounts() {
	printAllAccountsRecursively(accountList.getHead()->getNext());
	//for (DNode<BankAccount>* curr = accountList.getHead()->getNext(); curr != accountList.getTail(); curr = curr->getNext())
	//{
	//    cout << curr->getElem() << endl;
	//}//end for
}

void Bank::printAllAccountsRecursively(DNode<BankAccount>* Current) {
	if (Current != accountList.getTail()) {
		cout << Current->getElem() << endl;
		printAllAccountsRecursively(Current->getNext());
	}
	else
		return;
}

void Bank::printAccountsBelowAmount(double amount) {
	printAccountsBelowAmountRecursively(amount, accountList.getHead()->getNext());
	/*for (DNode<BankAccount>* curr = accountList.getHead()->getNext(); curr != accountList.getTail(); curr = curr->getNext())
	{
		BankAccount account = (BankAccount)curr->getElem();
		if(account.getbalance()<amount)
			cout << account.getownerName() << endl;
	}*///end for
}

void Bank::printAccountsBelowAmountRecursively(double amount, DNode<BankAccount>* current) {
	if (current != accountList.getTail()) {
		BankAccount account = (BankAccount)current->getElem();
		if (account.getbalance() <= amount) {
			cout << account.getownerName() << endl;
		}
		printAccountsBelowAmountRecursively(amount, current->getNext());
	}
	else {
		return;
	}
}

BankAccount Bank::getMaxAccount() {
	return getMaxAccountRecursively(accountList.getHead()->getNext(), accountList.getHead()->getNext()->getElem());
	//    DNode<BankAccount>* firstNode = accountList.getHead()->getNext();
	//    BankAccount currentMaxAccount= (BankAccount)firstNode->getElem(); /*Assume that the first is the Max*/
	//
	//    for (DNode<BankAccount>* curr = accountList.getHead()->getNext(); curr != accountList.getTail(); curr = curr->getNext())
	//    {
	//        BankAccount currentAccount = (BankAccount)curr->getElem();
	//        if (currentAccount.getbalance() > currentMaxAccount.getbalance()) {
	//            currentMaxAccount = currentAccount; /*update the max*/
	//        }
	//    }//end for
	//
	 /*  return currentMaxAccount;*/
}

BankAccount Bank::getMaxAccountRecursively(DNode<BankAccount>* current, BankAccount maxAccount) {

	if (current != accountList.getTail()) {
		BankAccount currentAccount = (BankAccount)current->getElem();
		if (currentAccount.getbalance() > maxAccount.getbalance()) {
			maxAccount = currentAccount;
		}
		return getMaxAccountRecursively(current->getNext(), maxAccount);
	}
	return maxAccount;
}
#endif