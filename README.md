

➢	In the program, the concept of Inheritance is used between classes. The base account
(Account) is linked with the derived classes (Account_Bank & Account_Stock) through the balancecash variable. In order to implement this method, the balancecash variable is declared as a protected member.
➢	In the first iteration of the program, the cash balance is set to $10000. After each time the program is run, the cash balance is stored in a text file and in the subsequent iterations, that value is called upon instead of the default $10000. Along with that, the stock transaction history and the bank transaction history are also stored inside 2 text files thereby leading to continuity each time the program is run. Deletion of these files, however, will result in the results being reset.
➢	Double linked list is used to store the stock portfolio in which each node contains the symbol name and the number of shares corresponding to it. The list is sorted in real time using bubble sort.
➢	STL Map is used to store the symbol and the price of the share.

DESIGN PATTERN: 

In the project, behavioral design pattern is used, and it is implemented using the virtual functions. The statement_funds function is declared as a virtual function which is used to print according to the call by stock account and bank account. 


FUNCTIONS USED: 

1)	Class Account(Base class):
•	set_cashbalance(): used to set the cash balance in account.
•	get_cashbalance(): used to retrieve the cash balance in the account.
2)	Class Account_Bank(Derived class):
•	balance_display(): used to view account balance.
•	deposit(): used to deposit cash into account.
•	withdraw(): used to withdraw cash from account.
•	balance_write(): used to write cash balance into text file “Cash_Balance.txt”.
•	statement_funds(): prints transaction history of account.
3)	Class Account_Stock(Derived class):
•	stock_display(): displays the stock price based on input symbol.
•	stock_buy(): buy shares depending upon symbol input, available balance and max amount willing to pay per share.
•	stock_sell(): sell shares depending upon symbol in portfolio.
•	update_bought(): update/create a symbol node in portfolio list after buying shares.
•	update_sold(): update/destroy a symbol node in portfolio list after selling shares.
•	portfolio_display(): displays the current portfolio.
•	statement_funds(): prints stock transaction history.
•	portfolio_read(): reads the stock portfolio for transactions.
•	write_portfolio():updates the stock portfolio after transactions.
•	search(): searches for a stock symbol.
•	plot_graph(): plots MATLAB graph.
•	Empty_or_not(): checks if list is empty.
•	balance_write(): writes account balance into file.

TEXT FILES:

•	bank_transaction_history.txt -Keeps in track the transaction history
•	Cash_Balance.txt -The current cash balance is stored in the text file
•	Portfolio_List.txt -Keeps in track the current stocks
•	Portfolio_Value.txt-Displays the total portfolio value along with the transaction date and time
•	stock_transaction_history.txt- Displays every transaction done by the user

