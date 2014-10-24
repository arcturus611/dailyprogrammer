#include <stdio.h>
#include <stdlib.h> // for srand, rand
#include <time.h>

int LENGTH = 25; 

void quicksort(int* a, int end1, int end2){
	if (end2-end1<=0){
		return;
	}
	
	int i; 
	int pivot = (end1+end2)/2; 
	int pivotVal = a[pivot];

	int temp_len = end2-end1+1;
	int temp[temp_len];

	int idx1=end1, idx2=end2; 
	int temp_idx1 = 0, temp_idx2 = temp_len-1; 

	while(idx1<pivot || idx2>pivot){
		if (idx1<pivot){
			if(a[idx1] > pivotVal){
				temp[temp_idx2--] = a[idx1++]; 
			}else
			{
				temp[temp_idx1++] = a[idx1++]; 
			}	
		}
		if (idx2>pivot){
			if(a[idx2]<pivotVal){
				temp[temp_idx1++] = a[idx2--]; 
			}else 
			{
				temp[temp_idx2--] = a[idx2--]; 
			}
		}
	}


	temp[temp_idx1] = a[pivot];

	idx1= end1;
  
	for (i = 0; i<end2-end1+1; i++){
		a[idx1++] = temp[i]; 
	} 
	
	
	int CurrIdx_of_PrevPV = temp_idx1 + end1; 	
	
	quicksort(a, end1, CurrIdx_of_PrevPV-1); //The right edge has to be 1 less than the current index of the previous pivotVal. I was wrongly assuming that pivot = Current index of the previous pivotVal, when in reality, pivot = PREVIOUS index of the previous pivotVal. 
		
	quicksort(a, CurrIdx_of_PrevPV+1, end2); 
	
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
