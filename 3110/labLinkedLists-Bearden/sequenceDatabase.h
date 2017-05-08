//Author: Ross Bearden
//Class: CSCI: 3110
//File: sequenceDatabase.h
//Purpose: This is the header file for a class called sequenceDatabase

#ifndef SEQUENCEDB_H
#define SEQUENCEDB_H

#include "DNA.h"
#include "DNAList.h"
#include <fstream>
#include <string>

using std::string;

class SequenceDatabase
{
public:
	//Default Constuctor
	SequenceDatabase();
	//Reads commands from the input file and take approprite measures
	void importEntries(string commandsFilename);
	


private:
	//Makes a DNA object
	int makeDNA(std::ifstream& myIn);
	//DNAList object
	DNAList newList;
};
#endif