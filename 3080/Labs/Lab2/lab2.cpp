//Author: Ross Bearden
//Date: 10/22/2014
//Class: 3080
//Assignment: Lab2

/*The purpose of this program is to read in a user supplied matrix and output the 
inverse of that matrix. The matrix should not be bigger than a 10X10 and it should be square.
It should also ask for the size of the matrix from the user*/

#include <iostream>
#include <string>

using namespace std;

//Global variables
const int MAX_SIZE = 10;													//This is the maximum size for the provided array

int main(){
	
	int matrixSize = 0;														//Holds the size of the matrix entered by the user
	float matrix1[MAX_SIZE][MAX_SIZE];										//Holds the matrix entered by the user
	float inverseMatrix[MAX_SIZE][MAX_SIZE];									//Holds the inverse of the entered matrix
	
	//Reading in the matrix size
	cout << "Input the size of the matrix: ";
	cin >> matrixSize;
	//Produces an error and ends the program if the entered size is larger than 10
	if ( matrixSize > MAX_SIZE){
		cout << "The size entered can not be larger than 10. " << endl << "Please run again with a correct size." << endl;
		return 1;
	}
	
	cout << endl;
	//Reading the matrix values
	cout << "Input the " << matrixSize << "X" << matrixSize << " matrix: " << endl;
	for( int i = 0; i < matrixSize; i++){
		for( int j = 0; j < matrixSize; j++){
			cin >> matrix1[i][j];
		}
	}
	cout << endl;

	//Setting up the identity matrix
	for( int i = 0; i < matrixSize; i++){
		for( int j = 0; j < matrixSize; j++){
			if( i == j){
				inverseMatrix[i][j] = 1;
			}
			else{
				inverseMatrix[i][j] = 0;
			}
		}
	}
	
	//Calculating the inverse matrix
	for( int i = 0; i < matrixSize; i++){
		float rowDiv = matrix1[i][i];															//Used to store the value on the main diagonal for later use
		
		//Makes the number on the main diagonal at (i,k) 1 on each pass
		for( int k = 0; k < matrixSize; k++){
			matrix1[i][k] = matrix1[i][k] / rowDiv;												//Divides each element in the user entered matrix on row 0 column k by the value in the main diagonal
			inverseMatrix[i][k] = inverseMatrix[i][k] / rowDiv;										//Divides each element in the identity matrix on row 0 column k by the value on the main diagonal of the user entered matrix
		}
		
		for( int j = 0; j < matrixSize; j++){
			//Executes if j is not referencing a number on the main diagonal
			if( j != i){
				float rowMul = matrix1[j][i] * -1;												//Multiply the value in row j column i by negative 1
			
				for( int k = 0; k < matrixSize; k++){
					matrix1[j][k] = matrix1[j][k] + rowMul * matrix1[i][k];							//Multiply the value in  matrix 1, row i column k by the value in rowMul and add it to the value in matrix 1, row j column k. This should result in a zero.
					inverseMatrix[j][k] = inverseMatrix[j][k] + rowMul * inverseMatrix[i][k];				//Multiply the value in  matrix 1, row i column k by the value in rowMul and add it to the value in inversematrix , row j column k. 
				}
			}
		}
	}
	
	cout << endl;
	
	//Outputting the matrix
	cout << "The inverse matrix is: " << endl;
	
	for( int i = 0; i < matrixSize; i++){
		for( int j = 0; j < matrixSize; j++){
			cout << inverseMatrix[i][j] << " ";
		}
		cout << endl;
	}
		
			
	return 0;
}