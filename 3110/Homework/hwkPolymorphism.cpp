/* Four essential ingredients for having a polymorphic method call:
 * 1) Must have inheritance
 * 2) Methods in the base class must be virtual
 * 3) The virtual methods should be overriden in the derived class if they will be used
 * 4) A pointer or reference to the base class needs to be pointing to or referencing a derived class 
*/

#include <iostream>
using std::cout;
using std::endl;

// Add class declarations and implementations HERE
//Abstract Base Class
class Account{

public:
	//Defualt Constructor
	Account() : balance(0) {}
	//Constructor with parameters
	Account(double bal) : balance(bal) {}
	//Virtual Default Destructor
	virtual ~Account() {}
	//Virtual Deposit method
	virtual void deposit(double num){balance += num;}
	//Virtual Withdraw Method
	virtual void withdraw(double num){balance -= num;}
	//Virtual Print method
	virtual void printInfo(){
		cout << "Balance: " << balance << endl;
	}

protected:
	double balance;
};

//Savings Account class derived from account (Inheritance)
class SavingsAccount : public Account{
public:
	//Constructor for Savings Account 
	SavingsAccount(double bal, const double interest) : Account(bal), interestRate(interest) {}
	//Deposit method overrides base deposit method
	void deposit(double num){balance += num;}
	//Withdraw Method overrides base withdraw method
	void withdraw(double num){balance -= num;}
	//Print mthod overrides base print method
	void printInfo(){
		cout << "Savings Account Information:" << endl;
		cout << "\tBalance: $" << balance << endl;
		cout << "\tInterest rate: " << interestRate << "%" << endl;
	}
	private:
	//Holds the intertest rate for the savings account
	const double interestRate;
};

//Checking Account class derived from account (Inheritance)
class CheckingAccount : public Account{
public:
	//Constructor for Checking Account
	CheckingAccount(double currentBal) : Account(currentBal), checkNum(0) {}
	//Deposit Method overrides base deposit method
	void deposit(double num){balance += num;}
	//Method to process checks for payments
	void processCheck(double payment, int check){
		balance -= payment;
		checkNum = check;
	}
	//Print method overrides base print method
	void printInfo(){
	cout << "Checking Account Information:" << endl;
	cout << "\tBalance: $" << balance << endl;
	cout << "\tLast check number processed: " << checkNum << endl;
	}

private:
	//Holds the last check number processed
	int checkNum;

};

//CDAcount class derived from account (Inheritance)
class CDAccount : public Account{
public:
	//Constructor for CDAccount
	CDAccount(double amount, const double interest, int length) : Account(amount), interestRate(interest), maturity(length) {}
	////Print method overrides base print method
	void printInfo(){
	cout << "CD Account Information:" << endl;
	cout << "\tBalance: $" << balance << endl;
	cout << "\tInterest rate: " << interestRate << "%" << endl;
	cout << "\tMaturity: " << maturity << " months" << endl;
	}
private:
	//Holds CD interest rate
	const double interestRate;
	//Holds length of CD
	int maturity;
};

//Constant Global Variables
const double SAVINGS_INTEREST_RATE = 1.2;
const double CD_INTEREST_RATE = 2.5;
const int NUM_BANK_ACCOUNTS = 3;
int main(){
    SavingsAccount firstHome( 1234.56, SAVINGS_INTEREST_RATE);
    CheckingAccount gasMoney( 78.90);
    CDAccount tuition( 5000.00, CD_INTEREST_RATE, 6);
    Account* bankAccounts[ NUM_BANK_ACCOUNTS ]; // array of 3 Account pointers

    firstHome.deposit( 987.65);
    gasMoney.deposit( 12.34);

    firstHome.withdraw( 2000.00);
    int checkNumber = 234;
    gasMoney.processCheck( 55.55, checkNumber);
    //Polymorphic Calls
    bankAccounts[0] = &firstHome;
    bankAccounts[1] = &gasMoney;
    bankAccounts[2] = &tuition;

    bankAccounts[1]->deposit( 20.00);
    bankAccounts[1]->withdraw( 50.00);

    for( int i = 0; i < NUM_BANK_ACCOUNTS; i++){
        cout << "(Bank account index " << i << ")\n";
        bankAccounts[i]->printInfo();
        cout << endl;
    }
    return 0;
}
    
