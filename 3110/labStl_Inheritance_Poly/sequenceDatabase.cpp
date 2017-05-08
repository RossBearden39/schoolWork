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
SequenceDatabase::SequenceDatabase() {
	sequenceData.clear();
}

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
			//Used for adding DNA, RNA, or AA objects
			if(letter == 'D' || letter == 'R' || letter == 'A'){
				int id = makeObject(myIn, letter);			//This function calls the DNA,RNA, or AA constructor and returns the id
				cout << "Adding " << id << " ..." << endl;
				
			}
			else if (letter == 'P'){
				myIn >> idNum;			//Gets the id for printing
				int check= -1;               //used if object could not be found
				cout << "Printing " << idNum << " ..." << endl;

				//Vector iterator
				vector<Sequence*>::iterator iter;
				for(iter = sequenceData.begin(); iter != sequenceData.end(); iter ++){
					if(idNum == (*iter)->GetID()){
						(*iter)->print();
						check = 1;
					}
				}

				if(check == -1) {
					cout << "Can not find item (" << idNum << ")!" << endl;
				}
			}
			else if (letter == 'O'){
				myIn >> idNum;			//Gets the id for obliterating
				cout << "Obliterating " << idNum << " ..." << endl;
				if(sequenceData.size() != 0){
					int flag = 0;
					flag = obliterate(idNum);
					if(flag == -1){
						cout << "Can not delete item (" << idNum << "), NOT found!" << endl;
					}					
				}
				else
					cout << "Can not delete item (" << idNum << "), NOT found!" << endl;
			}
			else if(letter == 'S'){		
				cout << "Entries: " << sequenceData.size() << " total" << endl;
			
			}

				
			//Take in the next command letter	
			myIn >> letter;
			cout << endl;
		}
	}
	else{
		cerr << "Unable to open file" << endl;
		return;
	}
}

//Function definition for the private makeDNA function
//Recieves the file stream variable and reads in the DNA data and returns the id number
int SequenceDatabase::makeObject(std::ifstream& myIn, const char& l){
	//These are all variables for all Sequence type derived classes
	string lab, seq;
	int seqLen, iD;
	//Recieve data
	myIn >> lab >> iD >> seq >> seqLen;
	//Handles DNA objects
	if(l == 'D'){
		int cI;					//temp codeIndex variable
		myIn >> cI;
		//Polymorphic Call that creates a DNA object and assigns it to a Sequence pointer
		Sequence* s = new DNA(lab, iD, seq, seqLen, cI);
		//Adds new DNA object to Sequence pointer vector
		sequenceData.push_back(s);
		s = nullptr;
	}
	//Handles RNA objects
	else if(l == 'R'){
		RNA::Type t;					//temp RNA type variable
		string val;						//temp string variable for RNA type
		myIn >> val;
		//This is not what I wanted to do, but I could not get my overloaded operator functions to work
		//This compare the read in value to those in the enum class and sets to appropriatly or outputs an error message and continues
		if(val == "mRNA"){
			t = RNA::Type(0);
		}
		else if(val == "rRNA"){
			t = RNA::Type(1);
		}
		else if(val == "tRNA"){
			t = RNA::Type(2);
		}
		else
			cerr << val << " is not a correct type of RNA" << endl;

		//Polymorphic Call that creates a DNA object and assigns it to a Sequence pointer
		Sequence* s = new RNA(lab, iD, seq, seqLen, t);
		//Adds new DNA object to Sequence pointer vector
		sequenceData.push_back(s);
		s = nullptr;
	}
	//Handles AA objects
	else if(l == 'A'){
		int oRF;					//temp variable for open reading frame
		myIn >> oRF;
		//Polymorphic Call that creates a DNA object and assigns it to a Sequence pointer
		Sequence* s = new AA(lab, iD, seq, seqLen, oRF);
		//Adds new DNA object to Sequence pointer vector
		sequenceData.push_back(s);
		s = nullptr;
	}

	return iD;
}

//Obliterate function that removes objects from the list and deallocates their memory
int SequenceDatabase::obliterate(int ID){
	//Vector iterator
	vector<Sequence*>::iterator iter;
	//temp flag
	int flag = -1;	for(iter = sequenceData.begin(); iter != sequenceData.end(); iter++){
		if(ID == (*iter)->GetID()){
			Sequence* goAway = (*iter);
			sequenceData.erase(iter);
			delete (goAway);
			flag = 1;
			break;

		}
	}
	return flag;
}