//Author: Ross Bearden
//Class: 3250
//Project: p5
//Purpose: Work with shared memory

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

//Pointer to the shared memory
void * region;

int main(){
	//Id
	int rc, status, error;
	//Map a shared memory space
	region = mmap(NULL, (sizeof(int) + 4), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	//Put a int pointer in the mapped memory
	int *count = (int*)(region+4);
	//Initialize counter
	*count = 0;
	//Fork a child process
	rc = fork();
	
	//In parent
	if(rc > 0){
		wait(&status);
		printf("Count is: %d\n", *count);
	}
	//In child process
	else if(rc == 0){
		
		int i;
		for(i = 0; i <= 10000000; i++){
			(*(int*)(region+4)) = i;
		}
		exit(0);
	}
	//Fork failed
	else{
		printf("The fork failed \n");
		exit(-1);
	}	
	
	error = munmap(region, sizeof(int));	
	exit(0);
}



