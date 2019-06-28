#include <iostream>
#ifndef UI_H
#define UI_H

#include "holder.h"
#include "LinkedList.h"
#include "transaction.h"

#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <sstream>
#include <fstream>
#include <Windows.h>
#include <stdio.h>
using namespace std;

class UI
{
public:
	//	---------------------------------------
	//			     PROGRAM FLOW
	//	---------------------------------------
	void run();
	//	---------------------------------------
	void doTransaction();
	//			----------------------------------------
	void payment();
	void deposit();
	void transferToOtherHolder();
	void payDueCredit();
	//			----------------------------------------
	void addHolder();
	void removeHolder();
	void showSavingHolders();
	void showCreditHolders();
	void showTransactionHistory();
	//	---------------------------------------
	//			 ADDITIONAL FUNCTIONS
	//	---------------------------------------
	void menuHeader();
	void addHolderHeader();
	void removeHolderHeader();
	void transactionHistoryHeader();
	void mySavingHoldersHeader();
	void myCreditHoldersHeader();
	bool holderExistsValidation(string name);
	bool savingHolderExistsValidation(string name);
	bool creditHolderExistsValidation(string name);
	void createTransaction(string typeOfTransaction, double amount, NODE<Holder> *curr);
	void writeToHolderTXT();
	void readFromHolderTXT();
	void readFromTransactionTXT();
	void writeToTransactionTXT();
	void doTransactionHeader();
	void paymentHeader();
	void transferHeader();
	void payDueCreditHeader();
	void depositHeader();

private:
	LinkedList<Holder> holderList;
	LinkedList<Transaction> transactionHistory;
};

//FUNCTION TO WRITE TRANSACTION TO TXT
void UI::writeToTransactionTXT()
{
	ofstream file;
	file.open("Transaction.txt", ios::trunc);
	//WRITE EVERY ELEMENT OF VECTOR TO TXT FILE, SEPARATED WITH COMAS
	if (file.is_open())
	{
		NODE<Transaction> *curr = transactionHistory.getFirst();
		while (curr != NULL)
		{
			stringstream ss;
			ss << curr->data.getDate() << "," << curr->data.getName() << ","
			   << curr->data.getTypeOfTransaction() << "," << curr->data.getAmount() << ","
			   << curr->data.getBalOrCred() << "," << curr->data.getTotalBalance() << ","
			   << curr->data.getTotalCredit() << "\n";
			file << ss.str();
			curr = curr->link;
		}
		file.close();
	}
}

//FUNCTION TO READ TRANSACTION.TXT
void UI::readFromTransactionTXT()
{
	string line;
	ifstream file;

	file.open("Transaction.txt");
	//IF THE FILE DOES NOT EXIST
	if (!file)
	{
		cout << "cannot open file " << endl;
	}
	//IF IT THE FILE EXISTS
	else
	{
		//GETS ALL THE DATAS FROM TXT FILE AND PUTS ALL THE STRINGS IN A LINE TO A LIST
		while (file)
		{
			getline(file, line);
			if (line != "")
			{
				int length = line.length();

				LinkedList<string> readFileList;
				string temp;
				for (int i = 0; i < length; i++)
				{
					if (line[i] == ',')
					{
						readFileList.insert(temp);
						temp = "";
					}
					else if (i == (length - 1))
					{
						temp += line[i];
						readFileList.insert(temp);
						temp = "";
					}
					else
					{
						temp += line[i];
					}
				}
				//SEPARATES EACH STRING AND INSERT THEM TO REAL TRANSACTION HISTORY LIST
				NODE<string> *curr = readFileList.getFirst();
				string date = curr->data;
				curr = curr->link;
				string name = curr->data;
				curr = curr->link;
				string typeOfTransaction = curr->data;
				curr = curr->link;
				double amount = atof(curr->data.c_str());
				curr = curr->link;
				double balOrCred = atof(curr->data.c_str());
				curr = curr->link;
				double totalBalance = atof(curr->data.c_str());
				curr = curr->link;
				double totalCredit = atof(curr->data.c_str());

				Transaction _transaction(date, name, typeOfTransaction, amount, balOrCred, totalBalance, totalCredit);
				transactionHistory.insert(_transaction);
			}
		}
	}
	file.close();
}

