#include<iostream>//Header Files are declared
#include<iomanip>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<sstream>
#include<map>
#include<time.h>
#include"StockPortfolio_Agrim.h"
#include"Account_Agrim.h"
#include"Account_Stock_Agrim.h"

//MATLAB Commands
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#pragma comment( lib, "libmx.lib" )//Matlab libraries are included
#pragma comment( lib, "libmex.lib" )    
#pragma comment( lib, "libeng.lib" )
#include "mex.h"//Matlab header file for calling MATLAB is included
#include<engine.h>
#include <yvals.h>													// Including libraries of MATLAB
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
#include <engine.h>


#pragma comment(lib, "libmx.lib")									// Loading libraries of MATLAB
#pragma comment(lib, "libmex.lib")
#pragma comment(lib, "libeng.lib")

using namespace std;

Account_Stock::Account_Stock()//Constructor is defined
{
	tempnum1 = 0;
	tempnum2 = 0;
	size = 0;
	set_cashbalance();
	balancecash = get_cashbalance();

	read1.open("Result_1.txt");//The stock data files are opened
	read2.open("Result_2.txt");

	//The data is retrieved and stored into a STL Map
	if (read1.is_open() && read2.is_open())
	{
		while (!read1.eof() && !read2.eof())
		{
			getline(read1, line1);
			s1 << line1;
			s1 >> symbol1 >> price1;
			stock_day1.insert(pair<string, double>(symbol1, price1));
			s1.str(" ");
			s1.clear();

			getline(read2, line1);
			s1 << line1;
			s1 >> symbol1 >> price1;
			stock_day2.insert(pair<string, double>(symbol1, price1));
			s1.str(" ");
			s1.clear();
		}
	}

	read1.close();//The files are closed
	read2.close();

	//The existing portfolio is retrieved
	this->portfolio_read();
	this->portfolioval_read();
}

Account_Stock::~Account_Stock()//The destructor is defined
{
	//Empty Destructor
}

//The function randomly selects a stock file
sym Account_Stock::file_select(sym file1, sym file2)
{
	srand(time(NULL));//Current time as seed for random number generator
	int randno;//Random Number is defined
	randno = rand() % 2;//Random number for the 2 different stock files

	if (randno == 1)//Return either of the two file choices based on random number
	{
		return file1;
	}
	else
	{
		return file2;
	}
}

bool Account_Stock::Empty_or_not() const//Function to check if the list is empty or not
{
	return(head == 0 && tail == 0);

}

void Account_Stock::portfolio_sort()//Function to sort the Linked list using bubble sort
{
	double x, y;
	x = 0;
	y = 0;
	if (head != NULL)
	{
		int indicator = 0;
		Node_Stock* current = head;
		Node_Stock* prev = 0;
		Node_Stock* temp = NULL;
		sym temp_sym;

		for (int i = 0; i < size; i++)
		{
			while (current->next != 0)
			{
				temp_sym = file_select(stock_day1, stock_day2);
				temp = current->next;

				sym::iterator it1;

				for (it1 = temp_sym.begin(); it1 != temp_sym.end(); it1++)
				{
					if (current->symb == it1->first)
					{
						x = it1->second;
					}
					if (temp->symb == it1->first)
					{
						y = it1->second;
					}
				}

				//comparing stock value
				if ((current->number_symbols) * x < (temp->number_symbols) * y)
				{
					temp->previous = current->previous;
					current->previous = temp;
					current->next = temp->next;

					indicator = 1;

					if (current->next != NULL)
					{
						current->next->previous = current;
					}
					temp->next = current;

					if (prev != 0)
					{
						prev->next = temp;
					}
					prev = temp;

					if (head == current)
					{
						head = temp;
					}
					if (current->next == 0)
					{
						tail = current;
					}
				}
				else
				{
					prev = current;
					current = current->next;
				}
			}

			if (indicator == 0)
			{
				break;
			}
			else
			{
				prev = NULL;
				current = head;
				indicator = 0;
			}
		}

	}
}

Node_Stock* Account_Stock::search(string a)//Function to search whether stock is present or not
{
	Node_Stock* current = head;

	while (current != NULL)
	{
		if (current->symb == a)
		{
			return current;//Return if found
		}

		current = current->next;
	}

	return NULL;//Returns a null value if it is not found
}

