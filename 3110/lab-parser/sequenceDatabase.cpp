//Author: Ross Bearden
//Class: CSCI: 3110
//File: sequenceDatabase.cpp
//Purpose: This is the implementation file for a class called sequenceDatabase

#include "sequenceDatabase.h"
#include <iostream>
#include <fstream>
#include <string>
//Default Constructor
sequenceDatabase::sequenceDatabase() : check(0) {}

//Import entries function definition
void sequenceDatabase::importEntries(string commandsFilename){
	std::ifstream myIn;			//file stream in variable
	myIn.open(commandsFilename);	//Opening file
	if(myIn.is_open()){			// checking to see if the file opened
		double idNum = 0;		//Value to hold the id number that is read
		char letter;				//Value to hold command character
		myIn >> letter;		//grabbing the first command character
		
		//While loop processes the command letter to determine appropriate action
		while(myIn){
			if(letter == 'D'){
				double id = makeDNA(myIn);			//This function call the DNA constructor and returns the DNA id
				std::cout << "Adding " << id << " ..." << std::endl << std::endl;
				
			}
			else if (letter == 'P'){
				myIn >> idNum;			//Gets the id for printing
				std::cout << "Printing " << idNum << " ..." << std::endl << std::endl;
			}
			else if (letter == 'O'){
				myIn >> idNum;			//Gets the id for obliterating
				std::cout << "Obliterating " << idNum << " ..." << std::endl << std::endl;
			}
			else if(letter == 'S'){			
				std::cout << "Entries: NYI" << std::endl << std::endl;
			}
			else{}
				
			//Take in the next command letter	
			myIn >> letter;
		}
	}
	else{
		std::cout << "Unable to open file" << std::endl;
		check = -1;
	}
}

//Function definition for the private makeDNA function
//Recieves the file stream variable and reads in the DNA data and returns the id number
double sequenceDatabase::makeDNA(std::ifstream& myIn){
	//These are all variables for the DNA constructor
	string lab, seq;
	double id;
	int seqLen, codeI;
	myIn >> lab >> id >> seq >> seqLen >> codeI;
	DNA(lab, id, seq, seqLen, codeI);
	return id;
}