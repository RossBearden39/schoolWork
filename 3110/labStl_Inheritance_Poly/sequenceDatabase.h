//Author: Ross Bearden
//Class: CSCI: 3110
//File: sequenceDatabase.h
//Purpose: This is the header file for a class called sequenceDatabase

#ifndef SEQUENCEDB_H
#define SEQUENCEDB_H

#include "DNA.h"
#include "RNA.h"
#include "AA.h"
#include <vector>

#include <fstream>
#include <string>


using std::vector;

class SequenceDatabase
{
public:
	//Default Constuctor
	SequenceDatabase();
	//Reads commands from the input file and take approprite measures
	void importEntries(string commandsFilename);

private:
	//Vector that holds sequence pointers
	vector<Sequence*> sequenceData;
	//Function used for adding DNA, RNA, or AA objects
	int makeObject(std::ifstream& myIn, const char& l);
	//Function that removes objects from the vector and deallocates memory
	int obliterate(int ID);
	
};
#endif