//FUNCTION TO WRITE TO TXT
void UI::writeToHolderTXT()
{
	ofstream file;
	file.open("Holder.txt", ios::trunc);
	//WRITE EVERY ELEMENT OF VECTOR TO TXT FILE, SEPARATED WITH COMAS
	if (file.is_open())
	{
		NODE<Holder> *curr = holderList.getFirst();
		while (curr != NULL)
		{
			stringstream ss;
			ss << curr->data.getType() << "," << curr->data.getName() << "," << curr->data.getAmount() << "\n";
			file << ss.str();
			curr = curr->link;
		}
		file.close();
	}
}

//FUNCTION TO READ HOLDER.TXT
void UI::readFromHolderTXT()
{
	string line;
	ifstream file;

	file.open("Holder.txt");
	//IF THE FILE DOES NOT EXIST
	if (!file)
	{
		cout << "cannot open file " << endl;
	}
	//IF IT THE FILE EXISTS
	else
	{
		//GETS ALL DATAS FROM TXT FILE AND PUTS ALL THE STRINGS IN A LINE TO A LIST
		while (file)
		{
			getline(file, line);
			if (line != "")
			{
				int length = line.length();
				LinkedList<string> readFileList;

				string temp;
				for (int i = 0; i < length; i++)
				{
					if (line[i] == ',')
					{
						readFileList.insert(temp);
						temp = "";
					}
					else if (i == (length - 1))
					{
						temp += line[i];
						readFileList.insert(temp);
						temp = "";
					}
					else
					{
						temp += line[i];
					}
				}

				//SEPARATES EACH STRING AND INSERT THEM TO REAL TRANSACTION HISTORY LIST
				NODE<string> *curr = readFileList.getFirst();
				string type = curr->data;
				curr = curr->link;
				string name = curr->data;
				curr = curr->link;
				double amount = atof(curr->data.c_str());
				Holder _holder(type, name, amount);
				holderList.insert(_holder);
			}
		}
	}
	file.close();
}

//HEADERS
//------------------------------------------------------------------------------------------------------------------------------------------
void UI::menuHeader()
{
	cout << "==================================\n"
			"Welcome to Smart Financial Manager\n"
			"==================================\n";
}

void UI::addHolderHeader()
{
	cout << "==================================\n"
			"	         ADD HOLDER\n"
			"==================================\n";
}
void UI::removeHolderHeader()
{
	cout << "==================================\n"
			"          REMOVE HOLDER\n"
			"==================================\n";
}
void UI::doTransactionHeader()
{
	cout << "==================================\n"
			"         DO TRANSACTION\n"
			"==================================\n";
}
void UI::paymentHeader()
{
	cout << "==================================\n"
			"            PAYMENT\n"
			"==================================\n";
}

void UI::depositHeader()
{
	cout << "==================================\n"
			"            DEPOSIT\n"
			"==================================\n";
}

void UI::transferHeader()
{
	cout << "==================================\n"
			"            TRANSFER\n"
			"==================================\n";
}

void UI::payDueCreditHeader()
{
	cout << "==================================\n"
			"          PAY DUE CREDIT\n"
			"==================================\n";
}

void UI::mySavingHoldersHeader()
{
	cout << "                SAVING HOLDERS\n"
			" ============================================== \n"
			"| Name Of Holder       | Balance              |\n"
			" ----------------------------------------------\n";
}

void UI::myCreditHoldersHeader()
{
	cout << "                CREDIT HOLDERS\n"
			" ============================================== \n"
			"| Name Of Holder       | Credit Due           |\n"
			" ----------------------------------------------\n";
}

void UI::transactionHistoryHeader()
{
	cout << "                                           TRANSACTION HISTORY\n"
			" ============================================================================================================== \n"
			"| DATE       | NAME OF HOLDER  | TYPE | AMOUNT          | BAL OR CRED     | TOTAL BALANCE   | TOTAL CREDIT    |\n"
			" --------------------------------------------------------------------------------------------------------------\n";
} //				10				15		    4		    15				15					15					15
//------------------------------------------------------------------------------------------------------------------------------------------

