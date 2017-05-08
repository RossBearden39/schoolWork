//Author: Ross Bearden
//Class: 3250
//Assignment: p6
//Purpose: Learning to use shared memory between programs running on the same machine

#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

int main(int argc, char* argv[]){
	
        //Create necessary variables for working with shared memory	
        int rc, shm_size, shmfd,errno;
	int *count;
        void *shmptr;
        sem_t *semptr;
        //Get page size
        shm_size = sysconf( _SC_PAGE_SIZE );

	//Create a shared memory segement and store the file descriptor to it
	shmfd = shm_open("srb5q_shm", O_CREAT|O_EXCL|O_RDWR|O_TRUNC, S_IRWXU);
	if(shmfd == -1){
		printf("%s\n", "Memory was opened");
		shmfd = shm_open("srb5q_shm", O_RDWR, S_IRWXU);
		//Map the shared memory into address space
		shmptr = mmap((void *)NULL, shm_size, PROT_WRITE|PROT_READ, MAP_SHARED, shmfd, 0);
		count = (shmptr + (sizeof(int) * 101));
	}
	//Used if memory did not exist
	else{
		printf("%s\n", "Memory was opened");
		//Resize the shared memory and map it into memory
		rc = ftruncate(shmfd,shm_size);
		shmptr = mmap((void *)NULL, shm_size, PROT_WRITE|PROT_READ, MAP_SHARED, shmfd, 0);
		//Place the number count in the the shared memory if it does not already exist
		count = (shmptr + (sizeof(int) * 101));
		*count = 0;
	}
		
	//Create semaphore
	semptr = sem_open("srb5q_sem", O_CREAT, 0644, 0);
        //Add numbers to the shared memory space and update the total count
	int tempAdd = 0;
        sem_post(semptr);
        int i = 1;
        while(i < argc){
		tempAdd = atoi(argv[i]);
		*((int*)(shmptr + sizeof(int) * (*count))) = tempAdd;
		(*count)++;
		i++;
	}
	
	//Write to the shared memory all numbers that were read in
	//write(shmfd, buff, (sizeof(int) * (*count)));
	//Sync all new values
	msync(shmptr, (sizeof(int) * (*count)),MS_SYNC);
	sem_close(semptr);
	//Close the shared memory file descriptor
	close(shmfd);
	//Unmap the shared memory 
	munmap(shmptr, shm_size);
	
	return 0;
}