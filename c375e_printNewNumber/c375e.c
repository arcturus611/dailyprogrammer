	/*
	Dailyprogrammer Challenge 375 [Easy] A number is input in computer then a new no should get printed by adding one to each of its digit. If you encounter a 9, insert a 10 (don't carry over, just shift things around).

For example, 998 becomes 10109.


	*/
	
	#include<stdio.h>
	#include<stdlib.h>
	#include<math.h>
	
	int add_digit_no_carry(int x){
		int y = 0;
		int place_value = 0;
		int q = x; 
		int r;
		
		if (x < 10)
			return x + 1;
		
		for(; q!=0 ; ){
			r = q%10; 
			q = q/10;
			y+= (r+1)*pow(10, place_value);
			place_value++;
			if(r==9) place_value++;
		}
		
		return y;
	}
	
	int main(int argc, char* argv[]){
		int user_input = strtol(argv[1], NULL, 10);
		int program_output = add_digit_no_carry(user_input);
		printf("User input is %d\n", user_input);
		printf("Program output is %d\n", program_output);
		return 0;
	}