//FUNCTION TO CHECK THE EXISTENCE OF THE HOLDER
bool UI::holderExistsValidation(string name)
{
	NODE<Holder> *curr = holderList.getFirst();
	while (curr != NULL)
	{
		if (curr->data.getName() == name)
		{
			return true;
		}
		curr = curr->link;
	}
	if (curr == NULL)
	{
		return false;
	}
}

//FUNCTION TO CHECK THE EXISTENCE OF "ONLY" SAVING HOLDER
bool UI::savingHolderExistsValidation(string name)
{
	NODE<Holder> *curr = holderList.getFirst();
	while (curr != NULL)
	{
		if (curr->data.getName() == name && curr->data.getType() == "S")
		{
			return true;
		}
		curr = curr->link;
	}
	if (curr == NULL)
	{
		return false;
	}
}

//FUNCTION TO CHECK THE EXISTENCE OF "ONLY" CREDIT HOLDER
bool UI::creditHolderExistsValidation(string name)
{
	NODE<Holder> *curr = holderList.getFirst();
	while (curr != NULL)
	{
		if (curr->data.getName() == name && curr->data.getType() == "C")
		{
			return true;
		}
		curr = curr->link;
	}
	if (curr == NULL)
	{
		return false;
	}
}

//FUNCTION TO REMOVE HOLDER
void UI::removeHolder()
{
	removeHolderHeader();
	showSavingHolders();
	showCreditHolders();
	string name;
	cout << "Input name >> " << endl;
	cin >> name;
	transform(name.begin(), name.end(), name.begin(), ::toupper);
	holderList.deleteSpecificItem(name);
}

//FUNCTION TO ADD HOLDER
void UI::addHolder()
{
	addHolderHeader();
	string name;
	string type;
	double amount;
	int num = 0;
	//CHECKS WHETHER IT IS UNIQUE (DOES NOT EXIST IN THE HOLDER LIST)
	do
	{
		if (num != 0)
		{
			cout << name << " already exists" << endl;
		}
		cout << "Name of Holder(e.g. Debit_BCA, OVO, GOPAY, BCA_CREDIT, HSBC_Platinum, WALLET)\n"
				"*NoSpaces*\n"
				"INPUT>> ";
		cin >> name;
		num += 1;
		transform(name.begin(), name.end(), name.begin(), ::toupper);
	} while (holderExistsValidation(name));

	//ASKS FOR THE TYPE OF HOLDER
	cout << "Type of Holder :\n"
			"1. Saving\n"
			"2. Credit\n"
			"INPUT>> ";
	cin >> type;

	//INSERT HOLDER DEPENDING ON THE TYPE
	if (type == "1")
	{
		cout << "Initialize Balance (Rp) \n"
				"INPUT>> ";
		cin >> amount;
		Holder holder("S", name, amount);
		holderList.insert(holder);
		if (amount != 0)
		{
			NODE<Holder> *curr = holderList.getFirst();
			do
			{
				if (curr->link == NULL)
				{
					createTransaction("NEW", amount, curr);
				}
				curr = curr->link;
			} while (curr != NULL);
		}
	}

	if (type == "2")
	{
		cout << "Initialize Credit (Rp) \n"
				"INPUT>> ";
		cin >> amount;
		Holder holder("C", name, amount);
		holderList.insert(holder);

		if (amount != 0)
		{
			NODE<Holder> *curr = holderList.getFirst();
			do
			{
				if (curr->link == NULL)
				{
					createTransaction("NEW", amount, curr);
				}
				curr = curr->link;
			} while (curr != NULL);
		}
	}
	cout << "Your holder has been successfuly created" << endl;
}

//FUNCTION TO SHOW SAVING HOLDERS ONLY WITH TABLE
void UI::showSavingHolders()
{
	double totalSaving = 0;
	mySavingHoldersHeader();
	NODE<Holder> *curr = holderList.getFirst();
	while (curr != NULL)
	{
		stringstream ss;
		ss << curr->data.getAmount();
		string amount = ss.str();
		string name = curr->data.getName();
		string type = curr->data.getType();

		if (type == "S")
		{
			totalSaving += curr->data.getAmount();
			printf("| %-20s | %-20s |\n", name.c_str(), amount.c_str());
		}
		curr = curr->link;
	}
	cout << " ----------------------------------------------\n";
	cout << "  TOTAL BALANCE        | " << totalSaving << endl;
	cout << endl;
}

