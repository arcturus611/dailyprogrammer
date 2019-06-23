	/* 
	dailyprogrammer Challenge 371[Easy] N Queens Validator
	*/
	#include<stdio.h>
	#include<stdbool.h>
	#include<stdlib.h>
	
	bool check_same_row(int* p){
		bool x = false;
		for (int i = 0; i < 7; i++){
			for (int j = i+1; j < 8; j++){
				if (p[i]==p[j]){
					x = true; 
					return x; 
				}
			}
		}
		return x;
	}
	
	bool check_same_diag(int* p){
		bool x = false; 
		for (int i = 0; i < 7; i++){
			for (int j = i+1; j < 8; j++){
				if (abs(p[i]-p[j])==abs(i-j)){
					x = true;
					return x;
				}
			}	
		}
		return x;
	}
	
	int main(int argc, char* argv[]){
		int p[8];
		scanf("%d %d %d %d %d %d %d %d", p, p+1, p+2, p+3, p+4, p+5, p+6, p+7); 
		bool row_flag; 
		bool diag_flag; 
		row_flag = check_same_row(p);
		diag_flag = check_same_diag(p);	
		if (!row_flag && !diag_flag){
			printf("Valid configuration\n");
		}else printf("Invalid configuration\n");
	}
