//Author: Ross Bearden
//Class: CSCI 3250
//Assignment: p4
//Purpose: See the differecnes between static and dynamic linking and dynamic loading

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dlfcn.h>

//Sub routine for pthread
void* Sub(void * arg);

//Typedef statements
typedef int (*pthread_function)(pthread_t*, pthread_attr_t*, void*, void*);
typedef void (*pthread_function2)(pthread_t, void*);
//void pthread_exit(void*);

int main(){
	//Return code for pthread creation
	int rc;
	//Pthread Id
	pthread_t thread_ID;
	//Pointer to a libraby
	void * library;
	//Error checker
	const char * error;
	pthread_function createThread;
	pthread_function2 bringThread;
	//pthread_function exitThread;
	
	//Open the library
	library = dlopen("libpthread.so.0", RTLD_LAZY);
	//Test library
	if(library == NULL){
		fprintf(stderr, "Could not open      : %s\n", dlerror());
		exit(1);
	}
	dlerror();
	
	createThread = dlsym(library, "pthread_create");
	if(error = dlerror()){
		fprintf(stderr, "Could not find pthread_create: %s\n" , error);
		exit(1);	
	}
	dlerror();
	
	bringThread = dlsym(library, "pthread_join");
	if(error = dlerror()){
		fprintf(stderr, "Could not find pthread_join: %s\n" , error);
		exit(1);	
	}
	dlerror();
	
	/*exitThread = dlysm(threadStuff, "pthread_exit");
	if(error = dlerror()){
		fprintf(stderr, "Could not find pthread_exit: %s\n" , error);
		exit(1);	
	}
	dlerror();*/
	
	//Create a pthread
	rc = (*createThread)(&thread_ID, NULL, Sub,(void*)NULL);
	
	//Join the thread back
	(*bringThread)(thread_ID,NULL);
	//Exit pthread
	//(*finish)(NULL);
	
	
	//Closes the opened library
	dlclose(library);
	return 0;
}

//Pthread Sub routine
void* Sub(void * arg){
	printf("Thread is in sub\n");
	return;
}
	