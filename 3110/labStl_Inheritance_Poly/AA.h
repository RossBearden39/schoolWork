//Author: Ross Bearden
//Class: CSCI: 3110
//File: AA.h
//Purpose: This is the header file for a derived class called AA
//		   This file gives the definition of AA objects

#include "Sequence.h"

class AA : public Sequence{
public:
	//Default Constructor
	AA();
	//Constructor
	AA(string l, int iD,string s,int sL, int oRF);

	//Get & Set methods for open reading file variable
	int GetORF();

	void SetORF(int val);
	
	//Print Method
	void print();

private:
	int openRF;
};