void Account_Stock::stock_display()//Function to display stock price of a symbol
{
	int indicator = 0;
	cout << "\n Enter Stock Symbol to be Displayed : ";
	cin >> stock_symbol;

	sym copy;
	sym::iterator it1;
	copy = file_select(stock_day1, stock_day2);//Randomly select a stock file
	for (it1 = copy.begin(); it1 != copy.end(); it1++)
	{
		if (stock_symbol == it1->first)
		{
			cout << "\nSymbol";
			cout << setw(20) << " Price/Share($)" << endl;
			cout << it1->first << setw(20) << it1->second << endl;
			indicator = 1;
		}
	}
	if (indicator == 0)
	{
		cout << "\nPlease enter a valid symbol\n";
	}
}

void Account_Stock::update_bought(string a, int n)//Function to update list after buying stock
{
	Node_Stock* temp;
	temp = new Node_Stock(a, n);

	Node_Stock* found = search(a);//Checks if symbol is present or not

	if (found == NULL)//Execute if symbol is not found
	{
		if (tail == NULL && head == NULL)//Execute if list is empty
		{
			temp->previous = NULL;
			temp->next = NULL;
			head = temp;
			tail = temp;
		}
		else//Adds to the end of list
		{
			Node_Stock* cpy = tail;
			tail->next = temp;
			tail = temp;
			tail->previous = cpy;
		}
		size++;
	}
	else//Increase the number of stock depending on the quantity bought
	{
		found->number_symbols = temp->number_symbols + found->number_symbols;
	}
	portfolio_sort();//Sort the linked list
}

void Account_Stock::update_sold(Node_Stock* f, int n)//Updates the list after stock is sold
{
	f->number_symbols = f->number_symbols - n;//The number of shares are subtracted from the total
	if (f->number_symbols == 0)//Deletes the node if the shares are now 0
	{
		if (f == head)
		{
			if (f == tail)//Checks if it is the only node in the list
			{
				head = NULL;
				tail = NULL;
				delete f;
				size--;
				return;
			}
			Node_Stock* temp1 = f->next;
			head = f->next;
			temp1->previous = NULL;
			delete f;
			size--;
			return;
		}
		else if (f == tail)
		{
			if (f == head)		//Checks if its the only node in the list
			{
				head = NULL;
				tail = NULL;
				delete f;
				size--;
				return;
			}
			Node_Stock* temp2 = f->previous;
			tail = f->previous;
			temp2->next = NULL;
			delete f;
			size--;
			return;
		}
		else//Deletes the node and rearranges the pointers
		{
			Node_Stock* temp3 = f->previous;
			Node_Stock* temp4 = f->next;
			temp3->next = f->next;
			temp4->previous = f->previous;
			delete f;
			size--;
			return;
		}
	}
}

void Account_Stock::stock_buy()//Function for buying shares
{
	int indicator = 0;
	sym copy;

	cout << "\nEnter the Stock Symbol you want to buy : ";
	cin >> stock_symbol;

	copy = file_select(stock_day1, stock_day2);
	for (sym::iterator it1 = copy.begin(); it1 != copy.end(); it1++)
	{
		if (stock_symbol == it1->first)
		{
			indicator = 1;
			stock_price = it1->second;
		}
	}
	if (indicator == 0)//Error message if symbol is not present
	{
		cout << "\nPlease enter a valid symbol\n";
		return;
	}
	cout << "\nEnter the number of Stocks you want to buy : ";
	cin >> stock_number;
	cout << "Please enter the Maximum Amount you are willing to pay per stock : ";
	cin >> maximum_amount;

	if (maximum_amount > stock_price)//Checks if the stock price is less than the maximum amount willing to pay
	{
		total_amount = stock_number * stock_price;
	}
	else
	{
		cout << "\nTransaction Incomplete! Enter a higher bid for the stock\n";
		return;
	}

	set_cashbalance();//Gets the cash balance
	balancecash = get_cashbalance();
	if (total_amount <= balancecash)//Checks if sufficient cash is available or not
	{
		balancecash = balancecash - total_amount;
		balance_write();
		cout << "\nTransaction Complete! You have purchased " << stock_number << " shares of " << stock_symbol << " for amount $" << total_amount << endl;

		time_t rawtime;//Gets the date and time
		struct tm timeinfo;
		char buffer[80];
		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);
		strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
		string str(buffer);

		statement_stock.open("stock_transaction_history.txt", ios::app);//Writes the transaction in the stock file
		statement_stock << left << setw(10) << "Buy";
		statement_stock << left << setw(15) << stock_symbol;
		statement_stock << left << setw(15) << stock_number;
		statement_stock << left << setw(20) << stock_price;
		statement_stock << left << setw(20) << total_amount;
		statement_stock << left << setw(25) << str << endl;
		statement_stock.close();

		statement_bank.open("bank_transaction_history.txt", ios::app);//Writes the transaction in the bank file as well
		statement_bank << left << setw(25) << "Withdraw(Stock)";
		statement_bank << left << setw(20) << total_amount;
		statement_bank << left << setw(30) << str;
		statement_bank << left << setw(10) << balancecash << endl;
		statement_bank.close();
	}
	else//Display an error message if sufficient funds are not present
	{
		cout << "Invalid Transaction! Make sure you have sufficient balance in your account\n";
		return;
	}

	update_bought(stock_symbol, stock_number);//Update the linked list
	portfolio_sort();//Sort the list
	portfolioval_write();
}

