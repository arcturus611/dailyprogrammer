	//r/dailyprogrammer easy challenge 14
	//blockwise list reverse
	#include<stdio.h>
	
	void blk_rev_list(int* arr, int len, int blk){
		int mark_start = 0;
		for(int i = 0; i<len; i+=blk){
			//i = index of start of block
			for(int j = i+blk-1; j>=i; j--){
				if(j<len){
					if(mark_start) 
						printf(", ");
					printf("%d",arr[j]);
				}
				mark_start = 1;
			}
		}
		printf("\n");
		
		return;
	}
	
	int main(int argc, char* argv[]){
		int arr1[] = {12, 24, 32, 44, 55, 66};
		int len1 = 6;
		int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
		int len2 = 11;
		
		blk_rev_list(arr1, len1, 2);
		blk_rev_list(arr2, len2, 3);	
		
		return 0;
	}
