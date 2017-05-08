//Author: Ross Bearden
//Class: CSCI: 3110
//File: Sequence.cpp
//Purpose: This is the implementation file for a class called Sequence
//		   This file creates and modifies Sequence objects

#include "Sequence.h"
#include <iostream>

using std::cout;
using std::endl;


//Default Constructor
Sequence::Sequence() : label(" "), iD(0), sequence(" "), seqLength(0) { }
//Constuctor with parameters
Sequence::Sequence(string l, int id,string s,int sl) : label(l), iD(id), sequence(s), seqLength(sl) {}

//Print method
//void Sequence::print(){
//	cout << "Sequence	" << "Label: " << GetL() << "	" << "ID: " << GetID() << "	" << "Sequence: " << GetS();
//	cout << "	" << "Length: " << GetSL() << "	" << "cD: " << GetCI() << endl << endl; 


//Get and set methods for the private data memebers
//Label

string Sequence::GetKey(){
	return label;
}

/*void Sequence::SetKey(string l){
	label = l;
}*/

//ID
int Sequence::GetID(){
	return iD;
}

/*void Sequence::SetID(int id){
	iD = id;
}*/

//Sequence
string Sequence::GetS(){
	return sequence;
}

/*void Sequence::SetS(string s){
	sequence = s;
}*/

//Sequence Length
int Sequence::GetSL(){
	return seqLength;
}

/*void Sequence::SetSL(int sl){
	seqLength = sl;
}*/

/*Code Index
int Sequence::GetCI(){
	return codeIndex;
}
	
void Sequence::SetCI(int ci){
	codeIndex = ci;
}*/