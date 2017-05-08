//Author: Ross Bearden
//Class: CSCI: 3110
//File: sequenceDatabase.h
//Purpose: This is the header file for a class called sequenceDatabase

#ifndef SEQUENCEDB_H
#define SEQUENCEDB_H

#include "DNA.h"
#include <fstream>
#include <string>

class sequenceDatabase
{
public:
	//Default Constuctor
	sequenceDatabase();
	//Reads commands from the input file and take approprite measures
	void importEntries(string commandsFilename);
	


private:
	//Makes a DNA object
	double makeDNA(std::ifstream& myIn);
	//Checks int for file
	int check;

};
#endif