//Author: Ross Bearden
//Class: CSCI 3110
//Date: 9-11-15
//File: DNAList.h
//Purpose: This file provides the class definition for a DNAList class
//It creates DNAList objects based on commands recieved in the sequenceDatabase class
//This class object will create a dummy node doubly linked list that holds DNA objects

#ifndef DNALIST_H
#define DNALIST_H
#include "DNA.h"

class DNAList
{
public:
	//Default Constructor
	DNAList();
	//Constructor with a DNA Object pointer parameter
	DNAList(DNA* obj);
	//Destructor
	~DNAList();
	//This method adds a new DNAnode to the end of the list
	void push_back(DNA* newNode);
	//This method recieves a DNA id number and returns a DNA object pointer if
	//the id exists
	DNA* findID(int searchID);
	//This method removes a specified DNANode from the list and deallocates the
	//memory
	int obliterate(int searchID);
	//This method returns the current size of the list
	int size();
	

private:
	struct DNANode{
		DNA* dnaPoint;
		DNANode* next;
		DNANode* prev;
	};
	DNANode* head;

};

#endif