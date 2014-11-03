	//r/dailyprogrammer challenge 82 (easy)
	//substring list
	
	#include<stdio.h>
	#include<stdlib.h>
	
	void print_substring_list(int n){
		for(int i = 0; i<n; i++){
			char curr = 'a' + i;
			for(int j = 0; j<n-i; j++){
				for (int k = 0; k<=j; k++){
					printf("%c", curr+k);
				}
				printf("\n");
			}
		}
		return;
	}
	
	int main(int argc, char* argv[]){
		int n = atoi(argv[1]);
		print_substring_list(n);
		return 0;
	}
