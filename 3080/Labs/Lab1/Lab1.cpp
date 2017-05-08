/*Ross Bearden
10/08/2014
Discrete Structures
Lab1
*/

/*The purpose of this lab is to perform matrix operations on two matrices that will be entered by the user.
The operations include summing, boolean and, boolean or, boolean product, and the product of the two matrices.
If an operation is unable to be performed on the matrices, an error message will be displayed explaining why it was 
unable to complete the operation. The user will also be given the option to quit the program or enter more matrices. */

//Assumptions
//The user will only enter p or q in the menu

//Compiler Directives
#include <iostream>
#include <string>

using namespace std;

//Global variables
const int MAX_SIZE = 10;				//the maximum number of rows and columns allowed in the arrays
int flag1;								//flag used to test for boolean matrix
int flag2;								//flag used to test for boolean matrix

//Function definitions for matrix operations
void Sum( int matrix1[][MAX_SIZE] /*IN*/, int m1Rows /*IN*/, int m1Cols /*IN*/, int matrix2[][MAX_SIZE] /*IN*/, int m2Rows /*IN*/, int m2Cols /*IN*/);   			//This function will sum the two arrays, if possible, and output the result
void BoolAnd( int matrix1[][MAX_SIZE] /*IN*/, int m1Rows /*IN*/, int m1Cols /*IN*/, int matrix2[][MAX_SIZE] /*IN*/, int m2Rows /*IN*/, int m2Cols /*IN*/);		//This function will perform a boolean and, if possible, on the arrays and output the result
void BoolOr( int matrix1[][MAX_SIZE] /*IN*/, int m1Rows /*IN*/, int m1Cols /*IN*/, int matrix2[][MAX_SIZE] /*IN*/, int m2Rows /*IN*/, int m2Cols /*IN*/);			//This function will perform a boolean or, iff possible, on the arrays and output the result
void BoolMultiply( int matrix1[][MAX_SIZE] /*IN*/, int m1Rows /*IN*/, int m1Cols /*IN*/, int matrix2[][MAX_SIZE] /*IN*/, int m2Rows /*IN*/, int m2Cols /*IN*/);		//This function will perform a boolean multiply, if possible, and output the result
void Product( int matrix1[][MAX_SIZE] /*IN*/, int m1Rows /*IN*/, int m1Cols /*IN*/, int matrix2[][MAX_SIZE] /*IN*/, int m2Rows /*IN*/, int m2Cols /*IN*/);		//This function will multiply the arrays, if possible, and output the result

//Beginning of main program
int main()
{
	//Variable Declarations
	int m1Rows;							//holds the number of rows for the first matrix entered
	int m1Cols;							//holds the number of columns for the first matrix entered
	int matrix1[MAX_SIZE][MAX_SIZE];			//holds the values of the first matrix
	int m2Rows;							//holds the number of rows for the second matrix entered
	int m2Cols;							//holds the number of columns for the second matrix entered
	int matrix2[MAX_SIZE][MAX_SIZE];			//holds the values for the second matrix
	char userChoice;						//holds the letter the user choose when asked how to proceed
	
	//Deciding on a course of action
	cout << "Which of the following do you wish to do:" << endl << endl;
	cout << "(p) Perform matrix operations" << endl << endl;
	cout << "(q) Quit" << endl << endl;
	cin >> userChoice;
	cout << endl;
	
	while( userChoice != 'q'){
		
		//Recieving the matrices
		cout << "Input the dimensions of the first matrix: ";
		cin >> m1Rows >> m1Cols;
		cout << endl;
		cout << "Input the first matrix: " << endl << endl;
		flag1 = 0;
		for( int i = 0; i < m1Rows; i++){
			for(int j = 0; j < m1Cols; j++){
				cin >> matrix1[i][j];
				if(matrix1[i][j] == 0 || matrix1[i][j] == 1)
					flag1++;
			}
		}
		cout << endl;
	
		cout << "Input the dimensions of the second matrix: ";
		cin >> m2Rows >> m2Cols;
		cout << endl;
		cout << "Input the second matrix: " << endl << endl;
		flag2 = 0;
		for( int i = 0; i < m2Rows; i++){
			for(int j = 0; j < m2Cols; j++){
				cin >> matrix2[i][j];
				if(matrix2[i][j] == 0 || matrix2[i][j] == 1)
					flag2++;
			}
		}
		cout << endl << endl;
	
		//Calling the matrix operation functions
		Sum( matrix1, m1Rows, m1Cols, matrix2, m2Rows, m2Cols);
		BoolAnd( matrix1, m1Rows, m1Cols, matrix2, m2Rows, m2Cols);
		BoolOr( matrix1, m1Rows, m1Cols, matrix2, m2Rows, m2Cols);
		BoolMultiply( matrix1, m1Rows, m1Cols, matrix2, m2Rows, m2Cols);
		Product( matrix1, m1Rows, m1Cols, matrix2, m2Rows, m2Cols);
		
		//Asking for a decsion again
		cout << "Which of the following do you wish to do:" << endl << endl;
		cout << "(p) Perform matrix operations" << endl << endl;
		cout << "(q) Quit" << endl << endl;
		cin >> userChoice;
		cout << endl;
	}
	
	cout << "Goodbye" << endl;	
	
	return 0;
}

