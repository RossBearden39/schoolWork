//Aurhtor: Ross Bearden
//Project: Lab Sorting
//File: mergesort.cpp
//Purpose: Supplies the function body for mergesort and mergeSortMain
//		   Also contians the definition and implementation of the merge function

#include "mergesort.h"

//This function starts a clock and calls mergeSortMain, then stops the clock when it returns 
//and outputs the time to stdout
void mergesort(int * array, int arraySize){
	clock_t begin, end;		//Clocks for tracking the timing of the search algorithm
	int * tempArray = new int[arraySize];			//temp array for merge function
	begin = clock();
	mergeSortMain(array, tempArray, 0, arraySize-1);
	end = clock();
	delete [] tempArray;
	std::cout << '\t' << diffClocks(end,begin);

}

//Merge Function
//Takes a int pointer to an array, the first, and last indices to be merged together
void merge(int * array, int * tempArray,  int first, int last){
	int arrayOne = first;					//Index for left half of array
	int midIndex = (first + last) / 2;		//Mid index of array
	int arrayTwo = midIndex + 1;			//Index for right half of array
	//Walk down array and insert smaller element from either side
	for(int i = first; i <= last; i++){
		//If left number is smaller than right number and left index is still in left side
		//Insert left number into temp array and advance left index. Else insert right number and advance right index
		if(array[arrayOne] <= array[arrayTwo]){
			if(arrayOne <= midIndex){
				tempArray[i] = array[arrayOne];
				arrayOne++;
			}
			else{
				tempArray[i] = array[arrayTwo];
				arrayTwo ++;
			}
		}
		//If right number is smaller than left number and right index is still in right side
		//Insert right number into temp array and advance right index. Else insert left number and advance left index
		else if(array[arrayTwo] < array[arrayOne]){
			if(arrayTwo <= last){
				tempArray[i] = array[arrayTwo];
				arrayTwo++;
			}
			else{
				tempArray[i] = array[arrayOne];
				arrayOne++;
			}
		}
	}
	//Copy temp array back into original array
	for(int i = first; i < last+1; i++){
		array[i] = tempArray[i];
	}
}

//This is the main merge sorting function
//Takes a int pointer to and array, the first, and the last arguments in the segment to be sorted
void mergeSortMain(int * array, int * tempArray, int first, int last){
	int midIndex = -1;
	//base case
	if(first < last){
		midIndex = (first+last)/2;
		//Sorts left half of array
		mergeSortMain(array, tempArray, first, midIndex);
		//Sorts right half of array
		mergeSortMain(array, tempArray, midIndex + 1, last);
		//Merges the arrays back together
		merge(array, tempArray, first, last);
	}
}

