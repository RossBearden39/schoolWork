//Author: Ross Bearden
//Class: CSCI: 3110
//File: RNA.cpp
//Purpose: This is the implementation file for a derived class called RNA
//		   This file creates and modifies RNA objects

#include "RNA.h"

//Default Constructor
RNA::RNA() {}

//Constructor
RNA::RNA(string l, int iD,string s,int sL,Type t)
	: Sequence(l, iD, s, sL), rnaType(t){
		
}

//Returns the current rnaType
string RNA::GetType()
{
	if(rnaType == 0)
		return "mRNA";
	else if (rnaType == 1)
		return "rRNA";
	else if (rnaType == 2)
		return "tRNA";
	else 
		return "No Type";
}

//Changes the rnaType variable
void RNA::SetType(Type t){
	rnaType = t;
}

//Print Method
void RNA::print(){
	cout << "RNA:		Label: " << GetL() << "	ID: " << GetID() <<  "	Sequence: " << GetS();
	cout << "	Length: " << GetSL() << "	Type: " << GetType() << endl;
}

//Really wanted to get this to work for ifstream or even assignment operator, but I could not make it happen
//Overloaded istream operator. Allows enum Type to be recieved via filestream
/*RNA::Type RNA::operator=(RNA::Type& type, string& val){
		
	//This loop compares the read in value to those in the enum class and sets the value appropriatlty
	//if it matches any. Otherwise it prints out an error message and continues.
	if(val == "mRNA"){
		type = RNA::Type(0);
	}
	else if(val == "rRNA"){
		type = RNA::Type(1);
	}
	else if(val == "tRNA"){
		type = RNA::Type(2);
	}
	else
		cerr << value << " is not a correct type of RNA" << endl;
	return type;
}*/