//FUNCTION TO SHOW CREDIT HOLDERS ONLY WITH TABLE
void UI::showCreditHolders()
{
	double totalCredit = 0;
	myCreditHoldersHeader();
	NODE<Holder> *curr2 = holderList.getFirst();
	while (curr2 != NULL)
	{
		stringstream ss2;
		ss2 << curr2->data.getAmount();
		string amount2 = ss2.str();
		string name2 = curr2->data.getName();
		string type2 = curr2->data.getType();

		if (type2 == "C")
		{
			totalCredit += curr2->data.getAmount();
			printf("| %-20s | %-20s |\n", name2.c_str(), amount2.c_str());
		}
		curr2 = curr2->link;
	}
	cout << " ----------------------------------------------\n";
	cout << "  TOTAL CREDIT         | " << totalCredit << endl;
	cout << endl;
}

//FUNCTION TO PRINT TRANSACTION HISTORY WITH TABLE
void UI::showTransactionHistory()
{
	transactionHistoryHeader();
	NODE<Transaction> *curr = transactionHistory.getFirst();
	while (curr != NULL)
	{
		string date = curr->data.getDate();
		string name = curr->data.getName();
		string type = curr->data.getTypeOfTransaction();

		stringstream ss1;
		ss1 << curr->data.getAmount();
		string amount = ss1.str();

		stringstream ss2;
		ss2 << curr->data.getBalOrCred();
		string balOrCred = ss2.str();

		stringstream ss3;
		ss3 << curr->data.getTotalBalance();
		string totalBalance = ss3.str();

		stringstream ss4;
		ss4 << curr->data.getTotalCredit();
		string totalCredit = ss4.str();

		printf("| %-10s | %-15s | %-4s | %-15s | %-15s | %-15s | %-15s |\n", date.c_str(), name.c_str(), type.c_str(), amount.c_str(), balOrCred.c_str(), totalBalance.c_str(), totalCredit.c_str());
		curr = curr->link;
	}
	cout << " --------------------------------------------------------------------------------------------------------------\n";
	cout << "*LEGEND\n"
			"PAY = PAYMENT\n"
			"DEP = DEPOSIT MONEY\n"
			"TRF = TRANSFER TO OTHER HOLDER\n"
			"CRE = DUE CREDIT PAYMENT\n"
			"NEW = INITIALIZE SAVING OR CREDIT"
		 << endl;
}

//FUNCTION TO WRITE TRANSACTION HISTORY
void UI::createTransaction(string typeOfTransaction, double amount, NODE<Holder> *curr)
{
	SYSTEMTIME str_t;
	GetSystemTime(&str_t);
	stringstream ss;
	ss << str_t.wYear << "/" << str_t.wMonth << "/" << str_t.wDay;
	string date = ss.str();
	string name = curr->data.getName();
	double balOrCred = curr->data.getAmount();
	double totalBalance = 0;
	double totalCredit = 0;

	NODE<Holder> *first = holderList.getFirst();
	while (first != NULL)
	{
		if (first->data.getType() == "S")
		{
			totalBalance += first->data.getAmount();
		}
		if (first->data.getType() == "C")
		{
			totalCredit += first->data.getAmount();
		}
		first = first->link;
	}

	Transaction _transaction(date, name, typeOfTransaction, amount, balOrCred, totalBalance, totalCredit);
	transactionHistory.insert(_transaction);
}

