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
SequenceDatabase::SequenceDatabase() : myHash(nullptr) {}

//Destructor
SequenceDatabase::~SequenceDatabase(){
	delete myHash;
}

//Import entries function definition
//THis function recieves the file input and takes actions based on the command character that is read
void SequenceDatabase::importEntries(string commandsFilename){
	std::ifstream myIn;				//file stream in variable
	myIn.open(commandsFilename);	//Opening file
	if(myIn.is_open()){				// checking to see if the file opened
		string newLabel;			//Value to hold the label that is read in for operation
		int size = 0;				//Value to hold the inital size of the Hash Table
		myIn >> size;				//The first line of the input file should be the hash table size
		myHash = new HashTable<Sequence>(size); //Creates a new hash table object and passes the size of the hash table to the constructor
		char letter;				//Value to hold command character
		myIn >> letter;				//grabbing the first command character


		//While loop processes the command letter to determine appropriate action
		while(myIn){
			//Used for adding DNA, RNA, or AA objects
			if(letter == 'D' || letter == 'R' || letter == 'A'){
				Sequence* sequencePnt = nullptr;
				sequencePnt = makeObject(myIn, letter);					//This function calls the DNA,RNA, or AA constructor and returns the label
				cout << "Adding " << sequencePnt->GetKey() << " ..." << endl;		//Prints out the label of the added object and the load factor of the table
				cout << "Load Factor: " << myHash->GetLoad() << endl;
				sequencePnt = nullptr;
			}
			//Used for printing
			else if (letter == 'P'){
				myIn >> newLabel;			//Gets the label for printing
				Sequence* found;
				cout << "Printing " << newLabel << " ..." << endl;
				found = myHash->RetieveKey(newLabel);
				if(found == nullptr) {
					cout << "Can not find item (" << newLabel << "), NOT found!" << endl;
				}
				else{
					found->print();
				}
			}
			//Used for Obliteratring objects
			else if (letter == 'O'){
				myIn >> newLabel;			//Gets the id for obliterating
				cout << "Obliterating " << newLabel << " ..." << endl;
				//Calls obliterate method, which returns true if object was removed
				if(myHash->ObliterateKey(newLabel)){
					myHash->GetLoad();					
				}
				else{
					cout << "Can not delete item (" << newLabel << "), NOT found!" << endl;
				}
			}
			//Used for diplaying number of items
			else if(letter == 'S'){		
				cout << "Entries: " << myHash->GetCount() << endl;
			}
				
			//Take in the next command letter	
			myIn >> letter;
			cout << endl;
		}
	}
	//If file cannot be opened
	else{
		cerr << "Unable to open file" << endl;
		return;
	}
}

//Function definition for the private makeDNA function
//Recieves the file stream variable and reads in the DNA data and returns the id number
Sequence* SequenceDatabase::makeObject(std::ifstream& myIn, const char& l){
	//These are all variables for all Sequence type derived classes
	string objectLabel, seq;
	int seqLen, iD;
	//Recieve data
	myIn >> objectLabel >> iD >> seq >> seqLen;
	//Handles DNA objects
	if(l == 'D'){
		int cI;					//temp codeIndex variable
		myIn >> cI;
		//Polymorphic Call that creates a DNA object and assigns it to a Sequence pointer
		Sequence* s = new DNA(objectLabel, iD, seq, seqLen, cI);
		//Adds new DNA object to Sequence hash table
		myHash->InsertKey(s);		
		return s;
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
		Sequence* s = new RNA(objectLabel, iD, seq, seqLen, t);
		//Adds new DNA object to Sequence pointer vector
		myHash->InsertKey(s);
		return s;
	}
	//Handles AA objects
	else if(l == 'A'){
		int oRF;					//temp variable for open reading frame
		myIn >> oRF;
		//Polymorphic Call that creates a DNA object and assigns it to a Sequence pointer
		Sequence* s = new AA(objectLabel, iD, seq, seqLen, oRF);
		//Adds new DNA object to Sequence pointer vector
		myHash->InsertKey(s);
		return s;
	}
	return nullptr;
}
