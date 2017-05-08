//Author: Ross Bearden
//Class: CSCI: 3110
//File: DNA.cpp
//Purpose: This is the implementation file for a class called DNA

#include "DNA.h"
#include <string>
#include <iostream>

//Default Constructor
DNA::DNA() : label(" "), iD(0), sequence(" "), seqLength(0), codeIndex(-1) { }
//Constuctor with parameters
DNA::DNA(string l, double id,string s,int sl,int ci) : label(l), iD(id), sequence(s), seqLength(sl), codeIndex(ci) {	}
//Print method
//print();

//Get and set methods for the private data memebers
//Label

string DNA::GetL(){
	return label;
}

void DNA::SetL(string l){
	label = l;
}

//ID
double DNA::GetID(){
	return iD;
}

void DNA::SetID(double id){
	iD = id;
}

//Sequence
string DNA::GetS(){
	return sequence;
}

void DNA::SetS(string s){
	sequence = s;
}

//Sequence Length
int DNA::GetSL(){
	return seqLength;
}

void DNA::SetSL(int sl){
	seqLength = sl;
}

//Code Index
int DNA::GetCI(){
	return codeIndex;
}
	
void DNA::SetCI(int ci){
	codeIndex = ci;
}