//Author: Samuel Bearden
//Course: CSCI 3250 
//Assignment: P0
//Purpose: Reads a file of numbers asnd displays each number on a seperate line along. Will also tell if the number is divisible
//		by three or five on the same line

#include <iostream>

int main ()
{
	int num;
	
	std::cin >> num;
	while(std::cin){
		std:: cout << num << ' ';
		if(num % 3 == 0)
			std::cout << "three" << ' ';
		if(num % 5 == 0)
			std::cout << "five" << ' ';
		std::cout << std::endl;
		std::cin >> num;
	}
	return 0;
}