void Account_Stock::stock_sell()//Function for selling the shares
{
	int indicator = 0;
	Node_Stock* temp = NULL;

	cout << "\nEnter Stock Symbol to sell:\n";
	cin >> stock_symbol;
	temp = search(stock_symbol);

	if (temp != NULL)
	{
		indicator = 1;
	}

	if (indicator == 0)
	{
		cout << "\nPlease enter a valid symbol\n";
		return;
	}

	cout << "\nEnter the number of shares you want to sell : ";
	cin >> stock_number;

	if (stock_number > temp->number_symbols)
	{
		cout << "Please enter a valid number\n";
		return;
	}

	cout << "\nEnter minimum amount which you want after selling the share : ";
	cin >> minimum_amount;

	sym sym_temp;
	sym_temp = file_select(stock_day1, stock_day2);
	sym::iterator it1;
	for (it1 = sym_temp.begin(); it1 != sym_temp.end(); it1++)
	{
		if (stock_symbol == it1->first)
		{
			stock_price = it1->second;
		}
	}

	if (stock_price < minimum_amount)
	{
		cout << "\nTransaction Incomplete! Please enter a lower bid\n";
		return;
	}

	set_cashbalance();//Get the cash balance
	balancecash = get_cashbalance();
	total_amount = stock_number * stock_price;
	balancecash = balancecash + total_amount;
	balance_write();
	cout << "\nTransaction Complete! You have sold " << stock_number << " shares of " << stock_symbol << " for amount $" << total_amount << endl;

	time_t rawtime;//gets the time and date
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
	string str(buffer);

	statement_stock.open("stock_transaction_history.txt", ios::app);//Writes the transaction in the stock file
	statement_stock << left << setw(10) << "Sell";
	statement_stock << left << setw(15) << stock_symbol;
	statement_stock << left << setw(15) << stock_number;
	statement_stock << left << setw(20) << stock_price;
	statement_stock << left << setw(20) << total_amount;
	statement_stock << left << setw(25) << str << endl;
	statement_stock.close();

	statement_bank.open("bank_transaction_history.txt", ios::app);//Writes the tranasaction in the bank file as well
	statement_bank << left << setw(25) << "Deposit(Stock)";
	statement_bank << left << setw(20) << total_amount;
	statement_bank << left << setw(30) << str;
	statement_bank << left << setw(10) << balancecash << endl;
	statement_bank.close();

	update_sold(temp, stock_number);//Updates the linked list
	portfolio_sort();//Sorts the list
	portfolioval_write();
}

void Account_Stock::portfolio_display()//Function for displaying the portfolio
{
	set_cashbalance();
	balancecash = get_cashbalance();
	portfolio_sort();

	Node_Stock* current = head;
	sym copy;

	double pr, val, port_val;
	double stock_val = 0;

	copy = file_select(stock_day1, stock_day2);

	if (size > 0)
	{
		cout << endl << left << setw(20) << "Company Symbol";
		cout << left << setw(20) << "Number";
		cout << left << setw(20) << "Price/Share($)";
		cout << left << setw(20) << "Total Value($)" << endl;
	}
	while (current != NULL)
	{
		for (sym::iterator it1 = copy.begin(); it1 != copy.end(); it1++)
		{
			if (current->symb == it1->first)
			{
				pr = it1->second;
				val = current->number_symbols * pr;

				cout << left << setw(20) << current->symb;
				cout << left << setw(20) << current->number_symbols;
				cout << left << setw(20) << pr;
				cout << left << setw(20) << val << endl;
				stock_val = stock_val + val;
			}
		}
		current = current->next;
	}

	if (size > 0)
	{
		cout << "\n Cash : $" << balancecash;
		cout << "\n Stock : $" << stock_val;
		port_val = balancecash + stock_val;
		cout << "\n Total Portfolio value : $" << port_val << endl;
	}
	else if (size == 0)
	{
		port_val = balancecash;
		cout << "\n Total portfolio value : $" << port_val << endl;
		cout << "\n You don't have any shares as of now\n";
	}
}

