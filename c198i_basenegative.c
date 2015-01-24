	/*
	Negative Base (?!) (r/dailyprogrammer Intermediate c198 jan 20, 2015)
	*/
	
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<math.h>
	#define MAX_LEN 100
	
	/*The idea is: when a number is in base b, it can be written as a polynomial in powers of b. To change it to base -b, this polynomial needs to be rewritten in powers of -b. */
	int convert_to_opp_polarity_base(int n, int b){
		int start_sub, CARRY_VAL;
		int nega_base = 0; 
		if(b<0){
			nega_base = 1;
			b = -b;
			char* str = (char *)malloc(MAX_LEN*sizeof(char));
			sprintf(str, "%d", n);
			if(strlen(str)%2) start_sub = 1;
			else start_sub = 0; 
			//odd length string means negative number going from neg to pos base
			CARRY_VAL = -1;
		}else{
			if(n<0){
				n = -n; 
				start_sub = 0;
			}else{
				start_sub = 1;
			}
			CARRY_VAL = 1;
		}
		
		int output = 0;
		int x, y; 
		int place_value = 0; 
		int carry = 0;
		
		if(start_sub){ //zeroth position digit to be ignored for subtraction
			output = n%10; 
			n/=10; 	
			place_value++;		
		}	
		
		while(n | abs(carry)){			
			x = n%10; 
			x+=carry; 
			
			if(x==0){
				y = 0; // in case of zero, no subtraction.
				carry = 0;
			}else{
				y = (b-x);
				carry = CARRY_VAL;
			}

			output+= y*pow(10, place_value);
			place_value++;
			n/=10;
			
			//next digit
			x = n%10; 
			x+=carry; //because you are add/sub-ing from previous subtraction
			
			if(x==b){
				y = 0; 
				carry = CARRY_VAL;
			}else if (x==-1){
				y = b-1; 
				carry = 1; 
			}else{ 
				y = x;
				carry = 0;
			}
			
			output+=y*pow(10, place_value);
			place_value++;
			n/=10;
		}
		
		return ((!start_sub) & nega_base) ? (-1)*output : output;
	}
	
	int main(int argc, char* argv[]){
		int r, n; 
		r = atoi(argv[1]); 
		n = atoi(argv[2]);
			
		printf("Converting %d from base %d to %d gives %d\n", n, r, -r, convert_to_opp_polarity_base(n, r));
		return 0;
	}
	
