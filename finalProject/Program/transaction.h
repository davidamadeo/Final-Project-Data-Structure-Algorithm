#include <iostream>
#ifndef TRANSACTION_H
#define TRANSACTION_H
using namespace std;

class Transaction
{
public:
	Transaction();
	Transaction(string date, string name, string typeOfTransaction, double amount, double balOrCred, double totalBalance, double totalCredit);
	string getDate();
	string getName();
	string getTypeOfTransaction();
	double getAmount();
	double getBalOrCred();
	double getTotalBalance();
	double getTotalCredit();

private:
	string date;
	string name;
	string typeOfTransaction;
	double amount;
	double balOrCred;
	double totalBalance;
	double totalCredit;
};

Transaction::Transaction()
{
}
Transaction::Transaction(string date, string name, string typeOfTransaction, double amount, double balOrCred, double totalBalance, double totalCredit)
{
	this->date = date;
	this->name = name;
	this->typeOfTransaction = typeOfTransaction;
	this->amount = amount;
	this->balOrCred = balOrCred;
	this->totalBalance = totalBalance;
	this->totalCredit = totalCredit;
}

string Transaction::getDate()
{
	return date;
}

string Transaction::getName()
{
	return name;
}

string Transaction::getTypeOfTransaction()
{
	return typeOfTransaction;
}

double Transaction::getAmount()
{
	return amount;
}

double Transaction::getBalOrCred()
{
	return balOrCred;
}

double Transaction::getTotalBalance()
{
	return totalBalance;
}

double Transaction::getTotalCredit()
{
	return totalCredit;
}
#endif
