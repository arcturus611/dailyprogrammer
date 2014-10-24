
#include <stdio.h>
#include <stdlib.h> // for srand, rand
#include <time.h>
#include "quickSort.h"
#define LENGTH 25 

int main(int argc, char** argv){

	int x[LENGTH]; 
	int i;
	srand(time(NULL)); 

	printf(" \n The given array is : "); 
	for(i =0; i< LENGTH; i++){
		x[i] = rand()%50 + 1; 
		printf("%d ", x[i]); 
	}
	printf("\n"); 

	quicksort(x, 0, LENGTH-1);

	printf(" \n The sorted array is : "); 
	for(i =0; i< LENGTH; i++){
		printf("%d ", x[i]); 
	}
	printf("\n"); 
}
