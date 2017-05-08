/*Author: Ross Bearden
Date: 11/5/2014
Class: Discrete Structures 3080
Assignment: Lab 3

Purpose: The purpose of this lab it to utilize Prim's algorithm to find the minimal spanning tree in a graph that will be input by the user
Requirements: The graph will have no more than 10 nodes.
			TGhe graph must be a simple weighted connected graph and the weights must be positive
			The user must enter a adjaceny matrix that has been modified with the weights of the graph
			Infinity will be represented by 999 in the adjacency matrix
			The algorithm will always start with node 1
*/

//Directives
#include <iostream>
#include <string>

using namespace std;

//Global Declarations
const int MAX_SIZE = 10;

//Start of the main prgram
int main() {
	
	//Variable Declarations
	int tempMin= 999;									//Holds the current minimum of the values in dArray
	int position= 0;									//Holds the postion of the minimum value in the dArray
	int matrixSize = 0;									//Holds the actual size of the matrix
	int adjMatrix[MAX_SIZE][MAX_SIZE] = {};					//Array that will hold the modified adjacency matrix
	int dArray[MAX_SIZE] = {};								//Array that will hold, for each node, the distance from the previous node in the shortest path
	int sArray[MAX_SIZE] = {};								//Array that will hold, for each node, the previous node in the shortest path
	int in[MAX_SIZE] = {};									//Holds the nodes that the algorithm has already used
	int f = 1;											//temp variable for hold the value currently being checked against finishedNodes
	
	
	cout << "Input the size of the matrix:  ";
	cin >> matrixSize;									//Input the size of the matrix to matrixSize
	cout << endl;
	cout << "Input the matrix: "<< endl;
	//Loops to recieve the contents of the matrix
	for( int i = 0; i < matrixSize; i++){
		for( int j = 0; j < matrixSize; j++){
			cin >> adjMatrix[i][j];
		}
	}
	
	//Testing to see that the array exists
	if(matrixSize <= 0){
		cerr << "The given size is not valid" << endl << "Please rerun and try again with an appropriate size" << endl;
		return 1;
	}
	cout << endl;
	
	//Filling the dArray and the sArray with the values from row one of the adjacency matrix
	for( int i = 0; i < 1; i++){
		for( int j = 0; j< matrixSize; j++){
			dArray[j] = adjMatrix[i][j];						//Fills the dArray with the contents of row one of the adjacency matrix
			sArray[j] = 1;								//Puts one in every spot of the sArray, one is the inital node
		}
	}
	in[0] = 1;											//Puts one into the array of completed nodes
	int z = 1;											//Integer to keep track of the next location to be filled in in
	
	int done = 0;										//Keeps track of whether all nodes have be plcaed into in
	while(done < matrixSize){
		bool fFlag = true;								//Resets the flag after each pass of the while loop
		tempMin = 999;									//Resets tempMin after each pass of the while loop
		//This loop finds the minimum node in the dArray that is not in In
		for(int i = 0; i < matrixSize; i++){
			for(int j = 0; j < matrixSize; j++){
				if( f == in[j]){
					j = matrixSize;
					fFlag = false;
				}
			}	
			if( fFlag && dArray[i] < tempMin ){
				tempMin = dArray[i];
				position = f;
			}
			fFlag = true;							//Resets the flag for the next check of the value in f
			f++;
		}
		in[z] = position;								//Puts the minimum node in dArray into in
		z++;					        				//Increments z to the next position within in to be filled
		f = 1;									//Resets f to one to check the the dArray against the values in adjMatrix on row designated by position
		fFlag = true;								//Resets the flag for the next check on f
		//This loop compares the values in the dArray not in In to the values in the adjMatrix on the row designated by the position variable and swap the values
		//in the adjMatrix for those in the dArray if they are lower. It also changes the values in the sArray to the value in position if the dArray value is changed
		for(int i = 0; i < matrixSize; i++){
			for(int j = 0; j < matrixSize; j++){
				if( f == in[j]){
					j = matrixSize;
					fFlag = false;
				}
			}
			if( fFlag && adjMatrix[position-1][i] < dArray[i]){
				dArray[i] = adjMatrix[position-1][i];
				sArray[i] = position;
			}
			f++;
			fFlag = true;
		}
		done++;
		f = 1;
	}
	
	//Outputting the arcs of the minimal spanning tree, excluding the first node
	cout << "The spanning tree consists of the following arcs: " << endl; 
	for(int i = 1; i < matrixSize; i++){
		cout << i + 1 << '-' << sArray[i] << endl;
	}
		
	
	return 0;
}