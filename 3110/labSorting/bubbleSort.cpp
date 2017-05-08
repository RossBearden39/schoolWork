//Aurhtor: Ross Bearden
//Project: Lab Sorting
//File: bubbleSort.cpp
//Purpose: Supplies the function body for bubbleSort
#include "bubbleSort.h"
//This function starts a clock the calls the bubble sort method and stops the clock after it returns
void bubbleSort(int * array, int arraySize){
	clock_t begin, end;				//clock variables that will be used to determine the sorting time
	begin = clock();
	bubbleSortMain(array, arraySize);
	end = clock();

	std::cout << "\t" << diffClocks(end, begin);
}

//This function implements a bubble sort on the recieved array
void bubbleSortMain(int * array, int arraySize){

	int itemToMove = -1;			//Holds the items currently being moved
	//Outer loop steps through the array one element at a time
	for(int i = arraySize - 1; i >= 1; i--){

		//Inner loop bubbles up the elements to their correct place in the array
		for(int j = 0; j < i; j++){
			//If the left > right, swap the two
			if(array[j] > array[(j+1)]){
				itemToMove = array[(j+1)];
				array[(j+1)] = array[j];
				array[j] = itemToMove;
			}
		}
	}

}