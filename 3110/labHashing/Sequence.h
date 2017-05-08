//Author: Ross Bearden
//Class: CSCI: 3110
//File: Sequence.h
//Purpose: This is the header file for a abstract base class called Sequence

#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::cerr;
using std::cout;
using std::endl;

class Sequence
{
public:
	//Default Constructor
	Sequence();
	//Constuctor with parameters
	Sequence(string l,int id,string s,int sl);
	//Print method
	virtual void print() = 0;
	//Get and set methods for the private data memebers
	//Label
	virtual string GetKey();
	//virtual void SetKey(string l);
	//ID
	virtual int GetID();
	//virtual void SetID(int id);
	//Sequence
	virtual string GetS();
	//virtual void SetS(string s);
	//Sequence Length
	virtual int GetSL();
	//virtual void SetSL(int sl); 
	//Code Index
	//int GetCI();
	//void SetCI(int ci);

//Private Data memebers of DNA class
protected:
	string label;
	int iD;
	string sequence;
	int seqLength;
};
#endif