#pragma once
#ifndef ACCOUNT_STOCK_AGRIM_H
#define ACCOUNT_STOCK_AGRIM_H

#include<iostream>//Header files are declared
#include<string>
#include<fstream>
#include<map>

#include"Account_Agrim.h"//The base header files are used
#include"StockPortfolio_Agrim.h"

using namespace std;

using namespace std;

//A STL map is used to hash symbol and its price 
typedef map<string, double>sym;

class Account_Stock :public Account//The derived class Account_Stock is defined from base class Account
{
public:
	//The constructor and destructor are defined
	Account_Stock();
	~Account_Stock();

	//The functions for stock operations are defined
	void stock_display();
	void stock_buy();
	void stock_sell();
	void update_bought(string, int);
	void update_sold(Node_Stock*, int);

	//The functions for portfolio are declared
	void portfolio_display();
	void portfolio_read();
	void write_portfolio();
	void portfolioval_read();
	void portfolioval_write();
	void balance_write();

	//The other necessary functions are declared
	sym file_select(sym, sym);
	Node_Stock* search(string);
	void portfolio_sort();
	virtual void statement_funds();
	bool Empty_or_not() const;
	void plot_graph();

private:
	//The private variables are declared
	Node_Stock* head;
	Node_Stock* tail;
	string stock_symbol;
	sym stock_day1, stock_day2;
	stringstream s1, s2;
	string line1, line2;
	double port_array[100];
	string time_array[100];
	int tempnum1, tempnum2;
	double stock_price;
	int stock_number;
	double maximum_amount, minimum_amount, total_amount;
	int size;
	double price;
	ofstream statement_stock, statement_bank;
	ifstream read1, read2;
	string symbol1;
	double price1;
};
#endif
