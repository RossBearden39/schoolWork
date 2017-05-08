/*   Project: Lab2
     Author: Ross Bearden
     Date: Feburary 15, 2017
     Purpose: The purpose of this project is to use a modified Gaussian Elimination 
              algorithm to find the unknowns in a system of equations.

	      For this project we will be assuming that there will be no more than 10 equations
	      with 10 unknows. We will also be assuming that there is a solution to the system.

	      We will be using threads to solve all of the columns at one time for each step.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mv;            //mutex variable
pthread_cond_t cv;             //condition variable for threads
pthread_cond_t cvM;            //condition variable for main

int rows;                 //number of rows for the array
int doneThreads = 0;      //Keeps track of threads that have finished current operations
int currRow = 0;          //Tracks the current row in the threads
float matrix[11][11];     //Matrix to hold up to 10 equations and B matrix
float divisor;            //Holds current divisor
float multiplier[9];     //Matrix to hold the mutipliers for the rows

/* Function that the threads run on the coefficent matrix
   After main has determined the divisor and multiplier for the current row,
   each thread will apply it to their respective column. Then they will sleep and wait for
   main.
*/

void *columnOp(void *mine)
{
  //Cast as int pointer then dereference and assign
  int me = *((int *)mine);
  int i, j;
  while(currRow < rows){
    //First divide whole row by divisor
    matrix[currRow][me] = matrix[currRow][me]/divisor;
    //Now apply multipliers and add to respective rows
    j = 0;
    for(i = 0; i < rows; i++){
      if(i == currRow){}
      else{
	matrix[i][me] += (matrix[currRow][me] * multiplier[j]);
	j++;
      }
      //Need locking stuff and wake up main
      
   }
    //Wait for main to get new divisor and multipliers
      pthread_mutex_lock(&mv);
         doneThreads++;
	 if(doneThreads < rows+1){
	   while(pthread_cond_wait(&cv,&mv) != 0);
	 }
	 else{
	   pthread_cond_signal(&cvM);
	   currRow++;
	   while( pthread_cond_wait(&cv, &mv) != 0);
	 }
	 
      pthread_mutex_unlock(&mv);
  }
}


/********begin main********/
main()
{
  int i, j, mainCnt;                   /*loop variable*/
  pthread_t threadId[11];               /*array for thread Ids*/
  int colNum[11];                      /*array for column numbers*/

  //Initialize mutex and condition variable
  pthread_mutex_init(&mv, NULL);
  pthread_cond_init(&cv, NULL);
  pthread_cond_init(&cvM, NULL);
  
  //Determine number of equations and read in the array
  printf("Input the number of items: ");
  scanf("%d", &rows);

  printf("Input the A array\n");
  for(i = 0; i < rows; i++){
    for(j = 0; j < rows; j++){
      scanf("%f", &matrix[i][j]);
    }
  }

  printf("Input the B array\n");
  for(i = 0; i < rows; i++){
    scanf("%f", &matrix[i][rows]);
  }
  
      
	   
  /*
  printf("Current matrix\n");
  //Test that array entered right
  for(i = 0; i < rows; i++){
    for(j = 0; j < rows+1; j++){
      printf("%f\t", matrix[i][j]);
    }
    printf("\n");
  }
  */

  //Prime the main actions loop before threads are created
  divisor = matrix[0][0];
  for(i = 1; i < rows; i++){
    multiplier[i-1] = 0.0 - matrix[i][0];
  }
  mainCnt = 1;
  /*
  for(i = 0; i < rows - 1; i++){
    printf("%f\n", multiplier[i]);
  }
  */
  
  //Create threads
  for(i = 0; i <= rows; i++)
    {
      colNum[i] = i;
      if(pthread_create(&threadId[i], NULL, columnOp, (void *)&colNum[i]) != 0){
	perror("Pthread_create failed");
	exit(0);
      }
    }

  //Main finds divisors and multipliers here then sleeps
  while(mainCnt < rows){
    pthread_mutex_lock(&mv);
    //Makes main sleep and wait for threads to finish
    while(doneThreads < rows+1){
      pthread_cond_wait(&cvM, &mv);
    }
    if(mainCnt < rows){
      //Gets new divisor and multipliers
      divisor = matrix[mainCnt][mainCnt];
      j = 0;
      for(i = 0; i < rows; i++){
	//Skips over row the divisor was in
	if(i == mainCnt){}
	else{
	  multiplier[j] = 0 - matrix[i][mainCnt];
	  j++;
	}
      }
    }

    //Update counnters and wake threads11
      mainCnt++;
      pthread_cond_broadcast(&cv);
      doneThreads = 0;
      pthread_mutex_unlock(&mv);
  }
  //Janky fix for little problem with threads getting stuck asleep
  while(doneThreads < rows+1){
    sleep(1);
  }
  pthread_cond_broadcast(&cv);
  //Join back all threads
    for(i = 0; i <=rows; i++){
      if(pthread_join(threadId[i], NULL) !=0){
	perror("Pthread_join failed");
	exit(0);
      }
    }
  
  //Print final values
  for(i = 0; i < rows; i++){
    printf("%f\n", matrix[i][rows]);
  }
  
  return(0);
}
