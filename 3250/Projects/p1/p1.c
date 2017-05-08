//Author: Ross Bearden
//Class: 3250
//Lab: p1
//Purpose: To learn forking and signal handeling

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void intHandler();
void quitHandler();
void childHandler();
void user1Handler();
void user2Handler();

int child, parent, status;

int main(){
	parent = getpid();
	
	if((child = fork()) == 0){
		signal(SIGUSR1, user1Handler);
		signal(SIGUSR2, user2Handler);
	}
	
	else if ( parent > 0){
		printf("Parent: %d\n", parent);
		printf("Child: %d\n", child);
		
		signal(SIGINT, intHandler);
		signal(SIGCHLD, childHandler);
		signal(SIGQUIT, quitHandler);
		
	}
	else{
		printf("The fork failed \n");
		exit(-1);
	}
	for(;;);
	exit(0);
}

void user1Handler(){
	printf("Child pid= %d\n", getpid());
}

void user2Handler(){
	printf("THe child has been terminated \n");
	exit(0);
}

void intHandler(){
	printf("Use SIGQUIT signal to terminate \n");
	
}
		
void quitHandler(){
	kill(child, SIGUSR2);
	
}

void childHandler(){
	wait(&status);
	printf("Child was terminated with status = %d\n", status);
	printf("Child pid was = %d\n", child);
	exit(0);
}