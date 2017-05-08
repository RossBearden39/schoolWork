//Aurhtor: Ross Bearden
//Project: Lab Sorting
//File: mergesortort.h
//Purpose: Supplies the function definition for mergesort and merge

#include "diffClocks.h"

//This function starts a clock and calls mergeSortMain, then stops the clock when it returns 
//and outputs the time to stdout
void mergesort(int * array, int arraySize);

//This is the main merge sorting function
void mergeSortMain(int * array, int * tempArray, int first, int last);


