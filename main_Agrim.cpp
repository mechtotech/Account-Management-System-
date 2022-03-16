#include<iostream>//Header files are declared
#include<string>
#include<fstream>
#include<sstream>
#include<utility>
#include "StockPortfolio_Agrim.h"
#include "Account_Agrim.h"
#include "Account_Bank_Agrim.h"
#include "Account_Stock_Agrim.h"
using namespace std;

int main()//Main function is declared
{
	Account_Bank b;//Object for bank account is declared
	Account_Stock s;//Object for stock account is declared
	Node_Stock* node = NULL;//Initial condition is defined

	int option1, option2, option3;//Initially the choice variables are set as 0 to prevent garbage values
	option1 = 0;
	option2 = 0;
	option3 = 0;

	cout << "Welcome to Account Management System. \n";//Welcome message is displayed

	while (option1 != 3)//Main Menu is displayed
	{
		cout << "\n1. Stock Portfolio Account";
		cout << "\n2. Bank Account";
		cout << "\n3. Exit";
		cout << "\nPlease select an account to access: ";
		cin >> option1;
		switch (option1)
		{
		case 1:
			while (option2 != 7)//Stock account options is displayed till it returns to previous menu
			{
				cout << "\nStock Portfolio account";
				cout << "\nPlease select one of the following options: ";
				cout << "\n1. Display the price for a stock symbol";
				cout << "\n2. Display the current portfolio";
				cout << "\n3. Buy shares";
				cout << "\n4. Sell shares";
				cout << "\n5. View a graph for the portfolio value";
				cout << "\n6. View transaction history";
				cout << "\n7. Return to previous menu";
				cout << "\nYour Choice: ";
				cin >> option2;
				switch (option2)
				{
				case 1:
					s.stock_display();//Function to display stocks
					break;
				case 2:
					s.portfolio_display();//Function to display portfolio
					break;
				case 3:
					s.stock_buy();//Function to buy shares
					break;
				case 4:
					s.stock_sell();//Function to sell shares
					break;
				case 5:
					cout << "Display graph here\n";
					//s.plot_graph();//Function to plot graph
					break;
				case 6:
					s.statement_funds();//Function to print history
					break;
				case 7:
					break;//To return to previous menu
				default:
					cout << "\nPlease enter a valid option.";
				}
			}
			option2 = 0;
			break;
		case 2:
			while (option3 != 5)//Bank account options are displayed until it returns to previous menu
			{
				cout << "\nBank Account";
				cout << "\nPlease select an option:";
				cout << "\n1. View account balance";
				cout << "\n2. Deposit money";
				cout << "\n3. Withdraw money";
				cout << "\n4. Print out history";
				cout << "\n5. Return to Previous Menu";
				cout << "\nYour Choice: ";
				cin >> option3;
				switch (option3)
				{
				case 1:
					b.balance_display();//Function to view balance
					break;
				case 2:
					b.deposit(); //Function to deposit money into account
					s.portfolioval_write();
					break;
				case 3:
					b.withdraw(); //Function to withdraw money from account
					s.portfolioval_write();
					break;
				case 4:
					b.statement_funds();//Function to print transaction history
					break;
				case 5:
					break;//To return to previous menu
				default:
					cout << "\nPlease enter a valid option";
				}
			}
			option3 = 0;
			break;

		case 3:
			s.write_portfolio();
			break;//To exit program
		default:
			cout << "\nPlease enter a valid option";
		}
	}
	return 0;//Successful termination of the program
}