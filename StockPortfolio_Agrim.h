#pragma once
#ifndef STOCKPORTFOLIO_AGRIM_H
#define STOCKPORTFOLIO_AGRIM_H

#include<iostream>//The header files are declared
#include<string>
#include "Account_Agrim.h"//The base header files are declared
using namespace std;

class Node_Stock//The class is declared for storing portfolio
{
	friend class Account_Stock;//The friend function is declared so as to share the variables

public:
	Node_Stock(string& s, int n) :symb(s), number_symbols(n)//Initial condition of linked list is defined
	{
		this->next = NULL;
		this->previous = NULL;
	}

private:
	//The pointing variables for Doubly linkedlist are defined
	Node_Stock* next;
	Node_Stock* previous;

	//The variables are declared for storing symbol and number of stocks
	string symb;
	int number_symbols;
};
#endif

