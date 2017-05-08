//Author: Ross Bearden
//Class: CSCI: 3110
//File: sequenceDatabase.h
//Purpose: This is the header file for a class called sequenceDatabase

#ifndef SEQUENCEDB_H
#define SEQUENCEDB_H

#include "DNA.h"
#include "RNA.h"
#include "AA.h"
#include "HashTable.h"

#include <fstream>
#include <string>




class SequenceDatabase
{
public:
	//Default Constuctor
	SequenceDatabase();
	//Destructor
	~SequenceDatabase();
	//Reads commands from the input file and take approprite measures
	void importEntries(string commandsFilename);

private:
	//HashTable object that holds a hash table for storing Sequence type objects
	HashTable<Sequence>* myHash;
	//Function used for adding DNA, RNA, or AA objects
	Sequence* makeObject(std::ifstream& myIn, const char& l);
	//Function that removes objects from the vector and deallocates memory
	
	
};
#endif