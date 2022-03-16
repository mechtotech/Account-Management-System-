#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<string>
#include"Account_Agrim.h"
using namespace std;

void Account::set_cashbalance()//Function for setting the cash balance
{
	int indicator = 0;//Indicator to check status of file
	ifstream file1;
	ofstream file2;

	file1.open("Cash_Balance.txt", ios_base::in);//Opens the Cash_Balance.txt file 

	if (file1.is_open())//Checks if any previous cash balance entry is present
	{
		while (!(file1.eof()))//Function to increment indicator value if previous entry is present
		{
			indicator++;
			break;
		}
	}

	file1.close();//File is closed

	if (indicator == 0)//If the indicator is 0, the balance is reset to $10000
	{
		double init_balance = 10000.00;

		file2.open("Cash_Balance.txt", ios_base::out);
		file2 << init_balance;//Write Initial Balance as $10000
		file2.close();

		ifstream readbal("Cash_Balance.txt", ios_base::in);//Read the balance from the file
		readbal >> balancecash;
		readbal.close();
	}
	else//If previous balance is present, use that balance for this instance of program
	{
		ifstream readbal("Cash_Balance.txt", ios_base::in);//Read the existing balance from the file
		readbal >> balancecash;
		readbal.close();
	}
}

double Account::get_cashbalance()//Function for getting cash balance
{
	return balancecash;//Returns the current cash balance
}

void Account::statement_funds()//Function for displaying the bank statement
{
	string line;
	ifstream statement_read;
	statement_read.open("bank_transaction_history.txt", ios::app);//Open the file
	cout << left << setw(25) << " Event ";
	cout << left << setw(20) << "Amount $";
	cout << left << setw(30) << "Date & Time";
	cout << left << setw(15) << "Balance $" << endl;

	while (!statement_read.eof())//Runs till the last line is reached
	{
		getline(statement_read, line);
		cout << line << endl;
	}
}