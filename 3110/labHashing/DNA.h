//Author: Ross Bearden
//Class: CSCI: 3110
//File: DNA.h
//Purpose: This is the header file for a derived class called DNA
//		   This file gives the definition of DNA objects

#include "Sequence.h"

class DNA : public Sequence{
public:
	//Default Constructor
	DNA();
	//Constructor
	DNA(string l, int iD,string s,int sL, int cI);
	//Get & Set Code Index
	int GetCode();
	void SetCode(int cI);
	//Print Method
	void print();

private:
	int codeIndex;
};