#include <iostream>
#ifndef HOLDER_H
#define HOLDER_H
using namespace std;

class Holder{
	public:
		Holder();
		Holder(string type, string name, double amount);
		void setAmount(double amount);

		string getType();
		string getName();
		double getAmount();
		
	private:	
		string type;
		string name;
		double amount;

};
Holder::Holder(){
}
Holder::Holder(string type,string name,double amount){
	this->type = type;
	this->name = name;
	this->amount = amount;
}

void Holder::setAmount(double amount){
	this->amount = amount;
}

double Holder::getAmount(){
	return amount;
}

string Holder::getName(){
	return name;
}
string Holder::getType(){
	return type;
}

#endif
