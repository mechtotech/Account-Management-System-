#pragma once
#ifndef ACCOUNT_AGRIM_H
#define ACCOUNT_AGRIM_H
//The base class is created
class Account
{
public:
	//The functions for getting and setting the cash balances are declared
	double get_cashbalance();
	void set_cashbalance();

	//A virtual function for printing transaction history is declared
	virtual void statement_funds();

protected:
	//Protected member for storing cash balance is declared
	double balancecash;
};
#endif


