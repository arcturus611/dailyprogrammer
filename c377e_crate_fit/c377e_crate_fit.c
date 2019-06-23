	#include<stdio.h>
	#include<string.h>
	#include<math.h>

	int ptoi(char* p){
		int x, len;
		x=0;
		len = strlen(p);
		for (int i = 0; i<len; i++){
			x+=(p[i]-'0')*pow(10, len-1-i);
		}
		return x;
	}
	
	int fit1(int X, int Y, int x, int y){
		return (X/x)*(Y/y);
	}
	 
	int fit2(int X, int Y, int x, int y){
		return (int)fmax(fit1(X, Y, x, y), fit1(X, Y, y, x)); 
	}
	
	int main(int argc, char* argv[]){
		int X, Y, x, y;
		
		if (argc < 5){
			printf("Error! Please enter four arguments!\n"); 
			return 0;	
		}
		
		X = ptoi(argv[1]);
		Y = ptoi(argv[2]);
		x = ptoi(argv[3]);
		y = ptoi(argv[4]);
		
		printf("The inputs are %d, %d, %d, and %d\n", X, Y, x, y);
		printf("The number of crates we can pack using FIT 1 is %d\n", fit1(X, Y, x, y));
		printf("The number of crates we can pack using FIT 2 is %d\n", fit2(X, Y, x, y));
		return 0;
	}
