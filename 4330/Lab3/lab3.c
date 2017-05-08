/*
  Author: Ross Bearden
  Class: CSCI 4330
  Date: 3/1/17
  Lab 3

  Purpose: The lab servers to simulate a the transactions of a very small ATM only bank in one day using muti-threading

 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

//Global Arrays to hold file pointers
FILE *atmFiles[3];
FILE *custFiles[4];                  
//struct for atm data
struct transaction{
  int atmNum;
  char accNum[10];
  char transType;
  float amount;
  float currBal;
};

//Character arrays for the account numbers. These are used to keep leading zeros
char accounts[4][10];

//Arrays to hold each accounts current balance
float currBal[4];

//Array of transaction structs to act as mains work queue
struct transaction queue[3];

//Tracker for mains work queue
int queueCount = 0;

//Tracker for finished threads
int doneThreads = 0;
int waitThread = 0;
//Mutex variable and condition variable
pthread_mutex_t mv = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
pthread_cond_t cvT =PTHREAD_COND_INITIALIZER;

//Function for the pthreads to execute
//Each will be working as a seperate ATM making transaction based on their file
void * atm(void *mine){
  //Turn void pointer input into int for thread id
  int me = *((int *)mine);
  int i = 0;                           //Indexing variable
  char accNum[20];                     //Current account numbers read from file
  char transType;                      //Current transaction type
  float changeAmt = 0;                   //Amount for withdrawl or deposit
  int sleepTime = 0;                   //Amount of time to sleep between transactions

  char line[256];                      //Holds whole line of input
  int  lineRead;
  //Loop until whole file has been read
  while(fgets(line, 256, atmFiles[me-1]) != NULL){
    lineRead = 1;
    while(lineRead == 1){
    if(queueCount < 3){
      //Read data in for file
      sscanf(line, "%s %c %f %d", accNum, &transType, &changeAmt, &sleepTime);
  
      //Find out which account is being accessed and update information
      if(strcmp(accNum, accounts[0]) == 0) i = 0;
      else if(strcmp(accNum, accounts[1]) == 0) i = 1;
      else if(strcmp(accNum, accounts[2]) == 0) i = 2;
      else if(strcmp(accNum, accounts[3]) == 0) i = 3;
      else{
	printf("The account number read does not match any accounts\n");
      }
  
      if(transType == 'w'){
	currBal[i] -= changeAmt;
      }
      else{
	currBal[i] += changeAmt;
      }
      if(currBal[i] < 0){
	printf("Accout: %s is overdrawn and has been charged $10\n", accNum);
	currBal[i] -= 10;
      }
      //Print current account and balance
      printf("Account: %s has a current balance of %f\n", accNum, currBal[i]);
      //Mutex lock for updating mains queue
    
      pthread_mutex_lock(&mv);

         queue[queueCount].atmNum = me;
         strcpy(queue[queueCount].accNum, accNum);
         queue[queueCount].transType =  transType;
         queue[queueCount].amount = changeAmt;
         queue[queueCount].currBal = currBal[i];
         queueCount++;
	 lineRead = 0;
      pthread_mutex_unlock(&mv);
    }
       //Wake up main if queue is full
    else{
      pthread_mutex_lock(&mv);
      waitThread++;
      if(waitThread == 3){
         pthread_cond_signal(&cv);
	 while(pthread_cond_wait(&cvT, &mv) != 0);
	 waitThread = 0;
      }
      else{
	while(pthread_cond_wait(&cvT, &mv) != 0);
      }
      pthread_mutex_unlock(&mv);
    }
    }
    //Sleep
    sleep(sleepTime);
  }
  //Thread is finished with file
  doneThreads++;
  printf("Done threads: %d\n" , doneThreads);
  pthread_cond_signal(&cv);
  return;
}

//Main start
int main(/*int argc, char **argv*/){

  float beginBal[4];                 //Array for customer beginning balances
  pthread_t threadId[3];             //Array for thread ids
  int i;                             //Looping variable
  
  //Open cust files and read account numbers
  custFiles[0] = fopen("cust0.dat", "r");
  custFiles[1] = fopen("cust1.dat", "r");
  custFiles[2] = fopen("cust2.dat", "r");
  custFiles[3] = fopen("cust3.dat", "r");

  for(i = 0; i < 4; i++){
    fscanf(custFiles[i], "%s" "%f", accounts[i], &beginBal[i]);
  }
  //Close and reopen files for appending. Also initialize currBal array
  for(i = 0; i < 4; i++){
    fclose(custFiles[i]);
    currBal[i] = beginBal[i];
  }
  custFiles[0] = fopen("cust0.dat", "a");
  custFiles[1] = fopen("cust1.dat", "a");
  custFiles[2] = fopen("cust2.dat", "a");
  custFiles[3] = fopen("cust3.dat", "a");

  //Open atm files
  atmFiles[0] = fopen("atm0.dat", "r");
  atmFiles[1] = fopen("atm1.dat", "r");
  atmFiles[2] = fopen("atm2.dat", "r");
  
  //Create threads
  for(i = 0; i < 3; i++){
    if(pthread_create(&threadId[i], NULL, atm, (void *)&i) != 0){
      perror("Pthread_create failed");
      exit(0);
    }
  }    
  
  //Main sleeps until work queue is full then wakes up, empties queue and goes back to sleep
  while(doneThreads < 3){
    //Sleep until queue is full
    pthread_mutex_lock(&mv);

    while(queueCount < 2 && doneThreads < 3){

      pthread_cond_wait(&cv, &mv);
    }
    //Add to customer files and empty queue
    int j = 0;
    for(i = 0; i < 3; i++){
      if(strcmp(queue[i].accNum, accounts[0]) == 0) j = 0;
      else if(strcmp(queue[i].accNum, accounts[1]) == 0) j = 1;
      else if(strcmp(queue[i].accNum, accounts[2]) == 0) j = 2;
      else j = 3;
      fprintf(custFiles[j], "%d\t %c\t %f\t %f\n", queue[i].atmNum, queue[i].transType, queue[i].amount, queue[i].currBal);
    }
    queueCount = 0;
    pthread_cond_broadcast(&cvT);
    pthread_mutex_unlock(&mv);
  }

  //Main waits for threads to join back
  for(i = 0; i < 1; i++){
    if(pthread_join(threadId[i], NULL) !=0){
      perror("Pthread_join failed");
      exit(0);
    }
  }
  
  //Close all files
  for(i = 0; i < 4; i++){
    fclose(custFiles[i]);
  }
  for(i = 0; i < 3; i++){
    fclose(atmFiles[i]);
  }
  //Main Prints out all customers account numbers and final balance
  for(i = 0; i < 4; i++){
    printf("The ending balance for %s is %f\n", accounts[i], currBal[i]);
  }

    return 0;
}
