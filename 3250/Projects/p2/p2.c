//Author: Ross Bearden
//Date: 9-30-15
//class: CSCI 3250
//Assignment: p2
//Purpose: Practice 

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string>
#include <iostream>

int rc, status, sock[2];

int main(){
	//Buffer for reading and writing
	char buff[101];
	
	//Creates Socket Pair
	socketpair(AF_UNIX, SOCK_STREAM, 0, sock);
	
	rc = fork();
	
	//parent Process
	if(rc > 0){
		std::string input;
		
		getline(std::cin, input);
		
		int bytes = input.size();
		
		while(std::cin){
			int q;
			for(q = 0; q < bytes; q++){
				buff[q] = input[q];
			}
			
			buff[bytes] = '\0';
			
			write(sock[0], buff, 100);
			
			read(sock[0],buff, 100);
			
			printf("%s\n", buff);
			
			getline(std::cin, input); 
			
			bytes = input.size();
		}
		
		shutdown(sock[0], SHUT_RDWR);
		waitpid(rc, &status, 1);
		printf("Child was terminated with status = %d\n" , status);
		printf("Child pid was = %d\n", rc);
	}
	
	else if(rc == 0){
		int getOut;
		
		while(getOut = read(sock[1], buff, 100) > 0){
			
			int i;
			for(i = 0; i < 100; i++){
				buff[i] = toupper(buff[i]);
			}
			write(sock[1], buff, 100);
		}
		if(getOut ==0){
			exit(0);
		}
	}
	
	else{
		printf("The fork failed\n");
		exit(-1);
	}
	exit(0);
}