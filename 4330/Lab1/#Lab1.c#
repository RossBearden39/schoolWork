/* Lab1: Integration using the trapizoid rule
   Author: Samuel Ross Bearden
   Date: 1/31/17
   Purpose: To calculate the area under the curve sqrt(4-x*x)
            from 0 to 2.
	    Using the trapezoid rule, there are no more than
	    50 partitions
*/

#include <stdio.h>
#include <pthread.h>  //Used for threads
#include <math.h>     //Needed for sqrt()

float width;	      	       	 // width for each segment
float rsum = 0.0;    		 // final result
pthread_mutex_t mutex1;  	 // mutual exclusion variable

//Calculate one segment of the area using trapeziod rule
void *trapeziod(void *thing)
{
	float partial_sum = 0.0;	 //single segment sum
	int me = *((int *)thing);	 //Determines segment
	double h1;			 //First height at start of segment
	double h2;			 //Second height at end of segment

	//Calcualte first height
	h1 = sqrt(4.0 - me*width*me*width);

	//Calculate second height
	h2 = sqrt(4.0 - (me*width +width)*(me*width+width));

	//Calculate partial_sum
	partial_sum = .5*((h1+h2)*width);

	//Increment the global area
	pthread_mutex_lock(&mutex1);
		rsum += partial_sum;
	pthread_mutex_unlock(&mutex1);

}

/******** main ********/

main()
{

	int num_proc;			//number of threads
	int i;				//loop variable
	pthread_t threadId[50];		//array for thread ids
	int segNum[50]; 		//Array for segments

	//initialize mutual exclusion variable
	pthread_mutex_init(&mutex1, NULL);

	//Determine number of partitions/threads
	printf("Input the number of partitions\n");
	scanf("%d", &num_proc);

	//Determine width
	width = 2.0/num_proc;

	//Create threads
	for(i = 0; i<num_proc; i++)
	{
		segNum[i] = i;
		if(pthread_create(&threadId[i], NULL, trapeziod, (void *)&segNum[i]) != 0)
				perror("Pthread_create fails");
	}

	//Join all threads before proceeding
	for(i = 0; i < num_proc; i++)
	      if(pthread_join(threadId[i],NULL) != 0)
	      		perror("Pthread_join fails");

	//Print result
	printf("The area under the curve is %f\n", rsum);

	return(0);

}
