//gcc -std=c99 -Wall -g c30i_luhn_algo.c -o c30i_luhn_algo
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int luhn_algo(char* num, char func){
	int l = strlen(num); 
	int double_start, undouble_start;
	if(func=='c')
		double_start = l%2; 
	else if (func == 'v')
		double_start = !(l%2); 
	undouble_start = !double_start; 

	int sum = 0;

	for(int i = undouble_start; i<l; i+=2){
		sum += (num[i]-'0'); 
	}

	for(int i = double_start; i<l; i+=2){
		switch(num[i]){
			case '5':
				sum+= 1; 
				break;
			case '6': 
				sum+= 3;
				break;
			case '7':		
				sum+= 5;
				break; 
			case '8':
				sum+= 7;
				break;	
			case '9':
				sum+= 9;
				break; 
			default: 
				sum+= 2*(num[i]-'0');
				break;
		}
		
	}

	return sum;
}

void create_luhn_check(char* num){
	int sum = luhn_algo(num, 'v');
	int check_digit = 10 - sum%10; 
	
	int new_len = strlen(num)+2; 
        int i;
	char* num_with_check_digit = malloc(new_len*sizeof(char));
	for ( i = 0; i<new_len-2; i++){
		num_with_check_digit[i] = num[i];
	}
	num_with_check_digit[new_len-2] = check_digit + '0'; 
	num_with_check_digit[new_len-1] = '\0';
	printf("Number with check digit appended: %s\n", num_with_check_digit);
	return;
}

int main(int argc, char* argv[]){
	int invalid_flag = luhn_algo(argv[1], 'c')%10;
	printf("Given number is %s\n", invalid_flag ? "Invalid" : "Valid");
	if(invalid_flag)
		create_luhn_check(argv[1]);
	return 0;
}
