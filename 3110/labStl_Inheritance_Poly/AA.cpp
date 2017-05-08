//Author: Ross Bearden
//Class: CSCI: 3110
//File: AA.cpp
//Purpose: This is the implementation file for a derived class called AA
//		   This file creates and modifies AA objects

#include "AA.h"

//Default Constructor
AA::AA() {}

//Constructor
AA::AA(string l, int iD,string s,int sL, int oRF)
	: Sequence(l, iD, s, sL) {
		if( oRF >= -3 && oRF <= 2)
			openRF = oRF;
		else
			cerr << oRF << " is not a appropriate open reading frame" << endl;
}

//Returns open reading file value
int AA::GetORF() {return openRF;}

//Sets the open reading value
void AA::SetORF(int val) 
{
	if ( val >= -3 && val <= 2)
		openRF = val;
	else
		cerr << val << " is not a valid open reading file value" << endl;
}

//Print Method
void AA::print(){
	cout << "AA:		Label: " << GetL() << "	ID: " << GetID() << "	Sequence: " << GetS();
	cout << "	Length: " << GetSL() << "	ORF: " << GetORF() << endl;
}