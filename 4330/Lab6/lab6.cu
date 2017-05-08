/* Author: Ross Bearden
   Instructor: Dr. Pettey
   Class: CSCI 4330
   Date: 05/03/17

   Purpose: This program will calculate the sum of two matrices using GPUs and the cuda 
            language to do the calculations
*/

#include <stdio.h>
#include <stdlib.h>


__global__ 
void vectorAdd(
  int* vector1,
  int* vector2,
  int* vectorResult)
{
  vectorResult[threadIdx.x] =
    vector1[threadIdx.x] +
    vector2[threadIdx.x];
}

int main(int argc, char* argv[])
{
  int rows = 16;
  int columns = 32;
  int i,j;
  int firstArray[rows][columns];
  int secondArray[rows][columns];

  //Read the matrices
  for(i = 0; i < rows; i++){
    for(j = 0; j < columns; j++){
      scanf("%d", &firstArray[i][j]);
    }
  }

  for(i = 0; i < rows; i++){
    for(j = 0; j < columns; j++){
      scanf("%d", &secondArray[i][j]);
    }
  }
/*
  for(i = 0; i < rows; i++){
    for(j = 0; j < columns; j++){
      printf("%d", firstArray[i][j]);
    }
  }

  for(i = 0; i < rows; i++){
    for(j = 0; j < columns; j++){
      printf("%d", secondArray[i][j]);
    }
  }
  */

  int* vector1;
  int* vector2;
  int sizeOfVector = 512;
  int* deviceResults;
  int hostResults[512];

  cudaMalloc((void**) &vector1, sizeof(int) * sizeOfVector);
  cudaMalloc((void**) &vector2, sizeof(int) * sizeOfVector);
  cudaMalloc((void**) &deviceResults, sizeof(int) * sizeOfVector);
  

  cudaMemcpy(vector1, firstArray, sizeof(int) * sizeOfVector,
    cudaMemcpyHostToDevice);
  cudaMemcpy(vector2, secondArray, sizeof(int) * sizeOfVector,
    cudaMemcpyHostToDevice);
  vectorAdd<<<1, sizeOfVector>>> (vector1, vector2, deviceResults);
  cudaMemcpy(hostResults, deviceResults, sizeof(int) * sizeOfVector,
    cudaMemcpyDeviceToHost);

  for(i = 0; i < rows; i++){
   for(j = 0; j < columns; j++){
    printf("%i  ", hostResults[j]);
    }
   printf("\n");
  }

  cudaFree(vector1);
  cudaFree(vector2);
  cudaFree(deviceResults);

  return 0;
}
