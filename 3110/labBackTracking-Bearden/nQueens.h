//Author: Ross Bearden
//Class: CSCI 3110
//File: nQueens.h
//Pupose: This file serves as the header file for a nQueens problem solver 

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

using std::string;
using std::vector;
using std::cerr;
using std::endl;

//This function determines if a queen position is possible or not
bool promising(char** theGrid, int size, int currRow, int currCol){
	for(int i = 0; i < currRow; i++){
		for(int j = 0; j < size; j++){
			if(i == currRow && theGrid[i][j] == 'Q'){
				return false;
			}
			else if(j == currCol && theGrid[i][j] == 'Q'){
				return false;
			}
			else if(abs(i - currRow) == abs(j - currCol) && theGrid[i][j] == 'Q'){
				return false;
			}
		}
	}
	return true;
}

//nQueens Solver function
/*** BACKTRACKING HERE ***/
bool nQueensSolver(char** theGrid, int size, int currRow){
	//If all queens are placed, returns true
	if(currRow >= size){
		return true;
	}
	else{
		for(int j = 0; j < size; j++){
				if(promising(theGrid, size, currRow, j)){
					theGrid[currRow][j] = 'Q';
					if(nQueensSolver(theGrid, size, currRow+1)){
						return true;
					}
					else
						theGrid[currRow][j] = '-';
				}
		}
		//If there is no solution, backtrack
		return false;
	}
}


//Function for printing the problem solution to a file
//Recieves an interger representing the size of the grid 
//and a string with the name of the output file
void printNQueensSolution(int n, string outPut){
	//Create output filestream variable
	std::ofstream myOut;
	myOut.open(outPut);
	//Test file opening
	if(!myOut){
		cerr << "Could not create output file" << endl;
		return;
	}
	//Create a 2-D vector
	char ** nGrid;
	//Create rows
	nGrid = new char*[n];
	//Allocate columns
	for(int i = 0; i < n; i ++){
		nGrid[i] = new char[n];
	}
	//Test allocation
	if(nGrid == nullptr){
		cerr << "Error: Memory could not be allocated" << endl;
		return;
	}
	//Initialize array
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			nGrid[i][j] = 0;
		}
	}
	//Start nQueens solver
	//Start at row 0
	bool solved = nQueensSolver(nGrid, n, 0);
	//Fill in rest of grid
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(nGrid[i][j] != 'Q'){
				nGrid[i][j] = '-';
			}
		}
	}
	//Print solution to file if it was solvable else print unsolvable
	if(solved){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				myOut << nGrid[i][j] << " ";
			}
			myOut << endl;
		}
	}
	else
		myOut << "No possible solutions for N queens!" << endl;
	//Clean up memory
	for(int i = 0; i < n; i++){
			delete [] nGrid[i];
	}
	delete [] nGrid;
	nGrid = nullptr;
	return;
}