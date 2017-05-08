//Author: Ross Bearden
//Class: CSCI: 3110
//File: HashTable.h
//Purpose: This is the header file amd implementation for a class called HashTable.h
// It will be used to create a hash table for storing Sequence type objects
//The class is templated to allow multiple data types to be used

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Sequence.h"
#include <list>

using std::list;

template <typename T>
class HashTable{
public:
	//constructor for the HashTable Object
	HashTable(unsigned int size);

	//Destructor for Hashtable object
	~HashTable();
	//Insert method for the hash table
	//Uses supplied key to place the new object in the hash table
	void InsertKey(T* newObject);

	//Obliterate method
	//Uses the supplied key to find the object in the hash table and removes it
	//Returns true if object was removed
	bool ObliterateKey(string removeKey);

	//Retieval Method
	//Uses supplied key to find an object in the hash table
	//Returns a pointer to the object in the hash table if it was found
	//Also prints out the number of nodes visited while searching the list and the current load factor
	T* RetieveKey(string searchKey);

	//Get/Set methods
	//Table Size
	unsigned int GetSize();

	//Load Factor
	double GetLoad();

	//Item count
	unsigned int GetCount();

private:
	
	//Table Size
	unsigned int tableSize;

	//Hash table
	//Stores lists of sequence type objects
	list<T*>* myArray;

	//Current item count
	unsigned int numOfItems;

	//Hash function
	//Takes a string and returns an unsigned int
	//Random hashing is the method used
	unsigned int Hash(string newKey);

	//Find Method
	//Used by the retrieve and obliterate function to find an object in the Hash table
	T* findObject(string findKey);

	//Remove method
	//Called by onbliterate to travese list and remove an object if it exists
	//returns true if it was removed
	bool removeObject(string remKey);

	//Increase the hash table size if load factor is greater than 1.0
	void Rehash();

	//Determines if a number is prime
	bool IsPrime() const;

};

//
//Purpose: This is the specification portion the class called HashTable
//

//Constructor for Hashtable class
template<typename T>
HashTable<T>::HashTable(unsigned int size) : numOfItems(0), tableSize(size) {
	myArray = new list<T*>[size]; 
}

//Destructor for hash table
template<typename T>
HashTable<T>::~HashTable(){
	tableSize = 0;
	numOfItems = 0;
	delete [] myArray;
	myArray = nullptr;
}

//Hash function		Private method
//Uses random hashing method
template<typename T>
unsigned int HashTable<T>::Hash(string newKey){
	unsigned int keyNum = 0;					//This will hold the intger value of the key

	//Convert the string to an integer
	for(unsigned int i = 0; i < newKey.length(); i++){
		if(newKey[i] >= 65 && newKey[i] <= 122){
			keyNum = (newKey[i] - 'A') + keyNum;
		}
		else{
			keyNum = newKey[i] + keyNum;
		}
	}

	//return the location in the hash table by dividing the keyNum by the table size
	return (keyNum % tableSize);

} 

//Get/Set Implementations

//Load Factor
template<typename T>
double HashTable<T>::GetLoad(){return double(numOfItems)/double(tableSize);}

//Table Size
template<typename T>
unsigned int HashTable<T>::GetSize(){return tableSize;}

//Number of Items
template<typename T>
unsigned int HashTable<T>::GetCount(){return numOfItems;}

//Insert method		Public Method
//Recieves a string key, calls hash function, which returns a integer
//Then places the object into the hash table at the designated position
template<typename T>
void HashTable<T>::InsertKey(T* newObject){
	/*if(GetLoad() >= 1){
		Rehash();
	}*/
	unsigned int keyPos= Hash(newObject->GetKey());				//Passes the key to the hash function and stores the returned integer
	myArray[keyPos].push_front(newObject);				//Pushes the object onto the list in the array at position keyPos
	numOfItems++;
}

//Rehash method		Private method
//If load factor is 1 or greater, a new hash table is created and all current values are transfered 
//to the new table
template< typename T>
void HashTable<T>::Rehash(){
	unsigned int oldSize = tableSize;		//holds the old table size
	tableSize = tableSize * 2;				//Doubles table size
	bool prime = false;						//Will be true when a prime number is found
	while(!IsPrime()){
		++tableSize;
	}
	//Creates the new hash table
	list<T*>* newArray = new list<T*>[tableSize];
	//loop transfers objects in old table to the new table
	for( unsigned int i = 0; i < oldSize; i++){
		//Create iterator to the lists in the hash table
		typename list<T*>::iterator iter = myArray[i].begin();
		//Transfer items one at a time from old hash table to new hash table
		T* remObj = nullptr;
		while(iter != myArray[i].end()){
			remObj = (*iter);
			myArray[i].pop_front();
			unsigned int keyPos= Hash(remObj->GetKey());				//Passes the key to the hash function and stores the returned integer
			newArray[keyPos].push_front(remObj);						//Pushes the object onto the list in the array at position keyPos
		}
	}
	delete [] myArray;
	myArray = newArray;
	newArray = nullptr;
}

//Is Prime method
//Determines if the recieved number is prime
template< typename T>
bool HashTable<T>::IsPrime() const{
   unsigned  int i = 2;
    while( i < tableSize ){
        if( tableSize % i == 0){
            return false;
        }
        i++;
    }
    return true;
}

//Obliterate Method		Public Method
//Recieves a key to remove
//Uses find key to find the object in the hash table
//Removes the object if found and returns true, otherwise returns false
template<typename T>
bool HashTable<T>::ObliterateKey(string removeKey){
	bool gone = false;							//Will be true if key was removed, false otherwise
	gone = removeObject(removeKey);
	return gone;
}

//Remove method   This is a private method
//Recieves a key for an object
//Uses key to find object in list, if it exists
//Remove object from list and returns true, otherwise returns false
template <typename T>
bool HashTable<T>::removeObject(string remKey){
	unsigned int pos = Hash(remKey);						//Gets the hash table position of the key
	T* remObj = nullptr;									//T pointer to hold object to be deleted if it is found
	//Create an iterator to search hash table list 
	typename list<T*>::iterator iter = myArray[pos].begin();
	while(iter != myArray[pos].end()){
		//If search key is found, remove object and return true
		if((*iter)->GetKey() == remKey){
			remObj = (*iter);
			myArray[pos].erase(iter);
			delete (remObj);
			numOfItems--;
			return true;
		}
		else{
			++iter;
		}
	}
	return false;
}


//Retrieve Method	Publice Method
//Calls the private find method which returns a pointer to the object if it was found
template<typename T>
T* HashTable<T>::RetieveKey(string searchKey){
	//int pos = Hash(searchKey);
	T* foundSeq = nullptr;
	foundSeq = findObject(searchKey);
	return foundSeq;
}

//Find method		Private Method
//Recieves key to be found and searches hash table for the key
//Returns nullptre if key could not be found
template<typename T>
T* HashTable<T>::findObject(string findKey){
	unsigned int pos = Hash(findKey);						//Gets the hash table position of the key
	T* returnObj = nullptr;							//T pointer to hold object if it is found
	//Create an iterator to search hash table list
	typename list<T*>::iterator iter = myArray[pos].begin();
	while(iter != myArray[pos].end()){
		//If search key is found, set pointer to it and break loop
		if((*iter)->GetKey() == findKey){
			returnObj = (*iter);
			iter = myArray[pos].end();
		}
		else{
			++iter;
		}
	}
	return returnObj;
}
#endif