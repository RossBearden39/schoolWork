//Author: Ross Bearden
//Class: CSCI: 3110
//File: DNA.cpp
//Purpose: This is the implementation file for a derived class called DNA
//		   This file creates and modifies DNA objects

#include "DNA.h"

//Default Constructor
DNA::DNA() : codeIndex(0) {}

//Constructor
DNA::DNA(string l, int iD,string s,int sL, int cI)
	: Sequence(l, iD, s, sL), codeIndex(cI) {}

//Get and Set code index
int DNA::GetCode() {return codeIndex;}

void DNA::SetCode(int cI) { codeIndex = cI;}

//Print Method
void DNA::print(){
	cout << "DNA:		Label: " << GetKey() << "	ID: " << GetID();
	cout << "	Sequence: " << GetS() << "	Length: " << GetSL();
	cout << "	cDNAStartIndex: " << GetCode() << endl;
}

