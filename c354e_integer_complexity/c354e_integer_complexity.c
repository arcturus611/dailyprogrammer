	//r/DailyProgrammer #354
	// To compile, I used: gcc -Wall -Wstrict-prototypes -std=c99 -pedantic c354e_integer_complexity.c -o c354e_integer_complexity -lm 
	// Without -lm, "collect2: ld returned 1 exit status"
	// Without -std=c99, error about comment style. 

	#include<stdio.h>
	#include<stdlib.h>
	#include<math.h>

	int get_user_input(void){
		int x;
		printf("In this program you will enter an integer, \n and we will factor it, \n check which pair of factors has the smallest sum, \n and return the sum. Enter the integer\n"); 
		scanf("%d", &x); 
		return x; 
	}

	int min_factors_sum(int x){
		double s = sqrt((double) x ); 
		int s_int = (int)ceil(s);
		int a, curr_sum, min_sum;
	
		min_sum = x+1; 
	
		for(int i = 1; i<= s_int; i++){
			if(!(x%i)){
			// if i divides x
				a = x/i;
				curr_sum = a + i;
				if(curr_sum< min_sum)
					min_sum = curr_sum; 
			}
		}
	
		return min_sum; 
	}

	int main(int argc, char** argv){
		int x = get_user_input();
		printf("User's input was %d\n", x); 

		int y = min_factors_sum(x); 
		printf("The minimum sum is of factors is %d\n", y); 
		return 0;
	}