//FUNCTION TO DO PAYMENT
//CHECKS WHETHER THERE IS ATLEAST 1 HOLDER (SAVING OR CREDIT)
void UI::payment()
{
	paymentHeader();
	double amount;
	string name;
	//Enter Amount
	cout << "Enter Amount\n"
			"INPUT>> ";
	cin >> amount;
	NODE<Holder> *curr = holderList.getFirst();
	if (curr == NULL)
	{
		cout << "You do not have a holder, Please create a new one" << endl;
	}
	else
	{
		//CHOOSES HOLDER WITH VALIDATION
		showSavingHolders();
		showCreditHolders();
		int num = 0;
		do
		{
			if (num != 0)
			{
				cout << "INVALID HOLDER\n";
			}
			cout << "Choose Holder\n"
					"INPUT>> ";
			num += 1;
			cin >> name;
			transform(name.begin(), name.end(), name.begin(), ::toupper);
		} while (!holderExistsValidation(name));

		//	CHANGES THE VALUE TO THE NEW ONE
		NODE<Holder> *curr = holderList.getFirst();
		while (curr != NULL)
		{
			if (name == curr->data.getName() && curr->data.getType() == "S")
			{
				if (curr->data.getAmount() >= amount)
				{
					double finalAmount = curr->data.getAmount() - amount;
					curr->data.setAmount(finalAmount);
					//					WRITE TRANSACTION TO transactionHistory
					//					-------------------------------------------------------------------------------------------------
					createTransaction("PAY", amount, curr);
					//					-------------------------------------------------------------------------------------------------
					cout << "You have successfuly made your payment with " << name << endl;
				}
				else
				{
					cout << "Insufficient Balance, Action Denied" << endl;
				}
				break;
			}
			else if (name == curr->data.getName() && curr->data.getType() == "C")
			{
				double finalAmount = curr->data.getAmount() + amount;
				curr->data.setAmount(finalAmount);
				cout << "You have successfuly made your payment with " << name << endl;
				//				WRITE TRANSACTION TO transactionHistory
				//				-------------------------------------------------------------------------------------------------
				createTransaction("PAY", amount, curr);
				//				-------------------------------------------------------------------------------------------------
				break;
			}
			curr = curr->link;
		}
	}
}

//FUNCTION TO DEPOSIT
//CHECKS WHETHER THERE IS ATLEAST 1 (SAVING HOLDER)
void UI::deposit()
{
	depositHeader();
	NODE<Holder> *saving = holderList.getFirst();
	while (saving != NULL)
	{
		if (saving->data.getType() == "S")
		{
			break;
		}
		saving = saving->link;
	}
	if (saving == NULL)
	{
		cout << "You have got no Saving Holder" << endl;
	}
	//IF THERE IS...
	else
	{
		double amount;
		string name;
		//ENTER AMOUNT
		cout << "Enter Amount\n"
				"INPUT>> ";
		cin >> amount;
		//CHOOSES HOLDER WITH VALIDATION
		showSavingHolders();
		int num = 0;
		do
		{
			if (num != 0)
			{
				cout << "INVALID HOLDER\n";
			}
			cout << "Choose Holder\n"
					"INPUT>> ";
			num += 1;
			cin >> name;
			transform(name.begin(), name.end(), name.begin(), ::toupper);
		} while (!savingHolderExistsValidation(name));

		//CHANGES THE VALUE TO THE NEW ONE
		NODE<Holder> *curr = holderList.getFirst();
		while (curr != NULL)
		{
			if (name == curr->data.getName())
			{
				double finalAmount = curr->data.getAmount() + amount;
				curr->data.setAmount(finalAmount);
				//				WRITE TRANSACTION TO transactionHistory
				//				-------------------------------------------------------------------------------------------------
				createTransaction("DEP", amount, curr);
				//				-------------------------------------------------------------------------------------------------
				cout << "You have successfuly deposited money to " << name << endl;
				break;
			}
			curr = curr->link;
		}
	}
}

