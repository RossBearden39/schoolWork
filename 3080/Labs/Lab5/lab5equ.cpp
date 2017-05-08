/*Author: Ross Bearden
Date: 12/10/14
Class: CSCI 3080
Assignment: Lab 5

Program 1: This portion of lab 5 will use a funtion with a single equation to calculate the following recurrance relation.
S(1) = 2
S(n) = 2*S(n-1) + n*2^n
The value for n will be supplied by the user.
*/

#include <iostream>
#include <cmath>

using namespace std;

//Function to calculate the recurrance relation using the supplied n
//Uses a single equation to calculate the value
long double FindTerm(double n /*In*/);

int main(){
	
	double n = 0;		//Variable to hold the value for n entered by the user
	
	cout << "Enter a value greater than 0 for the n of the recurrance relation" << endl;
	cin >> n;
	if(n == 0){
		cerr << "The value entered for n must be greater than 0" << endl;
		return 1;
	}
	cout << "The " << n << "th term is " << FindTerm(n) << endl;
	
	return 0; 
}


//Body of FindTerm
long double FindTerm(double n /*IN*/){
	
	return pow((double)2,n) *(n*(n+1)/2);

}
