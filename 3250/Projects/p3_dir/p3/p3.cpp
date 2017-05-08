//Author: Ross Bearden
//Class: CSCI 3250
//Projects: p3
//Purpose: Demonstrate simple usage of pthreads

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

//Declaration for calcPrime
void* CalcPrime(void * digit);

//Shared variable
int numPrimes;

//Mutex
pthread_mutex_t r;


int main(int argc, char* argv[]){
	
	//Return code
	int rc;
	//Thread id
	pthread_t thread_Id;
	//Initialize shared variable and mutex lock
	numPrimes = 0;
	pthread_mutex_init(&r, NULL);

	//Create enough threads for the amount of input
	for(int i = 0; i < (argc -1); i++){
		
		int j =atol(argv[i+1]);
		rc = pthread_create(&thread_Id,NULL,CalcPrime,(void *)j);
		if(rc != 0){
			printf("Create pthread error!\n");
			return(1);
		}	
		//Joins the pthread back with the original thread
		pthread_join(thread_Id,NULL);
		
		printf("The total number of primes for was: %d\n", numPrimes);
	}
	
	
	
	return 0;
}

//Function that the threads use to calculate the prime numbers 
void* CalcPrime(void* digit){
	//Prime counter
	int count = 0;
	int i;
	for(i = int(digit); i <(int(digit)+10000-1); i++){
		count = 0;
		if(int(digit) == 1 || int(digit) == 2){
			count =2;
		}
		else{
			int j;
			for(j = 1; j <=i; j ++){
				if(i%j==0){
					count++;
				}
			}
		}
		if(count ==2){
			//Accesses the shared variable
			pthread_mutex_lock(&r);
			numPrimes += count;
			pthread_mutex_unlock(&r);
		}
		//printf("Number of primes: %d\n", numPrimes);
	}
}


