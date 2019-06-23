	/* 
	Dailyprogrammer c374[Easy] additive persistence: how many loops of adding all digits of a number
	until only one digit remains
	*/
	#include<stdio.h>
	#include<stdbool.h>
	
	bool is_num_digits_one(int x){
		return x<10? true: false;  
	}
	
	int sum_digits(int x){
		int y = 0;
		while(x!=0){
			y+= x%10;
			x/=10;
		}
		return y;
	}
	
	int main (int argc, char* argv[]){
		int user_input, loop_count = 0;
		scanf("%d", &user_input);
		while(!is_num_digits_one(user_input)){
			loop_count++;
			user_input = sum_digits(user_input);
		}
		printf("The additive persistence is %d\n", loop_count);
	}
