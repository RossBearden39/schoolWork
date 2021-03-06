//Author: Ross Bearden
//Class: CSCI: 3110
//File: DNA.h
//Purpose: This is the header file for a class called DNA

#ifndef DNA_H
#define DNA_H
#include <string>

using std::string;

class DNA
{
public:
	//Default Constructor
	DNA();
	//Constuctor with parameters
	DNA(string l,double id,string s,int sl,int ci);
	//Print method
	//print();
	//Get and set methods for the private data memebers
	//Label
	string GetL();
	void SetL(string l);
	//ID
	double GetID();
	void SetID(double id);
	//Sequence
	string GetS();
	void SetS(string s);
	//Sequence Length
	int GetSL();
	void SetSL(int sl); 
	//Code Index
	int GetCI();
	void SetCI(int ci);

//Private Data memebers of DNA class
private:
	string label;
	double iD;
	string sequence;
	int seqLength;
	int codeIndex;
};
#endif