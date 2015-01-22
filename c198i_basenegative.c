	/*
	Negative Base (?!) (r/dailyprogrammer Intermediate c198 jan 20, 2015)
	*/
	
	#include<stdio.h>
	#include<stdlib.h>
	#include<math.h>
	
	int convert_to_decimal(int n, int r){
		int x, a;
		double idx;
		a = 0, idx = 0;
		
		while(n){
			x = n%10;
			a+= x*pow(r, idx);
			idx++;
			n/=10;
		}
		
		return a;
	}
	
	int convert_from_decimal(int n, int b){
		int x, a; 
		double idx; 
		a = 0, idx = 0;
		
		while(n){
			x = n%b;
			a+= x*pow(10, idx); 
			n/=b;
			idx++;
		}
		
		return a;
	}
	
	int convert_to_neg(int n, int b){
		int output = 0;
		int x, y; 
		int place_value = 0; 
		int carry = 0;
		
		if(n<0){
			n = -n; //the sign will screw things up in the algorithm; the programmer knows it's negative;
		}
		else{
			output = n%10; //don't do the subtraction on the zeroth position digit. 
			n/=10; 	
			place_value++;		
		}	
		
		while(n){
			x = n%10; 
			x+=carry; 
			
			if(x==0) y = 0; // in case of zero, no subtraction.
			else y = (b-x);

			output+= y*pow(10, place_value);
			place_value++;
			n/=10;
			
			x = n%10; 
			if(y) x++; //because you are adding from previous subtraction
			
			if(x==b){
				y = 0; 
				carry = 1;
			}else{ 
				y = x;
				carry = 0;
			}
			
			output+=y*pow(10, place_value);
			place_value++;
			n/=10;
		}
		
		return output;
	}
	
	int main(int argc, char* argv[]){
		int r, n; 
		r = atoi(argv[1]); 
		n = atoi(argv[2]);
	
		if(r<0){	
			int a = convert_to_decimal(n, r);
			printf("From base %d to base %d, we get %d to %d\n", r, -r, n, convert_from_decimal(a, -r));	
		}
		else 
			printf("From base %d to base %d, we get %d to %d\n", r, -r, n, convert_to_neg(n, r));	
		return 0;
	}