//Function definition for summing
void Sum( int matrix1[][MAX_SIZE] /*IN*/, int m1Rows /*IN*/, int m1Cols /*IN*/, int matrix2[][MAX_SIZE] /*IN*/, int m2Rows /*IN*/, int m2Cols /*IN*/){
	
	int tempMatrix[MAX_SIZE][MAX_SIZE];					//Temporary matrix to hold the answer of the sum
	
	//Checking to make sure the dimensions match and summing if they do
	if(m1Rows == m2Rows && m1Cols == m2Cols){
		for(int i =0; i < m1Rows; i++){
			for(int j = 0; j < m1Cols; j++){
				tempMatrix[i][j] = matrix1[i][j] + matrix2[i][j];		//Summing element by element and putting the answer in the temp matrix
			}
		}
		//Outputting the contents of the temp matrix, the sum of the matrices
		cout << "sum:" << endl;
		for(int i =0; i < m1Rows; i++){
			for(int j = 0; j < m1Cols; j++){
				cout << tempMatrix[i][j];
				cout << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}
	//Printed if the matrices could not be summed
	else{
		cout << "sum:  Unable to perform this operation because the dimensions are incompatible" << endl << endl;
	}
	
	return;
}

//Function definition for boolean and
void BoolAnd( int matrix1[][MAX_SIZE] /*IN*/, int m1Rows /*IN*/, int m1Cols /*IN*/, int matrix2[][MAX_SIZE] /*IN*/, int m2Rows /*IN*/, int m2Cols /*IN*/){
	
	int tempMatrix[MAX_SIZE][MAX_SIZE];					//Temp matrix for storing the result
	
	//Checking to see if the matrices have the correct dimensions and if they are boolean
	if(m1Rows == m2Rows && m1Cols == m2Cols){
 		if(flag1 == m1Rows * m1Cols && flag2 == m2Rows * m2Cols){
			for(int i = 0; i <m1Rows; i++){
				for(int j = 0; j < m1Cols; j++){
					if(matrix1[i][j] == 1 && matrix2[i][j] == 1)
						tempMatrix[i][j] = 1;
					else
						tempMatrix[i][j] = 0;
				}
			}
			//Outputting the contents of the temp matrix
			cout << "boolean and:" << endl;
			for(int i =0; i < m1Rows; i++){
				for(int j = 0; j < m1Cols; j++){
					cout << tempMatrix[i][j];
					cout << ' ';
				}
				cout << endl;
			}
			cout << endl;
		}
		//Printed if the matrices are not boolean
		else{
			cout << "boolean and:  Unable to perform this operation because the matrices are not boolean" << endl << endl;
		}
	}
	//Printed if the matrices were incompatible 
	else{
		cout << "boolean and:  Unable to perform this operation because the matrices are incompatible" << endl << endl;
	}
	
	return;
}

//Function definition for boolean or
void BoolOr( int matrix1[][MAX_SIZE] /*IN*/, int m1Rows /*IN*/, int m1Cols /*IN*/, int matrix2[][MAX_SIZE] /*IN*/, int m2Rows /*IN*/, int m2Cols /*IN*/){
	
	int tempMatrix[MAX_SIZE][MAX_SIZE];					//Temp matrix for storing the result
	
	//Checking to see if the matrices have the correct dimensions and if they are boolean
	if(m1Rows == m2Rows && m1Cols == m2Cols){
 		if(flag1 == m1Rows * m1Cols && flag2 == m2Rows * m2Cols){
			for(int i = 0; i <m1Rows; i++){
				for(int j = 0; j < m1Cols; j++){
					if(matrix1[i][j] == 1 || matrix2[i][j] == 1)
						tempMatrix[i][j] = 1;
					else
						tempMatrix[i][j] = 0;
				}
			}
			//Outputting the contents of the temp matrix
			cout << "boolean or:" << endl;
			for(int i =0; i < m1Rows; i++){
				for(int j = 0; j < m1Cols; j++){
					cout << tempMatrix[i][j];
					cout << ' ';
				}
				cout << endl;
			}
			cout << endl;
		}
		//Printed if the matrices are not boolean
		else{
			cout << "boolean or:  Unable to perform this operation because the matrices are not boolean" << endl << endl;
		}
	}
	//Printed if the matrices were incompatible 
	else{
		cout << "boolean or:  Unable to perform this operation because the matrices are incompatible" << endl << endl;
	}
	
	return;
}

//Function definition for boolean multiply
void BoolMultiply( int matrix1[][MAX_SIZE] /*IN*/, int m1Rows /*IN*/, int m1Cols /*IN*/, int matrix2[][MAX_SIZE] /*IN*/, int m2Rows /*IN*/, int m2Cols /*IN*/){
	
	int tempMatrix[MAX_SIZE][MAX_SIZE];				//Temp matrix for result storage
	
	//Checking for correct dimensions and boolean matrix
	if( m1Cols == m2Rows){
		if(flag1==m1Rows * m1Cols && flag2 == m2Rows * m2Cols){
			for(int i = 0; i < m1Rows; i++){
				for(int j = 0; j < m2Cols; j++){
					tempMatrix[i][j] = 0;
					for(int k = 0; k < m2Rows; k ++){
						if(matrix1[i][k] == 1 && matrix2[k][j] == 1){
							tempMatrix[i][j] = 1;
						}
					}
				}
			}
			//Outputting the contents of the temp matrix
			cout << "boolean multiply:" << endl;
			for(int i =0; i < m1Rows; i++){
				for(int j = 0; j < m2Cols; j++){
					cout << tempMatrix[i][j];
					cout << ' ';
				}
				cout << endl;
			}
			cout << endl;
		}
		//Printed if the matrices are not boolean
		else{
			cout << "boolean multiply:  Unable to perform this operation because the matrices are not boolean" << endl << endl;
		}
	}
	//Printed if the dimensions are not compatible
	else{
		cout << "boolean multiply:  Unable to perform this operation because the matrices are incompatible" << endl << endl;
	}
	
	return;
	
}

//Function definition for product
void Product( int matrix1[][MAX_SIZE] /*IN*/, int m1Rows /*IN*/, int m1Cols /*IN*/, int matrix2[][MAX_SIZE] /*IN*/, int m2Rows /*IN*/, int m2Cols /*IN*/){
	
	int tempMatrix[MAX_SIZE][MAX_SIZE];				//Temp matrix for result storage
	
	//Checking for correct dimensions 
	if( m1Cols == m2Rows){
		for(int i = 0; i < m1Rows; i++){
			for(int j = 0; j < m2Cols; j++){
				tempMatrix[i][j] = 0;
				for(int k = 0; k < m2Rows; k++){
					tempMatrix[i][j] = tempMatrix[i][j] + matrix1[i][k] * matrix2[k][j];
					
				}
			}
		}
		//Outputting the contents of the temp matrix
		cout << "multiply:" << endl;
		for(int i =0; i < m1Rows; i++){
			for(int j = 0; j < m2Cols; j++){
				cout << tempMatrix[i][j];
				cout << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}
	//Printed if the dimensions were incompatible
	else{
		cout << "multiply:  Unable to perform this operation because the dimensions are incompatible" << endl << endl;
	}
	
	return;
}