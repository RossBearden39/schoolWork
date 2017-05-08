#include <iostream>
using std::cout;
using std::endl;

int recursiveFunctionB(int a, int b){
    if (a < b) {
        return 0;
    }else{
        return 1 + recursiveFunctionB( a - b, b);
    }
}


// Put gcd() here
int gcd( int c, int d){
	//BASE CASES!!
	//This case returns c, which will be the GCD, if it is zero
	if(d == 0)
		return c;
	else
		return(gcd(d, c%d));
}


                                                   
int main(){                                        
    /* 1. Mystery Method */
    cout << "Mystery Method:\n";
    int num1, num2, result;                        
    num1 = 7;  num2 = 2;                           
    result = recursiveFunctionB( num1,  num2);
    /* 1.a.1 Show the recursive method calls that are generated HERE
		recursiveFunctionB(7,2) = 1 + recursiveFunctionB(5, 2);
							      1 + 1 + recursiveFunctionB(3, 2);
								  1 + 1 + 1 + recursiveFunctionB(1, 2);
								  1 + 1 + 1 + 0 = 3
    */

    num1 = 29;  num2 = 5;
    result = recursiveFunctionB( num1,  num2);
    /* 1.a.2 Show the recursive method calls that are generated HERE
		recursiveFunctionB(29,5) = 1 + recursiveFunctionB(24, 5);
								   1 + 1 + recursiveFunctionB(19, 5);
								   1 + 1 + 1 + recursiveFunctionB(14, 5);
								   1 + 1 + 1 + 1 + recursiveFunctionB(9, 5);
							   	   1 + 1 + 1 + 1 + 1 + recursiveFunctionB(4, 5);
								   1 + 1 + 1 + 1 + 1 + 0 = 5;
    */
    
    num1 = 5;  num2 = 7;
    result = recursiveFunctionB( num1,  num2);
    /* 1.a.3 Show the recursive method calls that are generated HERE
		recursiveFunctionB(5, 7) = 0
       
    */

    /* 1.b In just a few words, state what the method is computing assuming a > 0 and b > 0 for the initial call.
      The function is doing integer division
    */

    
    /* 2. Euclid's Algorithm */
    cout << "\nEuclid's Algorithm:\n";
    num1 = 36;
    num2 = 20;
    result = gcd( num1, num2);
    cout << "Greatest common denominator of " << num1 << " and " << num2 << " is " << result << endl;
    
    /* 3. Make Change (OPTIONAL) */
    // cout << "\nMake Change:\n";
    // int initialAmount = 10;
    // int coinValues[] = {1, 5, 10, 25, 50, 100};
    // int numCoins = 5;
    // result = makeChange( initialAmount, coinValues, numCoins /*...*/);
    // cout << "There are " << result << " ways to make change for " << initialAmount << " with " << numCoins << " US coins\n";
    // 
    // initialAmount = 100;
    // result = makeChange( initialAmount, coinValues, numCoins /*...*/);
    // cout << "There are " << result << " ways to make change for " << initialAmount << " with " << numCoins << " US coins\n";

    return 0;
}