//FUNCTION TO TRANSFER
//CHECKS WHETHER THERE ARE ATLEAST 2 (SAVING HOLDERS)
void UI::transferToOtherHolder()
{
	transferHeader();
	NODE<Holder> *saving = holderList.getFirst();
	int flag = 0;
	while (saving != NULL)
	{
		if (saving->data.getType() == "S")
		{
			flag += 1;
			if (flag == 2)
			{
				break;
			}
		}
		saving = saving->link;
	}
	if (saving == NULL)
	{
		cout << "You should have atleast 2 saving holders, Action Denied" << endl;
	}
	//IF THERE ARE...
	else
	{
		// CHECKS WETHER THE SENDER HOLDER EXISTS
		showSavingHolders();
		string sender;
		int num = 0;
		do
		{
			if (num != 0)
			{
				cout << "INVALID HOLDER\n";
			}
			cout << "Choose Sender Holder\n"
					"INPUT>> ";
			num += 1;
			cin >> sender;
			transform(sender.begin(), sender.end(), sender.begin(), ::toupper);
		} while (!savingHolderExistsValidation(sender));

		//CHECKS WETHER THE RECEIVER HOLDER EXISTS
		string receiver;
		int num2 = 0;
		do
		{
			if (num2 != 0)
			{
				cout << "INVALID HOLDER\n";
			}
			cout << "Choose Receiver Holder\n"
					"INPUT>> ";
			num2 += 1;
			cin >> receiver;
			transform(receiver.begin(), receiver.end(), receiver.begin(), ::toupper);
		} while (!savingHolderExistsValidation(receiver));

		//ASKS FOR AMOUNT
		double amount;
		//Enter Amount
		cout << "Enter Amount\n"
				"INPUT>> ";
		cin >> amount;

		//ADDS BALANCE OF THE RECEIVER AND SUBSTRACT BALANCE OF THE SENDER
		NODE<Holder> *curr = holderList.getFirst();
		NODE<Holder> *curr2 = holderList.getFirst();

		while (curr != NULL)
		{
			//CHECKS WETHER THE SENDER BALANCE IS SUFFICIENT TO COMPLETE THE TRANSACTION AND SUBSTRACT THE BALANCE OF THE SENDER
			if (sender == curr->data.getName() && curr->data.getAmount() >= amount)
			{
				double finalAmount = curr->data.getAmount() - amount;
				curr->data.setAmount(finalAmount);
				//			WRITE TRANSACTION TO transactionHistory
				//			-------------------------------------------------------------------------------------------------
				createTransaction("TRF", amount, curr);
				//			-------------------------------------------------------------------------------------------------
				//adds balance of the receiver
				while (curr2 != NULL)
				{
					if (receiver == curr2->data.getName())
					{
						double finalAmount2 = curr2->data.getAmount() + amount;
						curr2->data.setAmount(finalAmount2);
						//			WRITE TRANSACTION TO transactionHistory
						//			-------------------------------------------------------------------------------------------------
						createTransaction("TRF", amount, curr2);
						//			-------------------------------------------------------------------------------------------------
						cout << "Transfer Success" << endl;
						return;
					}
					curr2 = curr2->link;
				}
			}
			else
			{
				curr = curr->link;
			}
		}
		//if the sender's balance insufficient (less than amount)
		if (curr == NULL)
		{
			cout << "Insufficient Balance, Action Denied" << endl;
		}
	}
}

