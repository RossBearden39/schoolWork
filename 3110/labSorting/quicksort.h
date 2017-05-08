//Aurhtor: Ross Bearden
//Project: Lab Sorting
//File: quicksort.h
//Purpose: Supplies the function definition for quicksort

#include "diffClocks.h"

//This is the function definition for the outer quick sort function
//Starts a clock and calls the main quickSort function
void quicksort(int * array, int arrraySize);

//This is the definition for the main quicksort function
//Utilizes a function called partition to sor the array
void quickSortMain(int * array, int first, int last);