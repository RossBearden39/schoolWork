/*Author: Ross Bearden
  Class: CSCI 4330
  Date: 4/5/17
  Project: Lab 5

  Purpose: Calculate the the integral of (3sin(x/2)^3)^(1/2) from 0 to PI using the rectangular integration method.
  	       MPICH protocols are used, and the user must input the number of intervals they want upon execution
*/

#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define PI 3.14159265

int main(int argc, char * argv[])
{
	int nProc, myRank;
	double totalSum = 0.0;			//Holds final result					
	MPI_Status status;

	//Needed for all MPICH programs
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nProc);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

	float width = PI/nProc;			//Width of each interval

	double mySum = 0.0;				//Each rank has its own sum
	double height = 0.0;			//Each ranks rectangle height
	double mid = 0.0;				//Mid point of rectangle

	//find mid point
	mid = myRank*width + width/PI;

	//Find rectangle height
	height = sqrt(3 * (sin(mid/2)*sin(mid/2)*sin(mid/2)));

	mySum = height*width;

	//Adds all individual sums into final sum
	//Process zero starts the ring add
	if(myRank == 0){
		MPI_Send(&mySum, 1, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD);
		MPI_Recv(&totalSum, 1, MPI_DOUBLE, nProc -1, 1, MPI_COMM_WORLD, &status);
		printf("The intergral is equal to %f\n", totalSum);
	}	
	else{
		MPI_Recv(&totalSum, 1, MPI_DOUBLE, myRank -1, 1, MPI_COMM_WORLD, &status);
		totalSum += mySum;
		if(myRank == nProc -1)
			MPI_Send(&totalSum, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
		else
			MPI_Send(&totalSum, 1, MPI_DOUBLE, myRank +1, 1, MPI_COMM_WORLD);
	}
	/*
	//Rank 0 will print result
	if(myRank == 0){
		printf("The integral is equal to %f\n", totalSum);
	}
	*/
	//Needed to end MPICH programs
	MPI_Finalize();
} 
