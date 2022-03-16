#pragma once
#ifndef ACCOUNT_BANK_AGRIM_H
#define ACCOUNT_BANK_AGRIM_H

#include<iostream>//Header files are declared
#include<fstream>
#include<string>
#include<map>
#include<time.h>

#include"Account_Agrim.h"//The base header files are included
#include"StockPortfolio_Agrim.h"
using namespace std;

class Account_Bank : public Account//The base class Account is used for the derived class Account_Bank
{
public:
	//The constructor and destructor are defined
	Account_Bank();
	~Account_Bank();

	//The functions used for banking transactions are declared
	void balance_display();
	void deposit();
	void withdraw();
	void balance_write();

	//A virtual function is used for display of funds
	virtual void statement_funds();

private:
	//The private variables are declared
	double deposit_money;
	double withdraw_money;
	ofstream statement_bank;//The file operators are declared
	ifstream read_history;
};
#endif

