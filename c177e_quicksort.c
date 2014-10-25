
#include <stdio.h>
#include <stdlib.h> // for srand, rand
#include <time.h>
//#include "quickSort.h"
#define LENGTH 25 

void swap(int* x, int idx1, int idx2){
	int temp = x[idx1]; 
	x[idx1] = x[idx2]; 
	x[idx2] = temp; 
}

int partition(int* a, int end1, int end2){
	int pivot = (end1+end2)/2; 
	int i;
	int newPivot = end1;  // this is what we need to calculate and return

	swap(a, pivot, end2); 

	for(i = end1; i<end2; i++){
		if (a[i]<=a[end2]){
			swap(a, i, newPivot); 	
			newPivot++; // increase the newPivot index only if you are stuffing smaller values to the left of it. 
		}
	} 
	
	swap(a, newPivot, end2); // put orig pivotVal into the newPivot index
	
	return newPivot; 
}


void quicksort(int* a, int end1, int end2){
	if (end2-end1<=0){
		return;
	}

	int newPivot; 
	newPivot = partition(a, end1, end2);
	
	quicksort(a, end1, newPivot-1); 

	quicksort(a, newPivot+1, end2); 
	
	return; 
}
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
