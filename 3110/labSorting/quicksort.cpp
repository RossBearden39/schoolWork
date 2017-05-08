//Aurhtor: Ross Bearden
//Project: Lab Sorting
//File: quicksort.cpp
//Purpose: Supplies the function body for quicksort and quickSortMain
//Also includes a helper function called partiton

#include "quicksort.h"

//This is the function definition for the outer quick sort function
//Starts a clock and calls the main quickSort function
void quicksort(int * array, int arraySize){
	int first = 0;
	int last = arraySize -1;
	clock_t begin, end;				//clock variables that will be used to determine the sorting time
	begin = clock();				//Gets start time
	//Starts sort
	quickSortMain(array, first, last);
	end = clock();					//Gets end time
	//Outputs time the sorting took
	std::cout << "\t" << diffClocks(end, begin);
}

//This is the a helper function called partition
//It will choose a pivot and seperate the array into values less than the pivot and values greater than the pivot
//It will then place the pivot in its correct place and retrun the pivot
int partition(int * array, int first, int last){
	int pivot;						//Holds the value of the pivot
	int pivotIndex;					//Holds the index of pivot of the current array segment
	int midIndex = (first+last)/2;	
	//Pick pivot
	if(array[first] <= array[last] && array[first] >= array[midIndex]){
		pivotIndex = first;
	}
	else if(array[midIndex] >= array[first] && array[midIndex] <= array[last]){
		pivotIndex = midIndex;
	}
	else{
		pivotIndex = last;
	}
	pivot = array[pivotIndex];
	//Swap pivot out of the way
	int tempMove = array[first];
	array[first] = array[pivotIndex];
	array[pivotIndex] = tempMove;
	int partitionMarker = first;			//Divides the array into less than and greater than the pivot partitions
	//Move one item at a time from unknown portion of array into its proper partition
	for(int firstUnknown = first; firstUnknown <= last; firstUnknown++){
		if(array[firstUnknown] < pivot){
			partitionMarker++;
			tempMove = array[firstUnknown];
			array[firstUnknown] = array[partitionMarker];
			array[partitionMarker] = tempMove;
		}
	}
	pivotIndex = partitionMarker;
	tempMove = array[first];
	array[first] = array[partitionMarker];
	array[partitionMarker] = tempMove;
	return pivotIndex;
}

//This is the definition for the main quicksort function
//Utilizes a function called partition to sor the array
void quickSortMain(int * array, int first, int last){
	//base case
	if(first < last){
		int pivot = partition(array, first, last);
		quickSortMain(array, first, pivot-1);
		quickSortMain(array, pivot+1, last);
	}
}