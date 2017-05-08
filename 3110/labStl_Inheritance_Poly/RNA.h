//Author: Ross Bearden
//Class: CSCI: 3110
//File: RNA.h
//Purpose: This is the header file for a derived class called RNA
//		   This file gives the definition of RNA objects

#include "Sequence.h"


class RNA : public Sequence{
public:
	//Enum for RNA types
	enum Type{ mRNA, rRNA, tRNA};

	//Default Constructor
	RNA();
	//Constructor
	RNA(string l, int iD,string s,int sL, RNA::Type t);

	//Get & Set for rnaType
	string GetType();

	void SetType(Type t);
	
	//Print Method
	void print();

	//Overloaded operator>> so that enum Type can be recieved through the filestream
	//Really wanted this to work
	//RNA::Type RNA::operator=(RNA::Type type, string val); 

private:
	//type of RNA
	Type rnaType;
	
};