void Account_Stock::statement_funds()//Function for printing the stock transaction history
{
	ifstream myfile;
	myfile.open("stock_transaction_history.txt", ios::app);
	cout << left << setw(10) << "Event";
	cout << left << setw(15) << "Company Symbol";
	cout << left << setw(15) << "Number";
	cout << left << setw(20) << "Price/Share";
	cout << left << setw(20) << "Total Value";
	cout << left << setw(25) << "Date & Time" << endl;
	while (!myfile.eof())
	{
		getline(myfile, line1);
		cout << line1 << endl;
	}
}

void Account_Stock::write_portfolio()//Function to write portfolio
{
	portfolio_sort();//Sort the list
	Node_Stock* temp = head;
	ofstream myfile;
	myfile.open("Portfolio_List.txt", ios_base::out);
	while (temp != NULL)
	{
		myfile << temp->symb << "\t" << temp->number_symbols << endl;
		temp = temp->next;
	}
	myfile.close();
}

void Account_Stock::portfolio_read()//Function to read portfolio
{
	string a;
	int indicator = 0;
	int z;
	sym temp;
	string temp_symb;
	int temp_share;
	ifstream myfile;
	myfile.open("Portfolio_List.txt", ios_base::in);
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			getline(myfile, line1);
			s1 << line1;
			s1 >> temp_symb >> temp_share;
			temp.insert(pair<string, int>(temp_symb, temp_share));
			s1.clear();
			indicator = 1;
		}
	}
	myfile.close();
	if (indicator == 1)
	{
		for (sym::iterator it1 = temp.begin(); it1 != temp.end(); it1++)
		{
			a = it1->first;
			z = it1->second;
			update_bought(a, z);
		}
	}
}

void Account_Stock::balance_write()//Function to write cash balance
{
	ofstream myfile;
	myfile.open("Cash_Balance.txt", ios_base::out);
	myfile << endl << balancecash;
	myfile.close();
}

void Account_Stock::portfolioval_write()//Function to write portfolio value
{
	Node_Stock* ptr = head;
	double cost, total, port_val;
	cost = 0;
	total = 0;
	port_val = 0;
	sym copy;
	sym::iterator it1;
	ofstream write;
	copy = file_select(stock_day1, stock_day2);
	while (ptr != NULL)
	{
		for (it1 = copy.begin(); it1 != copy.end(); it1++)
		{
			if (ptr->symb == it1->first)
			{
				cost = it1->second;
				total = total + ptr->number_symbols * cost;
			}
		}
		ptr = ptr->next;
	}
	set_cashbalance();
	balancecash = get_cashbalance();
	port_val = total + balancecash;
	if (tempnum1 < 100)
	{
		port_array[tempnum1] = port_val;//Stores portfolio value in array for graph
	}

	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
	std::string str(buffer);
	if (tempnum2 < 100)
	{
		time_array[tempnum2] = str;//Stores time in time array
	}
	if (size == 0)
	{
		port_val = balancecash;
	}
	write.open("Portfolio_Value.txt", ios::app);
	write << port_val << "  " << str << endl;
	write.close();
	tempnum1++;
	tempnum2++;
}

void Account_Stock::portfolioval_read()//Function to read portfolio value
{
	string por_read;
	read1.open("Portfolio_List.txt", ios_base::in);
	while (!read1.eof())
	{
		getline(read1, line1);
		s1 << line1;
		s1 >> port_array[tempnum1] >> time_array[tempnum2] >> por_read;
		if (time_array[tempnum2] == "")
		{
			continue;
		}
		else
		{
			time_array[tempnum1].append(" ");
			time_array[tempnum1].append(por_read);
		}
		tempnum1++;
		tempnum2++;
		s1.clear();
	}
	read1.close();
}

void Account_Stock::plot_graph()//Function to plot graph using MATLAB
{

	cout << "Portfolio Value" << "\t\t" << "Date & Time" << endl;
	for (int i = 0; i < tempnum1; i++)
	{
		cout << "$" << port_array[i] << "\t\t" << time_array[i] << endl;
	}

	Engine* ep;
	ep = engOpen(NULL);
	if (ep == NULL)
	{
		cout << "Error: Not Found." << endl;
		exit(1);
	}
	
	mxArray* A;//Create mxArray and copy arrays into it
	A = mxCreateDoubleMatrix(1, tempnum1, mxREAL);
	memcpy((void*)mxGetPr(A), (void*)port_array, tempnum1 * sizeof(double));
	engPutVariable(ep, "yy", A);
	engEvalString(ep, "plot(yy);");//Plotting function
	engEvalString(ep, "title('Portfolio Variation Graph');");//Title for graph
	mxDestroyArray(A); //Destroy mxArray
	
	}
	