	//r/dailyprogrammer challenge 9 easy 
	//sort input digits 
	
	#include<stdio.h>
	#include<stdlib.h>
	
	int cmpfnc(const void* a, const void* b){
		return (*(const int* )a-*(const int* )b);
	}
	
	int main(int argc, char* argv[]){
		int N; 
		scanf("%d", &N);
		
		int arr[N];
		for (int i = 0; i<N; i++)
			scanf("%d", &arr[i]);
			
		qsort(arr, N, sizeof(int), cmpfnc);
		
		printf("Sorted array is...");
		for (int i = 0; i<N-1; i++)
			printf("%d, ", arr[i]);
		printf("%d\n", arr[N-1]);
		
		return 0;
	}
