//Author: Ross Bearden
//Class: CSCI 3110
//Date: 9-11-15
//File: DNAList.cpp
//Purpose: This file is the implementation file for the DNAList class

#include "DNAList.h"
#include "DNA.h"

//Default Constructor Definition
//Creates a dummy node and sets the dummy node pointers
DNAList::DNAList(){
	head = new DNANode;
	head->dnaPoint= nullptr;
	head->next = nullptr;
	head->prev = head;
}

//Single Parameter constructor
//Takes a DNA object pointer and puts the object in the list
//This will only be used if the default constructor was not used.
//Otherwise, nodes will enter the list in the push_back method
DNAList::DNAList(DNA* obj){
	//Creates a dummy head node for first item
	if(head == nullptr){
		head = new DNANode;
		head->next = nullptr;
		head->prev = head;
	}

	//Calls push back method
	push_back(obj);
	
}

//Destructor
//Deallocates all memory in the list except for the dummy head node
//Resets dummy head pointers
DNAList::~DNAList(){
	DNANode* temp = head->next;
	//Makes temp point to the last node in the list
	if(temp != nullptr){
		while(temp->next != nullptr){
			temp = temp->next;
		}
		//Deletes nodes from back to front
		while(temp->prev != head){
			temp = temp->prev;
			delete temp->next;
		}
		temp->next = nullptr;
	}
}

//This method is used to add new DNA nodes onto the end of the list
void DNAList::push_back(DNA* newNode){
	DNANode* temp = new DNANode;		//This will hold the data that needs to be inserted in the list 
	DNANode* curr = head;
	 

	//This loop will make temp point to the last node in the list
	while(curr != nullptr){
		temp->prev = curr;
		curr= curr->next;
		
	}
	temp->dnaPoint = newNode;
	temp->prev->next = temp;
	temp->next = nullptr;
	temp = nullptr;
}

//This method recieves a DNA ID to search for and returns a point to the DNA object
//If the ID is not in the list it will return a nullptr 
DNA* DNAList::findID(int searchID){
	DNANode* temp = head->next;
	while(temp != nullptr && temp->dnaPoint->GetID() != searchID){
		temp = temp->next;
	}
	if(temp == nullptr)
		return nullptr;
	else
		return temp->dnaPoint;
}

//This method removes a node from the list and deletes the memory it occupied
//If the node was not in the list it will return a -1, else it will return 1
int DNAList::obliterate(int searchID){
	DNANode* temp = head->next;
	int flag = -1;
	while(temp != nullptr && flag != 1){
		if( temp->dnaPoint->GetID() == searchID){
			//Takes care of size 1 lists and last node in the list
			if(temp->next == nullptr){
				flag = 1;
				temp->prev->next = nullptr;

			}
			//Middle of the list
			else{
				flag = 1;
				temp->next->prev = temp->prev;
				temp->prev->next = temp->next;
			}
			delete temp;
		}
		else
			temp = temp->next;
	}
	temp = nullptr;


	return flag;
}

//This method returns the size of the array
int DNAList::size(){
	DNANode* temp = head->next;
	int nodeCount = 0;
	while(temp != nullptr){
		 temp = temp->next;
		 nodeCount++;
	}
	temp = nullptr;
	return nodeCount;
}