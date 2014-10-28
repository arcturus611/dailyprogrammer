	//r/dailyprogrammer easy challenge 65
	//split number into denominations
	
	#include<stdio.h>
	#include<stdlib.h>
		
	double denominations[] = {100, 50, 10, 5, 1, .25, .10, .05, .01};
	char* denomination_names[] = {"hundred-dollar bill", "fifty-dollar bill", "ten-dollar bill", "five-dollar bill", "one-dollar bill", "quarter", "dime", "nickel", "penny"};
	
	void split_into_denominations(double n){
		int len = sizeof(denominations)/sizeof(denominations[0]);
		int powers[len];
		
		for(int i = 0; i<len; i++){
			double curr_denom = denominations[i];
			powers[i] = 0;
			
			while(n>=curr_denom){
				n-=curr_denom;
				powers[i]++;
			}
		}
		
		for (int i = 0; i<len; i++){
			if (powers[i]==1)
				printf("%d  %s\n", powers[i], denomination_names[i]);
			else if (powers[i]>1){
				if(i<len-1)
					printf("%d  %ss\n", powers[i], denomination_names[i]); 
				else 
					printf("%d pennies\n", powers[i]);
			}
		}
		
		return;
	}
	
	int main(int argc, char* argv[]){
		double N = atof(argv[1]);
		split_into_denominations(N);
		return 0;
	}
