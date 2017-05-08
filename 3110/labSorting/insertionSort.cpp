//Aurhtor: Ross Bearden
//Project: Lab Sorting
//File: insertionSort.cpp
//Purpose: Supplies the function body for insertionSort
#include "insertionSort.h"

//This function starts a clock the calls the insertion sort method and stops the clock after it returns
void insertionSort(int * array, int arraySize){
	clock_t begin, end;				//clock variables that will be used to determine the sorting time
	begin = clock();
	insertionSortMain(array, arraySize);
	end = clock();

	std::cout << "\t" << diffClocks(end, begin);
}





//This function implements an insertion sort on the recieved array
void insertionSortMain(int* array, int arraySize){

	int itemToInsert = -1;			//Holds the next item to be inserted into the sorted portiojn of the array

	int j = -1;						//Index for inner loop
	//Outer loop for stepping through array
	for( int i = 1; i < arraySize; i++){
		itemToInsert = array[i];

		//Set inner loop index
		j = i;
		while(j > 0 && array[j-1] > itemToInsert){
			array[j] = array[j-1];
			j--;

		}
		array[j] = itemToInsert;
	}
}