//FUNCTION TO PAY DUE CREDIT
//CHECKS WHETHER ATLEAST 1 CREDIT HOLDER AND 1 SAVING HOLDER
void UI::payDueCredit()
{
	payDueCreditHeader();
	//CHECKS WETHER THERE IS ATLEAST 1 CREDIT HOLDER
	NODE<Holder> *credit = holderList.getFirst();
	while (credit != NULL)
	{
		if (credit->data.getType() == "C")
		{
			break;
		}
		credit = credit->link;
	}

	NODE<Holder> *saving = holderList.getFirst();
	while (saving != NULL)
	{
		if (saving->data.getType() == "S")
		{
			break;
		}
		saving = saving->link;
	}

	if (credit == NULL || saving == NULL)
	{
		cout << "You should have atleast 1 credit and 1 saving holder" << endl;
	}

	//IF THERE ARE...
	else
	{
		//CHECKS WETHER THE RECEIVER HOLDER EXISTS
		showCreditHolders();
		string receiver;
		int num2 = 0;
		do
		{
			if (num2 != 0)
			{
				cout << "INVALID HOLDER\n";
			}
			cout << "Choose Credit Holder to be paid\n"
					"INPUT>> ";
			num2 += 1;
			cin >> receiver;
			transform(receiver.begin(), receiver.end(), receiver.begin(), ::toupper);
		} while (!creditHolderExistsValidation(receiver));

		//CHECKS WETHER THE SOURCE HOLDER EXISTS
		showSavingHolders();
		string sender;
		int num = 0;
		do
		{
			if (num != 0)
			{
				cout << "INVALID HOLDER\n";
			}
			cout << "Choose Source Holder\n"
					"INPUT>> ";
			num += 1;
			cin >> sender;
			transform(sender.begin(), sender.end(), sender.begin(), ::toupper);
		} while (!savingHolderExistsValidation(sender));

		//CHECKS FOR THE DUE CREDIT
		double amount;
		NODE<Holder> *curr0 = holderList.getFirst();
		while (curr0 != NULL)
		{
			if (receiver == curr0->data.getName())
			{
				amount = curr0->data.getAmount();
				cout << "TOTAL DUE CREDIT " << amount << endl;
				break;
			}
			curr0 = curr0->link;
		}
		//IF THERE IS NO DUE CREDIT IN THE CHOSEN HOLDER
		if (amount == 0)
		{
			cout << "INVALID DUE CREDIT" << endl;
		}
		//IF THERE IS...
		else
		{
			//ADDS BALANCEOF THE RECEIVER AND SUBSTRACT BALANCE OF THE SENDER
			NODE<Holder> *curr = holderList.getFirst();
			NODE<Holder> *curr2 = holderList.getFirst();

			while (curr != NULL)
			{
				//CHECKS WETHER THE SENDER BALANCE IS SUFFICIENT TO COMPLETE THE TRANSACTION AND SUBSTRACT THE BALANCE OF THE SENDER
				if (sender == curr->data.getName() && curr->data.getAmount() >= amount)
				{
					double finalAmount = curr->data.getAmount() - amount;
					curr->data.setAmount(finalAmount);
					//			WRITE TRANSACTION TO transactionHistory
					//			-------------------------------------------------------------------------------------------------
					createTransaction("CRE", amount, curr);
					//			-------------------------------------------------------------------------------------------------
					//ADDS BALANCE OF THE RECEIVER
					while (curr2 != NULL)
					{
						if (receiver == curr2->data.getName())
						{
							double finalAmount2 = curr2->data.getAmount() - amount;
							curr2->data.setAmount(finalAmount2);
							cout << "Due Credit Has Been Paid";
							//			WRITE TRANSACTION TO transactionHistory
							//			-------------------------------------------------------------------------------------------------
							createTransaction("CRE", amount, curr2);
							//			-------------------------------------------------------------------------------------------------
							return;
						}
						curr2 = curr2->link;
					}
				}
				else
				{
					curr = curr->link;
				}
			}
			//IF CHOSEN SAVING HOLDER HAS INSUFFICIENT BALANCE
			if (curr == NULL)
			{
				cout << "Insufficient Balance, Action Denied" << endl;
			}
		}
	}
}

//FUNCTION TO DO TRANSACTION
void UI::doTransaction()
{
	doTransactionHeader();
	string doTransaction;
	cout << "1. PAYMENT\n"
			"2. DEPOSIT MONEY\n"
			"3. TRANSFER TO OTHER HOLDER\n"
			"4. PAY DUE CREDIT\n"
			"INPUT>> ";
	cin >> doTransaction;
	if (doTransaction == "1")
	{
		payment();
	}
	if (doTransaction == "2")
	{
		deposit();
	}
	if (doTransaction == "3")
	{
		transferToOtherHolder();
	}
	if (doTransaction == "4")
	{
		payDueCredit();
	}
}

//MAIN PROGRAM RUNS HERE
void UI::run()
{
	//READS TXTs
	readFromHolderTXT();
	readFromTransactionTXT();
	string option;
	//MAIN LOOP
	while (true)
	{
		system("cls");
		menuHeader();
		cout << "1. DO TRANSACTION\n"
				"2. ADD HOLDER\n"
				"3. REMOVE HOLDER\n"
				"4. SHOW ALL HOLDERS & TRANSACTION HISTORY\n"
				"5. EXIT\n"
				"INPUT>> ";

		cin >> option;
		if (option == "1")
		{
			system("cls");
			doTransaction();
		}
		if (option == "2")
		{
			system("cls");
			addHolder();
		}
		if (option == "3")
		{
			system("cls");
			removeHolder();
		}
		if (option == "4")
		{
			system("cls");
			showSavingHolders();
			showCreditHolders();
			showTransactionHistory();
		}
		if (option == "5")
		{
			cout << "\n---Goodbye---";
			break;
		}
		//WRITE TO TXTsS
		writeToHolderTXT();
		writeToTransactionTXT();
		system("pause");
	}
}
#endif
