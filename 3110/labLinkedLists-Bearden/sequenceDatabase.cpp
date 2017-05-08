//Author: Ross Bearden
//Class: CSCI: 3110
//File: sequenceDatabase.cpp
//Purpose: This is the implementation file for a class called sequenceDatabase
//		   This file takes input from a file and follows the command letters to create and
//		   work with DNA objects

#include "sequenceDatabase.h"
#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::cerr;
using std::cout;
using std::endl;

//Default Constructor
SequenceDatabase::SequenceDatabase() : newList() {}

//Import entries function definition
//THis function recieves the file input and takes actions based on the command character that is read
void SequenceDatabase::importEntries(string commandsFilename){
	std::ifstream myIn;				//file stream in variable
	myIn.open(commandsFilename);	//Opening file
	if(myIn.is_open()){				// checking to see if the file opened
		int idNum = 0;			//Value to hold the id number that is read
		char letter;				//Value to hold command character
		myIn >> letter;				//grabbing the first command character
		
		//While loop processes the command letter to determine appropriate action
		while(myIn){
			if(letter == 'D'){
				int id = makeDNA(myIn);			//This function calls the DNA constructor and returns the DNA id
				cout << "Adding " << id << " ..." << endl << endl;
				
			}
			else if (letter == 'P'){
				myIn >> idNum;			//Gets the id for printing
				cout << "Printing " << idNum << " ..." << endl;
				if(newList.size() != 0){
					DNA* temp;
					temp = newList.findID(idNum);
					temp->print();
				}
				else
					cerr << "Can not find item (" << idNum << ")!" << endl << endl;

			}
			else if (letter == 'O'){
				myIn >> idNum;			//Gets the id for obliterating
				cout << "Obliterating " << idNum << " ..." << endl << endl;
				if(newList.size() != 0){
					int flag = 0;
					flag = newList.obliterate(idNum);
					if(flag == -1){
						cout << "Can not delete DNA (" << idNum << "), NOT found!" << endl;
					}					
				}
				else
					cout << "Can not delete DNA (" << idNum << "), NOT found!" << endl << endl;
				
			}
			else if(letter == 'S'){		
				cout << "Entries: " << newList.size() << endl << endl;
			
			}
			else{}
				
			//Take in the next command letter	
			myIn >> letter;
		}
	}
	else{
		cerr << "Unable to open file" << endl;
		return;
	}
}

//Function definition for the private makeDNA function
//Recieves the file stream variable and reads in the DNA data and returns the id number
int SequenceDatabase::makeDNA(std::ifstream& myIn){
	//This is a pointer to a DNA object
	DNA* dPoint;
	//These are all variables for the DNA constructor
	string lab, seq;
	int seqLen, codeI, id;
	//Recieve DNA data
	myIn >> lab >> id >> seq >> seqLen >> codeI;
	//This creates a DNA object and sets a DNA pointer to it
	dPoint = new DNA(lab, id, seq, seqLen, codeI);
	//This uses dPoint to add a new node to the list
	newList.push_back(dPoint);
	//Make dPoint Null
	dPoint = nullptr;
	
	return id;
}
