//Author: Ross Bearden
//Class: CSCI 3250
//Assignment: p4
//Purpose: See the differecnes between static and dynamic linking and dynamic loading

#include <stdio.h>
#include <stdlib.h>


//Sub routine for pthread
void* Sub(void * arg);
int pthread_create(pthread_t*, pthread_attr_t*, void *, void *); 
void pthread_join(pthread_t, void *);
void pthread_exit(void*);
int main(){
	//Return code for pthread creation
	int rc;
	
	//Pthread Id
	pthread_t thread_ID;
	
	//Create a pthread
	rc = pthread_create(&thread_ID, NULL, Sub,(void*)NULL);
	
	//Join the thread back
	pthread_join(thread_ID,NULL);
	pthread_exit(NULL);
}

//Pthread Sub routine
void* Sub(void * arg){
	printf("Thread is in sub\n");
	return;
}
	