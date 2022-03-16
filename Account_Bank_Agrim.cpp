#include<iostream>//The header files are declared
#include<cstdlib>
#include<string>
#include<time.h>
#include<fstream>
#include<sstream>
#include<map>
#include<iomanip>
#include"Account_Agrim.h"
#include"Account_Bank_Agrim.h"
using namespace std;

//The constructor is defined
Account_Bank::Account_Bank()
{
	set_cashbalance();
	balancecash = get_cashbalance();
	deposit_money = 0;
	withdraw_money = 0;

}

//The destructor is defined
Account_Bank::~Account_Bank()
{

}

//This function is used for displaying account balance
void Account_Bank::balance_display()
{
	set_cashbalance();
	balancecash = get_cashbalance();
	cout << "\n You have $" << balancecash << " in your bank account\n";
}

//This function is used for storing account balance in the file
void Account_Bank::balance_write()
{
	ofstream myfile;

	myfile.open("Cash_Balance.txt", ios_base::out);
	myfile << endl << balancecash;
	myfile.close();

}

//This function is used for depositing money
void Account_Bank::deposit()
{
	cout << "\nPlease select the Amount to be deposited : ";
	cin >> deposit_money;

	//Checks whether the amount is valid
	while (deposit_money < 0)
	{
		cout << "\nPlease Enter a valid deposit greater than $0\n";
		cin >> deposit_money;
	}
	//Updates the balance in the account
	set_cashbalance();
	balancecash = get_cashbalance();
	balancecash = balancecash + deposit_money;
	balance_write();
	cout << "\n Amount $" << deposit_money << " was deposited to your Account\n";

	//It gets the current time and date
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
	string str(buffer);

	//It stores the deposit update in the transaction history
	statement_bank.open("bank_transaction_history.txt", ios::app);
	statement_bank << left << setw(25) << "Deposit";
	statement_bank << left << setw(20) << deposit_money;
	statement_bank << left << setw(30) << str;
	statement_bank << left << setw(10) << balancecash << endl;
	statement_bank.close();
}

//This function is used to withdraw money from the bank account
void Account_Bank::withdraw()
{
	cout << "\nPlease enter the amount to withdraw : ";
	cin >> withdraw_money;

	set_cashbalance();
	balancecash = get_cashbalance();

	if (balancecash > 0)//Checks whether cash is present or not
	{
		if (withdraw_money <= balancecash)
		{
			//Updates the cash balance
			balancecash = balancecash - withdraw_money;
			balance_write();

			//It gets the current time and date
			time_t rawtime;
			struct tm timeinfo;
			char buffer[80];
			time(&rawtime);
			localtime_s(&timeinfo, &rawtime);
			strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
			string str(buffer);

			//It stores the deposit update in the transaction history
			statement_bank.open("bank_transaction_history.txt", ios::app);
			statement_bank << left << setw(25) << "Withdraw";
			statement_bank << left << setw(20) << withdraw_money;
			statement_bank << left << setw(30) << str;
			statement_bank << left << setw(15) << balancecash << endl;
			statement_bank.close();
		}
		else//Error message if sufficient money is not present
		{
			cout << "\nYou have insufficient funds in your account \n";
		}
	}
	else
	{
		cout << "\nAccount Balance is $0\n";
	}
}

//Function for printing the bank statement
void Account_Bank::statement_funds()
{
	ifstream statement_read;
	string line;
	statement_read.open("bank_transaction_history.txt", ios_base::in);
	cout << left << setw(25) << "Event ";
	cout << left << setw(20) << "Amount($)";
	cout << left << setw(30) << "Date & Time";
	cout << left << setw(15) << "Balance($)" << endl;

	while (!statement_read.eof())
	{
		getline(statement_read, line);
		cout << line << endl;
	}
}